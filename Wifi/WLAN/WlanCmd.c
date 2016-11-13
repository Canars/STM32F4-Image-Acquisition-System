/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "WlanCmd.h"

static const BYTE m_aSupportRate_G[]={
	0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c,  // Supported rates
	0x0c, 0x12, 0x18, 0x60 // Extended Supported rates
};

//--------------------------------------------------------------------
// Proviated functions
//--------------------------------------------------------------------
static CMD_STATUS CmdQueryBuffer(PWLAN_ADAPTER pAdapter)
{
	int nLoop = 0;

	// Check the flag
	while (WIFI_GET_FLAG(pAdapter, FLAG_CMDPROCESSING) && nLoop < 10) {
		delay_ms(1000);
		nLoop ++;
	}
	if (nLoop == 10)
		return CMD_ERROR_CMDPROCING;

	// Set flag to lock the cmd buffer
	WIFI_SET_FLAG(pAdapter, FLAG_CMDPROCESSING);

	return CMD_ERROR_SUCCESS;
}

static CMD_STATUS CmdReleaseBuffer(PWLAN_ADAPTER pAdapter)
{
	// Release the cmd buffer
	WIFI_CLR_FLAG(pAdapter, FLAG_CMDPROCESSING);

	return CMD_ERROR_SUCCESS;
}

static WORD CmdGetCmdRetCode(WORD nCmd)
{
	switch (nCmd) {
		case HostCmd_CMD_802_11_ASSOCIATE_EXT:
			nCmd = HostCmd_CMD_802_11_ASSOCIATE;
			break;
	}

	return 0x8000 | nCmd;
}

static BOOL CmdDownloadCmd(PWLAN_ADAPTER pAdapter)
{
	BOOL Status;
	PBaseHostCmd pCmdPtr = (PBaseHostCmd)pAdapter->m_cmd.pTxBuffer;
	WORD nTxSize = (pCmdPtr->Size & 1) ? pCmdPtr->Size + 5 : pCmdPtr->Size + 4;

	if (pCmdPtr) {
		pAdapter->m_cmd.pTxBuffer = NULL;

		TRACE("Cmd Downloading>>>>>>>>>>\r\n");
#if 0
		{
			int i;

			for (i = 1; i < nTxSize + 1; i ++) {
				TRACE("%02X,", pAdapter->ucCmdBuffer[i - 1]);
				if (i % 16 == 0)
					TRACE("\r\n");
			}
		}
#endif

		Status = If_WriteRegister2(CMD_RDWRPORT_REG, (PVOID)pCmdPtr, nTxSize);
		if (Status)
			Status = If_WriteRegister(CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
		if (!Status) {
			pAdapter->m_cmd.pRxBuffer = NULL;
			pAdapter->m_cmd.nRxSize = 0;
		}
		TRACE("\r\n****Download Over****\r\n\r\n");
	}

	return Status;
}

static WORD CmdProcessCmd(PWLAN_ADAPTER pAdapter, DWORD dwTimeout)
{
	int nLoop = 0;

	//TRACE("cmd=%04x(TxSize=%d) ...\n",nCmd,nTxSize);

	WIFI_CLR_FLAG(pAdapter, FLAG_INTRETURN);

	if (!CmdDownloadCmd(pAdapter))
		return 0;

	// Wait Cmd return
	while (!WIFI_GET_FLAG(pAdapter, FLAG_INTRETURN) && nLoop < 10) {
		delay_ms(1000);
		nLoop ++;
	}

	if (nLoop == 10)
		return 0;

	if (!pAdapter->m_cmd.pRxBuffer) {
		TRACE("CmdProcessCmd: cmd=%04x(nRxSize=0) OK.\r\n", pAdapter->m_cmd.nCommand);
		pAdapter->m_cmd.nRxSize = pAdapter->m_cmd.nTxSize;
	}
	else {
		PBaseHostCmd pCmd = (PBaseHostCmd)pAdapter->m_cmd.pRxBuffer;

		if (!(pCmd->Result == 0 && pCmd->SeqNum == pAdapter->m_cmd.nCmdNo &&
		      pAdapter->m_cmd.nRxSize >= pCmd->Size && pCmd->Command == CmdGetCmdRetCode(pAdapter->m_cmd.nCommand))) {
			pAdapter->m_cmd.nRxSize = 0;
			TRACE("CmdProcessCmd: cmd=%04x(nRxSize=%d) OK.\r\n", pAdapter->m_cmd.nCommand, pAdapter->m_cmd.nRxSize);
		}
	}

	return pAdapter->m_cmd.nRxSize;
}

static void CmdSetCmdInfo(PWLAN_ADAPTER pAdapter, WORD nCmd, PVOID pCmdTx, WORD nTxSize, PVOID pCmdRx, WORD nRxSize)
{
	PBaseHostCmd pCmdPtr = (PBaseHostCmd)pCmdTx;

	pCmdPtr->Command = nCmd;
	pCmdPtr->Size = nTxSize;
	pCmdPtr->SeqNum = ++ pAdapter->m_cmd.nCmdNo;
	pCmdPtr->Result = 0;

	pAdapter->m_cmd.nCommand = nCmd;
	pAdapter->m_cmd.pTxBuffer = pCmdTx;
	pAdapter->m_cmd.nTxSize = nTxSize;
	pAdapter->m_cmd.pRxBuffer = pCmdRx;
	pAdapter->m_cmd.nRxSize = nRxSize ? nRxSize : nTxSize;

	return;
}

static void CmdSetupScanCmd(PWLAN_ADAPTER pAdapter, char* pszSsid)
{
	PBYTE pCur = &pAdapter->m_ucCmdBuffer[0];
	PHostCmd_DS_802_11_SCAN pCmd = (PHostCmd_DS_802_11_SCAN) pCur;

	pCmd->BSSType = HostCmd_BSS_TYPE_ANY;
	FillMemory(pCmd->BSSID, 0xff, sizeof(pCmd->BSSID));
	pCur += MEMBER_OFFSET(HostCmd_DS_802_11_SCAN, SsIdParamSet);

	if (strlen(pszSsid) > 0) {
		MrvlIEtypes_SsIdParamSet_t* pSsid = (MrvlIEtypes_SsIdParamSet_t*)pCur;

		pSsid->Header.Type = TLV_TYPE_SSID;
		pSsid->Header.Len = (USHORT)strlen(pszSsid);
		MoveMemory(pSsid->SsId, pszSsid, strlen(pszSsid));

		pCur += sizeof(pSsid->Header) + pSsid->Header.Len;
	}
	if (1) {
		int i;
		MrvlIEtypes_ChanListParamSet_t* pChanList = (MrvlIEtypes_ChanListParamSet_t*)pCur;
		ChanScanParamSet_t* pChanScan;

		pChanList->Header.Type = TLV_TYPE_CHANLIST;
		pChanList->Header.Len = 0;
		pCur += sizeof(pChanList->Header);
		for (i = CMD_SCAN_CHANNEL_MIN; i <= CMD_SCAN_CHANNEL_MAX; i++) {
			pChanScan = (ChanScanParamSet_t*)pCur;
			pChanScan->ChanNumber = i;
			pChanScan->RadioType = HostCmd_SCAN_RADIO_TYPE_BG;
			pChanScan->ScanType = HostCmd_SCAN_TYPE_ACTIVE;
			pChanScan->MinScanTime = HostCmd_SCAN_MIN_CH_TIME;
			pChanScan->ScanTime = HostCmd_SCAN_MIN_CH_TIME;
			pChanList->Header.Len += sizeof(ChanScanParamSet_t);
			pCur += sizeof(ChanScanParamSet_t);
		}
	}
	if(1) {
		MrvlIEtypes_RatesParamSet_t* pRates=(MrvlIEtypes_RatesParamSet_t*)pCur;

		pRates->Header.Type=TLV_TYPE_RATES;
		pRates->Header.Len=sizeof(m_aSupportRate_G);
		MoveMemory(pRates->Rates, m_aSupportRate_G, pRates->Header.Len);

		pCur+=sizeof(pRates->Header)+pRates->Header.Len;
	}

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_SCAN, pCmd, pCur - (PBYTE)pCmd, pCmd, ADAPTER_CMD_BUFFER_LENGTH);

	return ;
}

