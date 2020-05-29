#include <linux/batterydata-lib.h>

static struct single_row_lut fcc_temp = {
	.x		= {-20, 0, 25, 40, 60},
	.y		= {1811, 1799, 1790, 1779, 1768},
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
				{702, 188, 100, 89, 83},
				{717, 195, 105, 94, 87},
				{715, 195, 104, 93, 87},
				{687, 198, 110, 97, 91},
				{660, 206, 115, 101, 95},
				{663, 203, 120, 106, 99},
				{679, 204, 125, 111, 102},
				{704, 208, 127, 114, 105},
				{736, 203, 116, 106, 100},
				{814, 200, 104, 95, 90},
				{936, 203, 104, 93, 87},
				{1079, 211, 107, 96, 91},
				{1245, 223, 112, 100, 96},
				{1450, 240, 117, 103, 99},
				{1706, 261, 122, 107, 100},
				{2044, 286, 126, 108, 100},
				{2531, 320, 129, 109, 101},
				{3187, 367, 127, 106, 99},
				{4134, 415, 135, 112, 102},
				{4919, 453, 145, 120, 111},
				{6407, 476, 154, 126, 115},
				{7895, 499, 164, 133, 120},
				{9383, 521, 174, 140, 126},
				{12557, 537, 180, 146, 131},
				{15982, 540, 184, 147, 133},
				{17941, 502, 173, 147, 136},
				{23037, 484, 165, 133, 131},
				{29593, 534, 175, 138, 127},
				{36223, 646, 193, 151, 140},
				{43242, 1833, 256, 179, 183}
	}
};


static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 5,
	.temp		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4313, 4313, 4311, 4309, 4305},
				{4226, 4237, 4242, 4243, 4242},
				{4158, 4178, 4185, 4187, 4187},
				{4103, 4123, 4133, 4135, 4134},
				{4036, 4074, 4083, 4085, 4085},
				{3981, 4017, 4033, 4037, 4038},
				{3936, 3971, 3991, 3994, 3994},
				{3901, 3932, 3952, 3955, 3955},
				{3865, 3891, 3906, 3911, 3912},
				{3835, 3853, 3863, 3868, 3868},
				{3813, 3824, 3833, 3836, 3837},
				{3794, 3801, 3810, 3813, 3814},
				{3778, 3784, 3792, 3794, 3795},
				{3763, 3772, 3778, 3779, 3780},
				{3749, 3762, 3768, 3767, 3764},
				{3734, 3747, 3757, 3754, 3747},
				{3707, 3727, 3736, 3733, 3725},
				{3674, 3705, 3704, 3700, 3695},
				{3637, 3691, 3689, 3685, 3678},
				{3614, 3683, 3682, 3680, 3674},
				{3595, 3679, 3679, 3677, 3673},
				{3576, 3674, 3677, 3675, 3669},
				{3557, 3669, 3675, 3672, 3663},
				{3534, 3659, 3665, 3668, 3658},
				{3505, 3644, 3652, 3646, 3639},
				{3464, 3614, 3624, 3624, 3605},
				{3413, 3566, 3577, 3578, 3561},
				{3358, 3501, 3514, 3515, 3497},
				{3295, 3413, 3429, 3432, 3412},
				{3203, 3278, 3297, 3308, 3281},
				{3000, 3000, 3000, 3000, 3000}
	}
};


struct bms_battery_data LGE_L70_CHEM_1900mAh_data = {
	.fcc				= 1900,
	.fcc_temp_lut			= &fcc_temp,
	.fcc_sf_lut				= &fcc_sf,
	.pc_temp_ocv_lut		= &pc_temp_ocv,
	.rbatt_sf_lut			= &rbatt_sf,
	.default_rbatt_mohm	= 206
};
