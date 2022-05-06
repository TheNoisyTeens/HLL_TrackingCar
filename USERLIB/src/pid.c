#include "pid.h"

/*
* 功能：进行pid计算
*/
void CalcPositionPID(PositionPID_t* pid)
{
	float intergal_spare_k = 0.0f;
	
	pid->err = pid->tar - pid->cur;//误差
	
	/*误差限幅*/  //**************************************************？
	if(fabs(pid->err) < pid->err_min_abs)
		pid->err = 0.0f;
	
	/*积分分离————防超调*/
	if(fabs(pid->err) > pid->begin_integral_min_abs &&
		 fabs(pid->err) < pid->stop_integral_max_abs)
	{
		pid->err_integral += pid->err;
		intergal_spare_k = 1.0f;;
	}
	else
	{
		if(pid->is_integral_spare)
			intergal_spare_k = 0.0f;
	}
	
	/*积分限幅————积分抗饱和*/
	pid->err_integral = Limit(pid->err_integral, -pid->err_integral_max_abs, pid->err_integral_max_abs);
	
	
	pid->k = pid->err - pid->old_err;//差分
	
	
	/*各项输出计算*/
	pid->kp_output = pid->kp * pid->err;
	pid->ki_output = pid->ki * pid->err_integral * intergal_spare_k;
	pid->kd_output = pid->kd * pid->k;
	
	/*输出限幅————输出抗饱和*/
	pid->output = pid->kp_output + pid->ki_output + pid->kd_output;
	pid->output = Limit(pid->output, -pid->output_max_abs, pid->output_max_abs);

	
	pid->old_err = pid->err;
}


