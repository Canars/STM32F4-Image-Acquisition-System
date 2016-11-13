#include "Includes.h"
#include "rm68042.h"
#include "dcmi_ov2640.h"
//#include "flash.h"
#include "uIP_App.h"
#include "udp_client.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"

extern u8 DCMI_FLAG;
extern u8 DMA2_Stream1_TC_FLAG;
extern u8 Dma_FreeBuf_No;
extern u8 Dma_FreeBuf_Ok;

//设置主频标准168MHZ
void RCC_Configuration()
{
	RCC_DeInit();//RCC寄存器初始化
	RCC_HSEConfig(RCC_HSE_ON);//使用外部时钟
	if(RCC_WaitForHSEStartUp() == SUCCESS)//等待外部时钟启动
	{
		RCC_PLLCmd(DISABLE);//配置PLL钱关闭主PLL
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//选择PLL时钟为系统时钟
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//HCLK(AHB）时钟为系统时钟1分频
		RCC_PCLK1Config(RCC_HCLK_Div4);//PCLK1(APB1)时钟为HCLK4分频，TIM2,3,4,5,6,7,12,13,14为2分频
		RCC_PCLK2Config(RCC_HCLK_Div2);//PCLK2(APB2)时钟为HCLK2分频，TIM1,8,9,10,11为HCLK1分频
		RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);//PLL时钟配置PLL_M=8,PLL_N=336,PLL_P=2,PLL_Q=7
		RCC_PLLCmd(ENABLE);//开启PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	}
}

void led3_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}
int  main()
{
	u8 tcnt=0;
	u8 udp_client_tsta = 0xFF;
	BOOL bStatus;
	RCC_Configuration();//配置时钟
	delay_init();
	usart_init();
	
#ifdef BUILD_FOR_WRITEFIRMWARE
	If_WriteFirmware ();
	while (1);
#endif
	bStatus = Wlan_Init(g_pWlanAdapter);
	if (!bStatus) 
	{
		TRACE("Wlan init failed!!\r\n");
		return 0;
	}
	uIP_Net_Init();
//	if (1)
//	{ // Create default profile
//		WiFiCmd_RunCommand ("set ssid WiFiTest");
//		WiFiCmd_RunCommand ("set networktype infra");
//		WiFiCmd_RunCommand ("set authmode open");
//		WiFiCmd_RunCommand ("set encrymode wep");
//		WiFiCmd_RunCommand ("set keyascii 1234567890");
//	}
//	WiFiCmd_RunCommand ("ctrl connect");
	
	if (1)
	{ // Create default profile
		WiFiCmd_RunCommand ("set ssid WiFiTest_Adhoc");
		WiFiCmd_RunCommand ("set networktype adhoc");
		WiFiCmd_RunCommand ("set authmode open");
		WiFiCmd_RunCommand ("set encrymode wep");
		WiFiCmd_RunCommand ("set keyascii 1234567890");
	}
	WiFiCmd_RunCommand ("ctrl connect");
	
	/*OV2640启用*/
	OV2640_HW_Init();
	OV2640_JpegDcmiInit();
	OV2640_JPEGConfig(JPEG_320x240);
	DMA_Cmd(DMA2_Stream1,ENABLE);
	DCMI_Cmd(ENABLE);
	DCMI_CaptureCmd(ENABLE);

	while(1)
	{
		uip_polling();
		if(Dma_FreeBuf_Ok == 1)//DMA有空闲缓冲区了
		{
			if(udp_client_sta & 1<<7)//如果udp连接存在
				udp_client_sta |= 1<<5;//标记有数据要发送
//			usart_sendJPEGdata();;
			Dma_FreeBuf_Ok = 0;
		}
		if(WIFI_GET_FLAG(g_pWlanAdapter,FLAG_PKTRCVED))
		{
			WIFI_CLR_FLAG(g_pWlanAdapter,FLAG_PKTRCVED);
			uip_pro();//网络命令的解析
		}
		if(usart_struct.USART_Sta & USART_STA_RECEIVED)
		{
			WiFiCmd_RunCommand((char*)usart_struct.USART_RX_BUF);
			usart_struct.USART_Sta &= ~USART_STA_RECEIVED;
			usart_struct.USART_RX_Cnt = 0;
		}
	}
}
