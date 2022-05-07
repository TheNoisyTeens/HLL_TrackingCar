#ifndef __POWER_H__
#define __POWER_H__

#include "stm32f4xx.h"

#define POWER1_CTRL_ON GPIO_SetBits(GPIOH, GPIO_Pin_2)
#define POWER2_CTRL_ON GPIO_SetBits(GPIOH, GPIO_Pin_3)
#define POWER3_CTRL_ON GPIO_SetBits(GPIOH, GPIO_Pin_4)
#define POWER4_CTRL_ON GPIO_SetBits(GPIOH, GPIO_Pin_5)

#define POWER1_CTRL_OFF GPIO_ResetBits(GPIOH, GPIO_Pin_2)
#define POWER2_CTRL_OFF GPIO_ResetBits(GPIOH, GPIO_Pin_3)
#define POWER3_CTRL_OFF GPIO_ResetBits(GPIOH, GPIO_Pin_4)
#define POWER4_CTRL_OFF GPIO_ResetBits(GPIOH, GPIO_Pin_5)


void Power_Ctrl_Init(void);
void Power_Ctrl_ON(void);

#endif  /*__POWER_H__*/

