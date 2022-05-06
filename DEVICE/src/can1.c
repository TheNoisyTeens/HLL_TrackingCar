#include "can1.h"


MotorEncoder_t motors[7];


void InitCan1(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
    
	  /*CAN初始化*/
	//配置主控制寄存器CAN_MCR 
  can.CAN_TTCM = DISABLE;
  can.CAN_ABOM = DISABLE;
  can.CAN_AWUM = DISABLE;
  can.CAN_NART = DISABLE;
  can.CAN_RFLM = DISABLE;
  can.CAN_TXFP = ENABLE;    
	
  can.CAN_Mode = CAN_Mode_Normal;
  can.CAN_SJW  = CAN_SJW_1tq;
  can.CAN_BS1 = 8;
  can.CAN_BS2 = 4;
  can.CAN_Prescaler = 3;   //CAN BaudRate 45/(1+9+5)/3=1Mbps
  CAN_Init(CAN1, &can);

	can_filter.CAN_FilterNumber = 0;
	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh= 0x0000;
	can_filter.CAN_FilterIdLow = 0x0000;
	can_filter.CAN_FilterMaskIdHigh = 0x0000;
	can_filter.CAN_FilterMaskIdLow  = 0x0000;
	can_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
  
  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
  CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
}

void InitCan1NVIC(void)
{
	NVIC_InitTypeDef       nvic;
	
	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 2;
  nvic.NVIC_IRQChannelSubPriority = 1;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
}



float power_data[4];

void CAN1_RX0_IRQHandler(void)
{
	static u16 can_cnt = 100;
	CanRxMsg can1_rx_msg;
	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		CAN_Receive(CAN1, CAN_FIFO0, &can1_rx_msg);	
		
			switch(can1_rx_msg.StdId)
			{
				case 0x201:
//					Reload(FL);//？
					motors[FL].cur_mechanical_angle = (can1_rx_msg.Data[0]<<8)|(can1_rx_msg.Data[1]);
					motors[FL].cur_speed = (can1_rx_msg.Data[2]<<8)|(can1_rx_msg.Data[3]);
				  //motors[FL].UpdateIntegralAngle(&(motors[FL]));
					break;
				case 0x202:
//					Reload(FR);
					motors[FR].cur_mechanical_angle = (can1_rx_msg.Data[0]<<8)|(can1_rx_msg.Data[1]);
					motors[FR].cur_speed = (can1_rx_msg.Data[2]<<8)|(can1_rx_msg.Data[3]);
				  //motors[FR].UpdateIntegralAngle(&motors[FR]);
					break;
				case 0x203:
//					Reload(BL);
					motors[BL].cur_mechanical_angle = (can1_rx_msg.Data[0]<<8)|(can1_rx_msg.Data[1]);
					motors[BL].cur_speed = (can1_rx_msg.Data[2]<<8)|(can1_rx_msg.Data[3]);
				  //motors[BL].UpdateIntegralAngle(&motors[BL]);
					break;
				case 0x204:
//					Reload(BR);
					motors[BR].cur_mechanical_angle = (can1_rx_msg.Data[0]<<8)|(can1_rx_msg.Data[1]);
					motors[BR].cur_speed = (can1_rx_msg.Data[2]<<8)|(can1_rx_msg.Data[3]);
				  //motors[BR].UpdateIntegralAngle(&motors[BR]);
					break;
				case 0x211:
					//printf("0x211\r\n");
//					Reload(AMMETER);//电流
//					Reload(VOLTMETER);//电压
					power_data[0] = (float)((short)((can1_rx_msg.Data[1]<<8)|(can1_rx_msg.Data[0])) / 100.f);
					power_data[1] = (float)((short)((can1_rx_msg.Data[3]<<8)|(can1_rx_msg.Data[2])) / 100.f);
					power_data[2] = (float)((short)((can1_rx_msg.Data[5]<<8)|(can1_rx_msg.Data[4])) / 100.f);
					power_data[3] = (float)((short)((can1_rx_msg.Data[7]<<8)|(can1_rx_msg.Data[6])) / 100.f);
					//printf("%.2f    \t%.2f    \t%.2f    \t%.2f\r\n",power_data[0],power_data[1],power_data[2],power_data[3]);
				  break;
				default:
//					printf("untitled_%d\r\n",can1_rx_msg.StdId);
					break;
		}
  }
}


/*
* 功能：发送数据（电流值）给底盘电机
*/
void Can1SendMsg2Chassis(int16_t fl, int16_t fr, int16_t bl, int16_t br)
{
		CanTxMsg tx_message;
    tx_message.StdId = 0x200;    //电调接收报文
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08; //数据长度为8字节,高位先行
    tx_message.Data[0] = (uint8_t)(fl >> 8); //fl高8位
    tx_message.Data[1] = (uint8_t)fl;        //fl低8位
    tx_message.Data[2] = (uint8_t)(fr >> 8);
    tx_message.Data[3] = (uint8_t)fr;
    tx_message.Data[4] = (uint8_t)(bl >> 8);
    tx_message.Data[5] = (uint8_t)bl;
    tx_message.Data[6] = (uint8_t)(br >> 8);
    tx_message.Data[7] = (uint8_t)br;
    CAN_Transmit(CAN1,&tx_message);
}

