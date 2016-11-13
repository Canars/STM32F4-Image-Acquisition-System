#include "uip.h"
#include "udp_client.h"
#include "dhcps.h"
#include "usart.h"
#include "dcmi_ov2640.h"
#include <string.h>
u8 udp_client_sta = 0;//客户端状态
int udp_client_len = 0;
u32 udp_client_data_buf[512];
//[7]:0,无连接;1,已经连接;
//[6]:0,无数据;1,收到客户端数据
//[5]:0,无数据;1,有数据需要发送
void uip_udp_init(void)
{
	uip_ipaddr_t ipaddr;
	static struct uip_udp_conn *conn_udp = 0;
	
	conn_udp = uip_udp_new(&ipaddr, HTONS(UDP_RPORT));//远程端口
	if(0 != conn_udp) 
	{
		// 绑定本地端口
		uip_udp_bind(conn_udp, HTONS(UDP_LPORT));//本地端口
		udp_client_sta |= 1<<7;
	}
}
void udp_appcall(void)
{
	struct udp_client_appstate *s = (struct udp_client_appstate *)&uip_udp_conn->appstate;
	if(udp_client_sta & 1<<5)//有数据需要发送
	{
		if(uip_udp_conn->rport == HTONS(UDP_RPORT))
		{
			if(DMA_GetCurrentMemoryTarget(DMA2_Stream1) == 0)//当前DMA正在向Memory_0即Image_Buffer1传输数据，Memory_1即Image_Buffer2空闲
			{
//				usart_SendString("2_hello!\r\n");//测试用
				s->textptr = Image_Buffer2;
				s->textlen = IMAGE_BUFFER_SIZE*4;
				uip_send(s->textptr,s->textlen);
        udp_client_sta &= ~(1<<5);		//清除数据发送标记		
			}
			else
			{
//				usart_SendString("1_hello!\r\n");//测试用
				s->textptr = Image_Buffer1;
				s->textlen = IMAGE_BUFFER_SIZE*4;
				uip_send(s->textptr,s->textlen);
				udp_client_sta &= ~(1<<5);		//清除数据发送标记				
			}
		}
	}
  //收到新数据	
	if(uip_newdata()) 
	{
//		usart_SendString("Receive new data\r\n");
		if(uip_udp_conn->lport == DHCPS_SERVER_PORT)
		{
//			usart_SendString("dhcp_init!\r\n");
			Dhcp_PktHandler(uip_appdata,uip_len);
		}
  }
}

void uip_log(char *msg)
{}
	
void tcp_appcall(void)
{}
	

