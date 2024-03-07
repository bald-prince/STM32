#include "../GuiLite.h"

static const unsigned short raw_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 23080, 63878, 63488, 63488, 63488, 63488, 63813, 31370, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 33548, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 39659, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 6469, 63683, 63488, 63488, 63488, 64333, 64398, 63520, 63488, 63488, 63585, 8484, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 35108, 63488, 63488, 63618, 65535, 65535, 65535, 65535, 63813, 63488, 63488, 47461, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 61927, 63488, 63488, 65015, 65535, 65535, 65535, 65535, 65373, 63488, 63488, 63845, 97, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59684, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63715, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65535, 65535, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65438, 65535, 65015, 64853, 65535, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65503, 65113, 63488, 63488, 64755, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64788, 63488, 63488, 64463, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 59717, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63748, 65, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 10597, 63650, 63488, 63488, 65535, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63585, 18854, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 39659, 63488, 63488, 63488, 63488, 65503, 64820, 63488, 63488, 64495, 65535, 63488, 63488, 63488, 63488, 47851, 32, 0, 0, 0, 
    0, 0, 0, 37449, 63488, 63488, 63488, 63488, 64300, 65535, 64885, 63488, 63488, 64560, 65535, 64463, 63488, 63488, 63488, 63488, 49899, 32, 0, 0, 
    0, 0, 31500, 63520, 63488, 63488, 63780, 65535, 65535, 65048, 64040, 63488, 63488, 63878, 64918, 65535, 65535, 64008, 63488, 63488, 63488, 39627, 0, 0, 
    0, 2275, 63715, 63488, 63488, 63878, 65535, 65373, 63618, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65210, 65535, 64170, 63488, 63488, 63585, 8582, 0, 
    0, 45771, 63488, 63488, 63488, 65535, 65210, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 64983, 65535, 63715, 63488, 63488, 56011, 0, 
    2340, 63845, 63488, 63488, 65048, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65503, 65373, 63488, 63488, 63553, 4453, 
    12548, 63488, 63488, 63520, 65535, 64333, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63975, 65535, 63780, 63488, 63488, 24868, 
    33028, 63488, 63488, 64300, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65535, 64658, 63488, 63488, 47591, 
    43333, 63488, 63488, 64820, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65178, 65178, 63488, 63488, 53573, 
    41155, 63488, 63488, 65080, 65340, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65048, 65438, 63488, 63488, 51427, 
    43333, 63488, 63488, 64820, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65178, 65178, 63488, 63488, 53605, 
    32995, 63488, 63488, 64300, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65535, 64658, 63488, 63488, 47559, 
    12548, 63488, 63488, 63520, 65535, 64333, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63975, 65535, 63780, 63488, 63488, 22820, 
    2340, 63845, 63488, 63488, 65048, 65535, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65470, 65340, 63488, 63488, 63553, 8647, 
    0, 43658, 63488, 63488, 63488, 65535, 65243, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 64983, 65535, 63715, 63488, 63488, 55978, 0, 
    0, 227, 63715, 63488, 63488, 63845, 65535, 65438, 63618, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 65210, 65535, 64138, 63488, 63488, 63618, 8549, 0, 
    0, 0, 27209, 63520, 63488, 63488, 63715, 65535, 65535, 65113, 64170, 63845, 63813, 64105, 64983, 65535, 65535, 63943, 63488, 63488, 63488, 33288, 0, 0, 
    0, 0, 0, 39627, 63488, 63488, 63488, 63488, 64430, 65405, 65535, 65535, 65535, 65535, 65503, 64560, 63488, 63488, 63488, 63488, 49867, 0, 0, 0, 
    0, 0, 0, 0, 37579, 63553, 63488, 63488, 63488, 63488, 63488, 63650, 63683, 63488, 63488, 63488, 63488, 63488, 63488, 45771, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 16904, 59652, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 63488, 61635, 25161, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 23048, 57994, 63748, 63618, 63553, 63553, 63618, 63715, 60042, 29354, 32, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 260, 10597, 8354, 8354, 10565, 2373, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
extern const BITMAP_INFO temperature_bmp;
const BITMAP_INFO temperature_bmp ={
    24,
    47,
    16,
    (unsigned short*)raw_data
};