static void CmdSetupAssociateCmd(PWLAN_ADAPTER pAdapter, PBSSINFO pBssInfo)
{
	PBYTE pCur = &pAdapter->m_ucCmdBuffer[0];
	PHostCmd_DS_802_11_ASSOCIATE_EXT pCmd = (PHostCmd_DS_802_11_ASSOCIATE_EXT)pCur;

	if (1) {
		IEEEtypes_CapInfo_t cap = *(IEEEtypes_CapInfo_t*)&pBssInfo->IEsFixed.Capabilities;

		cap.QoS = 0;
		MoveMemory(&pCmd->PeerStaAddr, &pBssInfo->Bssid.MacAddress, sizeof(pCmd->PeerStaAddr));
		pCmd->CapInfo = cap;
		pCmd->ListenInterval = 0x14;
		pCmd->BcnPeriod = pBssInfo->IEsFixed.BeaconInterval;
		pCmd->DtimPeriod = 3;

		pCur += MEMBER_OFFSET(HostCmd_DS_802_11_ASSOCIATE_EXT, SsIdParamSet);
	}
	if (1) {
		MrvlIEtypes_SsIdParamSet_t* pSsid = (MrvlIEtypes_SsIdParamSet_t*)pCur;

		pSsid->Header.Type = TLV_TYPE_SSID;
		pSsid->Header.Len = (USHORT)pBssInfo->Bssid.Ssid.SsidLength;
		MoveMemory(pSsid->SsId, pBssInfo->Bssid.Ssid.Ssid, pSsid->Header.Len);

		pCur += sizeof(pSsid->Header) + pSsid->Header.Len;
	}
	if (1) {
		MrvlIEtypes_PhyParamSet_t* pPhy = (MrvlIEtypes_PhyParamSet_t*)pCur;

		pPhy->Header.Type = TLV_TYPE_PHY_DS;
		pPhy->Header.Len = sizeof(pPhy->fh_ds.DsParamSet);
		MoveMemory(&pPhy->fh_ds.DsParamSet, &pBssInfo->nChannel,
		           sizeof(pPhy->fh_ds.DsParamSet));

		pCur += sizeof(pPhy->Header) + pPhy->Header.Len;
	}
	if (1) {
		int f, cbDest;
		PBYTE pDest;
		MrvlIEtypes_RatesParamSet_t* pRate = (MrvlIEtypes_RatesParamSet_t*)pCur;

		pDest = pRate->Rates;
		cbDest = 0;
		for (f = 0; f < sizeof(m_aSupportRate_G); f++)
			pDest[cbDest++] = m_aSupportRate_G[f];
		
		pRate->Header.Type = TLV_TYPE_RATES;
		pRate->Header.Len = cbDest;

		pCur += sizeof(pRate->Header) + pRate->Header.Len;
	}
	if (1)   {
		MrvlIEtypesHeader_t* pHead = (MrvlIEtypesHeader_t*)pCur;

		pHead->Type = TLV_TYPE_TSFTIMESTAMP;
		pHead->Len = sizeof(ULONGLONG) * 2;
		pCur += sizeof(*pHead);
		MoveMemory(pCur, &pBssInfo->nNetworkTSF, sizeof(ULONGLONG));
		pCur += sizeof(ULONGLONG);
		MoveMemory(pCur, &pBssInfo->IEsFixed.Timestamp, sizeof(ULONGLONG));
		pCur += sizeof(ULONGLONG);
	}
	if (1)   {
		MrvlIEtypes_AuthType_t* pAt = (MrvlIEtypes_AuthType_t*)pCur;

		pAt->Header.Type = TLV_TYPE_AUTH_TYPE;
		pAt->Header.Len = sizeof(pAt->AuthType);
		switch (pAdapter->m_CurProfile.AuthMode) {
			case AuthMode_Open:
				pAt->AuthType = Wlan802_11AuthModeOpen;
				break;
			case AuthMode_Shared:
				pAt->AuthType = Wlan802_11AuthModeShared;
				break;
			default:
				pAt->AuthType = (USHORT) - 1;
		}

		pCur += sizeof(pAt->Header) + pAt->Header.Len;
	}

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_ASSOCIATE_EXT, pCmd, pCur - (PBYTE)pCmd, pCmd, ADAPTER_CMD_BUFFER_LENGTH);
}

