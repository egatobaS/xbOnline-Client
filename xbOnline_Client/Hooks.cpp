#include "main.h"

bool ExecutudeChallenge = false;

char CrashData_1[0x500] = { 0 };
char CrashData_2[0x500] = { 0 };
char CrashData_3[0x500] = { 0 };

Detour HrBreakDetour;
Detour XamInputGetStateDetour;
Detour KeDebugMonitorFunctionDetour;
XEX_EXECUTION_ID SpoofedExecutionId;
XamInputGetStateStub XamInputGetStateOriginal;

typedef int(*pKeDebugMonitorFunction)(EXCEPTION_POINTERS * ExceptionInfo);
pKeDebugMonitorFunction KeDebugMonitorFunctionStub;

HrBreakStub HrBreakOriginal;

#if defined(DEVKIT)
NetDll_XnpLogonSetChallengeResponseStub NetDll_XnpLogonSetChallengeResponseOriginal = (NetDll_XnpLogonSetChallengeResponseStub)0x81848528;
#else
NetDll_XnpLogonSetChallengeResponseStub NetDll_XnpLogonSetChallengeResponseOriginal = (NetDll_XnpLogonSetChallengeResponseStub)0x81740F48;
#endif

DMHRAPI HrBreak(LPCSTR szCommand, LPSTR szResponse, DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD Address = 0;

	if (FGetNamedDwParam(szCommand, "addr", &Address, szResponse)) {
		Address = Address;
	}
	else
	{
		if (FGetDwParam(szCommand, "read", &Address))
			Address = Address;
		else if (FGetDwParam(szCommand, "write", &Address))
			Address = Address;
		else if (FGetDwParam(szCommand, "readwrite", &Address))
			Address = Address;
		else if (FGetDwParam(szCommand, "execute", &Address))
			Address = Address;
	}

	if ((Address & 0xFFF00000) == g_ModuleBaseAddress) {
		return E_FAIL;
	}

	if ((Address & 0xFFF00000) == 0x91C40000) {

		return E_FAIL;
	}

	if ((Address & 0xFFF00000) == 0x90A00000) {

		return E_FAIL;
	}

	if ((Address & 0xFFF00000) == 0x91C10000) {

		return E_FAIL;
	}

	if ((Address & 0xFFF00000) == 0x90F00000) {

		return E_FAIL;
	}

	if ((Address & 0xFFF00000) == 0x90D90000) {

		return E_FAIL;
	}
	if ((Address & 0xFFF00000) == 0x91C40000) {

		return E_FAIL;
	}
	if ((Address & 0xFFF00000) == 0x92000000) {

		return E_FAIL;
	}
	if ((Address & 0xFFF00000) == 0x913E0000) {

		return E_FAIL;
	}
	return HrBreakOriginal(szCommand, szResponse, cchResponse, pdmcc);
}

NTSTATUS XexLoadImageHook(LPCSTR XexName, DWORD Flags, DWORD MinimumVersion, PHANDLE Handle)
{
	HANDLE mHandle = NULL;

	NTSTATUS Result = XexLoadImage(XexName, Flags, MinimumVersion, &mHandle);

	if (Handle != NULL) *Handle = mHandle;

	if (NT_SUCCESS(Result)) HookXexLoad((PLDR_DATA_TABLE_ENTRY)mHandle);
	return Result;
}


