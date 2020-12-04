#ifndef FILTERS_H_
#define FILTERS_H_

#include "arm_math.h"

#define NUM_TAPS 50
#define BLOCK_SIZE 1024
#define TEST_LENGTH_SAMPLES 4*1024
#define NUM_BLOCKS TEST_LENGTH_SAMPLES/BLOCK_SIZE

typedef enum {LP, HP, BP, DISABLE}filter;

void FILR_init_LP();
void FILR_init_HP();
void FILR_init_BP();
void init_Buffer(uint32_t *Buffer);
void do_filter(filter type);


#endif /* FILTERS_H_ */
