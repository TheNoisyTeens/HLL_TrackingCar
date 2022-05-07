#ifndef __CAN1_H__
#define __CAN1_H__

#include "stm32f4xx.h" 
		
//Ӧ���ǵ����ţ������������
#define FL                         0
#define FR                         1
#define BL                         2
#define BR                         3

//������ͱ�������--һ�����������
typedef struct _MotorEncoder_t
{
	u8 is_first_power_on_flag;
	short cur_mechanical_angle;//��ǰ��е�Ƕ�
	short old_mechanical_angle;//ǰһ�̻�е�Ƕ�
	short cur_speed;//��ǰ�ٶ�
	
	short cur_mechanical_angle_dev;
	int cur_integral_angle;
	
	void(*UpdateIntegralAngle)(struct _MotorEncoder_t* self);
}MotorEncoder_t;



void InitCan1(void);
void InitCan1NVIC(void);
void Can1SendMsg2Chassis(int16_t fl, int16_t fr, int16_t bl, int16_t br);

#endif