static void CmdScanInterpret2(PWLAN_ADAPTER pAdapter, PBYTE pCur, PBYTE pEnd, PBSSINFO pBssInfo)
{
	PSrBssDesc pbd = (PSrBssDesc)pCur;
	PNDIS_WLAN_BSSID_EX pBid = (PNDIS_WLAN_BSSID_EX)&pBssInfo->Bssid;
	PNDIS_802_11_FIXED_IEs pFie = &pBssInfo->IEsFixed;
	int nRateCnt = 0;

	TRACE("+CmdScanInterpret2()\r\n");

	TRACE("CmdScanInterpret2: Rssi=%d TsInterval=%04x Cap=%04x\n"
	      "\r\nAP Address=%02x%02x%02x-%02x%02x%02x\n",
	      -(int)(pbd->nRssi & 0x7f), pbd->nTsInterval, pbd->nCapability,
	      pbd->aApPhyAddr[0], pbd->aApPhyAddr[1], pbd->aApPhyAddr[2],
	      pbd->aApPhyAddr[3], pbd->aApPhyAddr[4], pbd->aApPhyAddr[5]);

	MoveMemory(pBid->MacAddress, pbd->aApPhyAddr, sizeof(pBid->MacAddress));
	pBid->Rssi = -(LONG)(pbd->nRssi & 0x7f);
	MoveMemory(pFie->Timestamp, pbd->aTimeStamp, sizeof(pFie->Timestamp));
	pFie->BeaconInterval = pbd->nTsInterval;
	pBid->Configuration.Length = sizeof(NDIS_802_11_CONFIGURATION);
	pBid->Configuration.BeaconPeriod = pbd->nTsInterval;
	pFie->Capabilities = pbd->nCapability;
	if (1) {
		IEEEtypes_CapInfo_t cap;

		*(PUSHORT)(&cap) = pbd->nCapability;
		MoveMemory((void*)&cap, (void*)&pbd->nCapability, sizeof(cap));
		pBid->Privacy = cap.Privacy ? Ndis802_11PrivFilter8021xWEP : Ndis802_11PrivFilterAcceptAll;
		pBid->InfrastructureMode = cap.Ibss ? Ndis802_11IBSS : Ndis802_11Infrastructure;
	}
	pCur += sizeof(SrBssDesc);
	pBssInfo->IELength = sizeof(*pFie);
	if (pCur + 2 < pEnd) {
		ULONG nLen = MIN(pEnd - pCur, sizeof(pBssInfo->IEsVariable));

		pBssInfo->IELength += nLen;
		MoveMemory(pBssInfo->IEsVariable, pCur, nLen);
		pCur = pBssInfo->IEsVariable;
		pEnd = pCur + nLen;
	}
	pBid->Length = MEMBER_OFFSET(NDIS_WLAN_BSSID_EX, IEs) + pBssInfo->IELength;
	pBid->Length = ALIGN_UP(pBid->Length, 4);

	while (pCur + (2 + pCur[1]) <= pEnd) {
		switch (pCur[0]) { //IE Type
			case SSID:
			{
				char szSsid[33];
				
				CopyMemory(szSsid, pCur + 2, pCur[1]);
				szSsid[pCur[1]] = 0;
				TRACE("CmdScanInterpret2: Find SSID(%d,%s)\r\n", pCur[1], szSsid);
				if (pCur[1]) {
					pBid->Ssid.SsidLength = MIN(pCur[1], sizeof(pBid->Ssid.Ssid));
					MoveMemory(pBid->Ssid.Ssid, pCur + 2, pBid->Ssid.SsidLength);
					pBid->Ssid.Ssid[pBid->Ssid.SsidLength] = 0;
				}
				break;
			}
			case SUPPORTED_RATES:
				TRACE("CmdScanInterpret2: Find Rates(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					nRateCnt = MIN(pCur[1], sizeof(pBid->SupportedRates));
					MoveMemory(pBid->SupportedRates, pCur + 2, nRateCnt);
				}
				break;
			case FH_PARAM_SET:
				TRACE("CmdScanInterpret2: Find Frequency Hopping(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					IEEEtypes_FhParamSet_t* pFH = (IEEEtypes_FhParamSet_t*)pCur;
					pBid->NetworkTypeInUse = Ndis802_11FH;
					pBid->Configuration.DSConfig = 0;
					pBid->Configuration.FHConfig.Length = sizeof(NDIS_802_11_CONFIGURATION_FH);
					pBid->Configuration.FHConfig.HopPattern = pFH->HopPattern;
					pBid->Configuration.FHConfig.HopSet = pFH->HopSet;
					pBid->Configuration.FHConfig.DwellTime = pFH->DwellTime;
					pBssInfo->nChannel = 0;
				}
				break;
			case DS_PARAM_SET:
				TRACE("CmdScanInterpret2: Find Direct Spectrum(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					//should add A B G support
					IEEEtypes_DsParamSet_t* pDS = (IEEEtypes_DsParamSet_t *)pCur;
					pBid->NetworkTypeInUse = Ndis802_11OFDM24;
					pBid->Configuration.DSConfig = 2407 + (pDS->CurrentChan * 5);
					pBssInfo->nChannel = pDS->CurrentChan;
					TRACE("CmdScanInterpret2: Find DS Channel %d(%s)\r\n", pDS->CurrentChan, pBid->Ssid.Ssid);
					break;
				}
				break;
			case CF_PARAM_SET:
				TRACE("CmdScanInterpret2: CF(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					pBssInfo->pCfParamSet = (IEEEtypes_CfParamSet_t*)pCur;
				}
				break;
			case IBSS_PARAM_SET:
				TRACE("CmdScanInterpret2: IBSS(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					IEEEtypes_IbssParamSet_t* pIbss = (IEEEtypes_IbssParamSet_t*)pCur;
					pBid->Configuration.ATIMWindow = pIbss->AtimWindow;
					pBssInfo->pIbssParamSet = pIbss;
				}
				break;
			case COUNTRY_INFO:
				TRACE("CmdScanInterpret2: Country(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					pBssInfo->pCountryInfo = (IEEEtypes_CountryInfoFullSet_t*)pCur;
				}
				break;
			case ERP_INFO:
				TRACE("CmdScanInterpret2: ERP(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					IEEEtypes_ERPInfo_t* pERP = (IEEEtypes_ERPInfo_t*)pCur;
					pBssInfo->nERPFlags = pERP->ERPFlags;
				}
				break;
			case EXTENDED_SUPPORTED_RATES:
				TRACE("CmdScanInterpret2: Extend supported rates(%d)\r\n", pCur[1]);
				if (pCur[1] && nRateCnt) {
					int nRateCnt2 = MIN(pCur[1], sizeof(pBid->SupportedRates) - nRateCnt);
					MoveMemory((PBYTE)(pBid->SupportedRates) + nRateCnt, pCur + 2, nRateCnt2);
				}
				break;
			case ELE_CISCO_CLIENT_TX_PWR:
				TRACE("CmdScanInterpret2: ccx tpc(%d)\r\n", pCur[1]);
				if (pCur[1]) {
					// need to do
				}
				break;
		}
		pCur += 2 + pCur[1]; //IE Length;
	}
	TRACE("-CmdScanInterpret2()\r\n");
}

