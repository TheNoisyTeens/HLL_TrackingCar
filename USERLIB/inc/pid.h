#ifndef __PID_H__
#define __PID_H__

#include "sys.h"
#include "math.h"

/*
* 宏定义：PPID初始化（位置式PID）
*/
#define new_PPID(a,b,c,d,e,f,g,h,i,j) {\
	.kp                     = a,\
	.ki                     = b,\
	.kd                     = c,\
	.tar                    = 0,\
	.cur                    = 0,\
	.err                    = 0,\
	.old_err                = 0,\
	.err_integral           = 0,\
	.k                      = 0,\
	.is_integral_spare      = d,\
	.output_max_abs         = e,\
	.err_integral_max_abs   = f,\
	.err_min_abs            = g,\
	.begin_integral_min_abs = h,\
	.stop_integral_max_abs  = i,\
	.kp_output              = 0,\
	.ki_output              = 0,\
	.kd_output              = 0,\
	.output                 = 0,\
	.Calc                   = j\
}

typedef struct _PPID_t
{
	/* 三项系数 */
	float kp;
	float ki;
	float kd;
	
	float tar;//目标值
	float cur;//当前值
	
	float err;//当前误差
	float old_err;//上一次误差
	
	float err_integral;//积分和
	float k;//err差分
	
	u8    is_integral_spare;      //选择是否使用积分分离
	
	/* 积分、输出限幅——抗饱和 */
	float output_max_abs;         //输出限幅
	float err_integral_max_abs;   //积分限幅
	
	/* 积分分离——防超调 */  //**********************************************************不知道？
	float err_min_abs;            //当fabs(err) < err_min_abs时，err = 0//误差限幅
	float begin_integral_min_abs; //当fabs(err) < err_integral_min_abs时不积分
	float stop_integral_max_abs;  //当fabs(err) > err_integral_max_abs时不积分
	
	/* 输出 */
	float kp_output;
	float ki_output;
	float kd_output;
	float output;
	
}PositionPID_t;


void CalcPositionPID(PositionPID_t* pid);


#endif
