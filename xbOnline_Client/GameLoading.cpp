#include "main.h"

WCHAR xbOnlineModuleErrorMessage[0x200] = { 0 };

byte b1BLKey[16] = { 0xDD,0x88,0xAD,0x0C,0x9E,0xD6,0x69,0xE7,0xB5,0x67,0x94,0xFB,0x68,0x56,0x3E,0xFA }; //Hypervisor 0x16390
byte bHvRomMagic[16] = { 0x4E, 0x4E, 0x44, 0x67, 0x00, 0x00, 0x58, 0x42, 0x4F, 0x58, 0x5F, 0x52, 0x4F, 0x4D, 0x5F, 0x42 }; //Hypervisor 0x16260 (Includes Kernel Version, which we will take from 0x2 in the HV)
byte GameKey[6] = { 0x05, 0x71, 0x84, 0x91, 0xD1, 0xC7 };

CheatManager GameManager;

void DownloadGameAddress(int TitleID, void* GameData, int Size)
{
	printf("Downloading Game Data For Title ID: %X\n", TitleID);
	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	printf("Geneology:");
	for (int i = 0; i < 16; i++)
		printf("%02X", Geneology[i]);
	printf("\n");

	Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

	if (Connection->GetCheatData(g_Session, 0, TitleID, (unsigned char*)GameData, Size)) {

	}
	delete Connection;
}

void LoadCheat(int TitleID)
{
	ThreadPastGameData* Data = (ThreadPastGameData*)TitleID;
	ThreadPastGameData* SecondGame = (ThreadPastGameData*)Data->AnotherGame;

	if (Data->istoLoadAnotherGame)
	{
		if (SecondGame->isCheatEnabled)
			GameManager.LoadCheat(SecondGame->ID, SecondGame->TitleID, SecondGame->titleName, SecondGame->titleIp, SecondGame->Name);
	}

	if (Data->isCheatEnabled)
		GameManager.LoadCheat(Data->ID, Data->TitleID, Data->titleName, Data->titleIp, Data->Name);

	if (Data->istoLoadAnotherGame)
		delete SecondGame;

	delete Data;
}

CheatManager::CheatManager()
{
	for (int i = 0; i < 30; i++) {
		isModuleLoaded[i] = false;
		Modulehandle[i] = 0;
	}
	LastTitleIDPlayed = 0;
}

void CheatManager::UnloadCheats()
{
	printf("Starting to Unload Cheato\n");

	for (int i = 0; i < 30; i++)
	{
		printf("Data with ID %i: %X %X %X %X\n", i, isModuleLoaded[i], Modulehandle[i], LastTitleIDPlayed, XamGetCurrentTitleId());

		if (isModuleLoaded[i] && Modulehandle[i] && (LastTitleIDPlayed != XamGetCurrentTitleId() || (LastTitleIDPlayed == XamGetCurrentTitleId() && !isChallengeMultiplayer)))
		{
			for (int e = 0; e < 255; e++) {
				lastCheatLoadedPath[i][e] = 0;
			}
			*(short*)((int)Modulehandle[i] + 0x40) = 0x01;

			printf("XexUnloadImage Ret: %X\n", XexUnloadImage(Modulehandle[i]));

			printf("Cheat is supposed to be unloaded\n");

			isModuleLoaded[i] = false;
			Modulehandle[i] = 0;
		}
	}
}

void CheatManager::UnloadCheatsNoMP()
{
	printf("Starting to Unload Cheato\n");

	for (int i = 0; i < 30; i++)
	{
		printf("Data with ID %i: %X %X %X %X\n", i, isModuleLoaded[i], Modulehandle[i], LastTitleIDPlayed, XamGetCurrentTitleId());

		if (isModuleLoaded[i] && Modulehandle[i] && (LastTitleIDPlayed != XamGetCurrentTitleId()))
		{
			for (int e = 0; e < 255; e++) {
				lastCheatLoadedPath[i][e] = 0;
			}
			*(short*)((int)Modulehandle[i] + 0x40) = 0x01;

			printf("XexUnloadImage Ret: %X\n", XexUnloadImage(Modulehandle[i]));

			printf("Cheat is supposed to be unloaded\n");

			isLastTitleTF2 = false;
			isLastTitleCSGO = false;

			isModuleLoaded[i] = false;
			Modulehandle[i] = 0;
		}
	}
}