static CMD_STATUS CmdScanInterpret(PWLAN_ADAPTER pAdapter, PBYTE pCur, int nSize, PBSSINFO pBssInfo)
{
	PBYTE pEnd, pEnd2 = pCur + nSize;
	PSrBssDesc pbd;

	if (pBssInfo) {
		ZeroMemory(pBssInfo, sizeof(BSSINFO));
		while (pCur < pEnd2) {
			pbd = (PSrBssDesc)(pCur);
			pEnd = pCur + (2 + pbd->nSize);
			CmdScanInterpret2(pAdapter, pCur, pEnd, pBssInfo);
			pCur = pEnd;
		}
	}

	return CMD_ERROR_SUCCESS;
}

static void CmdSetupWepKeyCmd(PWLAN_ADAPTER pAdapter, USHORT nCmdAct)
{
	PBYTE pCur = &pAdapter->m_ucCmdBuffer[0];
	PHostCmd_DS_802_11_SET_WEP pCmd = (PHostCmd_DS_802_11_SET_WEP)pCur;

	ZeroMemory(pCmd, sizeof(*pCmd));
	pCmd->Action = nCmdAct;
	if (nCmdAct == HostCmd_ACT_ADD) {
		BYTE nWepType;

		pCmd->KeyIndex = 0;
		switch (g_pWlanAdapter->m_KeyMaterial.ucKeyLength) {
			case 5:
				nWepType = HostCmd_TYPE_WEP_40_BIT;
				break;
			case 13:
				nWepType = HostCmd_TYPE_WEP_104_BIT;
				break;
			case 16:
				nWepType = HostCmd_TYPE_WEP_128_BIT;
				break;
			default:
				nWepType = HostCmd_TYPE_WEP_40_BIT;
		}
		//TRACE("Wlan.CmdSetWep: KI=%d,KM=%08x,nLen=%04x\n",pCmd->KeyIndex,pWep->KeyMaterial,pWep->KeyLength);
		*(PBYTE)(&pCmd->WEPTypeForKey1 + pCmd->KeyIndex) = nWepType;
		MoveMemory(pCmd->WEP1 + 16 * pCmd->KeyIndex,
		           g_pWlanAdapter->m_KeyMaterial.ucMaterial,
		           g_pWlanAdapter->m_KeyMaterial.ucKeyLength);

		TRACE("KeyLength: 0x%08X\r\n", g_pWlanAdapter->m_KeyMaterial.ucKeyLength);
		TRACE("WepType: 0x%08X\r\n", nWepType);
		{
			DWORD i;

			TRACE("KeyMaterial:\r\n");
			for (i = 0; i < g_pWlanAdapter->m_KeyMaterial.ucKeyLength; i ++)
				TRACE("0x%02X,", g_pWlanAdapter->m_KeyMaterial.ucMaterial[i]);
			TRACE("\r\n");
		}

		/*      // No need to do this???
		        if(pAdapter->m_WepKey.ulKeyIndex & 0x80000000) {
		            pAdapter->m_nic.nTxKeyIndex=pCmd->KeyIndex;
		            pAdapter->m_nic.nTxKeyLength=pAdapter->m_WepKey.ulKeyLength;
		            MoveMemory(pAdapter->m_nic.aTxKeyMaterial, pAdapter->m_WepKey.ucKeyMaterial, pAdapter->m_WepKey.ulKeyLength);
		        }
		        else if(pAdapter->m_nic.nTxKeyLength) {
		            switch(pAdapter->m_nic.nTxKeyLength) {
		                case 5:nWepType=HostCmd_TYPE_WEP_40_BIT;break;
		                case 13:nWepType=HostCmd_TYPE_WEP_104_BIT;break;
		                case 16:nWepType=HostCmd_TYPE_WEP_128_BIT;break;
		                default:nWepType=HostCmd_TYPE_WEP_40_BIT;
		            }
		            pCmd->KeyIndex=pAdapter->m_nic.nTxKeyIndex;
		            *(PBYTE)(&pCmd->WEPTypeForKey1+pCmd->KeyIndex)=nWepType;
		            MoveMemory(pCmd->WEP1+16*pCmd->KeyIndex,pAdapter->m_nic.aTxKeyMaterial,pAdapter->m_nic.nTxKeyLength);
		        }
		*/
	}
	else if (nCmdAct == HostCmd_ACT_REMOVE) {
		WORD nKeyIndex = 0;

		// ????
		//pAdapter->m_nic.nTxKeyIndex=nKeyIndex;
		//pAdapter->m_nic.nTxKeyLength=0;
		//ZeroMemory(pAdapter->m_nic.aTxKeyMaterial,sizeof(pAdapter->m_nic.aTxKeyMaterial));
		*(PBYTE)(pCmd->WEP1 + 16 * nKeyIndex) = 0xff;
	}

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_SET_WEP, pCmd, sizeof(*pCmd), pCmd, 0);
}

