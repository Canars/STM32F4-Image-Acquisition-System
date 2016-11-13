/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "WiFiCommand.h"

int _ParseLine (char *pLine, char *argv[])
{
	int nargs = 0;

	while (nargs < WIFICMD_MAXARGS) {
		while ((*pLine == ' ') || (*pLine == '\t')) {
			++ pLine;
		}
		if (*pLine == '\0') {
			argv[nargs] = NULL;
			return (nargs);
		}

		argv[nargs++] = pLine;

		while (*pLine && (*pLine != ' ') && (*pLine != '\t')) {
			++ pLine;
		}

		if (*pLine == '\0') {
			argv[nargs] = NULL;
			return (nargs);
		}

		*pLine++ = '\0';
	}

	return (nargs);
}

int _DoSetCmd (char *pszCmd, char* pszParam)
{
	int nRet = WIFICMD_RESULT_SUCCESS;

	if (!strcmp (pszCmd, "ssid")) {
		if ((strlen(pszParam) == 0) || (strlen(pszParam) > 32))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, szSSID), (PBYTE)pszParam, strlen(pszParam) + 1);
	}
	else if (!strcmp (pszCmd, "networktype")) {
		NETWORKTYPE type = (NETWORKTYPE)0;

		if (!strcmp(pszParam, "infra"))
			type = NetworkType_Infrastructure;
		else if ((!strcmp(pszParam, "adhoc")))
			type = NetworkType_AdHoc;

		if (!type)
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, NetworkType), (PBYTE)&type, sizeof(NETWORKTYPE));
	}
	else if (!strcmp (pszCmd, "authmode")) {
		AUTHMODE mode = (AUTHMODE)0;

		if (!strcmp(pszParam, "open"))
			mode = AuthMode_Open;
		else if ((!strcmp(pszParam, "shared")))
			mode = AuthMode_Shared;

		if (!mode)
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, AuthMode), (PBYTE)&mode, sizeof(AUTHMODE));
	}
	else if (!strcmp (pszCmd, "encrymode")) {
		ENCRYMODE mode = (ENCRYMODE)0;

		if (!strcmp(pszParam, "disable"))
			mode = EncryMode_Disable;
		else if ((!strcmp(pszParam, "wep")))
			mode = EncryMode_WEP;

		if (!mode)
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, EncMode), (PBYTE)&mode, sizeof(ENCRYMODE));
	}
	else if (!strcmp (pszCmd, "keyascii")) {
		if ((strlen(pszParam) == 0) || (strlen(pszParam) > 64))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, szKey), (PBYTE)pszParam, strlen(pszParam) + 1);
	}
	else if (!strcmp (pszCmd, "macaddr")) {
		UCHAR ucMac[6];

		if (!WlanMisc_String2Mac(pszParam, ucMac))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ucMacAddr), (PBYTE)ucMac, 6);
	}
	else if (!strcmp (pszCmd, "ipaddr")) {
		ULONG ulIp;

		if (!WlanMisc_String2Ip(pszParam, &ulIp))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulIP), (PBYTE)&ulIp, sizeof(ULONG));
	}
	else if (!strcmp (pszCmd, "subnet")) {
		ULONG ulSubNet;

		if (!WlanMisc_String2Ip(pszParam, &ulSubNet))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulSubNet), (PBYTE)&ulSubNet, sizeof(ULONG));
	}
	else if (!strcmp (pszCmd, "gatewayipaddr")) {
		ULONG ulGatewayIp;

		if (!WlanMisc_String2Ip(pszParam, &ulGatewayIp))
			nRet = WIFICMD_RESULT_ERRORPARAM;
		else
			Flash_Write8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulGatewayIp), (PBYTE)&ulGatewayIp, sizeof(ULONG));
	}
	else
		nRet = WIFICMD_RESULT_UNKNOWOPTION;

	return nRet;
}

