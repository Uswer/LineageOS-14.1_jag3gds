#include <linux/batterydata-lib.h>

static struct single_row_lut fcc_temp = {
	.x		= {-20, 0, 25, 40, 60},
	.y		= {3099, 3141, 3135, 3121, 3094},
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
				{879, 224, 100, 90, 91},
				{922, 228, 102, 91, 93},
				{919, 228, 102, 91, 93},
				{968, 236, 105, 94, 94},
				{1036, 241, 109, 97, 96},
				{1029, 255, 115, 99, 97},
				{1047, 245, 121, 104, 101},
				{1054, 234, 130, 110, 104},
				{1072, 230, 117, 107, 102},
				{1113, 228, 106, 96, 97},
				{1171, 230, 105, 95, 95},
				{1241, 233, 107, 98, 98},
				{1326, 236, 110, 100, 101},
				{1420, 245, 114, 100, 99},
				{1603, 258, 110, 96, 97},
				{1956, 271, 107, 95, 97},
				{2690, 309, 108, 97, 97},
				{3976, 367, 119, 101, 100},
				{5841, 421, 135, 110, 106},
				{7891, 458, 151, 121, 115},
				{9000, 480, 157, 124, 119},
				{10340, 485, 160, 127, 123},
				{11748, 474, 162, 132, 126},
				{13534, 502, 171, 138, 131},
				{15976, 543, 186, 146, 136},
				{19453, 601, 207, 157, 143},
				{23902, 680, 231, 169, 150},
				{28832, 888, 259, 184, 160},
				{34162, 1426, 308, 209, 178},
				{36278, 2624, 467, 284, 237}
	}
};




static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 5,
	.temp		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4335, 4333, 4328, 4323, 4314},
				{4233, 4258, 4260, 4257, 4251},
				{4166, 4199, 4203, 4201, 4196},
				{4104, 4145, 4149, 4148, 4144},
				{4056, 4093, 4098, 4098, 4094},
				{3975, 4040, 4051, 4050, 4046},
				{3923, 3984, 4005, 4006, 4003},
				{3876, 3936, 3963, 3966, 3963},
				{3839, 3896, 3912, 3917, 3914},
				{3816, 3861, 3871, 3873, 3872},
				{3798, 3832, 3842, 3843, 3843},
				{3781, 3808, 3818, 3820, 3820},
				{3763, 3786, 3798, 3800, 3799},
				{3742, 3769, 3781, 3778, 3771},
				{3717, 3751, 3759, 3752, 3741},
				{3681, 3726, 3727, 3719, 3706},
				{3623, 3701, 3695, 3688, 3676},
				{3548, 3683, 3680, 3673, 3659},
				{3471, 3650, 3658, 3654, 3642},
				{3418, 3610, 3627, 3623, 3605},
				{3391, 3584, 3604, 3600, 3585},
				{3360, 3556, 3579, 3575, 3558},
				{3330, 3525, 3548, 3544, 3530},
				{3307, 3489, 3513, 3509, 3496},
				{3283, 3450, 3476, 3473, 3462},
				{3258, 3411, 3439, 3437, 3427},
				{3236, 3368, 3399, 3398, 3388},
				{3211, 3321, 3351, 3348, 3338},
				{3178, 3262, 3284, 3280, 3269},
				{3112, 3179, 3183, 3177, 3166},
				{3000, 3000, 3000, 3000, 3000}
	}
};


struct bms_battery_data LGE_BL_47TH_3200mAh_LG_Chem_data = {
	.fcc				= 3200,
	.fcc_temp_lut			= &fcc_temp,
	.fcc_sf_lut				= &fcc_sf,
	.pc_temp_ocv_lut		= &pc_temp_ocv,
	.rbatt_sf_lut			= &rbatt_sf,
	.default_rbatt_mohm	= 146
};
