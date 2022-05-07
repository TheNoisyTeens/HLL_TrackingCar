#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"

/*常用LED控制三种状态：亮、灭、反转*/
#define	digitalHi(p,i)		 {p->BSRRL=i;}	 	
#define digitalLo(p,i)		 {p->BSRRH=i;}	 
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态
/*亮*/
#define LED_GREEN_ON			   digitalLo(GPIOF,GPIO_Pin_14) //板载LED_GREEN
#define LED_RED_ON			   	 digitalLo(GPIOE,GPIO_Pin_11)
#define LED_LASER_ON			   digitalHi(GPIOG,GPIO_Pin_13)

/*灭*/
#define LED_GREEN_OFF		    digitalHi(GPIOF,GPIO_Pin_14)
#define LED_RED_OFF		   		digitalHi(GPIOE,GPIO_Pin_11)
#define LED_LASER_OFF			   digitalLo(GPIOG,GPIO_Pin_13)

/*LED 反转*/									
#define LED_GREEN_TOGGLE		 digitalToggle(GPIOF,GPIO_Pin_14) 						
#define LED_RED_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_11) 
#define LED_LASER_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_11)


void Init_Led(void);

#endif