int _DoGetCmd (char *pszCmd, char* pszParam)
{
	int nRet = WIFICMD_RESULT_SUCCESS;

	if (!strcmp (pszCmd, "ssid")) {
		char szSSID[33];

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, szSSID), (PBYTE)szSSID, 33);
		if ((strlen(szSSID) == 0) || (strlen(szSSID) > 32))
			nRet = WIFICMD_RESULT_PARAMNOTSET;
		else
			strcpy (pszParam, szSSID);
	}
	else if (!strcmp (pszCmd, "networktype")) {
		NETWORKTYPE type = (NETWORKTYPE)0;

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, NetworkType), (PBYTE)&type, sizeof(NETWORKTYPE));

		if (type == NetworkType_Infrastructure)
			strcpy (pszParam, "infra");
		else if (type == NetworkType_AdHoc)
			strcpy (pszParam, "adhoc");
		else
			nRet = WIFICMD_RESULT_PARAMNOTSET;
	}
	else if (!strcmp (pszCmd, "authmode")) {
		AUTHMODE mode = (AUTHMODE)0;

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, AuthMode), (PBYTE)&mode, sizeof(AUTHMODE));

		if (mode == AuthMode_Open)
			strcpy (pszParam, "open");
		else if (mode == AuthMode_Shared)
			strcpy (pszParam, "shared");
		else
			nRet = WIFICMD_RESULT_PARAMNOTSET;
	}
	else if (!strcmp (pszCmd, "encrymode")) {
		ENCRYMODE mode = (ENCRYMODE)0;

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, EncMode), (PBYTE)&mode, sizeof(ENCRYMODE));

		if (mode == EncryMode_Disable)
			strcpy (pszParam, "disable");
		else if (mode == EncryMode_WEP)
			strcpy (pszParam, "wep");
		else
			nRet = WIFICMD_RESULT_PARAMNOTSET;
	}
	else if (!strcmp (pszCmd, "keyascii")) {
		char szKey[65];

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, szKey), (PBYTE)&szKey, 65);
		if ((strlen(szKey) == 0) || (strlen(szKey) > 64))
			nRet = WIFICMD_RESULT_PARAMNOTSET;
		else
			strcpy (pszParam, szKey);
	}
	else if (!strcmp (pszCmd, "macaddr")) {
		UCHAR ucMac[6];

		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ucMacAddr), (PBYTE)&ucMac, 6);
		sprintf (pszParam, "%02X:%02X:%02X:%02X:%02X:%02X", ucMac[0], ucMac[1], ucMac[2], ucMac[3], ucMac[4], ucMac[5]);
	}
	else if (!strcmp (pszCmd, "ipaddr")) {
		ULONG ulIp;
		UCHAR ucIp[4];
		
		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulIP), (PBYTE)&ulIp, sizeof(ULONG));
		DWORD2IP(ulIp, ucIp);
		sprintf (pszParam, "%d.%d.%d.%d", ucIp[0], ucIp[1], ucIp[2], ucIp[3]);
	}
	else if (!strcmp (pszCmd, "subnet")) {
		ULONG ulSubNet;
		UCHAR ucIp[4];
		
		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulSubNet), (PBYTE)&ulSubNet, sizeof(ULONG));
		DWORD2IP(ulSubNet, ucIp);
		sprintf (pszParam, "%d.%d.%d.%d", ucIp[0], ucIp[1], ucIp[2], ucIp[3]);
	}
	else if (!strcmp (pszCmd, "gatewayipaddr")) {
		ULONG ulGatewayIp;
		UCHAR ucIp[4];
		
		Flash_Read8BitData(WIFI_PROFILE_ADDR + MEMBER_OFFSET(WiFiProfile, ulGatewayIp), (PBYTE)&ulGatewayIp, sizeof(ULONG));
		DWORD2IP(ulGatewayIp, ucIp);
		sprintf (pszParam, "%d.%d.%d.%d", ucIp[0], ucIp[1], ucIp[2], ucIp[3]);
	}
	else
		nRet = WIFICMD_RESULT_UNKNOWOPTION;

	return nRet;
}

int _DoCtrlCmd (char *pszCmd, char* pszParam)
{
	int nRet = WIFICMD_RESULT_SUCCESS;

	if (!strcmp (pszCmd, "scan")) {
	}
	else if (!strcmp (pszCmd, "connect")) {
		WiFiApi_ProcessAssoc ();
	}
	else if (!strcmp (pszCmd, "disconnect")) {
	}
	else
		nRet = WIFICMD_RESULT_UNKNOWOPTION;

	return nRet;
}

int WiFiCmd_RunCommand (char *pLine)
{
	char *argv[WIFICMD_MAXARGS], szLineCopy[128];
	int nRet = WIFICMD_RESULT_SUCCESS;

	strcpy (szLineCopy, pLine);
	_ParseLine(szLineCopy, argv);
	if (!strcmp (argv[0], "set"))
		nRet = _DoSetCmd (argv[1], argv[2]);
	else if (!strcmp (argv[0], "get")) {
		char szBuffer[128];
		
		nRet = _DoGetCmd (argv[1], szBuffer);
		if (nRet == WIFICMD_RESULT_PARAMNOTSET)
			Console_Print ("notset\r\n");
		else if (nRet == WIFICMD_RESULT_UNKNOWOPTION)
			Console_Print ("Unknown option.\r\n");
		else
			Console_Print (szBuffer);
	}
	else if (!strcmp (argv[0], "ctrl"))
		nRet = _DoCtrlCmd (argv[1], argv[2]);
	else
		nRet = WIFICMD_RESULT_UNKNOWCMD;

	if (nRet == WIFICMD_RESULT_UNKNOWCMD)
		Console_Print ("Unknown command.\r\n");
	else if (nRet == WIFICMD_RESULT_UNKNOWOPTION)
		Console_Print ("Unknown option.\r\n");
	else if (nRet == WIFICMD_RESULT_ERRORPARAM)
		Console_Print ("Parameter error.\r\n");
	else
		Console_Print("Process OK.\r\n");

	return nRet;
}
