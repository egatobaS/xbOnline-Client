#include "main.h"

/*
mflr %r11
std %r11, -8(%r1)
std %r31, -0x10(%r1)
std %r30, -0x18(%r1)
std %r29, -0x20(%r1)
std %r28, -0x28(%r1)
std %r27, -0x30(%r1)
std %r26, -0x38(%r1)
std %r25, -0x40(%r1)
stdu %r1, -0xF0(%r1)

mr %r3, %r4
mr %r4, %r5
mr %r5, %r6
mr %r6, %r7
mr %r7, %r8

li %r6, 0
cmpwi cr6, %r4, 0
blelr cr6
mtctr %r4

loc_loop:
lbzx %r5, %r6, %r3
xori %r5, %r5, 0x29
stbx %r5, %r6, %r3
addi %r6, %r6, 1
bdnz loc_loop

addi %r1, %r1, 0xF0
ld %r11, -8(%r1)
mtlr %r11
ld %r25, -0x40(%r1)
ld %r26, -0x38(%r1)
ld %r27, -0x30(%r1)
ld %r28, -0x28(%r1)
ld %r29, -0x20(%r1)
ld %r30, -0x18(%r1)
ld %r31, -0x10(%r1)
li %r3, 0
blr

*/

/*
mflr %r11
std %r11, -8(%r1)
std %r31, -0x10(%r1)
std %r30, -0x18(%r1)
std %r29, -0x20(%r1)
std %r28, -0x28(%r1)
std %r27, -0x30(%r1)
std %r26, -0x38(%r1)
std %r25, -0x40(%r1)
stdu %r1, -0xF0(%r1)

mr %r3, %r4
mr %r4, %r5
mr %r5, %r6
mr %r6, %r7
mr %r7, %r8

li        %r11, 0
cmpwi     cr6, %r4, 0
blelr     cr6
mtctr     %r4

loc_90E0A378:
lbzx      %r10, %r11, %r3
extsb     %r10, %r10
xor       %r10, %r10, %r4
xori      %r10, %r10, 0xC
not       %r10, %r10
extsb     %r10, %r10
stbx      %r10, %r11, %r3
addi      %r11, %r11, 1
bdnz      loc_90E0A378

addi %r1, %r1, 0xF0
ld %r11, -8(%r1)
mtlr %r11
ld %r25, -0x40(%r1)
ld %r26, -0x38(%r1)
ld %r27, -0x30(%r1)
ld %r28, -0x28(%r1)
ld %r29, -0x20(%r1)
ld %r30, -0x18(%r1)
ld %r31, -0x10(%r1)
li %r3, 0
blr

*/

/*
Made By Sabotage, Krazaki & OSM - 2017

Thanks to :

Sabotage - Stealing shit
Krazaki - Stealing shit too
OSM - Being a god
Konroi - Sponsorship & Funding
Jester - Inspiration & Shit talking
Alexb - Moral Support
TUC - Inspiration & Shit talking
Matrix Mods - responses on plain text
Nigel - Being a good bloke (and giving us all of james' shit & devkit loot (and don't forget, doing drugs))
Blasts Mods - Blasts Modding people
Jay - Hud shit
MLP - Server Security (He actually helped) & Pen testing
Anon Live - Pen testing
iMoD1998 - (This guy actually helped)
Exile - Moral Support
Lachie Web Dev (Panel)

*/



bool isFirst = false;

bool g_bDevKitMode = false;

bool g_GettingUpdate = false;

bool g_GotSessionKey = false;
bool g_isThreadRunning = false;

long long g_TimeleftInSeconds = 0;
unsigned long long g_Endtime = 0;
unsigned int g_ModuleBaseAddress = 0;

HANDLE g_hModule = 0;

Detour NetDll_XnpLogonSetChallengeResponseDetour;
LDR_DATA_TABLE_ENTRY g_EntryTable;
CLIENT_AUTH_STATUS g_GlobalStatus = NO_CONNECTED;