//--------------------------------------------------------------------
// Functions exported
//--------------------------------------------------------------------
void CmdOnCmdUpLdRdy(PWLAN_ADAPTER pAdapter)
{
	if (pAdapter->m_cmd.pRxBuffer) {
		WORD nSize;
		BOOL rc = If_ReadRegister(SCRATCH_2_REG, &nSize) == sizeof(WORD);

		if (rc) {
			WORD nSize2;

			ZeroMemory(pAdapter->m_cmd.pRxBuffer, pAdapter->m_cmd.nRxSize);
			if (nSize > pAdapter->m_cmd.nRxSize)
				nSize = pAdapter->m_cmd.nRxSize;
			nSize2 = nSize & 1 ? nSize + 1 : nSize;
			rc = If_ReadRegister2(CMD_RDWRPORT_REG, pAdapter->m_cmd.pRxBuffer, nSize2) == nSize2;
			//rc = Hw_ReadData(CMD_RDWRPORT_REG, (WORD*)pAdapter->m_cmd.pRxBuffer, nSize2);
		}
		if (rc)
			pAdapter->m_cmd.nRxSize = nSize;
		else {
			pAdapter->m_cmd.nRxSize = nSize;
			pAdapter->m_cmd.pRxBuffer = NULL;
		}
	}
	If_WriteRegister(CARD_INT_CAUSE_REG, CIC_CmdUpLdOvr);
}

CMD_STATUS CmdSsidScan(PWLAN_ADAPTER pAdapter, char* pszSsid, PBSSINFO pBssInfo)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	// Setup command
	CmdSetupScanCmd(pAdapter, pszSsid);
	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (nRet) {
		PHostCmd_DS_802_11_SCAN_RSP pCmdR = (PHostCmd_DS_802_11_SCAN_RSP)pAdapter->m_cmd.pRxBuffer;

		if (pBssInfo && pCmdR->NumberOfSets) {
			nRet = MIN(pCmdR->BSSDescriptSize, nRet - sizeof(*pCmdR));
			CmdScanInterpret(pAdapter, (PBYTE)(pCmdR + 1), nRet, pBssInfo);
		}
	}
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdAssociateExt(PWLAN_ADAPTER pAdapter, PBSSINFO pBssInfo)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	TRACE("+CmdAssociateExt()\r\n");

	// Setup command
	CmdSetupAssociateCmd(pAdapter, pBssInfo);
	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (nRet) {
		PHostCmd_DS_802_11_ASSOCIATE_RESULT pCmdR = (PHostCmd_DS_802_11_ASSOCIATE_RESULT)&pAdapter->m_ucCmdBuffer[0];

		//TRACEDATA("CmdAssocData",pCmd,pCur-PBYTE(pCmd));
		stat = (nRet >= sizeof(*pCmdR) && pCmdR->StatusCode == 0) ? CMD_ERROR_SUCCESS : CMD_ERROR_UNKNOWN;
		TRACE("Wlan.CmdAssociateExt: rc=%08x,SC=%04x,AID=%04x\r\n", nRet, pCmdR->StatusCode, pCmdR->AssociationID, pCmdR->AssociationID);
		if (stat == CMD_ERROR_SUCCESS) {
			PNDIS_802_11_ASSOCIATION_INFORMATION pAI = (PNDIS_802_11_ASSOCIATION_INFORMATION)pAdapter->m_ucAssocInfo;
			int nBufLen, nIeLen = (int)pCmdR->Size - MEMBER_OFFSET(HostCmd_DS_802_11_ASSOCIATE_RESULT, IELength);

			pAI->ResponseFixedIEs.Capabilities = pCmdR->CapInfo;
			pAI->ResponseFixedIEs.StatusCode = pCmdR->StatusCode;
			pAI->ResponseFixedIEs.AssociationId = pCmdR->AssociationID;
			pAI->AvailableResponseFixedIEs |= NDIS_802_11_AI_RESFI_CAPABILITIES;
			pAI->AvailableResponseFixedIEs |= NDIS_802_11_AI_RESFI_STATUSCODE;
			pAI->AvailableResponseFixedIEs |= NDIS_802_11_AI_RESFI_ASSOCIATIONID;

			nBufLen = (int)sizeof(pAdapter->m_ucAssocInfo) - (int)pAI->OffsetResponseIEs;
			nIeLen = MAX(0, MIN(nBufLen, nIeLen));
			MoveMemory((void*)((PBYTE)pAI + pAI->OffsetResponseIEs), (void*)&pCmdR->IELength, nIeLen);
			pAI->ResponseIELength = (ULONG)nIeLen;

			WIFI_SET_FLAG(pAdapter, FLAG_MEDIA_CONNECTED);
		}
	}
	else
		stat = CMD_ERROR_UNKNOWN;

	CmdReleaseBuffer(pAdapter);

	TRACE("-CmdAssociateExt()\r\n");

	return stat;
}

