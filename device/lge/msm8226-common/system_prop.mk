# IO Scheduler
PRODUCT_PROPERTY_OVERRIDES += \
    sys.io.scheduler=bfq

# System properties
PRODUCT_PROPERTY_OVERRIDES += \
    persist.hwc.mdpcomp.enable=true \
    persist.timed.enable=true \
    ro.opengles.version=196608 \
    ro.qualcomm.perf.cores_online=2 \
    ro.vendor.extension_library=libqti-perfd-client.so \
    dalvik.vm.dex2oat-flags=--no-watch-dog \
    debug.qualcomm.sns.hal=0 \
    debug.qualcomm.sns.daemon=e \
    debug.qualcomm.sns.libsensor1=e

# Wifi properties
PRODUCT_PROPERTY_OVERRIDES += \
    ro.data.large_tcp_window_size=true \
    wifi.interface=wlan0 \
    wifi.supplicant_scan_interval=200

# Telephony properties
PRODUCT_PROPERTY_OVERRIDES += \
    persist.radio.proc_nw_scan=0 \
    ro.use_data_netmgrd=true \
    persist.data.netmgrd.qos.enable=true \
    ro.telephony.call_ring.multiple=0 \
    rild.libpath=/vendor/lib/libril-qc-qmi-1.so \
    rild.libargs=-d[SPACE]/dev/smd0 \
    persist.data.qmi.adb_logmask=0

# GPS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.gps.qc_nlp_in_use=0 \
    ro.gps.agps_provider=1

# Audio properties
PRODUCT_PROPERTY_OVERRIDES += \
    mm.enable.smoothstreaming=true \
    ro.qc.sdk.audio.fluencetype=endfire \
    persist.audio.fluence.voicecall=true \
    audio.offload.buffer.size.kb=32 \
    av.offload.enable=true \
    av.streaming.offload.enable=true \
    use.voice.path.for.pcm.voip=true \
    audio.offload.multiple.enabled=false \
    audio.offload.gapless.enabled=true \
    tunnel.audio.encode=true \
    media.aac_51_output_enabled=true \
    audio.offload.pcm.16bit.enable=true \
    audio.offload.pcm.24bit.enable=true \
    use.voice.path.for.pcm.voip=true \
    persist.audio.calfile0=/etc/acdbdata/Bluetooth_cal.acdb \
    persist.audio.calfile1=/etc/acdbdata/General_cal.acdb \
    persist.audio.calfile2=/etc/acdbdata/Global_cal.acdb \
    persist.audio.calfile3=/etc/acdbdata/Handset_cal.acdb \
    persist.audio.calfile4=/etc/acdbdata/Hdmi_cal.acdb \
    persist.audio.calfile5=/etc/acdbdata/Headset_cal.acdb \
    persist.audio.calfile6=/etc/acdbdata/Speaker_cal.acdb

# Camera
PRODUCT_PROPERTY_OVERRIDES += \
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true

# My properties
PRODUCT_PROPERTY_OVERRIDES += \
    cm.updater.uri=http://mr-ap.ru/lineageos14.1/jag3gds/api/updates.json \
    pm.sleep_mode=1 \
    ro.ril.disable.power.collapse=0 \
    ro.ril.enable.amr.wideband=1 \
    persist.cust.tel.eons=1 \
    ro.ril.gprsclass=10 \
    ro.ril.hsdpa.category=8 \
    ro.ril.hsupa.category=6 \
    ro.ril.hsxpa=1 \
    net.tcp.buffersize.default=4096,87380,256960,4096,16384,256960 \
    net.tcp.buffersize.wifi=4096,87380,256960,4096,16384,256960 \
    net.tcp.buffersize.umts=4096,87380,256960,4096,16384,256960 \
    net.tcp.buffersize.gprs=4096,87380,256960,4096,16384,256960 \
    net.tcp.buffersize.edge=4096,87380,256960,4096,16384,256960 \
    net.rmnet0.dns1=8.8.8.8 \
    net.rmnet0.dns2=8.8.4.4 \
    net.dns1=8.8.8.8 \
    net.dns2=8.8.4.4 \
    boot.fps=20 \
    ro.config.hw_quickpoweron=true \
    logcat.live=disable \
    ro.telephony.call_ring.delay=0 \
    ring.delay=0

