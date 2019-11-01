#ifndef __LOW_PASS_FILTER_H__
#define __LOW_PASS_FILTER_H__
#include "arm_math.h"                   // ARM::CMSIS:DSP


q15_t low_pass_filter(q15_t *input);
void low_pass_filter_init(void);

#endif