CMD_STATUS CmdSetWepKey(PWLAN_ADAPTER pAdapter, USHORT nCmdAct)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	// Setup command
	CmdSetupWepKeyCmd(pAdapter, nCmdAct);
	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet) {
		stat = CMD_ERROR_UNKNOWN;
	}
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdDeauthenticate(PWLAN_ADAPTER pAdapter, PBSSINFO pBssInfo)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_802_11_DEAUTHENTICATE pCmd = (PHostCmd_DS_802_11_DEAUTHENTICATE)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	// Setup command
	MoveMemory(&pCmd->MacAddr, &pBssInfo->Bssid.MacAddress, sizeof(pCmd->MacAddr));
	pCmd->ReasonCode = 3; //Station is leaving
	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_DEAUTHENTICATE, pCmd, sizeof(*pCmd), pCmd, 0);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet)
		stat = CMD_ERROR_UNKNOWN;
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdMacAddress(PWLAN_ADAPTER pAdapter, USHORT nCmdAct, NDIS_802_11_MAC_ADDRESS* pMA)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_CMD_MAC_ADDRESS pCmd = (PHostCmd_DS_CMD_MAC_ADDRESS)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	pCmd->Action = nCmdAct;
	if (nCmdAct == CMD_ACT_SET) {
		MoveMemory(pCmd->MacAddress, pMA, sizeof(pCmd->MacAddress));
		TRACE("Setting MAC Addr: %02X-%02X-%02X-%02X-%02X-%02X\r\n", pMA[0], pMA[1], pMA[2], pMA[3], pMA[4], pMA[5]);
	}
	CmdSetCmdInfo(pAdapter, HostCmd_CMD_MAC_ADDRESS, pCmd, sizeof(*pCmd), pCmd, ADAPTER_CMD_BUFFER_LENGTH);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet)
		stat = CMD_ERROR_UNKNOWN;

	if (nCmdAct == CMD_ACT_GET) {
		MoveMemory(pMA, pCmd->MacAddress, sizeof(*pMA));
		TRACE("Got MAC Addr: %02X-%02X-%02X-%02X-%02X-%02X\r\n", pCmd->MacAddress[0], pCmd->MacAddress[1], pCmd->MacAddress[2], pCmd->MacAddress[3], pCmd->MacAddress[4], pCmd->MacAddress[5]);
	}
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdGSpiBusCfg(PWLAN_ADAPTER pAdapter, USHORT nCmdAct, PUSHORT pnDataClk, PUSHORT pnRegClk)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_CMD_GSPI_BUS_CONFIG pCmd = (PHostCmd_DS_CMD_GSPI_BUS_CONFIG)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	pCmd->Action = nCmdAct;
	if (nCmdAct == CMD_ACT_SET) {
		pCmd->BusDelayMode = 0x06 | B_BIT_4;
		pCmd->HostTimeDelayToReadPort = (*pnDataClk) * 16;
		pCmd->HostTimeDelayToReadregister = (*pnRegClk) * 16;
	}

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_GSPI_BUS_CONFIG, pCmd, sizeof(*pCmd), pCmd, ADAPTER_CMD_BUFFER_LENGTH);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet)
		stat = CMD_ERROR_UNKNOWN;
	else if (nCmdAct == CMD_ACT_GET) {
		*pnDataClk = pCmd->HostTimeDelayToReadPort / 16;
		*pnRegClk = pCmd->HostTimeDelayToReadregister / 16;
	}
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdSubscribeEvent(PWLAN_ADAPTER pAdapter)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_802_11_SUBSCRIBE_EVENT pCmd = (PHostCmd_DS_802_11_SUBSCRIBE_EVENT)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	pCmd->Action = CMD_ACT_SET;
	pCmd->Events = RSSI_LOW | LINK_LOSS; //|RSSI_HIGH;
	pCmd->RssiLow.Header.Type = TLV_TYPE_RSSI;
	pCmd->RssiLow.Header.Len  = TLV_PAYLOAD_SIZE;
	pCmd->RssiLow.RSSIValue   = 68;//UCHAR(-m_cmd.nRssiLowValue);//68;
	pCmd->RssiLow.RSSIFreq    = 16;

	pCmd->SnrLow.Header.Type = TLV_TYPE_SNR;
	pCmd->SnrLow.Header.Len  = TLV_PAYLOAD_SIZE;
	pCmd->SnrLow.SNRValue    = 0;
	pCmd->SnrLow.SNRFreq     = 0;

	pCmd->FailCnt.Header.Type = TLV_TYPE_FAILCOUNT;
	pCmd->FailCnt.Header.Len  = TLV_PAYLOAD_SIZE;
	pCmd->FailCnt.FailValue   = 0;
	pCmd->FailCnt.FailFreq    = 0;

	pCmd->BcnMiss.Header.Type  = TLV_TYPE_BCNMISS;
	pCmd->BcnMiss.Header.Len   = TLV_PAYLOAD_SIZE;
	pCmd->BcnMiss.BeaconMissed = LINK_LOST_BEACONCNT;
	pCmd->BcnMiss.Reserved     = 0;

	pCmd->RssiHigh.Header.Type = TLV_TYPE_RSSI_HIGH;
	pCmd->RssiHigh.Header.Len  = TLV_PAYLOAD_SIZE;
	pCmd->RssiHigh.RSSIValue   = 58;//UCHAR(-(m_cmd.nRssiLowValue+m_mgr.nRoamingRssiDiffH));//58;
	pCmd->RssiHigh.RSSIFreq    = 16;

	pCmd->SnrHigh.Header.Type = TLV_TYPE_SNR_HIGH;
	pCmd->SnrHigh.Header.Len  = TLV_PAYLOAD_SIZE;
	pCmd->SnrHigh.SNRValue    = 0;
	pCmd->SnrHigh.SNRFreq     = 0;

	pCmd->PreBcnMiss.Header.Type      = TLV_TYPE_PREBCNMISS;
	pCmd->PreBcnMiss.Header.Len       = TLV_PAYLOAD_SIZE;
	pCmd->PreBcnMiss.PreBeaconMissed  = 0;
	pCmd->PreBcnMiss.Reserved         = 0;

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_SUBSCRIBE_EVENT, pCmd, sizeof(*pCmd), pCmd, 0);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet)
		stat = CMD_ERROR_UNKNOWN;
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdMacControl(PWLAN_ADAPTER pAdapter, USHORT nCmdAct)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_MAC_CONTROL pCmd = (PHostCmd_DS_MAC_CONTROL)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;

	if (stat != CMD_ERROR_SUCCESS)
		return stat;

	TRACE("CmdMacControl: Action=0x%04x\r\n", nCmdAct);

	// Setup command
	pCmd->Action = nCmdAct;

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_MAC_CONTROL, pCmd, sizeof(*pCmd), pCmd, 0);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (!nRet)
		stat = CMD_ERROR_UNKNOWN;
	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdListScan(PWLAN_ADAPTER pAdapter, char* pszSsid)
{

	return CMD_ERROR_SUCCESS;
}

