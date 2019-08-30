#include "main.h"

Detour HrBreakDetour;
Detour XamInputGetStateDetour;
Detour KeDebugMonitorFunctionDetour;

XEX_EXECUTION_ID SpoofedExecutionId;
XamInputGetStateStub XamInputGetStateOriginal;

HrBreakStub HrBreakOriginal;

NetDll_XnpLogonSetChallengeResponseStub NetDll_XnpLogonSetChallengeResponseOriginal = (NetDll_XnpLogonSetChallengeResponseStub)0x817412B8;


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

void HookXexLoad(PLDR_DATA_TABLE_ENTRY ModuleHandle)
{
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 407, (DWORD)XexGetProcedureAddressHook);
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 408, (DWORD)XexLoadExecutableHook);
	PatchModuleImport_F(ModuleHandle, MODULE_KERNEL, 409, (DWORD)XexLoadImageHook);

	XEX_EXECUTION_ID* ExecutionId = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(ModuleHandle->XexHeaderBase, 0x00040006);

	if (ExecutionId == 0) return;

	if ((!wcscmp(ModuleHandle->BaseDllName.Buffer, L"hud.xex")))
	{
		if (xb_custom_xui)
			XuiSceneCreateDetour.HookFunction("hud.xex", MODULE_XAM, 855, (DWORD)xuiz_s::xam_s::XuiSceneCreate);
	}

	if (!wcscmp(ModuleHandle->BaseDllName.Buffer, L"dash.xex"))
	{
		if (xb_custom_xui)
		{
			xuiz.xam.HookRuntimeDashFunctions();

			if (GetHandle((void*)DashBaseAddr, (PHANDLE)&dashHandle))
				XuiElementBeginRender_Orig = (XuiElementBeginRender_t)XuiElementBeginRenderDetour.HookFunction((DWORD)ResolveFunction_0(dashHandle, 0x28D3), (DWORD)XuiElementBeginRender_hook);
		}
	}


	if (g_GlobalStatus != NO_CONNECTED)
	{
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

					if (xb_cheats_bf4 && BattleField4_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE) || (g_GlobalStatus == NO_CONNECTED)))
						CreateXboxThread(LoadCheat, (void*)FirstData);
					else
					{
						if (FirstData)
							delete FirstData;
					}
				}
			}
			break;
		}

		case 0x45410950:
		{
			if (!wcscmp(ModuleHandle->BaseDllName.Buffer, L"BF.Main.xex"))
			{
				while (!isFirst) Sleep(1);

				if (((ExecutionId->Version & 0x0000FF00) >> 8) == 0)
				{
					isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x50FEF168);


					GameManager.UnloadCheats();

					ThreadPastGameData* FirstData = new ThreadPastGameData;

					int ID = GameManager.GetValidID();

					FirstData->ID = ID;
					FirstData->TitleID = ExecutionId->TitleID;
					strcpy(FirstData->titleName, "/xbOHd.png");
					strcpy(FirstData->titleIp, ServerOneIp);

					strcpy(FirstData->Name, "XAPI.xex");

					FirstData->istoLoadAnotherGame = false;

					FirstData->isCheatEnabled = xb_cheats_bf3;

					if (g_GlobalStatus != EXPIRED)
					{
						if (xb_cheats_bf3 && isChallengeMultiplayer && BattleField3_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
						{
							CreateXboxThread(LoadCheat, (void*)FirstData);
						}
						else
						{
							if (FirstData)
								delete FirstData;
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
					else
					{
						if (FirstData)
							delete FirstData;
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

				GameManager.UnloadCheats();

				ThreadPastGameData* FirstData = new ThreadPastGameData;

				int ID = GameManager.GetValidID();

				FirstData->ID = ID;
				FirstData->TitleID = ExecutionId->TitleID;
				strcpy(FirstData->titleName, "/xbOnline_NiceImage.png");
				strcpy(FirstData->titleIp, ServerOneIp);

				strcpy(FirstData->Name, "Ihelper.xex");
				FirstData->istoLoadAnotherGame = false;
				FirstData->isCheatEnabled = xb_cheats_aw;

				if (g_GlobalStatus != EXPIRED)
				{
					if (xb_bypass_aw)
						InitAW();

					if (xb_cheats_aw && server_cod_aw && isChallengeMultiplayer && AW_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
					else
					{
						if (FirstData)
							delete FirstData;
					}
				}
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
					else
					{
						if (FirstData)
							delete FirstData;
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

				SecondData->isCheatEnabled = true;

				FirstData->isCheatEnabled = xb_cheats_mw3;

				if (g_GlobalStatus != EXPIRED)
				{
					if ((xb_cheats_mw3 || xb_cheats_mw3_onhost) && server_cod_mw3 && isChallengeMultiplayer && MW3_BuildFunctions() && MW3_BuildFunctions_OnHost() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
					else
					{
						if (SecondData)
							delete SecondData;

						if (FirstData)
							delete FirstData;
					}
				}
			}
			break;
		}

		case 0x41560817:
		{
			while (!isFirst) Sleep(1);

			if (((ExecutionId->Version & 0x0000FF00) >> 8) == 9)
			{
				isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x5B11C269);

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

				SecondData->isCheatEnabled = true;

				FirstData->isCheatEnabled = xb_cheats_mw2;

				if (g_GlobalStatus != EXPIRED)
				{
					if ((xb_cheats_mw2 || xb_cheats_mw2_onhost) && server_cod_mw2 && isChallengeMultiplayer && MW2_BuildFunctions() && MW2_BuildFunctions_OnHost() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
					else
					{
						if (SecondData)
							delete SecondData;

						if (FirstData)
							delete FirstData;
					}
				}

			}
			break;
		}

		case  0x41560855:
		{

			while (!isFirst) Sleep(1);

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
					else
					{
						if (FirstData)
							delete FirstData;
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
						else
						{
							if (FirstData)
								delete FirstData;
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
						else
						{
							if (FirstData)
								delete FirstData;
						}
					}
				}
			}
			break;
		}

		case  0x415607E6:
		{

			while (!isFirst) Sleep(1);


			if (((ExecutionId->Version & 0x0000FF00) >> 8) == 4)
			{
				isChallengeMultiplayer = (ModuleHandle->TimeDateStamp == 0x4A78A577);

				GameManager.UnloadCheats();

				ThreadPastGameData* FirstData = new ThreadPastGameData;

				int ID = GameManager.GetValidID();

				FirstData->ID = ID;
				FirstData->TitleID = ExecutionId->TitleID;
				strcpy(FirstData->titleName, "/NiceImage360.png");
				strcpy(FirstData->titleIp, ServerOneIp);

				strcpy(FirstData->Name, "XAPI.xex");

				FirstData->istoLoadAnotherGame = false;

				FirstData->isCheatEnabled = xb_cheats_cod4;

				if (g_GlobalStatus != EXPIRED)
				{
					if (xb_cheats_cod4 && server_cod_mw && isChallengeMultiplayer && Cod4_BuildFunctions() && ((g_GlobalStatus == TIMELEFT) || (g_GlobalStatus == FREEMODE)))
					{
						CreateXboxThread(LoadCheat, (void*)FirstData);
					}
					else
					{
						if (FirstData)
							delete FirstData;
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
}

DWORD NetDll_XnpLogonSetChallengeResponse(SOCKET s, PBYTE ChallengeBuffer, size_t BufferSize)
{
	memset(ChallengeBuffer, 0, BufferSize);

	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

	if (!Connection->GetSecurityChallenge((unsigned char*)&KeyVault, ChallengeBuffer, (((KeyVault.ConsoleCertificate.ConsolePartNumber[2] << 4) & 0xF0) | (KeyVault.ConsoleCertificate.ConsolePartNumber[3] & 0x0F)))) {
		SetLiveBlock(true);
		RebootConsole();
	}

	delete Connection;

	

	return NetDll_XnpLogonSetChallengeResponseOriginal(XNCALLER_SYSAPP, s, ChallengeBuffer, BufferSize);
}

DWORD XeKeysExecuteHook(PBYTE Buffer, DWORD Size, PBYTE Salt, int* KrnlBuild, PDWORD r7, PDWORD r8)
{
	if (WantKvLess)
		GetKvData(6);

	//Hash our Payload, make sure this never changes
	if (!xbVerifyPayload(Buffer, Size))
	{
		SetLiveBlock(true);
		RebootConsole();
	}

	memset(Buffer, 0, Size);

	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

	if (!Connection->GetXamChallenge(g_Session, Salt, Spoofed_CPUKey, (((KeyVault.ConsoleCertificate.ConsolePartNumber[2] << 4) & 0xF0) | (KeyVault.ConsoleCertificate.ConsolePartNumber[3] & 0x0F)), Buffer)) {
		SetLiveBlock(true);
		RebootConsole();
	}

	//CWriteFile("xbOnline:\\ChallengeDidWeFuckup.bin", Buffer, 0x100);
	//memcpy(LastChallengeBufferXam, Buffer, Size);

	delete Connection;

	return ERROR_SUCCESS;
}


