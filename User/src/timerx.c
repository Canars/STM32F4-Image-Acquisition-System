/**
  ******************************************************************************
  * @file    timerx.c
  * @author  赵灿
  * @version V1.0
  * @date    14-April-2014
  * @brief   This file includes the driver for STM32F407VGT6's TIM used by UIP
  ******************************************************************s************
*/
#include "timerx.h"
u32 uip_timer=0;//uip 计时器，每10ms增加1.

//基本定时器7中断初始化
//这里时钟选择为APB1的2倍，而APB1为42M,故TIM7时钟为84M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器7!
//Tout = (arr+1)*(psc+1)/Tclk  , 其中Tclk = 84Mhz
void TIM7_Int_Init(u16 arr,u16 psc)
{	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //(999)设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //(839)设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig( TIM7,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//使能定时器7更新触发中断
 
	TIM_Cmd(TIM7, ENABLE);  //使能TIMx外设
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 								 
}

//定时器7中断服务程序	 
void TIM7_IRQHandler(void)
{ 	
	u8 flag=0;
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
  	uip_timer++;//uip计时器增加1	
	} 
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 			    		  			    	    
}