NTSTATUS XexLoadExecutableHook(PCHAR XexName, PHANDLE Handle, DWORD Flags, DWORD MinimumVersion)
{
	HANDLE mHandle = NULL;
	NTSTATUS result = XexLoadExecutable(XexName, &mHandle, Flags, MinimumVersion);

	if (Handle != NULL) *Handle = mHandle;

	if (NT_SUCCESS(result)) HookXexLoad((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle);

	return result;
}

DWORD XSecurityCreateProcessHook(DWORD dwHardwareThread)
{
	return ERROR_SUCCESS;
}

VOID XSecurityCloseProcessHook()
{
	return;
}

VOID __cdecl APCWorker(void* Arg1, void* Arg2, void* Arg3)
{

	if (Arg2) ((LPOVERLAPPED_COMPLETION_ROUTINE)Arg2)((DWORD)Arg3, 0, (LPOVERLAPPED)Arg1);
}

DWORD XSecurityVerifyHook(DWORD dwMilliseconds, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{

	if (lpCompletionRoutine)	NtQueueApcThread((HANDLE)-2, (PIO_APC_ROUTINE)APCWorker, lpOverlapped, (PIO_STATUS_BLOCK)lpCompletionRoutine, 0);

	return ERROR_SUCCESS;
}

DWORD XSecurityGetFailureInfoHook(PXSECURITY_FAILURE_INFORMATION pFailureInformation)
{
	if (pFailureInformation->dwSize == 0x14) {
		pFailureInformation->dwBlocksChecked = 0x64;
		pFailureInformation->dwFailedHashes = 0;
		pFailureInformation->dwFailedReads = 0;
		pFailureInformation->dwTotalBlocks = 0x64;
	}
	else if (pFailureInformation->dwSize == sizeof(XSECURITY_FAILURE_INFORMATION)) {
		pFailureInformation->dwBlocksChecked = 0x100;
		pFailureInformation->dwFailedHashes = 0;
		pFailureInformation->dwFailedReads = 0;
		pFailureInformation->dwTotalBlocks = 0x100;
		pFailureInformation->fComplete = TRUE;
	}
	else return ERROR_NOT_ENOUGH_MEMORY;
	return ERROR_SUCCESS;
}

DWORD XexGetProcedureAddressHook(HANDLE hand, DWORD dwOrdinal, PVOID* pvAddress)
{
	if (hand == GetModuleHandle(MODULE_XAM)) {
		switch (dwOrdinal) {
		case 0x9BB:
			*pvAddress = XSecurityCreateProcessHook;
			return 0;
		case 0x9BC:
			*pvAddress = XSecurityCloseProcessHook;
			return 0;
		case 0x9BD:
			*pvAddress = XSecurityVerifyHook;
			return 0;
		case 0x9BE:
			*pvAddress = XSecurityGetFailureInfoHook;
			return 0;
		}
	}
	return XexGetProcedureAddress(hand, dwOrdinal, pvAddress);
}

BOOL XexCheckExecutablePrivilegeHook(DWORD priv)
{
	if (priv == 6) return TRUE;

	return XexCheckExecutablePrivilege(priv);
}

XEX_EXECUTION_ID* RtlImageXexHeaderFieldHook(void* HeaderBase, DWORD ImageKey)
{
	XEX_EXECUTION_ID* ExecID = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(HeaderBase, ImageKey);


	if (ImageKey == 0x40006 && ExecID)
	{
		//printf("xbOnline - RtlImageXexHeaderFieldHook with ImageKey... 0x%X, Title ID: 0x%X\n", ImageKey, ExecID->TitleID);

		switch (ExecID->TitleID)
		{
		case 0x9002:	 // This is Akward.
		case 0xFFFF0055: // Xex Menu
		case 0xC0DE9999: // Xex Menu alt
		case 0xFFFE07FF: // XShellXDK
		case 0xF5D20000: // FSD
		case 0xFFFF011D: // DashLaunch
		case 0xFFFEFF43: // Xell Launch GOD
		case 0xFEEDC0DE: // XYZProject
		case 0xFFED0707: // SNES360
		case 0x00000176: // XM360
		case 0x00000167: // FSD3
		case 0x00FBAFBA: // FinalBurnAlpha
		case 0x00000174: // MAME360
		case 0x00000171: // FCE360
		case 0xFFFF051F: // Atari2600
		case 0x1CED2911: // PS1Emu
		case 0x00000115: // GenisisPlus
		case 0x00000189: // Simple360NandFlasher
		case 0x00000155: // PSCRX
		case 0x00000184: // OpenBOR
		case 0x58550B60: // Custom Game
		case 0x58550E53: // Shutshimi
		case 0x00000166: // Aurora 
		case 0x00000172: // DSon360
		case 0x00000198: // Demon Nand Switcher
		case 0xFFED7301: // GameboyAdvanceEmu
		case 0x00000191: // Rick360
		case 0x00000197: // ppsp
		case 0x00000193: // Raw360
		case 0x00000192: // Rem360
		case 0x00000186: // MilkyTracker 
		case 0x00000194: // Exult360
		case 0x00000187: // xBermuda360
		case 0x00000173: // PCEngine
		case 0xFFFFA500: // Amiga360
		case 0x00000195: // XeBoyAdvance 
		case 0x75447253: // Q2Custom
		case 0x07022007: // NeoGeo Pocket 
		case 0x00000188: // Flash360
		case 0x00001039: // SNES360PAL2
		case 0x00000175: // SMS360
		case 0x03172006: // PCEngine
		case 0x00000185: // OpenJazz360 
		case 0x00000169: // Capcom CPXIII
		case 0x00000183: // Quake3_360
		case 0x00000182: // Virtual Jaguar
		case 0x00000177: // NXE2GOD
		case 0xFFED7300: // SegaMegaDrive
		case 0x00000178: // SuperMarioDrive
		case 0x00000179: // FFPlay
		case 0x00000170: // XeXMenu2.0
		case 0x00000180: // D0SB0x
		case 0x000003D0: // 3D0
		case 0x00000119: // ScumVm
		case 0x00000181: // Play System 3 Emu
		case 0x66776655: // Star Control 2
		case 0xD008D009: // Doom Legacy
		case 0x53544232: // SuperTransBall2
		case 0xFFFF7269: // RiseofTheTriad
		case 0x0A600853: // Decent
		case 0x00C76C3B: // Mad Bomber 
		case 0x00000001: // FxMenu(XexMenuEdit)
		case 0x00000196: // xCBR
		case 0x08192006: // Pokemon Mini
		case 0x10022007: // MSX
		case 0x07162006: // Commodore64
		case 0x08152006: // Supervision
		case 0x03202006: // Atari Lnyx 
		case 0x10052007: // Intellivision
		case 0x08272006: // Atari7800
		case 0x10082007: // Atari5200
		case 0x07012007: // Wonderswan
		case 0x10122007: // AmStrad CMC
		{
			Tramps->CallFunction(memcpy_Function, (int)ExecID, (int)&SpoofedExecutionId, sizeof(XEX_EXECUTION_ID), 0, false);
			break;
		}
		}
	}
	else if (ImageKey == 0x40006 && !ExecID)
	{
		ExecID = &SpoofedExecutionId;
	}
	return ExecID;
}

void DumpCrash()
{
	FILE* fp = NULL;
	fopen_s(&fp, "HDD:\\xbOnline.log", "a");

	if (fp != NULL) {

		printf(CrashData_1);
		fprintf(fp, CrashData_1);

		printf(CrashData_2);
		fprintf(fp, CrashData_2);

		printf(CrashData_3);
		fprintf(fp, CrashData_3);
	}
	fclose(fp);
}

int KeDebugMonitorFunction(EXCEPTION_POINTERS * ExceptionInfo)
{

	sprintf(CrashData_1, "Exception Information\nException Address: 0x%08X\nException Code: 0x%08X\n\nGeneral Purpose Registers\nCR : 0x%016I64X XER: 0x%016I64X\nr0 : 0x%016I64X r1 : 0x%016I64X r2 : 0x%016I64X\nr3 : 0x%016I64X r4 : 0x%016I64X r5 : 0x%016I64X\nr6 : 0x%016I64X r7 : 0x%016I64X r8 : 0x%016I64X\nr9 : 0x%016I64X r10: 0x%016I64X r11: 0x%016I64X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress, ExceptionInfo->ExceptionRecord->ExceptionCode, ExceptionInfo->ContextRecord->Cr, ExceptionInfo->ContextRecord->Xer, ExceptionInfo->ContextRecord->Gpr0, ExceptionInfo->ContextRecord->Gpr1, ExceptionInfo->ContextRecord->Gpr2, ExceptionInfo->ContextRecord->Gpr3, ExceptionInfo->ContextRecord->Gpr4, ExceptionInfo->ContextRecord->Gpr5, ExceptionInfo->ContextRecord->Gpr6, ExceptionInfo->ContextRecord->Gpr7, ExceptionInfo->ContextRecord->Gpr8, ExceptionInfo->ContextRecord->Gpr9, ExceptionInfo->ContextRecord->Gpr10, ExceptionInfo->ContextRecord->Gpr11);
	sprintf(CrashData_2, "r12: 0x%016I64X r13: 0x%016I64X r14: 0x%016I64X\nr15: 0x%016I64X r16: 0x%016I64X r17: 0x%016I64X\nr18: 0x%016I64X r19: 0x%016I64X r20: 0x%016I64X\nr21: 0x%016I64X r22: 0x%016I64X r23: 0x%016I64X\nr24: 0x%016I64X r25: 0x%016I64X r26: 0x%016I64X\nr27: 0x%016I64X r28: 0x%016I64X r29: 0x%016I64X\nr30: 0x%016I64X r31: 0x%016I64X\n\n", ExceptionInfo->ContextRecord->Gpr12, ExceptionInfo->ContextRecord->Gpr13, ExceptionInfo->ContextRecord->Gpr14, ExceptionInfo->ContextRecord->Gpr15, ExceptionInfo->ContextRecord->Gpr16, ExceptionInfo->ContextRecord->Gpr17, ExceptionInfo->ContextRecord->Gpr18, ExceptionInfo->ContextRecord->Gpr19, ExceptionInfo->ContextRecord->Gpr20, ExceptionInfo->ContextRecord->Gpr21, ExceptionInfo->ContextRecord->Gpr22, ExceptionInfo->ContextRecord->Gpr23, ExceptionInfo->ContextRecord->Gpr24, ExceptionInfo->ContextRecord->Gpr25, ExceptionInfo->ContextRecord->Gpr26, ExceptionInfo->ContextRecord->Gpr27, ExceptionInfo->ContextRecord->Gpr28, ExceptionInfo->ContextRecord->Gpr29, ExceptionInfo->ContextRecord->Gpr30, ExceptionInfo->ContextRecord->Gpr31);
	sprintf(CrashData_3, "Control Registers\nMSR: 0x%08X IAR :  0x%08X\nLR : 0x%08X CTR :  0x%08X\n\nCall Stack\n0x%08X (Exception Address)\n0x%08X (Link Register)\n\n", ExceptionInfo->ContextRecord->Msr, ExceptionInfo->ContextRecord->Iar, ExceptionInfo->ContextRecord->Lr, ExceptionInfo->ContextRecord->Ctr, ExceptionInfo->ExceptionRecord->ExceptionAddress, ExceptionInfo->ContextRecord->Lr);

	HANDLE hThread1 = 0; DWORD threadId1 = 0;
	ExCreateThread(&hThread1, 0x100000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)DumpCrash, 0, 0x2);
	XSetThreadProcessor(hThread1, 4);
	ResumeThread(hThread1);
	CloseHandle(hThread1);

	XLaunchNewImage(NULL, NULL);

	return KeDebugMonitorFunctionStub(ExceptionInfo);
}

bool UnloadTest = false;


void UnloadMonitorThread(void* ptr)
{
	while (true)
	{
		if (UnloadTest)
		{
			GameManager.UnloadCheats();
			UnloadTest = false;
		}
		Sleep(100);
	}
}

bool isLastTitleCSGO = false, isLastTitleTF2 = false;
bool isDevkit = false;

void HookXexLoad(PLDR_DATA_TABLE_ENTRY ModuleHandle)
{
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 407, (DWORD)XexGetProcedureAddressHook);
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 408, (DWORD)XexLoadExecutableHook);
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 409, (DWORD)XexLoadImageHook);

	XEX_EXECUTION_ID* ExecutionId = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(ModuleHandle->XexHeaderBase, 0x00040006);

	if (ExecutionId == 0) return;


