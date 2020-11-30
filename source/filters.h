/*
 * filers.h
 *
 *  Created on: Nov 30, 2020
 *      Author: Momo
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "arm_math.h"


void FILR_init_LP();
void FILR_init_HP();
void FILR_init_BP();


void init_Buffer(uint32_t *Buffer);
void do_filter(uint8_t Type);


#endif /* FILTERS_H_ */
