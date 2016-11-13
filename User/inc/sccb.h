#ifndef __SCCB_H
#define __SCCB_H
#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//SCCB 驱动代码	   
//赵灿
//修改日期:2014/1/29
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOB->MODER  &=  0xFFF3FFFF;\
												GPIOB->PUPDR  &= ~0x00080000;\
												GPIOB->PUPDR  |=  0x00040000;}//PB9上拉输入
#define SCCB_SDA_OUT() {GPIOB->MODER  &= ~0x00080000;\
												GPIOB->MODER  |=  0x00040000;\
												GPIOB->OTYPER |=  0x0200;\
												GPIOB->OSPEEDR |= 0x000C0000;\
												GPIOB->PUPDR  &= ~0x00080000;\
												GPIOB->PUPDR  |=  0x00040000;}//PB9开漏输出，上拉，High Spped(100MHz)

//IO操作函数	 
#define SCCB_SCL_H()   		GPIOB->BSRRL = GPIO_Pin_8	 	//PB8  SCL_H
#define SCCB_SCL_L()      GPIOB->BSRRH = GPIO_Pin_8	  //PB8  SCL_L											
#define SCCB_SDA_H()    	GPIOB->BSRRL = GPIO_Pin_9	  //PB9  SDA_H
#define SCCB_SDA_L()      GPIOB->BSRRH = GPIO_Pin_9   //PB9  SDA_L

#define SCCB_READ_SDA()   GPIOB->IDR & GPIO_Pin_9     //读PB9    
#define SCCB_ID   			  0X60  			//OV5640的SCCB_ID

///////////////////////////////////////////
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_WR_HalfWord(u16 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u16 reg,u8 data);
u8 SCCB_RD_Reg(u16 reg);
#endif