#if defined(DEVKIT)
	if ((!wcscmp(ModuleHandle->BaseDllName.Buffer, L"xshell.xex")))
	{
		wchar_t* XboxDev = L"%s@blasts.pw";

		memcpy((wchar_t*)0x8160E254, XboxDev, (sizeof("%s@blasts.pw") * 2) + 1);

		strcpy((char*)0x8160D8E4, "%ws@blasts.pw");
		strcpy((char*)0x8160D898, "@blasts.pw");

		*(int*)(0x817A69CC) = 0x60000000;
	}
#endif	

#if defined(DEVKIT)

#else
	if ((!wcscmp(ModuleHandle->BaseDllName.Buffer, L"hud.xex")))
	{
		if (xb_custom_xui)
			XuiSceneCreateDetour.HookFunction("hud.xex", MODULE_XAM, 855, (DWORD)xuiz_s::xam_s::XuiSceneCreate);
	}

	if (!wcscmp(ModuleHandle->BaseDllName.Buffer, L"dash.xex"))
	{
		char* hazz = "Hazz is a Theif. Everything he has is stolen. Fax.";
		hazz[0] = 0;
		DbgPrint(hazz);

		if (xb_custom_xui)
		{
			xuiz.xam.HookRuntimeDashFunctions();

			if (GetHandle((void*)DashBaseAddr, (PHANDLE)&dashHandle))
				XuiElementBeginRender_Orig = (XuiElementBeginRender_t)XuiElementBeginRenderDetour.HookFunction((DWORD)ResolveFunction_0(dashHandle, 0x28D3), (DWORD)XuiElementBeginRender_hook);
			//PatchInJump_2(0x921E7A10, (DWORD*)xuiz_s::xam_s::XuiSceneCreate, false);
			//XuiSceneCreateDetour_Dash.HookFunction("dash.xex", MODULE_XAM, 855, (DWORD)xuiz_s::xam_s::XuiSceneCreate);
			//XuiSceneCreateDetour_Dash.HookFunction(0x921E7A10, (DWORD)xuiz_s::xam_s::XuiSceneCreate_Dash);
		}
	}
