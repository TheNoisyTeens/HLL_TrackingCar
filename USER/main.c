#include "stm32f4xx.h"
#include "can1.h"
#include "delay.h"
#include "power.h"
#include "led.h"




int main(void)
{
	//��ʼ��
	Init_Led();
	InitCan1();//can1���շ���
	
	
	
	//������Դ
	void Power_Ctrl_ON();
	
	while(1)
	{
		//����CAN�źŷ���
		Can1SendMsg2Chassis(500,500,500,500);
		
	}

}
