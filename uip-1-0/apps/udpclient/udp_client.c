#include "uip.h"
#include "udp_client.h"
#include "dhcps.h"
#include "usart.h"
#include "dcmi_ov2640.h"
#include <string.h>
u8 udp_client_sta = 0;//�ͻ���״̬
int udp_client_len = 0;
u32 udp_client_data_buf[512];
//[7]:0,������;1,�Ѿ�����;
//[6]:0,������;1,�յ��ͻ�������
//[5]:0,������;1,��������Ҫ����
void uip_udp_init(void)
{
	uip_ipaddr_t ipaddr;
	static struct uip_udp_conn *conn_udp = 0;
	
	conn_udp = uip_udp_new(&ipaddr, HTONS(UDP_RPORT));//Զ�̶˿�
	if(0 != conn_udp) 
	{
		// �󶨱��ض˿�
		uip_udp_bind(conn_udp, HTONS(UDP_LPORT));//���ض˿�
		udp_client_sta |= 1<<7;
	}
}
void udp_appcall(void)
{
	struct udp_client_appstate *s = (struct udp_client_appstate *)&uip_udp_conn->appstate;
	if(udp_client_sta & 1<<5)//��������Ҫ����
	{
		if(uip_udp_conn->rport == HTONS(UDP_RPORT))
		{
			if(DMA_GetCurrentMemoryTarget(DMA2_Stream1) == 0)//��ǰDMA������Memory_0��Image_Buffer1�������ݣ�Memory_1��Image_Buffer2����
			{
//				usart_SendString("2_hello!\r\n");//������
				s->textptr = Image_Buffer2;
				s->textlen = IMAGE_BUFFER_SIZE*4;
				uip_send(s->textptr,s->textlen);
        udp_client_sta &= ~(1<<5);		//������ݷ��ͱ��		
			}
			else
			{
//				usart_SendString("1_hello!\r\n");//������
				s->textptr = Image_Buffer1;
				s->textlen = IMAGE_BUFFER_SIZE*4;
				uip_send(s->textptr,s->textlen);
				udp_client_sta &= ~(1<<5);		//������ݷ��ͱ��				
			}
		}
	}
  //�յ�������	
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
	

