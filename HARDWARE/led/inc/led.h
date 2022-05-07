#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"

/*����LED��������״̬�������𡢷�ת*/
#define	digitalHi(p,i)		 {p->BSRRL=i;}	 	
#define digitalLo(p,i)		 {p->BSRRH=i;}	 
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬
/*��*/
#define LED_GREEN_ON			   digitalLo(GPIOF,GPIO_Pin_14) //����LED_GREEN
#define LED_RED_ON			   	 digitalLo(GPIOE,GPIO_Pin_11)
#define LED_LASER_ON			   digitalHi(GPIOG,GPIO_Pin_13)

/*��*/
#define LED_GREEN_OFF		    digitalHi(GPIOF,GPIO_Pin_14)
#define LED_RED_OFF		   		digitalHi(GPIOE,GPIO_Pin_11)
#define LED_LASER_OFF			   digitalLo(GPIOG,GPIO_Pin_13)

/*LED ��ת*/									
#define LED_GREEN_TOGGLE		 digitalToggle(GPIOF,GPIO_Pin_14) 						
#define LED_RED_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_11) 
#define LED_LASER_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_11)


void Init_Led(void);

#endif
