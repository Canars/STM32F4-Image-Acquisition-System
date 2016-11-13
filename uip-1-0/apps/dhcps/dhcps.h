#ifndef __DHCPS_H
#define __DHCPS_H
#include "stm32f4xx.h"
#define BOOTP_BROADCAST					0x8000

#define DHCP_REQUEST					1
#define DHCP_REPLY						2
#define DHCP_HTYPE_ETHERNET				1
#define DHCP_HLEN_ETHERNET				6
#define DHCP_MSG_LEN					236

#define DHCP_STATE_IDLE					0
#define DHCP_STATE_DISCOVER				1
#define DHCP_STATE_OFFER				2
#define DHCP_STATE_REQUEST				3
#define DHCP_STATE_DECLINE				4
#define DHCP_STATE_ACK					5
#define DHCP_STATE_NAK					6
#define DHCP_STATE_RELEASE				7

#define DHCP_TYPE_DISCOVER				1
#define DHCP_TYPE_OFFER					2
#define DHCP_TYPE_REQUEST				3
#define DHCP_TYPE_DECLINE				4
#define DHCP_TYPE_ACK					5
#define DHCP_TYPE_NAK					6
#define DHCP_TYPE_RELEASE				7

#define DHCP_OPTION_SUBNET_MASK			1
#define DHCP_OPTION_ROUTER				3
#define DHCP_OPTION_DNS_SERVER			6
#define DHCP_OPTION_REQ_IPADDR			50
#define DHCP_OPTION_LEASE_TIME			51
#define DHCP_OPTION_MSG_TYPE			53
#define DHCP_OPTION_SERVER_ID			54
#define DHCP_OPTION_INTERFACE_MTU		26
#define DHCP_OPTION_PERFORM_ROUTER_DISCOVERY 31
#define DHCP_OPTION_BROADCAST_ADDRESS	28
#define DHCP_OPTION_REQ_LIST			55
#define DHCP_OPTION_END					255

#define DHCPS_SERVER_PORT				67
#define DHCPS_CLIENT_PORT				68

#define DHCP_MAGIC_COOKIE 				"\x63\x82\x53\x63"
#define DHCP_XID						"\xad\xde\x12\x23"

#define DHCPMSG_OPTION_LENGTH		312
typedef struct
{
	uint8_t op;
	uint8_t htype;
	uint8_t hlen;
	uint8_t hops;
	uint8_t xid[4];
	uint16_t secs;
	uint16_t flags;
	uint8_t ciaddr[4];
	uint8_t yiaddr[4];
	uint8_t siaddr[4];
	uint8_t giaddr[4];
	uint8_t chaddr[16];
	uint8_t sname[64];
	uint8_t file[128];
	uint8_t options[DHCPMSG_OPTION_LENGTH];
} DHCPMsg, *PDHCPMSG;

typedef struct
{
	unsigned long ulServerIp;
	unsigned long ulClientIp;
} DHCPInfo, *PDHCPINFO;

//
// Exported functions declare
//
void Dhcp_Init(const void *mac_addr, int mac_len);
void Dhcp_PktHandler(u8* pInBuffer, u16 usLen);
#endif