CMD_STATUS CmdBssidScan(PWLAN_ADAPTER pAdapter, char* pszSsid)
{

	return CMD_ERROR_SUCCESS;
}

CMD_STATUS CmdAdHocStart(PWLAN_ADAPTER pAdapter, PBSSINFO pBssInfo)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PHostCmd_DS_802_11_AD_HOC_START pCmd = (PHostCmd_DS_802_11_AD_HOC_START)&pAdapter->m_ucCmdBuffer[0];
	PHostCmd_DS_802_11_AD_HOC_RESULT pCmdR = (PHostCmd_DS_802_11_AD_HOC_RESULT)(pCmd+1);
	PNDIS_WLAN_BSSID_EX pBid = (PNDIS_WLAN_BSSID_EX)(&pBssInfo->Bssid);
	PNDIS_802_11_FIXED_IEs pFie = &pBssInfo->IEsFixed;
	WORD nRet;

	ZeroMemory(pCmd,sizeof(*pCmd));
	//Configure Cmd Parameters
	strcpy((char*)pCmd->SSID, pAdapter->m_CurProfile.szSSID);
	pCmd->BSSType = HostCmd_BSS_TYPE_IBSS;
	pCmd->BeaconPeriod = cmdAdhocBacconPeriod;
	pCmd->DTIMPeriod = (UCHAR)cmdPsNumDtims;
	pCmd->SsParamSet.IbssParamSet.ElementId = IBSS_PARAM_SET;
	pCmd->SsParamSet.IbssParamSet.Len = 2;
	pCmd->SsParamSet.IbssParamSet.AtimWindow = cmdAdhocAtimWindow;
	pCmd->PhyParamSet.DsParamSet.ElementId = DS_PARAM_SET;
	pCmd->PhyParamSet.DsParamSet.Len = 1;
	pCmd->PhyParamSet.DsParamSet.CurrentChan = cmdAdhocChannel;
	pCmd->ProbeDelay = HostCmd_SCAN_PROBE_DELAY_TIME; 
	pCmd->Cap.Ibss = 1;
	pCmd->Cap.ShortPreamble = 1;
	pCmd->Cap.Privacy = (pAdapter->m_CurProfile.EncMode== EncryMode_WEP?1:0);
	MoveMemory(pCmd->BasicDataRates, m_aSupportRate_G, sizeof(m_aSupportRate_G));  

	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_AD_HOC_START, pCmd, sizeof(*pCmd), pCmd + 1, ADAPTER_CMD_BUFFER_LENGTH - sizeof(*pCmd));

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (nRet < sizeof(*pCmdR))
		stat = CMD_ERROR_UNKNOWN;

	if(stat == CMD_ERROR_SUCCESS) {
		ZeroMemory(pBssInfo,sizeof(*pBssInfo));
		//Configure BssInfo
		MoveMemory(pBid->MacAddress,pCmdR->BSSID,sizeof(pBid->MacAddress));
		pBssInfo->nScanCounter = 0; //////???
		pBssInfo->IELength=sizeof(*pFie);
		pBid->Rssi = -10;
		pBid->Configuration.Length=sizeof(NDIS_802_11_CONFIGURATION);
		MoveMemory(&pFie->Capabilities,&pCmd->Cap,sizeof(pFie->Capabilities));
		pBid->Privacy = pAdapter->m_CurProfile.EncMode== EncryMode_WEP?
			Ndis802_11PrivFilter8021xWEP:Ndis802_11PrivFilterAcceptAll;
		pBid->InfrastructureMode = Ndis802_11IBSS;
		pBid->Ssid.SsidLength = strlen(pAdapter->m_CurProfile.szSSID);
		MoveMemory(pBid->Ssid.Ssid, pAdapter->m_CurProfile.szSSID, strlen(pAdapter->m_CurProfile.szSSID));
		if(1) {
			INT nLen = 2 + pCmd->PhyParamSet.DsParamSet.Len;
			PBYTE pCur = (PBYTE)(&pBssInfo->IEsFixed) + pBssInfo->IELength;
			IEEEtypes_DsParamSet_t* pDS = (IEEEtypes_DsParamSet_t *)pCur;

			MoveMemory(pDS, &pCmd->PhyParamSet.DsParamSet, nLen);
			pBid->NetworkTypeInUse = Ndis802_11OFDM24;
			pBid->Configuration.DSConfig = 2407+(pDS->CurrentChan*5);
			pBssInfo->nChannel = pDS->CurrentChan;
			pBssInfo->IELength += nLen;
		}
		if(1) {
			INT nLen = 2 + pCmd->SsParamSet.IbssParamSet.Len;
			PBYTE pCur = (PBYTE)(&pBssInfo->IEsFixed) + pBssInfo->IELength;
			IEEEtypes_IbssParamSet_t* pIbss = (IEEEtypes_IbssParamSet_t*)pCur;

			MoveMemory(pIbss,&pCmd->SsParamSet.IbssParamSet,nLen);
			pBssInfo->pIbssParamSet = pIbss;
			pBssInfo->IELength += nLen;
		}
		pBid->Length = MEMBER_OFFSET(NDIS_WLAN_BSSID_EX, IEs)+pBssInfo->IELength;
		pBid->Length = (pBid->Length+3) & ~3;
	}

	CmdReleaseBuffer(pAdapter);
	
	return stat;
}

