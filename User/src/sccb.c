#include "sccb.h"
#include "delay.h"
 //////////////////////////////////////////////////////////////////////////////////	 
//SCCB ��������	   
//�Բ�
//�޸�����:2014/2/2
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////	 

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
    SCCB_SDA_H();     //�����߸ߵ�ƽ	   
    SCCB_SCL_H();	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(50);  
    SCCB_SDA_L();
    delay_us(50);	 
    SCCB_SCL_L();	    //�����߻ָ��͵�ƽ��������������Ҫ	  
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    SCCB_SDA_L();
    delay_us(50);	 
    SCCB_SCL_H();	
    delay_us(50); 
    SCCB_SDA_H();	
    delay_us(50);
}  
//����NA�ź�
void SCCB_No_Ack(void)
{
	delay_us(50);
	SCCB_SDA_H();	
	SCCB_SCL_H();	
	delay_us(50);
	SCCB_SCL_L();	
	delay_us(50);
	SCCB_SDA_L();	
	delay_us(50);
}
//SCCB,д��һ���ֽ�
//����ֵ:1,�ɹ�;0,ʧ��. 
u8 SCCB_WR_Byte(u8 dat)
{
	u8 j,res;	 
	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80)
			SCCB_SDA_H();	
		else 
			SCCB_SDA_L();
		dat<<=1;
		delay_us(50);
		SCCB_SCL_H();	
		delay_us(50);
		SCCB_SCL_L();		   
	}			 
	SCCB_SDA_IN();		//����SDAΪ���� 
	delay_us(50);
	SCCB_SCL_H();			//���յھ�λ,���ж��Ƿ��ͳɹ�
	delay_us(50);
	if(SCCB_READ_SDA())
		res=0;  //SDA=1����ʧ�ܣ�����0
	else 
		res=1;         //SDA=0���ͳɹ�������1
	SCCB_SCL_L();		 
	SCCB_SDA_OUT();		//����SDAΪ���    
	return res;  
}	 
//SCCB,д�������ֽ�
//����ֵ:1���ɹ���0��ʧ��
u8 SCCB_WR_HalfWord(u16 dat)
{
	if(0 == SCCB_WR_Byte(dat >> 8))
		return 0;
	if(0 == SCCB_WR_Byte(dat))
		return 0;
	return 1;
}
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
u8 SCCB_RD_Byte(void)
{
	u8 temp=0,j;    
	SCCB_SDA_IN();		//����SDAΪ����  
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		delay_us(50);
		SCCB_SCL_H();
		temp=temp<<1;
		if(SCCB_READ_SDA())
			temp++;   
		delay_us(50);
		SCCB_SCL_L();
	}	
	SCCB_SDA_OUT();		//����SDAΪ���    
	return temp;
} 							    
//д�Ĵ���
//����ֵ:1,�ɹ�;0,ʧ��.
u8 SCCB_WR_Reg(u16 reg,u8 data)
{
	u8 res=0;
	SCCB_Start(); 					//����SCCB����
	if(0==SCCB_WR_Byte(SCCB_ID))//д����ID
	{
		res=0;
		SCCB_Stop();
		return res;
	}
	else
		res=1;
	delay_us(100);
  if(0==SCCB_WR_HalfWord(reg))//д�Ĵ�����ַ
	{
		res=0;
		SCCB_Stop();
		return res;
	}
	else
		res=1;
	delay_us(100);
  if(0==SCCB_WR_Byte(data))//д����
	{
		res=0;
		SCCB_Stop();
		return res;
	} 		
  else
		res=1;
  SCCB_Stop();	  
  return	res;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
u8 SCCB_RD_Reg(u16 reg)
{
	u8 val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(SCCB_ID);		//д����ID	  
	delay_us(100);	 
  SCCB_WR_HalfWord(reg);			//д�Ĵ�����ַ	  
	delay_us(100);	  
	SCCB_Stop();   
	delay_us(100);	   
	//���üĴ�����ַ�󣬲��Ƕ�
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//���Ͷ�����	  
	delay_us(100);
  val=SCCB_RD_Byte();		 	//��ȡ����
  SCCB_No_Ack();
  SCCB_Stop();
  return val;
}
