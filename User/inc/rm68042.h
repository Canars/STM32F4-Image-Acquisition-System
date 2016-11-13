/******************************************************************************************************************************/
#ifndef __RM68042_H
#define __RM68042_H	
#include "stm32f4xx.h"

//6804 LCD�Ĵ���  Command(C) Read(R) Write(W)
#define R0             0x00		//nop												C
#define R1             0x01		//soft_reset								C
#define R10            0x0A		//get_power_mode						R
#define R11						 0x0B		//get_address_mode					R   Bits[7:3] only
#define R12            0x0C		//get_pixel_format					R
#define R13            0x0D		//get_display_mode					R
#define R14            0x0E		//get_signal_mode						R
#define R15            0x0F		//get_diagnostic_result			R		Bits[7:6] only
#define R16            0x10		//enter_sleep_mode					C
#define R17            0x11		//exit_sleep_mode						C
#define R18            0x12		//enter_partial_mode				C
#define R19            0x13		//enter_normal_mode					C
#define R32            0x20		//exit_invert_mode				  C
#define R33            0x21		//enter_invert_mode					C
// #define R38						 0x26		//set_gamma_curve						W			����gamma����
#define R40            0x28		//set_display_off						C
#define R41            0x29		//set_display_on						C
#define R42						 0x2A		//set_column_address				W
#define R43            0x2B		//set_page_address					W
#define R44						 0x2C		//write_memory_start				W
// #define R45            0x2D		//write_LUT									W
#define R46            0x2E		//read_memory_start					R
#define R48            0x30		//set_partial_area					W
#define R51            0x33		//set_scroll_area						W
#define R52            0x34		//set_tear_off							C							
#define R53            0x35		//set_tear_on								W
#define R54            0x36		//set_address_mode					W		Bits[7:3],Bits[1:0] only
#define R55            0x37		//set_scroll_start					W
#define R56            0x38		//exit_idle_mode						C
#define R57            0x39		//enter_idle_mode						C
#define R58						 0x3A		//Set_Pixel_Format 					W
#define R60            0x3C		//write_memory_contiue			W	
#define R62            0x3E		//read_memory_contiue				R
#define R68            0x44		//set_tear_scanline					W
#define R69            0x45		//get_scanline							R
#define R161           0xA1		//read_DDB_start						R


#define R176					 0xB0		//Command Access Protect		W/R
#define R177           0xB1		//Low Power Mode_Control		W/R
#define R179					 0xB3		//Frame Memory Access and Interface setting           W/R
#define R180					 0xB4		//Display Mode and Frame Memory Write Mode Setting 		W/R
#define R191					 0xBF   //Device code Read          R  �豸���� This is the most significant parameter !!!!!
#define R192           0xC0		//Panel Driving Setting			W/R
#define R193           0xC1   //Display Timing Setting for Normal Mode              W/R
#define R194           0xC2		//Display Timing Setting for Partial Mode							W/R
#define R195					 0xC3		//Display Timing Setting for idle Mode                W/R 
#define R197           0xC5		//Frame rate and inversion Control
#define R198           0xC6		//Interface Control																		W/R
#define R200           0xC8		//Gamma Setting							W
#define R208					 0xD0		//Power Setting    					W/R
#define R209					 0xD1		//VCOM Control							W/R
#define R210					 0xD2		//Power Setting for Noramal Mode 		W/R
#define R211					 0xD3		//Power Setting for Partial Mode    W/R
#define R212           0xD4		//Power Setting for idle Mode				W/R
#define R224					 0xE0		//NV Memory Write    				W/R
#define R225					 0xE1		//NV Memory Control					W/R
#define R226					 0xE2		//NV Memory Status   				W/R
#define R227					 0xE3		//NV Memory Protection      W/R
#define R229           0xE5							  		 

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;					//LCD ID
	u8  dir;				//���������������ƣ�0��������1��������	
	u8	wramcmd;		//��ʼдGRAMָ��
	u8  setxcmd;		//����x����ָ��
	u8  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         		 0x001F  
#define BRED             0XF81F
#define GRED 						 0XFFE0
#define GBLUE						 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F	//���ɫ
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 //��ɫ
#define BRRED 					 0XFC07 //�غ�ɫ
#define GRAY  					 0X8430 //��ɫ
//GUI��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/******************************************************************************************************************************/	
#define RST_HIGH()		GPIOB->BSRRL = GPIO_Pin_11
#define RST_LOW()			GPIOB->BSRRH = GPIO_Pin_11

//LCD��ַ�ṹ��
typedef struct
{
	u16 LCD_REG;		//����д������
	u16 LCD_RAM;		//����д������
} LCD_TypeDef;

//ʹ��NOR/SRAM�� Bank1.sector1,��ַλHADDR[27,26]=11 A16��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����!
/* A16 ��Ϊ��ַ��,��17λΪ0��ʾ���Ϊ1��ʾ����*/
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0001FFFE))
#define LCD                ((LCD_TypeDef *) LCD_BASE)
/******************************************************************************************************************************/


/*****************************FUNCTION DECLARE********************************************/
void LCD_Init(void);													   											//��ʼ��
void LCD_DisplayOn(void);																							//����ʾ
void LCD_DisplayOff(void);																						//����ʾ
void LCD_Clear(u16 Color);	 																					//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);																//���ù��
void LCD_DrawPoint(u16 x,u16 y);																			//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);												//���ٻ���
u16  LCD_ReadPoint(u16 x,u16 y); 																			//���� 
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);										//����
//void LCD_DrawCircle(u16 x0,u16 y0,u8 r);															//��Բ
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   					//������
void LCD_DrawRiangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3);			//��������	
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   						//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);					//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);								//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  								//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);	//��ʾһ���ַ���,12/16����

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16  LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//������ɨ�跽��
void LCD_Display_Dir(u8 dir);						//������Ļ��ʾ����
#endif