CMD_STATUS CmdAdHocStop(PWLAN_ADAPTER pAdapter)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	PBaseHostCmd pCmd = (PBaseHostCmd)&pAdapter->m_ucCmdBuffer[0];
	WORD nRet;
	
	CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_AD_HOC_STOP, pCmd, sizeof(*pCmd), pCmd, ADAPTER_CMD_BUFFER_LENGTH);

	nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
	if (nRet != sizeof(*pCmd))
		stat = CMD_ERROR_UNKNOWN;

	CmdReleaseBuffer(pAdapter);

	return stat;
}

CMD_STATUS CmdSetTxPowerLevel(PWLAN_ADAPTER pAdapter, USHORT nPowerLevel)
{
	CMD_STATUS stat = CmdQueryBuffer(pAdapter);
	WORD nRet;

	if (1) {
		OID_MRVL_DS_TPC_CFG cfg;
		POID_MRVL_DS_TPC_CFG pTpcCfg = &cfg;
		PHostCmd_DS_802_11_TPC_CFG pCmd = (PHostCmd_DS_802_11_TPC_CFG)&pAdapter->m_ucCmdBuffer[0];
		
		ZeroMemory(&cfg,sizeof(cfg));
		pCmd->Action = CMD_ACT_SET;
		MoveMemory(&pCmd->Enable, &pTpcCfg->Enable,sizeof(*pCmd)-MEMBER_OFFSET(HostCmd_DS_802_11_TPC_CFG,Enable));

		CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_TPC_CFG, pCmd, sizeof(*pCmd), pCmd, ADAPTER_CMD_BUFFER_LENGTH);
		nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
		if (nRet != sizeof(*pCmd))
			stat = CMD_ERROR_UNKNOWN;
	}

	if(1) { //stat == CMD_ERROR_SUCCESS) {
		USHORT bEnablePA=TRUE;
		int nTxSize;
		MrvlIEtypes_PowerAdapt_Group_t iePag;
		MrvlIEtypes_PowerAdapt_Group_t* pIePag = &iePag;
		PHostCmd_DS_802_11_POWER_ADAPT_CFG_EXT pCmd = (PHostCmd_DS_802_11_POWER_ADAPT_CFG_EXT)&pAdapter->m_ucCmdBuffer[0];

		iePag.Header.Type=0x114;
		iePag.Header.Len=sizeof(PA_Group_t)*3;
		iePag.PA_Group[0].PowerAdaptLevel = nPowerLevel;
		iePag.PA_Group[0].RateBitmap=0x1800;
		iePag.PA_Group[1].PowerAdaptLevel = nPowerLevel;
		iePag.PA_Group[1].RateBitmap=0x07e0;
		iePag.PA_Group[2].PowerAdaptLevel = nPowerLevel;
		iePag.PA_Group[2].RateBitmap=0x000f;
	
		pCmd->Action = CMD_ACT_SET;
		pCmd->EnablePA = bEnablePA;
		MoveMemory(&pCmd->PowerAdaptGroup,pIePag,sizeof(*pIePag));
		nTxSize = MEMBER_OFFSET(HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT,PowerAdaptGroup);
		nTxSize+=sizeof(pCmd->PowerAdaptGroup.Header)+pCmd->PowerAdaptGroup.Header.Len;

		CmdSetCmdInfo(pAdapter, HostCmd_CMD_802_11_POWER_ADAPT_CFG_EXT, pCmd, nTxSize, pCmd, ADAPTER_CMD_BUFFER_LENGTH);
		nRet = CmdProcessCmd(pAdapter, CMD_TIMEOUT_MAX);
		if (nRet != nTxSize)
			stat = CMD_ERROR_UNKNOWN;
	}

	CmdReleaseBuffer(pAdapter);

	return stat;
}

