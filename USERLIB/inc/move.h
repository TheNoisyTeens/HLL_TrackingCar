#ifndef __MOVE_H__
#define __MOVE_H__

#include "stm32f4xx.h" 


void forward(int16_t current);
void back(int16_t current);
void left_little(int16_t current);
void left_big(int16_t current);
void right_little(int16_t current);
void right_big(int16_t current);
void left_turn(int16_t current);
void right_turn(int16_t current);



#endif