#endif	


	switch (ExecutionId->TitleID)
	{

	case 0x454109BA:
	{
		while (!isFirst) Sleep(1);

		if (ModuleHandle->TimeDateStamp == 0x5642B1D0)
		{
			isChallengeMultiplayer = true;
			UnloadTest = true;

			while (UnloadTest) {
				Sleep(10);
			}

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/ClientIcon.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			FirstData->istoLoadAnotherGame = false;

			FirstData->isCheatEnabled = xb_cheats_bf4;

			if (g_GlobalStatus != EXPIRED)
			{
				KeDebugMonitorFunctionStub = (pKeDebugMonitorFunction)KeDebugMonitorFunctionDetour.HookFunction((unsigned int)0x882FB7B8, (int)KeDebugMonitorFunction);

				if (xb_cheats_bf4 && BattleField4_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					CreateXboxThread(LoadCheat, (void*)FirstData);
			}
		}
		break;
	}

	case 0x45410950:
	{
#if defined(DEVKIT)

		static HANDLE Nig = NULL;

		if (!Nig)
			XexLoadImage("xbOnline:\\SwapDisc.xex", 8, 0, &Nig);

		if (!wcscmp(ModuleHandle->BaseDllName.Buffer, L"BF.Main.xex"))
			*(int*)0x834dde90 = 0x48000068;


		break;
#endif

		if (!wcscmp(ModuleHandle->BaseDllName.Buffer, L"BF.Main.xex"))
		{
			while (!isFirst) Sleep(1);

			if (((ExecutionId->Version & 0x0000FF00) >> 8) == 0)
			{
				isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x50FEF168);

#if defined(DEVKIT)
				*(int*)0x834dde90 = 0x48000068;
#endif
				GameManager.UnloadCheats();

				ThreadPastGameData* FirstData = new ThreadPastGameData;

				int ID = GameManager.GetValidID();

				FirstData->ID = ID;
				FirstData->TitleID = ExecutionId->TitleID;
				strcpy(FirstData->titleName, "/xbOHd.png");
				strcpy(FirstData->titleIp, ServerOneIp);

				strcpy(FirstData->Name, "XAPI.xex");

				FirstData->istoLoadAnotherGame = false;

				FirstData->isCheatEnabled = true;

				if (g_GlobalStatus != EXPIRED)
				{
					if (isChallengeMultiplayer && BattleField3_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
				}
			}
			break;
		}
	}

	case 0x415608FC:
	{
		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 17)
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x544F01BE);

			InitGhosts();

			GameManager.UnloadCheats();

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/CoolImage.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			FirstData->istoLoadAnotherGame = false;

			FirstData->isCheatEnabled = xb_cheats_ghosts;

			if (g_GlobalStatus != EXPIRED)
			{
				if (xb_cheats_ghosts && server_cod_ghosts && isChallengeMultiplayer && Ghosts_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
				{
					CreateXboxThread(LoadCheat, (void*)FirstData);
				}
			}
		}

		break;
	}

	case 0x41560914:
	{
		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 17) {
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x55C2C3C7);
			InitAW();
		}
		break;
	}

	case 0x415608C3:
	{
		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 18) {

			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x53643D71);

			GameManager.UnloadCheats();

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/xbOnline_Notify.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			FirstData->istoLoadAnotherGame = false;

			FirstData->isCheatEnabled = xb_cheats_bo2;

			if (g_GlobalStatus != EXPIRED)
			{
				if (xb_bypass_bo2)
					InitBlackOps2();

				if (xb_cheats_bo2 && server_cod_bo2 && isChallengeMultiplayer && BlackOps2_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
				{
					CreateXboxThread(LoadCheat, (void*)FirstData);
				}
			}
		}
		break;
	}

	case 0x4156091D:
	{
		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 8) {
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x5717EF77);
			InitBlackOps3();
		}
		break;
	}

	case 0x415608CB:
	{

		while (!isFirst) Sleep(1);

#if defined(DEVKIT)
		*(long long*)0x8232A2F8 = 0x386000017C6A59AE;
		*(int*)0x8232A300 = 0x4BFFFFD0;

		*(int*)0x82524D14 = 0x60000000;
		*(int*)0x8252EE00 = 0x60000000;
#endif
		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 24)
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x5B10A113);

			GameManager.UnloadCheats();

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/Logo_xbO.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			ThreadPastGameData* SecondData = new ThreadPastGameData;

			ID = GameManager.GetValidID();

			SecondData->ID = ID;
			SecondData->TitleID = ExecutionId->TitleID;
			strcpy(SecondData->titleName, "/Notif.png");
			strcpy(SecondData->titleIp, ServerOneIp);

			strcpy(SecondData->Name, "lhelper.xex");

			FirstData->AnotherGame = (void*)SecondData;

			FirstData->istoLoadAnotherGame = server_cod_mw3;

			SecondData->isCheatEnabled = xb_cheats_mw3_onhost;

			FirstData->isCheatEnabled = xb_cheats_mw3;

			if (g_GlobalStatus != EXPIRED)
			{
#if defined(DEVKIT)
				if (xb_cheats_mw3 && server_cod_mw3)
					MSG_ReadBitsCompressOriginal = (MSG_ReadBitsCompress_t)MSG_ReadBitsCompressedDetour.HookFunction((unsigned int)0x822A4688, (unsigned int)MSG_ReadBitsCompressHook);
#endif			
				if ((xb_cheats_mw3 || xb_cheats_mw3_onhost) && server_cod_mw3 && isChallengeMultiplayer && MW3_BuildFunctions() && MW3_BuildFunctions_OnHost() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
				{
					CreateXboxThread(LoadCheat, (void*)FirstData);
				}
			}
		}
		break;
	}

	case 0x41560817:
	{

		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 8)
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x50749AC3);

			GameManager.UnloadCheats();

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/Notification.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			ThreadPastGameData* SecondData = new ThreadPastGameData;

			ID = GameManager.GetValidID();

			SecondData->ID = ID;
			SecondData->TitleID = ExecutionId->TitleID;
			strcpy(SecondData->titleName, "/test.png");
			strcpy(SecondData->titleIp, ServerOneIp);

			strcpy(SecondData->Name, "lhelper.xex");

			FirstData->AnotherGame = (void*)SecondData;

			FirstData->istoLoadAnotherGame = true;

			SecondData->isCheatEnabled = xb_cheats_mw2_onhost;

			FirstData->isCheatEnabled = xb_cheats_mw2;

			if (g_GlobalStatus != EXPIRED)
			{
#if defined(DEVKIT)
				if (xb_cheats_mw2_onhost || xb_cheats_mw2)
					MSG_ReadBitsCompressOriginal = (MSG_ReadBitsCompress_t)MSG_ReadBitsCompressedDetour.HookFunction((unsigned int)0x82234980, (unsigned int)MSG_ReadBitsCompressHook);
#endif			
				if ((xb_cheats_mw2 || xb_cheats_mw2_onhost) && server_cod_mw2 && isChallengeMultiplayer && MW2_BuildFunctions() && MW2_BuildFunctions_OnHost() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
				{
					CreateXboxThread(LoadCheat, (void*)FirstData);
				}
			}

				}
		break;
			}

	case  0x41560855:
	{
		while (!isFirst) Sleep(1);

#if defined(DEVKIT)
		*(int*)(0x824FA18C) = 0x60000000;
		*(int*)0x822562D4 = 0x48000020;
#endif

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 11 || (((ExecutionId->Version & 0x0000FF00) >> 6) != 0))
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x4E542876);

			GameManager.UnloadCheats();

			ThreadPastGameData* FirstData = new ThreadPastGameData;

			int ID = GameManager.GetValidID();

			FirstData->ID = ID;
			FirstData->TitleID = ExecutionId->TitleID;
			strcpy(FirstData->titleName, "/CoolLogo.png");
			strcpy(FirstData->titleIp, ServerOneIp);

			strcpy(FirstData->Name, "XAPI.xex");

			FirstData->istoLoadAnotherGame = false;

			FirstData->isCheatEnabled = xb_cheats_bo1;

			if (g_GlobalStatus != EXPIRED)
			{
				if (xb_cheats_bo1 && server_cod_bo1 && isChallengeMultiplayer && BO1_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
				{
					CreateXboxThread(LoadCheat, (void*)FirstData);
				}
			}
		}

		break;
	}

	case 0x5841125A:
	{
		while (!isFirst) Sleep(1);

		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 0)
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x5022C826);

			if (isChallengeMultiplayer)
			{
				ThreadPastGameData* FirstData = new ThreadPastGameData;

				int ID = GameManager.GetValidID();

				FirstData->ID = ID;
				FirstData->TitleID = ExecutionId->TitleID;
				strcpy(FirstData->titleName, "/testpng.png");
				strcpy(FirstData->titleIp, ServerOneIp);

				strcpy(FirstData->Name, "XAPI.xex");

				FirstData->istoLoadAnotherGame = false;

				FirstData->isCheatEnabled = xb_cheats_csgo;

				if (g_GlobalStatus != EXPIRED)
				{
					if (xb_cheats_csgo && server_csgo && isChallengeMultiplayer && CSGO_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						isLastTitleCSGO = true;

						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
				}
			}
		}
		break;
	}

	case 0x4541080F:
	{
		while (!isFirst) Sleep(1);
		if (((ExecutionId->Version & 0x0000FF00) >> 8) == 1 || ((ExecutionId->Version & 0x0000FF00) >> 8) == 5)
		{
			isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x46D8E028);

			if (isChallengeMultiplayer)
			{
				ThreadPastGameData* FirstData = new ThreadPastGameData;

				int ID = GameManager.GetValidID();

				FirstData->ID = ID;
				FirstData->TitleID = ExecutionId->TitleID;
				strcpy(FirstData->titleName, "/coolpics.png");
				strcpy(FirstData->titleIp, ServerOneIp);

				strcpy(FirstData->Name, "XAPI.xex");

				FirstData->istoLoadAnotherGame = false;

				FirstData->isCheatEnabled = xb_cheats_tf2;

				if (g_GlobalStatus != EXPIRED)
				{
					if (xb_cheats_tf2 && server_cod_waw && isChallengeMultiplayer && TF2_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						isLastTitleTF2 = true;

						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
				}
			}
		}
		break;
	}

	default:
	{
		if (isLastTitleCSGO || isLastTitleTF2)
		{
			GameManager.UnloadCheatsNoMP();
			break;
		}

		GameManager.UnloadCheats();
		break;
	}

		}
	}

