#ifndef __INCLUDES_H
#define __INCLUDES_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stm32f4xx.h"

#include "BaseTypes.h"
#include "BaseDefs.h"
#include "GSPI.h"
#include "flash.h"
#include "usart.h"
#include "delay.h"
//-----------------------------------------------------------------------------
// Wifi reference headers
//-----------------------------------------------------------------------------
#include "WifiDefs.h"
#include "WifiCfg.h"
//-----------------------------------------------------------------------------
// NDIS layer headers
//-----------------------------------------------------------------------------
#include "Ndis.h"
#include "Ndisdef.h"

//-----------------------------------------------------------------------------
// Marvell defined headers
//-----------------------------------------------------------------------------
#include "MrvConstant.h"
#include "MrvStruct.h"
#include "MrvHostCmd.h"

//-----------------------------------------------------------------------------
// Wifi headers
//-----------------------------------------------------------------------------
#include "WlanAdapter.h"
#include "Wifi_Hw.h"
#include "Wifi_If.h"
#include "WlanCmd.h"
#include "WlanInit.h"
#include "WlanPkt.h"
#include "WlanMisc.h"

//-----------------------------------------------------------------------------
// Headers for user
//-----------------------------------------------------------------------------
#include "WifiApiExport.h"
#include "WIFICommand.h"

//-----------------------------------------------------------------------------
// For debug only
//-----------------------------------------------------------------------------

//
// Global variables declare
//
extern WLAN_ADAPTER g_Adapter;

#endif // __INCLUDES_H__
