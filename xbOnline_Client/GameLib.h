#pragma once

struct SYS_FUNCTION_ADDRESS
{
	void* HookFunction;
	void* XNotify;
	void* memcpy;
	void* memset;
	void* strcpy;
	void* memcmp;
	void* strcmp;
	void* Sleep;
	void* MmIsAddressValid;
	void* FIsMmIoAddress;
	void* GetDetours;
};

extern int Func_ptr[2];
extern long long spoofedMachineID;
extern unsigned char spoofedMacAddress[6];
extern unsigned char Text_SerialNumber[12];
extern unsigned char Text_ConsoleID[13];
extern unsigned char spoofedConsoleID[8];
extern unsigned char spoofedSerialNumber[8];

void RandomValues();
void BuildStartFunctions();

extern Detour XNetXnAddrToMachineIdDetour;
extern Detour NetDll_XNetGetTitleXnAddrDetour;

DWORD NetDll_XNetGetTitleXnAddrHook(XNCALLER_TYPE xnc, XNADDR * pxna);
int XNetXnAddrToMachineIdHook(XNCALLER_TYPE xnc, XNADDR* pxnaddr, unsigned long long* qwMachineId);