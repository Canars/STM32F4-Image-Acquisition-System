/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "WlanMisc.h"

//--------------------------------------------------------------------
// Exported functions
//--------------------------------------------------------------------
#define HEX(c)  ((c)<='9'?(c)-'0':(c)<='F'?(c)-'A'+0xA:(c)-'a'+0xA)

UCHAR WlanMisc_ASCII2WEPKey(CHAR *pszKeyASCII, UCHAR *pucKeyMaterial)
{
	UCHAR ucSize = (UCHAR)strlen(pszKeyASCII);

	TRACE("+SetWEPKey()\r\n");

	switch (ucSize) {
		case KeySizeValue_40_64bit_ASCII:
		case KeySizeValue_104_128bit_ASCII:
			CopyMemory(pucKeyMaterial, pszKeyASCII, strlen(pszKeyASCII));
			ucSize = (UCHAR)strlen(pszKeyASCII);
			break;
		case KeySizeValue_40_64bit_HEX:
		case KeySizeValue_104_128bit_HEX: {
				UCHAR *psz = (UCHAR*)pszKeyASCII;
				UCHAR *pTarget = pucKeyMaterial;

				while (*psz) {
					UINT8 val1, val2;

					val1 = HEX(*psz);
					psz ++;
					val2 = HEX(*psz);
					psz ++;

					*pTarget = (val1 << 4) + val2;
					pTarget ++;
				}
				ucSize = pTarget - pucKeyMaterial;
				break;
			}
		default:
			return 0;
	}

	TRACE("-SetWEPKey()\r\n");

	return ucSize;
}

BOOL WlanMisc_String2Ip(char *pszString, ULONG *pulIp)
{
	UCHAR i, nargs = 0, byte[4];
	char *argv[4];

	while (nargs < 4) {
		while ((*pszString == ' ') || (*pszString == '\t')) {
			++ pszString;
		}
		if (*pszString == '\0') {
			argv[nargs] = NULL;
			break;
		}

		argv[nargs ++] = pszString;

		while (*pszString && (*pszString != '.')) {
			++ pszString;
		}

		if (*pszString == '\0') {
			argv[nargs] = NULL;
			break;
		}

		*pszString ++ = '\0';
	}
	
	if (nargs != 4)
		return FALSE;

	for (i = 0; i < 4; i ++)
		byte[i] = atoi (argv[i]);

	*pulIp = ((DWORD)(BYTE)(byte[3])|(DWORD)(BYTE)(byte[2])<<8|(DWORD)(BYTE)(byte[1])<<16|(DWORD)(BYTE)(byte[0])<<24);

	return TRUE;
}

BOOL WlanMisc_String2Mac(char *pszString, PBYTE pbMac)
{
	UCHAR i, nargs = 0;
	char *argv[6];

	while (nargs < 6) {
		while ((*pszString == ' ') || (*pszString == '\t')) {
			++ pszString;
		}
		if (*pszString == '\0') {
			argv[nargs] = NULL;
			break;
		}

		argv[nargs ++] = pszString;

		while (*pszString && (*pszString != ':')) {
			++ pszString;
		}

		if (*pszString == '\0') {
			argv[nargs] = NULL;
			break;
		}

		*pszString ++ = '\0';
	}
	
	if (nargs != 6)
		return FALSE;

	for (i = 0; i < 6; i ++) {
		UINT8 val1, val2;

		val1 = HEX(argv[i][0]);
		val2 = HEX(argv[i][1]);

		pbMac[i] = (val1 << 4) + val2;
	}

	return TRUE;
}


