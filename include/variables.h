#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "global.h"

// thread pris
#define THREAD_PRI_RESET 30
#define THREAD_PRI_IDLE_INIT 100

// thread IDs
#define THREAD_ID_IDLE 1
#define THREAD_ID_RESET 21

typedef struct
{
  u8	pad;
  u8	yearhi;
  u8	yearlo;
  u8	month;
  u8	day;
  u8	hour;
  u8	minute;
  u8	second;
} LEODiskTime;

typedef	struct
{
  u64		lineNumber;
  LEODiskTime	time;
} LEOSerialNum;

typedef struct
{
  u8		gameName[4];
  u8		gameVersion;
  u8		diskNumber;
  u8		ramUsage;
  u8		diskUsage;
  LEOSerialNum	serialNumber;
  u8		company[2];
  u8		freeArea[6];
} LEODiskID;

extern LEODiskID D_800AA9E0;

#endif
