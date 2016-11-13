/**
  ******************************************************************************
  * @file    timerx.h
  * @author  ут╡с
  * @version V1.0
  * @date    14-April-2014
  * @brief   This file includes the header file for timer.c
  ******************************************************************s************
*/
#ifndef __TIMERX_H
#define __TIMERX_H
#include "stm32f4xx.h"
void TIM7_Int_Init(u16 arr,u16 psc);
#endif