/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "WlanPkt.h"

//--------------------------------------------------------------------
// Proviated functions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Exported functions
//--------------------------------------------------------------------
BOOL WlanPkt_RcvePkt(PWLAN_ADAPTER Adapter, PVOID pBuf, PUINT pnLen)
{
	BOOL nStatus = TRUE;
	WORD nBufLen, nPktLen;

	if (If_ReadRegister(SCRATCH_1_REG, &nBufLen) != sizeof(WORD))
		nStatus = FALSE;
	if (nStatus) {
		//the RxPkt is always 802.3 but ethernet2
		if (nBufLen <= sizeof(RxPD) + MRVDRV_ETH_HEADER_SIZE + 8 ||
		    nBufLen > sizeof(RxPD) + MRVDRV_MAXIMUM_ETH_PACKET_SIZE) {
			TRACE("PktRcvePkt: nBufLen=%d !\r\n", nBufLen);
			nStatus = FALSE;
		}
	}
	if (nStatus) {
		PRxPD pRxPD = NULL;
		UINT nPktBuffLen;

		// Alloc memory for packet rcve
		nPktBuffLen = sizeof(WCB) + nBufLen;
		nPktBuffLen += (nBufLen & 1) ? 1 : 0;

		if (nPktBuffLen > PKT_RCVE_BUFF_LENGTH) {
			TRACE("PktRcvePkt: Error packet length(too long) = %d!!\r\n", nPktBuffLen);
			If_WriteRegister(CARD_INT_CAUSE_REG, CIC_RxUpLdOvr);
			return FALSE;
		}

		// Alloc temp buffer for packet receive
		pRxPD = (PRxPD)AllocMemory(nPktBuffLen);//(PRxPD)ucPktRcveBuffer;
		if (!pRxPD) {
			TRACE("PktRcvePkt: memory alloc failed!\r\n");
			If_WriteRegister(CARD_INT_CAUSE_REG, CIC_RxUpLdOvr);
			*pnLen = 0;
			return FALSE;
		}

		nPktLen = nBufLen - sizeof(RxPD);
		if (nBufLen & 1)
			nBufLen++;
		if (If_ReadRegister2(DATA_RDWRPORT_REG, (PVOID)pRxPD, nBufLen) != nBufLen)
			nStatus = FALSE;
		if (nPktLen != pRxPD->PktLen) {
			TRACE("PktRcvePkt: nPktLen!=pRxPD->PktLen[%d!=%d]\n", nPktLen, pRxPD->PktLen);
			nStatus = FALSE;
			*pnLen = 0;
		}
		else {
			CopyMemory(pBuf, (PBYTE)pRxPD + pRxPD->PktPtr, nPktLen);
			CopyMemory((PBYTE)pBuf + 12, (PBYTE)pBuf + 20, nPktLen - 20);
			*pnLen = nPktLen - 8;
		}
		// Free the temp buffer
		FreeMemory(pRxPD);
	}
	If_WriteRegister(CARD_INT_CAUSE_REG, CIC_RxUpLdOvr);

	return nStatus;
}

BOOL WlanPkt_SendPkt(PWLAN_ADAPTER Adapter, PVOID pBuf, UINT nBufLen)
{
	PWCB pWcb = NULL;
	BOOL nStatus;
	UINT nPktBuffLen;

	// Calculate the packet length
	nPktBuffLen = sizeof(WCB) + nBufLen;
	nPktBuffLen += (nBufLen & 1) ? 5 : 4;

	if (nPktBuffLen > PKT_SEND_BUFF_LENGTH) {
		TRACE("PktSendPkt: Error packet length(too long) = %d!!\r\n", nPktBuffLen);
		If_WriteRegister(CARD_INT_CAUSE_REG, CIC_RxUpLdOvr);
		return FALSE;
	}

	// pWcb = (PWCB)ucPktSendBuffer;
	// Alloc temp buffer for packet receive
	pWcb = (PWCB)AllocMemory(nPktBuffLen);//(PRxPD)ucPktRcveBuffer;
	if (!pWcb) {
		TRACE("PktSendPkt: memory alloc failed!\r\n");
		return FALSE;
	}

	ZeroMemory((PVOID)pWcb, sizeof(WCB));
	CopyMemory((PBYTE)(pWcb + 1), pBuf, nBufLen);
	pWcb->Status = MRVDRV_WCB_STATUS_USED;
	pWcb->PktLen = nBufLen;
	pWcb->PktPtr = sizeof(WCB);
	CopyMemory(pWcb->DestMACAdrHi, pBuf, MRVDRV_ETH_ADDR_LEN);
	nBufLen += sizeof(WCB);
	nBufLen += (nBufLen & 1) ? 5 : 4;
#if 0
	{
		if (1) {
			PBYTE pBuf = (PBYTE)pWcb;
			UINT i;

			TRACE("pWcb->Status: 0x%08X\r\n", pWcb->Status);
			TRACE("pWcb->TxControl: 0x%08X\r\n", pWcb->TxControl);
			TRACE("pWcb->PktPtr: 0x%08X\r\n", pWcb->PktPtr);
			TRACE("pWcb->PktLen: 0x%08X\r\n", pWcb->PktLen);

			TRACE("Packet Data:\r\n");
			for (i = 0; i < nBufLen; i ++) {
				TRACE("%02X,", pBuf[i]);
				if (((i + 1) % 16) == 0) {
					TRACE("\r\n");
				}
			}

			TRACE("\r\n");
		}
	}
#endif

	if (If_WriteRegister2(DATA_RDWRPORT_REG, (PVOID)pWcb, nBufLen) != nBufLen)
		nStatus = FALSE;
	If_WriteRegister(CARD_INT_CAUSE_REG, CIC_TxDnLdOvr);

	// Alloc temp buffer for packet receive
	FreeMemory(pWcb);

	return nStatus;
}

void WlanPkt_OnPktSend(PWLAN_ADAPTER Adapter)
{
}

void WlanPkt_OnPktRcve(PWLAN_ADAPTER Adapter)
{
	TRACE("+PktOnPktRcve()\r\n");

	WIFI_SET_FLAG(Adapter, FLAG_PKTRCVED);

	TRACE("-PktOnPktRcve()\r\n");
}

