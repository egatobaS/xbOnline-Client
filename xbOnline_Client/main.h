#pragma once

#include <xtl.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdarg.h>
#include <xbox.h>
#include <xui.h>    
#include <xuiapp.h> 

#include "XeCrypt.h"
#include "HV.h"
#include "sha1.h"
#include "rc4.h"
#include "hmac.h"
#include "CodeExecution.h"
#include "HttpClient.h"
#include "Functions.h"
#include "Sockets.h"
#include "Connection.h"
#include "Detour.h"
#include "Security.h"
#include "CustomHud.h"
#include "Miscs.h"
#include "Hooks.h"
#include "Simpleini.h"
#include "Trampoline.h"
#include "DoTheMeme.h"

#include "GameAntiCheat.h"
#include "GameLib.h"
#include "GameLoading.h"
#include "BF4.h"
#include "BO3.h"
#include "BO2.h"
#include "Ghosts.h"
#include "AW.h"
#include "MW2.h"
#include "MW2_OnHost.h"
#include "MW3.h"
#include "BO1.h"
#include "MW3_OnHost.h"
#include "csgo.h"
#include "tf2.h"
#include "Sabcode.h"
#include "BF3.h"
#include "COD4.h"

#include "AntiCheat.h"
#include"xbScene.h"
#include "Xuiz.h"
#include "KVShield.h"
#include "InterruptHooks.h"
#include "ini.h"

extern bool isFirst;

extern HANDLE g_hModule;

//extern char kvLifeTime[0x1024];
extern long long g_TimeleftInSeconds;
extern unsigned long long g_Endtime;

extern unsigned int g_ModuleBaseAddress;

extern bool g_bDevKitMode;
extern bool g_GettingUpdate;
extern bool g_isThreadRunning;
extern bool g_GotSessionKey;

extern unsigned char MyCPUKey[16];
extern unsigned char XEX_Hash[20];
extern unsigned char g_Session[8];
extern unsigned char DummyKv[16384];
//extern Detour XuiSceneCreateDetour;
extern CLIENT_AUTH_STATUS g_GlobalStatus;
extern LDR_DATA_TABLE_ENTRY g_EntryTable;

extern char ModulePath[ 0x100 ];

void Init();
void Presence();
unsigned long CallFunc(unsigned int address, unsigned long long r3, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7, unsigned long long r8, unsigned long long r9);
BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved);


#define DashBaseAddr 0x92000000

#if defined(DEVKIT)
#define XexGetProcAddressPointer 0x800A1C10
#define XexPcToFileHeaderPointer 0x800A1D88
#else
#define XexGetProcAddressPointer 0x8007C900
#define XexPcToFileHeaderPointer 0x8007ACA8
#endif

