/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_TAG "lights"

#include <cutils/log.h>
#include <cutils/properties.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/types.h>

#include <hardware/lights.h>

/******************************************************************************/

//#define HAVE_KEYBOARD

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

static struct light_state_t g_battery;
static struct light_state_t g_notification;
static struct light_state_t g_attention;
static int g_charge_led_active;

char const*const LCD_FILE = "/sys/class/leds/lcd-backlight/brightness";

/* RGB file descriptors */
char const*const RED_LED_FILE = "/sys/class/leds/red/brightness";
char const*const RED_BLINK_FILE = "/sys/class/leds/red/blink";
char const *const LED_RED_RAMP_STEP_FILE = "/sys/class/leds/red/ramp_step_ms";
char const *const LED_RED_DUTY_FILE = "/sys/class/leds/red/duty_pcts";

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) ((a)<(b)?(b):(a))
#endif

// Number of steps to use in the duty array
#define LED_DT_DUTY_STEPS       50
// Brightness ramp up/down time for blinking
#define LED_DT_RAMP_MS          500

void init_globals(void)
{
    pthread_mutex_init(&g_lock, NULL);
    memset(&g_battery, 0, sizeof(g_battery));
    memset(&g_notification, 0, sizeof(g_notification));

    g_charge_led_active = 0;
}

static int
write_string(const char *path, const char *buffer)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        int bytes = strlen(buffer);
        int amt = write(fd, buffer, bytes);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            ALOGE("write_string failed to open %s (%s)\n", path, strerror(errno));
            already_warned = 1;
        }
        return -errno;
    }
}

static int
write_int(const char *path, int value)
{
    char buffer[20];
    sprintf(buffer, "%d\n", value);
    return write_string(path, buffer);
}


static int
is_lit(struct light_state_t const* state)
{
    return state->color & 0x00ffffff;
}

static int
rgb_to_brightness(const struct light_state_t *state)
{
    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff))
            + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}


static int
set_light_backlight(struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    int brightness = rgb_to_brightness(state);

    pthread_mutex_lock(&g_lock);
    err = write_int(LCD_FILE, brightness);
    pthread_mutex_unlock(&g_lock);

    return err;
}

static int
set_light_locked(struct light_device_t *dev, struct light_state_t *state)
{
    int err = 0;
    int onMS, offMS;
    int red;

    if (state == NULL) {
        write_int(RED_BLINK_FILE, 0);
        write_int(RED_LED_FILE, 0);
        return 0;
    }

    switch (state->flashMode) {
        case LIGHT_FLASH_TIMED:
            onMS = state->flashOnMS;
            offMS = state->flashOffMS;
            break;
        case LIGHT_FLASH_NONE:
        default:
            onMS = 0;
            offMS = 0;
            break;
    }

    red = (state->color >> 16) & 0xFF;

    if (onMS > 0 && offMS > 0) {
        char dutystr[(3+1)*LED_DT_DUTY_STEPS+1];
        char* p = dutystr;
        int stepMS;
        int n;

        onMS = max(onMS, LED_DT_RAMP_MS);
        offMS = max(offMS, LED_DT_RAMP_MS);
        stepMS = (onMS+offMS)/LED_DT_DUTY_STEPS;

        p += sprintf(p, "0");
        for (n = 1; n < (onMS/stepMS); ++n) {
            p += sprintf(p, ",%d", min((100*n*stepMS)/LED_DT_RAMP_MS, 100));
        }
        for (n = 0; n < LED_DT_DUTY_STEPS-(onMS/stepMS); ++n) {
            p += sprintf(p, ",%d", 100 - min((100*n*stepMS)/LED_DT_RAMP_MS, 100));
        }
        p += sprintf(p, "\n");

        err = write_int(LED_RED_RAMP_STEP_FILE, stepMS);
        err = write_string(LED_RED_DUTY_FILE, dutystr);
        err = write_int(RED_BLINK_FILE, 1);

    } else {
        write_int(RED_LED_FILE, red);
    }
    return err;
}


static int
handle_light_locked(struct light_device_t *dev)
{
    int retval = 0;
    set_light_locked(dev, NULL);

    if (is_lit(&g_attention)) {
	retval = set_light_locked(dev, &g_attention);
    } else if (is_lit(&g_notification)) {
	retval = set_light_locked(dev, &g_notification);
    } else {
	retval = set_light_locked(dev, &g_battery);
    }

    return retval;
}

static int
set_light_battery(struct light_device_t* dev,
        struct light_state_t const* state)
{
    pthread_mutex_lock(&g_lock);

    g_battery = *state;
    handle_light_locked(dev);
    pthread_mutex_unlock(&g_lock);

    return 0;
}

static int
set_light_notification(struct light_device_t* dev,
        struct light_state_t const* state)
{
    pthread_mutex_lock(&g_lock);
    g_notification = *state;
    handle_light_locked(dev);
    pthread_mutex_unlock(&g_lock);

    return 0;
}

static int
set_light_attention(struct light_device_t* dev,
        struct light_state_t const* state)
{
    pthread_mutex_lock(&g_lock);

    g_attention = *state;
    if (state->flashMode == LIGHT_FLASH_HARDWARE) {
        if (g_attention.flashOnMS > 0 && g_attention.flashOffMS == 0) {
            g_attention.flashMode = LIGHT_FLASH_NONE;
        }
    } else if (state->flashMode == LIGHT_FLASH_NONE) {
        g_attention.color = 0;
    }
    set_light_locked(dev, state);

    pthread_mutex_unlock(&g_lock);

    return 0;
}

static int
close_lights(struct light_device_t *dev)
{
    if (dev) {
        free(dev);
    }
    return 0;
}


/******************************************************************************/
static int open_lights(const struct hw_module_t* module, char const* name,
        struct hw_device_t** device)
{
    int (*set_light)(struct light_device_t* dev,
            struct light_state_t const* state);

    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name)) {
	set_light = set_light_backlight;
    }
    else if (0 == strcmp(LIGHT_ID_BATTERY, name)) {
	set_light = set_light_battery;
    }
    else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name)) {
	set_light = set_light_notification;
    }
    else if (0 == strcmp(LIGHT_ID_ATTENTION, name)) {
	set_light = set_light_attention;
    }
    else {
        ALOGW("%s: unknown led id %s", __FUNCTION__, name);
        return -EINVAL;
    }

    pthread_once(&g_init, init_globals);

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;
    return 0;
}


static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "LG G3s lights Module",
    .author = "vm03, Quarx, Google",
    .methods = &lights_module_methods,
};
