/******************************************************************************************************************************/
#ifndef __RM68042_H
#define __RM68042_H	
#include "stm32f4xx.h"

//6804 LCD寄存器  Command(C) Read(R) Write(W)
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
// #define R38						 0x26		//set_gamma_curve						W			设置gamma曲线
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
#define R191					 0xBF   //Device code Read          R  设备编码 This is the most significant parameter !!!!!
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

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;					//LCD ID
	u8  dir;				//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u8	wramcmd;		//开始写GRAM指令
	u8  setxcmd;		//设置x坐标指令
	u8  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         		 0x001F  
#define BRED             0XF81F
#define GRED 						 0XFFE0
#define GBLUE						 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F	//洋红色
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 //棕色
#define BRRED 					 0XFC07 //棕红色
#define GRAY  					 0X8430 //灰色
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/******************************************************************************************************************************/	
#define RST_HIGH()		GPIOB->BSRRL = GPIO_Pin_11
#define RST_LOW()			GPIOB->BSRRH = GPIO_Pin_11

//LCD地址结构体
typedef struct
{
	u16 LCD_REG;		//代表写入命令
	u16 LCD_RAM;		//代表写入数据
} LCD_TypeDef;

//使用NOR/SRAM的 Bank1.sector1,地址位HADDR[27,26]=11 A16作为数据命令区分线 
//注意设置时STM32内部会右移一位对齐!
/* A16 作为地址线,第17位为0表示命令，为1表示数据*/
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0001FFFE))
#define LCD                ((LCD_TypeDef *) LCD_BASE)
/******************************************************************************************************************************/


/*****************************FUNCTION DECLARE********************************************/
void LCD_Init(void);													   											//初始化
void LCD_DisplayOn(void);																							//开显示
void LCD_DisplayOff(void);																						//关显示
void LCD_Clear(u16 Color);	 																					//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);																//设置光标
void LCD_DrawPoint(u16 x,u16 y);																			//画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);												//快速画点
u16  LCD_ReadPoint(u16 x,u16 y); 																			//读点 
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);										//画线
//void LCD_DrawCircle(u16 x0,u16 y0,u8 r);															//画圆
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   					//画矩形
void LCD_DrawRiangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3);			//画三角形	
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   						//填充单色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);					//填充指定颜色
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);								//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  								//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//显示 数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);	//显示一个字符串,12/16字体

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16  LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//设置屏扫描方向
void LCD_Display_Dir(u8 dir);						//设置屏幕显示方向
#endif
