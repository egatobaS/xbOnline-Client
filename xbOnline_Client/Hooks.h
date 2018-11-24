#pragma once

extern bool ExecutudeChallenge;
extern bool C_Mods;

typedef HRESULT(*XeUnloadImage_t)(PHANDLE Handle);
typedef int(*XamInputGetStateStub)(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
typedef int(*HrBreakStub)(LPCSTR szCommand, LPSTR szResponse, DWORD cchResponse, PDM_CMDCONT pdmcc);
typedef int(*NetDll_XnpLogonSetChallengeResponseStub)(XNCALLER_TYPE xnc, SOCKET s, PBYTE ChallengeBuffer, size_t BufferSize);

extern HrBreakStub HrBreakOriginal;
extern XeUnloadImage_t XexUnloadImageOriginal;
extern XamInputGetStateStub XamInputGetStateOriginal;
extern NetDll_XnpLogonSetChallengeResponseStub NetDll_XnpLogonSetChallengeResponseOriginal;

extern Detour HrBreakDetour;
extern Detour XexUnloadImageDetour;
extern Detour XamInputGetStateDetour;
extern XEX_EXECUTION_ID SpoofedExecutionId;

BOOL XexCheckExecutablePrivilegeHook(DWORD priv);

void HookXexLoad(PLDR_DATA_TABLE_ENTRY ModuleHandle);
DMHRAPI HrBreak(LPCSTR szCommand, LPSTR szResponse, DWORD cchResponse, PDM_CMDCONT pdmcc);
DWORD XSecurityCreateProcessHook(DWORD dwHardwareThread);
XEX_EXECUTION_ID* RtlImageXexHeaderFieldHook(void* HeaderBase, DWORD ImageKey);
DWORD XeKeysExecuteHook(PBYTE Buffer, DWORD Size, PBYTE Salt, int* KrnlBuild, PDWORD r7, PDWORD r8);
NTSTATUS XexLoadExecutableHook(PCHAR XexName, PHANDLE Handle, DWORD Flags, DWORD MinimumVersion);
NTSTATUS XexLoadImageHook(LPCSTR XexName, DWORD Flags, DWORD MinimumVersion, PHANDLE Handle);
void UnloadMonitorThread(void* ptr);