#include <linux/batterydata-lib.h>

static struct single_row_lut fcc_temp = {
	.x		= {-20, 0, 25, 40, 60},
	.y		= {2034, 2070, 2070, 2068, 2061},
	.cols	= 5
};

static struct single_row_lut fcc_sf = {
	.x		= {0},
	.y		= {100},
	.cols	= 1
};

static struct sf_lut rbatt_sf = {
	.rows		= 30,
	.cols		= 5,
	.row_entries		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf		= {
				{1115, 286, 100, 84, 82},
				{1110, 287, 100, 84, 82},
				{1182, 293, 102, 86, 84},
				{1193, 299, 106, 89, 86},
				{1200, 302, 112, 92, 88},
				{1156, 312, 118, 96, 90},
				{1158, 301, 126, 101, 94},
				{1158, 295, 128, 107, 98},
				{1185, 298, 113, 99, 93},
				{1224, 299, 106, 90, 88},
				{1280, 303, 107, 90, 87},
				{1367, 305, 111, 93, 90},
				{1527, 309, 116, 96, 92},
				{1798, 324, 117, 95, 93},
				{2191, 351, 116, 94, 91},
				{2657, 397, 117, 94, 90},
				{3388, 461, 124, 97, 90},
				{4429, 516, 133, 104, 98},
				{5654, 543, 141, 108, 101},
				{6020, 535, 147, 112, 104},
				{6527, 550, 152, 116, 108},
				{7710, 577, 161, 120, 110},
				{9729, 612, 170, 126, 113},
				{12980, 652, 181, 131, 116},
				{17100, 700, 192, 135, 117},
				{23375, 761, 201, 138, 120},
				{29553, 864, 217, 147, 126},
				{36235, 1086, 244, 160, 135},
				{42118, 1472, 296, 183, 150},
				{46972, 2525, 378, 229, 189},
	}
};

static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 5,
	.temp		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4329, 4327, 4321, 4316, 4308},
				{4224, 4252, 4254, 4251, 4246},
				{4154, 4193, 4197, 4195, 4191},
				{4094, 4137, 4143, 4142, 4137},
				{4043, 4083, 4091, 4090, 4086},
				{3958, 4029, 4044, 4042, 4038},
				{3912, 3974, 3997, 3998, 3994},
				{3867, 3929, 3953, 3955, 3952},
				{3833, 3890, 3902, 3906, 3904},
				{3808, 3855, 3863, 3865, 3864},
				{3787, 3824, 3835, 3836, 3835},
				{3766, 3796, 3813, 3813, 3812},
				{3745, 3772, 3793, 3792, 3790},
				{3724, 3754, 3774, 3771, 3765},
				{3700, 3738, 3751, 3746, 3738},
				{3670, 3723, 3723, 3717, 3705},
				{3630, 3704, 3704, 3697, 3685},
				{3584, 3681, 3675, 3668, 3656},
				{3530, 3648, 3642, 3636, 3622},
				{3488, 3618, 3618, 3611, 3599},
				{3459, 3600, 3603, 3597, 3585},
				{3426, 3583, 3588, 3583, 3571},
				{3392, 3564, 3573, 3568, 3557},
				{3361, 3543, 3557, 3553, 3541},
				{3324, 3518, 3536, 3531, 3517},
				{3290, 3486, 3504, 3498, 3483},
				{3249, 3448, 3460, 3453, 3438},
				{3219, 3398, 3404, 3397, 3381},
				{3195, 3330, 3329, 3322, 3304},
				{3132, 3226, 3220, 3213, 3193},
				{3000, 3000, 3000, 3000, 3000}
	}
};

struct bms_battery_data LGE_LGC_2040mAH_data = {
	.fcc				= 2040,
	.fcc_temp_lut			= &fcc_temp,
	.fcc_sf_lut				= &fcc_sf,
	.pc_temp_ocv_lut		= &pc_temp_ocv,
	.rbatt_sf_lut			= &rbatt_sf,
	.default_rbatt_mohm	= 175
};
