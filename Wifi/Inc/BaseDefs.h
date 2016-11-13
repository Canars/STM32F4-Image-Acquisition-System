/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __BASE_DEFS_H__
#define __BASE_DEFS_H__
//-----------------------------------------------------------------------------
// Convenient
//-----------------------------------------------------------------------------
#define KBytes(x)				((x) << 10)
#define MBytes(x)				(KBytes(x) << 10)
#define GBytes(x)				(MBytes(x) << 10)

#define ALIGN_UP(v, align)		(((v) + align - 1) & ~(align - 1))
#define ALIGN_DOWN(v, align)	((v) & ~(align - 1))

#define LOBYTE(l)				((BYTE)(l))
#define LOWORD(l)				((WORD)(l))
#define MAKEDWORD(a,b)			((DWORD)(WORD)(a)|((DWORD)(WORD)(b)<<16))
#define FOURCC(a,b,c,d)			((DWORD)(BYTE)(a)|(DWORD)(BYTE)(b)<<8|(DWORD)(BYTE)(c)<<16|(DWORD)(BYTE)(d)<<24)
#define UNFOURCC(val,array)			\
	do {							\
		array[3] = (BYTE)((val >> 24) & 0x000000FF); \
		array[2] = (BYTE)((val >> 16) & 0x000000FF); \
		array[1] = (BYTE)((val >> 8) & 0x000000FF); \
		array[0] = (BYTE)((val >> 0) & 0x000000FF); \
	} while(0)


#define HIBYTE(l)				((BYTE)((l)>>8))
#define MAKEWORD(a,b)			((WORD)(BYTE)(a)|((WORD)(BYTE)(b)<<8))
#define HIWORD(l)				((WORD)((l)>>16))

#define WAIT_OBJECT_0			0
#define WAIT_FAILED				0xFFFFFFFE
#define WAIT_TIMEOUT			0xFFFFFFFE

#define STATUS_UNSUCCESSFUL     ((INT)0xC0000001L)
#define STATUS_SUCCESS          ((INT)0x00000000L) // ntsubauth
#define STATUS_INSUFFICIENT_RESOURCES    		((INT)0xC000009AL)     // ntsubauth
#define STATUS_NOT_SUPPORTED    ((INT)0xC00000BBL)
#define STATUS_PENDING          ((INT)0x00000103L)    // winnt

//-----------------------------------------------------------------------------
// Macro functions
//-----------------------------------------------------------------------------
#define max(a,b)				(((a) > (b)) ? (a) : (b))
#define MAX						max

#define min(a,b)				(((a) < (b)) ? (a) : (b))
#define MIN						min

#define MEMBER_OFFSET(TYPE,MEM) ((int)(char*)&(((TYPE*)0)->MEM))

#define CopyMemory(pDest,pSrc,nLength)		memcpy(pDest,pSrc,nLength)
#define FillMemory(pDest,nFill,nLength)		memset(pDest,nFill,nLength)
#define ZeroMemory(pDest,nLength)			memset(pDest,0,nLength)
#define MoveMemory(pDest,pSrc,nLength)		memcpy(pDest,pSrc,nLength)
#define AllocMemory(nLength)				malloc(nLength)
#define FreeMemory(pMem)					free(pMem)
#define CompareMemory(pMem1,pMem2,nLength) 	memcmp(pMem1,pMem2,nLength)
#define EqualMemory(pMem1,pMem2,nLength)	!CompareMemory(pMem1,pMem2,nLength)
//-----------------------------------------------------------------------------
// Habits
//-----------------------------------------------------------------------------
#ifndef TRUE
#define TRUE 					1
#endif

#ifndef FALSE
#define FALSE 					0
#endif

#ifndef NULL
#define NULL					0
#endif

#ifndef MAXWORD
#define MAXWORD					0xFFFF
#endif

//-----------------------------------------------------------------------------
// Endian
//-----------------------------------------------------------------------------
#define ENDIANCHANGE16(A)                 ((((USHORT)(A) & 0xff00) >> 8) | \
        (((USHORT)(A) & 0x00ff) << 8))
#define ENDIANCHANGE32(A)                 ((((UINT)(A) & 0xff000000) >> 24) | \
        (((UINT)(A) & 0x00ff0000) >> 8) | \
        (((UINT)(A) & 0x0000ff00) << 8) | \
        (((UINT)(A) & 0x000000ff) << 24))

#endif	// __BASE_DEFS_H__