unsigned char MyCPUKey[16] = { 0 };

unsigned char g_Session[8] = { 0 };
unsigned char XEX_Hash[20] = { 0 };

unsigned char hBreakPattern[12] = {
	0x7C, 0x9A, 0x23, 0x78, 0x7C, 0xBE, 0x2B, 0x78, 0x38, 0xA0, 0x00, 0x00
};

unsigned char Corona_1BL_Key_Fix[16] = {
	0xDD, 0x88, 0xAD, 0x0C, 0x9E, 0xD6, 0x69, 0xE7, 0xB5, 0x67, 0x94, 0xFB,
	0x68, 0x56, 0x3E, 0xFA
};

unsigned char DmWalkLoadedModulesExPattern[16] = {
	0x94, 0x21, 0xFF, 0x40, 0x7C, 0x77, 0x1B, 0x78, 0x7C, 0x96, 0x23, 0x78,
	0x3E, 0xA0, 0x02, 0xDA
};


//void SearchForFiles(std::vector<std::string>&  Files, const char* Directory, const char* Type)
//{
//	WIN32_FIND_DATA file;
//	HANDLE search_handle = FindFirstFile(Directory, &file);
//
//	if (search_handle)
//	{
//		do
//		{
//			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//			{
//				if ((!lstrcmp(file.cFileName, ".")) || (!lstrcmp(file.cFileName, "..")))
//					continue;
//
//				std::string FilePath = Directory;
//				FilePath = FilePath.substr(0, FilePath.size() - 1);
//				FilePath = (FilePath + (std::string)file.cFileName + "\\*").c_str();
//
//				SearchForFiles(Files, FilePath.c_str(), Type);
//			}
//			else
//			{
//				std::string FilePath = Directory;
//				FilePath = FilePath.substr(0, FilePath.size() - 1);
//				FilePath = FilePath + (std::string)(file.cFileName);
//
//				if (FilePath.find(Type) != std::string::npos)
//					Files.push_back(FilePath);
//			}
//		} while (FindNextFile(search_handle, &file));
//		FindClose(search_handle);
//	}
//
//}
//
//std::vector<std::string> GetAllFilesOfType(const char* Directory, const char* Type)
//{
//	std::vector < std::string> Files;
//
//	SearchForFiles(Files, Directory, Type);
//
//	return  Files;
//}
//
//
//bool ReadStuff(LPCSTR FileName, PVOID Buffer, ULONG Length, LONG Start)
//{
//	long st = 0;
//	HANDLE FileHandle;
//
//	IO_STATUS_BLOCK io;
//
//	FileHandle = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (FileHandle == INVALID_HANDLE_VALUE) {
//		return FALSE;
//	}
//
//	if (FAILED(st))
//		return false;
//
//
//	LARGE_INTEGER FilePointer = { 0 };
//
//
//	FilePointer.LowPart = Start;
//	st = NtReadFile(FileHandle, NULL, NULL, NULL, &io, Buffer, Length, &FilePointer);
//
//	if (FAILED(st))
//	{
//		CloseHandle(FileHandle);
//		return false;
//	}
//
//	CloseHandle(FileHandle);
//
//	return true;
//}
//
//int GetXexTitleID(const char* Path)
//{
//	unsigned char Buffer[0x1000] = { 0 };
//
//	if (ReadStuff(Path, Buffer, 0x1000, 0))
//	{
//		for (int i = 0; i < 0x1000; i += 4)
//		{
//			if (*(int*)(Buffer + i) == 0x00040006)
//			{
//				int Position = *(int*)(Buffer + i + 0x4);
//
//				if (ReadStuff(Path, Buffer, 0x10, Position))
//					return *(int*)(Buffer + 0xC);
//				else return -1;
//			}
//		}
//	}
//	return -1;
//}

