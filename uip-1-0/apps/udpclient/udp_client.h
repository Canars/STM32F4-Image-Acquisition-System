#ifndef __UDP_CLIENT_H
#define __UDP_CLIENT_H
#include "stm32f4xx.h"

#define UDP_LPORT  9999
#define UDP_RPORT  9999

//定义应用程序回调函数 
#ifndef UIP_APPCALL
#define UIP_APPCALL  tcp_appcall//定义回调函数为 udp_appcall 
#endif

#ifndef UIP_UDP_APPCALL
#define UIP_UDP_APPCALL udp_appcall
#endif
extern u8 udp_client_sta;//客户端状态

//定义 uip_udp_appstate_t 数据类型，用户可以添加应用程序需要用到
//成员变量。不要更改结构体类型的名字，因为这个类型名会被uip引用。
//uip.h 中定义的 	struct uip_conn  结构体中引用了 uip_udp_appstate_t	
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