#pragma optimize( "", off )

__int64 __declspec(naked) TestHook()
{
	int Local_r3, Local_r11;
	__asm
	{
		mflr    r12
		stw     r12, -8(r1)
		std     r31, -0x10(r1)
		stwu    r1, -0x88(r1)

		mr Local_r3, r3
		mr Local_r11, r11
	};


	if (Local_r11 == 0x90a19020)
	{
		if (*(int*)(0x90A09AD0) == 0x3C8081A7)
		{
			*(int*)(0x90A09AD0) = 0x3C8081A7;
			*(int*)(0x90A09AD4) = 0x60841B6C;
		}

	}

	if (Local_r11 == 0x91a1cf30)
	{
		if (*(int*)(0x91A102AC) == 0x3C8081A7)
		{
			*(int*)(0x91A102AC) = 0x3C8081A7;
			*(int*)(0x91A102B0) = 0x60841B6C;
		}
	}

	__asm
	{
		li r5, 0
		li r4, 1
		mr r11, Local_r11
		mr r3, Local_r3
		mtctr r11
		bctrl
		addi    r1, r1, 0x88
		lwz     r12, -8(r1)
		mtlr    r12
		ld      r31, -10h(r1)
		blr

	}
}

#pragma optimize( "", on ) 




void CheatManager::LoadCheat(int ID, int TitleID, const char* titleName, const char* titleIp, const char* Name)
{
	char TempIpBuffer[255] = { 0 };
	char OriginalIP[255] = { 0 };
	strcpy(OriginalIP, titleIp);
	strcpy(TempIpBuffer, ServerTwoIp);

	printf("LoadCheat Called with ID: %i for %s\n", ID, titleName);


	for (int i = 0; i < 30; i++)
	{
		printf("Comparing to String %s\n", &lastCheatLoadedPath[i][0]);

		if (isModuleLoaded[i] && Modulehandle[i] && !strcmp(titleName, &lastCheatLoadedPath[i][0])) {

			printf("LoadCheat Xex Unloaded and waiting to reload\n");

			for (int e = 0; e < 255; e++) {
				lastCheatLoadedPath[i][e] = 0;
			}

			*(short*)((int)Modulehandle[i] + 0x40) = 0x01;

			XexUnloadImage(Modulehandle[i]);

			isModuleLoaded[i] = false;
			Modulehandle[i] = 0;

		}
	}
	isModuleLoaded[ID] = false;

	printf("Copying titleName to Buffer\n");

	strcpy(&lastCheatLoadedPath[ID][0], titleName);

	if ((XamGetCurrentTitleId() == TitleID))
	{
		printf("Title ID found and starting load\n");

		int ModuleLength = 0;
		unsigned char* KrazakisShoe = 0;

		int DownloadTries = 0;

		printf("Starting download Loop\n");

		while (DownloadTries < 50)
		{

			if (DownloadFile(TempIpBuffer, titleName, &KrazakisShoe, &ModuleLength))
			{
				if ((KrazakisShoe <= 0) || (ModuleLength <= 0))
				{
					printf("Size or Module Pointer was NULL\n");
					continue;
				}

				if (ModuleLength < 0x14)
					continue;

				printf("Xex downloaded from ip: %s\n", TempIpBuffer);

				unsigned char DataDigest[0x14] = { 0 };
				sha1(KrazakisShoe, ModuleLength - 0x14, DataDigest);

				if (!memcmp(DataDigest, &KrazakisShoe[ModuleLength - 0x14], 0x14)) {

					printf("digest completed and correct\n");

					RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), b1BLKey, 16, b1BLKey[1]);
					RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), bHvRomMagic, 16, b1BLKey[1]);
					RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), GameKey, 6, GameKey[2]);

					LastTitleIDPlayed = XamGetCurrentTitleId();

					LoadedForTitleID[ID] = LastTitleIDPlayed;

					printf("Loading xex via XexLoadImageFromMemory_\n");
					Sleep(500);

					bool ImageBaseFound = false;
					DWORD ImageBaseAddress = 0;

					unsigned int* ImageMemoryBuffer = (unsigned int*)(KrazakisShoe + 0x32FF);

					for (int i = 0; i < 0x40; i++) {

						if (ImageMemoryBuffer[i] == 0x00010201) {
							ImageBaseFound = true;
							ImageBaseAddress = ImageMemoryBuffer[i + 1];
							break;
						}
					}

					if (ImageBaseAddress != 0)
					{
						HANDLE LoadedModuleHandle = GetModuleHandleByBaseAddress(ImageBaseAddress);
						if (LoadedModuleHandle != (HANDLE)-1)
						{
							PLDR_DATA_TABLE_ENTRY Module = (PLDR_DATA_TABLE_ENTRY)LoadedModuleHandle;

							//DbgPrint("Found bad module:  %ws\n", Module->BaseDllName.Buffer);

							if (Module->BaseDllName.Buffer)
								swprintf(xbOnlineModuleErrorMessage, L"xbOnline Cheats failed to load!\nPlease remove %ws", Module->BaseDllName.Buffer);
							else
								swprintf(xbOnlineModuleErrorMessage, L"xbOnline Cheats failed to load!\nPlease remove incompatible plugin(s)");

							XNotify(xbOnlineModuleErrorMessage);
							Modulehandle[ID] = 0;
							isModuleLoaded[ID] = false;

							break;
						}
					}
					//XexLoadImage("xbOnline:\\IW3MP.xex", 8, 0, &Modulehandle[ID]);

					int LocalVariable = (int)TestHook;

					int bk_1 = *(int*)0x8007A6EC;
					int bk_2 = *(int*)0x8007A6F0;
					int bk_3 = *(int*)0x8007A6F8;

					*(int*)0x8007A6EC = 0x3d800000 | ((LocalVariable & 0xFFFF0000) >> 16);
					*(int*)0x8007A6F0 = 0x618c0000 | (LocalVariable & 0x0000FFFF);
					*(int*)0x8007A6F8 = 0x7d8903a6;

					XexLoadImageFromMemory_(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), Name, 8, 0, (HMODULE*)&Modulehandle[ID]);

					*(int*)0x8007A6EC = bk_1;
					*(int*)0x8007A6F0 = bk_2;
					*(int*)0x8007A6F8 = bk_3;

					if (Modulehandle[ID])
					{
						printf("Modulehandle: %X\n", Modulehandle[ID]);

						isModuleLoaded[ID] = true;

						if (KrazakisShoe)
							XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);

						break;
					}
					else
					{
						printf("XEX did not loaded Handle Empty\n");
					}
				}
				else printf("Hash failed from ip: %s\n", TempIpBuffer);

				if (KrazakisShoe)
					XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);
			}
			else printf("Download failed ip: %s\n", TempIpBuffer);


			if (DownloadTries % 2)
				strcpy((char*)TempIpBuffer, OriginalIP);
			else
				strcpy((char*)TempIpBuffer, ServerTwoIp);

			DownloadTries++;


		}
	}
	//if ( !isModuleLoaded[ ID ] )
	//	XNotify( L"xbOnline Cheats Failed to Load! - Please check your plugin list!" );
}

int CheatManager::GetValidID()
{
	for (int i = 0; i < 30; i++) {

		if (!GameManager.isModuleLoaded[i] && !GameManager.Modulehandle[i]) {
			isModuleLoaded[i] = true;
			return i;
		}
	}
	return -1;
}