void Presence()
{

	//if (CreateSymbolicLink("xbOnlineUsb:\\", NAME_USB, TRUE) != ERROR_SUCCESS) {
	//}
	//unsigned long long TimeAtStart = GetTickCount();
	//DbgPrint("Starting Search\n");
	//std::vector < std::string> FilesUsbs = GetAllFilesOfType("xbOnlineUsb:\\*", ".xex");
	//std::vector < std::string> FilesHdd = GetAllFilesOfType("xbOnline:\\*", ".xex");
	//DbgPrint("Search Ended at: %i\n", GetTickCount() - TimeAtStart);
	//for (int i = 0; i < FilesHdd.size(); i++)
	//{
	//	DbgPrint("%s %X\n", FilesHdd[i].c_str(), GetXexTitleID(FilesHdd[i].c_str()));
	//}
	//for (int i = 0; i < FilesUsbs.size(); i++)
	//{
	//	DbgPrint("%s %X\n", FilesUsbs[i].c_str(), GetXexTitleID(FilesHdd[i].c_str()));
	//}
	//
	DownloadGameAddresses();

	while (!g_isThreadRunning)
	{
		unsigned char CPUKey[0x10] = { 0 };
		unsigned char Geneology[0x10] = { 0 };

		Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

		Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

		Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

		if (Connection->Presence(g_Session, &g_TimeleftInSeconds, &g_GlobalStatus)) {
			isFirst = true;
			g_Endtime = time(NULL) + g_TimeleftInSeconds;
		}


		if (isFirst && server_cod_mw)
		{
#if defined(DEVKIT)
#else
			WriteDank();
#endif
		}

		if (isFirst)
			Sleep(30000);

		delete Connection;
	}
}



void GetSessionKey()
{

	Sleep(1000);

#if defined(DEVKIT)
#else
	bool hasInit = false;
	if (xb_custom_xui && !hasInit)
	{
		HANDLE hThread1 = 0; DWORD threadId1 = 0;

		ExCreateThread(&hThread1, 0, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)PathHuds, NULL, 0x2);
		XSetThreadProcessor(hThread1, 4);
		ResumeThread(hThread1);
		CloseHandle(hThread1);
		hasInit = true;
	}
#endif

	if (!g_GotSessionKey)
	{
		while (g_GlobalStatus == NO_CONNECTED)
		{
			XNADDR xna = { 0 };

			int i = XNetGetTitleXnAddr(&xna);

			if (i != XNET_GET_XNADDR_PENDING) {

				if (xna.ina.S_un.S_un_b.s_b1 == 0 && xna.ina.S_un.S_un_b.s_b2 == 0 && xna.ina.S_un.S_un_b.s_b3 == 0 && xna.ina.S_un.S_un_b.s_b4 == 0) {

					Sleep(100);

					continue;
				}

				unsigned char CPUKey[0x10] = { 0 };
				unsigned char Geneology[0x10] = { 0 };

				Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

				Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

				Client Connection(CPUKey, Geneology, XEX_Hash);

				if (Connection.GetSession(g_Session, &g_TimeleftInSeconds, &g_GlobalStatus) && !GotAnewUpdate) {

					g_Endtime = time(NULL) + g_TimeleftInSeconds;

					g_GotSessionKey = true;

					HANDLE hThread1 = 0; DWORD threadId1 = 0;
					ExCreateThread(&hThread1, 0, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)Presence, NULL, 2 | CREATE_SUSPENDED);
					XSetThreadProcessor(hThread1, 4);
					ResumeThread(hThread1);
					CloseHandle(hThread1);
				}

				if (g_GlobalStatus != NO_CONNECTED)
					break;
			}
		}
	}
}

