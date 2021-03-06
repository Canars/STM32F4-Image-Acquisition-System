/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "ctype.h"

unsigned char _ctype[] = {
_C,_C,_C,_C,_C,_C,_C,_C,			// 0-7
_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,		// 8-15
_C,_C,_C,_C,_C,_C,_C,_C,			// 16-23
_C,_C,_C,_C,_C,_C,_C,_C,			// 24-31
_S|_SP,_P,_P,_P,_P,_P,_P,_P,			// 32-39
_P,_P,_P,_P,_P,_P,_P,_P,			// 40-47
_D,_D,_D,_D,_D,_D,_D,_D,			// 48-55
_D,_D,_P,_P,_P,_P,_P,_P,			// 56-63
_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,	// 64-71
_U,_U,_U,_U,_U,_U,_U,_U,			// 72-79
_U,_U,_U,_U,_U,_U,_U,_U,			// 80-87
_U,_U,_U,_P,_P,_P,_P,_P,			// 88-95
_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,	// 96-103
_L,_L,_L,_L,_L,_L,_L,_L,			// 104-111
_L,_L,_L,_L,_L,_L,_L,_L,			// 112-119
_L,_L,_L,_P,_P,_P,_P,_C,			// 120-127
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		// 128-143
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		// 144-159
_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,   // 160-175
_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,       // 176-191
_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,       // 192-207
_U,_U,_U,_U,_U,_U,_U,_P,_U,_U,_U,_U,_U,_U,_U,_L,       // 208-223
_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,       // 224-239
_L,_L,_L,_L,_L,_L,_L,_P,_L,_L,_L,_L,_L,_L,_L,_L};      // 240-255
