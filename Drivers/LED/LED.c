/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "Project.h"

BOOL LED_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init (GPIOC, &GPIO_InitStructure);

	// Turn off all LED first
	LED_TurnOff (LED1);
	LED_TurnOff (LED2);
	LED_TurnOff (LED3);
	LED_TurnOff (LED4);

	return TRUE;
}

BOOL LED_TurnOn (UINT16 usLed)
{
	GPIO_ResetBits (GPIOC, usLed);

	return TRUE;
}

BOOL LED_TurnOff (UINT16 usLed)
{
	GPIO_SetBits (GPIOC, usLed);

	return TRUE;
}

BOOL LED_Flash (UINT16 usLed)
{
	if (GPIO_ReadOutputDataBit(GPIOC, usLed) == Bit_RESET)
		GPIO_SetBits(GPIOC, usLed);
	else
		GPIO_ResetBits(GPIOC, usLed);

	return TRUE;
}