void Init()
{
	SetLiveBlock(true);
	if (!Mount_Drive())
	{
		if (!DriveOverRide())
			if (OpenedTray()) return;

		if (!InitializeHvPeekPoke())
		{
			if (!ProcessCPUKeyBin(PATH_CPUKEYB))
			{
				LoadINI();

				g_bDevKitMode = *(DWORD*)0x8E038610 & 0x8000 ? false : true;

				//
				if (!FileExists("xbOnline:\\dummy."))
				{
					unsigned char* xboProtect = (unsigned char*)malloc(0x4000);

					memset(xboProtect, 0, 0x4000);

					CWriteFile("xbOnline:\\dummy.", xboProtect, 0x4000);
					free(xboProtect);
				}

				DWORD Version = ((XboxKrnlVersion->Major & 0xF) << 28) | ((XboxKrnlVersion->Minor & 0xF) << 24) | (XboxKrnlVersion->Build << 8) | (XboxKrnlVersion->Qfe);
				ZeroMemory(&SpoofedExecutionId, sizeof(XEX_EXECUTION_ID));
				SpoofedExecutionId.Version = Version;
				SpoofedExecutionId.BaseVersion = Version;
				SpoofedExecutionId.TitleID = 0xFFFE07D1;

				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 408, (int)XexLoadExecutableHook, false);
				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 409, (int)XexLoadImageHook, false);
				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 410, (int)XexLoadImageFromMemory_XamHook, false);
				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 0x12B, (int)RtlImageXexHeaderFieldHook, false);
				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 404, (int)XexCheckExecutablePrivilegeHook, false);
				Tramps->CallFunction(PatchModuleImport_Function, (int)MODULE_XAM, (int)MODULE_KERNEL, 0x25F, (int)XeKeysExecuteHook, false);

#if defined(DEVKIT)
				NetDll_XnpLogonSetChallengeResponseDetour.HookFunction((DWORD)0x81A1BEB0, (DWORD)NetDll_XnpLogonSetChallengeResponse);

				*(DWORD*)0x817A5484 = 0x38600006;
				*(DWORD*)0x81CB9874 = 0x38600001;
				*(DWORD*)0x81732850 = 0x38600000;

				*(DWORD*)0x800af860 = 0x60000000;

#else



				InitializeCriticalSection(&KvProtectionSection);
				//if (xb_custom_kvp)
				IoCreateFileOriginal = (IoCreateFile_t)IoCreateFileDetour.HookFunction((DWORD)0x8006B0B0, (DWORD)IoCreateFileHook);

				HvPokeDWORD(0x8000010600032198, 0x38600001);
				HvPokeDWORD(0x8000010600032158, 0x60000000);
				HvPokeDWORD(0x8000010600032168, 0x60000000);

				//Poke the 1BL to the Hypervisor, otherwise coronas cannot execute payloads through HvxKeysExecute.
				HvPokeBytes(0x8000010200016390, Corona_1BL_Key_Fix, 16);

				NetDll_XnpLogonSetChallengeResponseDetour.HookFunction((DWORD)0x81857310, (DWORD)NetDll_XnpLogonSetChallengeResponse); //Update

				*(int*)0x8167F8D8 = 0x38600000; //Update
				*(int*)(0x81689780) = 0x4E800020; //Update
				*(int*)(0x81689688) = 0x4E800020; //Update
#endif	
				HANDLE hThread1 = 0; DWORD threadId1 = 0;
				ExCreateThread(&hThread1, 0, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)UnloadMonitorThread, NULL, 2 | CREATE_SUSPENDED);
				XSetThreadProcessor(hThread1, 4);
				ResumeThread(hThread1);
				CloseHandle(hThread1);

				if (!Process_KV())
				{
					ProcessKeyVault();

					if (!SetMacAddress())
					{
						XamCacheReset(XAM_CACHE_TICKETS);
						Tramps->CallFunction(memcpy_Function, (int)0x8E03AA40, (int)KVDigest, 0x10, 0, false);
					}
				}

				CreateXboxThread(GetSessionKey, GetSessionKey);
			}
		}
	}
}

