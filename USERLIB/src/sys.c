#include "sys.h"  


float Limit(float value, float min, float max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	
	return value;
}

float Gate(float value, float min, float max)
{
	if(value > min && value < max)
		return 0;
	
	return value;
}

float Map(float value, float src_left, float src_right, float dest_left, float dest_right)
{
	return (dest_right - dest_left) / (src_right - src_left) * (value - src_left) + dest_left;
}

float ZF(float val)
{
	if(val > 0) return 1;
	if(val < 0) return -1;
	else return 0;
}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















