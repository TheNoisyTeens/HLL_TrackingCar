#include "stm32f4xx.h"
#include "can1.h"
#include "delay.h"
#include "power.h"
#include "led.h"




int main(void)
{
	//初始化
	Init_Led();
	InitCan1();//can1接收发送
	
	
	
	//开启电源
	void Power_Ctrl_ON();
	
	while(1)
	{
		//测试CAN信号发送
		Can1SendMsg2Chassis(500,500,500,500);
		
	}

}