void RegisterFunctions()
{
	Tramps->RegisterFunction((int)Init, Init_Function);
	Tramps->RegisterFunction((int)Presence, Presence_Thread);
	Tramps->RegisterFunction((int)PatchModuleImport, PatchModuleImport_Function);
	Tramps->RegisterFunction((int)GetCPUKey, GetCPUKey_Function);
	Tramps->RegisterFunction((int)xbCreateBoxKey, xbCreateBoxKey_Function);
	Tramps->RegisterFunction((int)ExecuteCode, ExecuteCode_Function);
	Tramps->RegisterFunction((int)memcpy, memcpy_Function);
}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		Tramps = new Tampoline();

		RegisterFunctions();

		AntiPasswordTheft();
#if defined(DEVKIT)

		ApplyPatches(rglXam);

		*(int*)(0x819658d0) = 0x60000000;
		*(int*)(0x81965924) = 0x60000000;
		*(int*)(0x8175C8EC) = 0x48000010;
		*(int*)(0x817B3A14) = 0x60000000;

		CurrentPath = (int)malloc(0x100);
		GetBootedPath((HMODULE)ModuleHandle, (char*)CurrentPath);
#else
		CurrentPath = *(int*)(0x81670FFC);
#endif	
		ApplyPatches(Console_Patches);

		::g_hModule = ModuleHandle;

		memcpy(&g_EntryTable, ModuleHandle, sizeof(LDR_DATA_TABLE_ENTRY));
		g_ModuleBaseAddress = (unsigned int)g_EntryTable.NtHeadersBase;

		Tramps->CallFunction(Init_Function, 0, 0, 0, 0, false);


#if defined(DEVKIT)
		HrBreakOriginal = (HrBreakStub)HrBreakDetour.HookFunction(0x91F48A38, (unsigned int)HrBreak);
		MmIsAddressValidOriginal = (MmIsAddressValid_t)MmIsAddressValidDetour.HookFunction((DWORD)ResolveFunction("xboxkrnl.exe", 191), (DWORD)MmIsAddressValidHook);
		MmDbgReadCheckOriginal = (MmDbgReadCheck_t)MmDbgReadCheckDetour.HookFunction((DWORD)ResolveFunction("xboxkrnl.exe", 427), (DWORD)MmDbgReadCheckHook);
		Tramps->CallFunction(PatchModuleImport_Function, (int)"xbdm.xex", (int)MODULE_KERNEL, 191, (int)MmIsAddressValidHook, false);
		Tramps->CallFunction(PatchModuleImport_Function, (int)"xbdm.xex", (int)MODULE_KERNEL, 427, (int)MmDbgReadCheckHook, false);
#else


		MmIsAddressValidOriginal = (MmIsAddressValid_t)MmIsAddressValidDetour.HookFunction((DWORD)ResolveFunction("xboxkrnl.exe", 191), (DWORD)MmIsAddressValidHook);
		MmDbgReadCheckOriginal = (MmDbgReadCheck_t)MmDbgReadCheckDetour.HookFunction((DWORD)ResolveFunction("xboxkrnl.exe", 427), (DWORD)MmDbgReadCheckHook);
		Tramps->CallFunction(PatchModuleImport_Function, (int)"xbdm.xex", (int)MODULE_KERNEL, 191, (int)MmIsAddressValidHook, false);
		Tramps->CallFunction(PatchModuleImport_Function, (int)"xbdm.xex", (int)MODULE_KERNEL, 427, (int)MmDbgReadCheckHook, false);

		DmWalkLoadedModulesExOrginal = (DmWalkLoadedModulesExStub)DmWalkLoadedModulesExDetour.HookFunction(((unsigned int)AlignedMemorySearch(".text", DmWalkLoadedModulesExPattern, 16) - 0x8), (unsigned int)DmWalkLoadedModulesEx);
		HrBreakOriginal = (HrBreakStub)HrBreakDetour.HookFunction(((unsigned int)AlignedMemorySearch(".text", hBreakPattern, 12) - 0x10), (unsigned int)HrBreak);
#endif	
		RemoveFromList(ModuleHandle);
}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{

		g_isThreadRunning = true;
		Sleep(2000);
	}

	return TRUE;

}



