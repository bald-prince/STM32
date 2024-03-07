#include "../GuiLite.h"

static const unsigned short raw_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18984, 13599, 15743, 21064, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8385, 17726, 5180, 5180, 19839, 21063, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8353, 32383, 3132, 7260, 7260, 3100, 28159, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25849, 3133, 7260, 7260, 7260, 7260, 3133, 25849, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2048, 25619, 5246, 7260, 7260, 7260, 7260, 7260, 7260, 3166, 31957, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29680, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7359, 23308, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8353, 13631, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 15711, 6273, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26111, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 26046, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 27830, 3133, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5214, 23605, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 31728, 5279, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7327, 31760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 23144, 19839, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 19839, 16772, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 27929, 3133, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3133, 29977, 2048, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 27533, 5246, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5278, 25388, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 19773, 5212, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 19741, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 34070, 3165, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3133, 42490, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 8386, 13534, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 9340, 18950, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 29878, 3165, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5213, 21459, 0, 0, 0, 0, 0, 
    0, 0, 0, 6273, 13598, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 17791, 10531, 0, 0, 0, 0, 
    0, 0, 0, 25620, 5213, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3133, 29910, 0, 0, 0, 0, 
    0, 0, 25224, 15646, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 15613, 18885, 0, 0, 0, 
    0, 0, 19148, 7326, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5278, 19180, 0, 0, 0, 
    0, 0, 28060, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 5148, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5181, 25915, 0, 0, 0, 
    0, 10499, 11487, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3068, 5148, 3068, 5180, 7260, 7260, 7260, 7260, 7260, 30141, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 13599, 16870, 0, 0, 
    0, 14988, 5278, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 988, 42622, 65535, 65535, 19740, 5148, 7260, 7260, 1020, 44734, 59295, 3068, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5246, 14923, 0, 0, 
    0, 13204, 7293, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 19708, 65535, 57215, 65535, 65535, 5148, 7260, 7228, 7228, 65535, 11388, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5213, 21623, 0, 0, 
    10466, 17693, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3100, 38462, 65535, 923, 9308, 65535, 15580, 5180, 988, 48862, 50974, 1020, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 17693, 8386, 0, 
    10499, 11519, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3100, 38494, 63455, 923, 7260, 65535, 15580, 5180, 7228, 65535, 9340, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 11486, 8386, 0, 
    10597, 7326, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 21821, 65535, 50942, 61375, 65535, 5148, 988, 50942, 50942, 1020, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7358, 10597, 0, 
    10696, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 1020, 46814, 65535, 65535, 23901, 3068, 9340, 65535, 7260, 7228, 7228, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7359, 10696, 0, 
    6503, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 1020, 7260, 5180, 3100, 1020, 53022, 48862, 1020, 1020, 13468, 15548, 1020, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7359, 6504, 0, 
    4455, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 7260, 5180, 11420, 65535, 7228, 1020, 38462, 65535, 65535, 55102, 3068, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 9407, 4456, 0, 
    8584, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 988, 55135, 46782, 988, 5180, 65535, 53022, 42622, 65535, 23901, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7359, 8584, 0, 
    16936, 7359, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 15548, 65535, 5180, 5180, 19708, 65535, 3068, 923, 63455, 40542, 3100, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 9439, 14856, 0, 
    0, 11487, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 988, 57215, 42622, 1020, 5180, 17596, 65535, 11388, 955, 65535, 36382, 3100, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 11486, 8419, 0, 
    8353, 15548, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 15580, 65535, 5180, 7228, 7260, 1020, 65535, 65535, 65535, 65535, 13500, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 15547, 6273, 0, 
    0, 25750, 5213, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3068, 65535, 40574, 1020, 7260, 7260, 5180, 13500, 61343, 65503, 25981, 3100, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 3133, 27830, 0, 0, 
    0, 10564, 11551, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 21788, 5180, 7260, 7260, 7260, 7260, 5180, 1020, 1020, 5148, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 13663, 8386, 0, 0, 
    0, 0, 13204, 5213, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5213, 13204, 0, 0, 0, 
    0, 0, 14757, 13599, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 13663, 14725, 0, 0, 0, 
    0, 0, 0, 25553, 5278, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 5279, 17068, 0, 0, 0, 0, 
    0, 0, 0, 6273, 40475, 1053, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 1053, 42556, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 12579, 31958, 5246, 5180, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 5246, 46749, 14725, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 31760, 17823, 3133, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 5213, 15647, 29647, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 27305, 32089, 15743, 3133, 7261, 7228, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7260, 7228, 7261, 3166, 13631, 23572, 8320, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 10466, 29779, 11256, 13631, 7391, 3133, 5213, 7294, 7326, 5213, 3133, 7391, 15711, 19642, 21359, 16805, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8386, 8452, 34037, 27797, 6701, 6734, 21426, 31891, 6339, 16805, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
extern const BITMAP_INFO humidity_bmp;
const BITMAP_INFO humidity_bmp ={
    35,
    47,
    16,
    (unsigned short*)raw_data
};