DWORD NetDll_XnpLogonSetChallengeResponse(SOCKET s, PBYTE ChallengeBuffer, size_t BufferSize)
{
	memset(ChallengeBuffer, 0, BufferSize);

	int AttemptCount = 0;

	while (true)
	{

		unsigned char CPUKey[0x10] = { 0 };
		unsigned char Geneology[0x10] = { 0 };

		Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

		Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

		Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

		if (Connection->GetSecurityChallenge((unsigned char*)&KeyVault, ChallengeBuffer, (((KeyVault.ConsoleCertificate.ConsolePartNumber[2] << 4) & 0xF0) | (KeyVault.ConsoleCertificate.ConsolePartNumber[3] & 0x0F)))) {

			break;
		}

		delete Connection;

		AttemptCount++;

		if (AttemptCount > 4) {
			SetLiveBlock(true);
			RebootConsole();
		}
	}
	//GetMachineAccountKey();
	return NetDll_XnpLogonSetChallengeResponseOriginal(XNCALLER_SYSAPP, s, ChallengeBuffer, BufferSize);
}

int Count = 0;


DWORD XeKeysExecuteHook(PBYTE Buffer, DWORD Size, PBYTE Salt, int* KrnlBuild, PDWORD r7, PDWORD r8)
{
	//Hash our Payload, make sure this never changes
	if (!xbVerifyPayload(Buffer, Size))
	{
		SetLiveBlock(true);
		RebootConsole();
	}

	memset(Buffer, 0, Size);
	int AttemptCount = 0;

	while (true)
	{
		unsigned char CPUKey[0x10] = { 0 };
		unsigned char Geneology[0x10] = { 0 };

		Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

		Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

		Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

		if (Connection->GetXamChallenge(g_Session, Salt, Spoofed_CPUKey, (((KeyVault.ConsoleCertificate.ConsolePartNumber[2] << 4) & 0xF0) | (KeyVault.ConsoleCertificate.ConsolePartNumber[3] & 0x0F)), Buffer)) {

			Count++;

			*(int*)(&Buffer[0] + 0x34) = XKEUpdateSequence;

			break;
		}

		delete Connection;

		AttemptCount++;

		if (AttemptCount > 4) {
			SetLiveBlock(true);

			RebootConsole();
		}
	}

	//Write Ticket for Debugging Purposes...
	//GetMachineAccountKey();
	return ERROR_SUCCESS;
}



