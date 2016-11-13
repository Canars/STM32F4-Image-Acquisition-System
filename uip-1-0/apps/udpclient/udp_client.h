#ifndef __UDP_CLIENT_H
#define __UDP_CLIENT_H
#include "stm32f4xx.h"

#define UDP_LPORT  9999
#define UDP_RPORT  9999

//����Ӧ�ó���ص����� 
#ifndef UIP_APPCALL
#define UIP_APPCALL  tcp_appcall//����ص�����Ϊ udp_appcall 
#endif

#ifndef UIP_UDP_APPCALL
#define UIP_UDP_APPCALL udp_appcall
#endif
extern u8 udp_client_sta;//�ͻ���״̬

//���� uip_udp_appstate_t �������ͣ��û��������Ӧ�ó�����Ҫ�õ�
//��Ա��������Ҫ���Ľṹ�����͵����֣���Ϊ����������ᱻuip���á�
//uip.h �ж���� 	struct uip_conn  �ṹ���������� uip_udp_appstate_t	
struct udp_client_appstate
{
	u8 state;
	u32 *textptr;
	int textlen;
};
typedef struct udp_client_appstate uip_udp_appstate_t;

void uip_udp_init(void);
void udp_appcall(void);
void tcp_appcall(void);
#endif