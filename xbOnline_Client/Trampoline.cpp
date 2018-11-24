#include "main.h"

Tampoline* Tramps;

int Tampoline::CallFunction(int FunctionID, long long Param1, long long Param2, long long Param3, long long Param4, bool ping)
{
	void* ptr = ResolveFunction(FunctionID);

	if (ping)
		return ((int(*)(...))ptr)(Param1, Param2, Param3, Param4);
	else
		return CallFunction((int)FunctionID, Param1, Param2, Param3, Param4, true);

	return 0;
}

void Tampoline::RegisterFunction(int Address, int ID)
{
	RegisterCount++;

	this->Address.resize(RegisterCount + 1);

	long long address = Address;
	address = (address << 32) | ID;

	this->Address[RegisterCount] = address;
}

void* Tampoline::ResolveFunction(int ID)
{
	for (int i = 0; i <= RegisterCount; i++)
	{
		if (ID == (this->Address[i] & 0xFFFFFFFF)) {
			return (void*)(this->Address[i] >> 32);
		}
	}
	return (void*)-1;
}

Tampoline::Tampoline()
{
	RegisterCount = 0;
}



void GetNewUpdate()
{
	int Attempts = 0;

	int XEX_SIZE = 0;

	unsigned char* XBO_XEX = 0;

	while (Attempts < 50)
	{
		if (XBO_XEX)
			free(XBO_XEX);

		if (DownloadFile("IP here", "/XEXHERE.xex", &XBO_XEX, &XEX_SIZE))
		{
			if (XEX_SIZE && XBO_XEX && *(int*)(XBO_XEX) == 0x58455832)
			{
				unsigned char xbSha[0x14] = { 0 };

				sha1(XBO_XEX, (XEX_SIZE - 0x14), xbSha);

				if (!memcmp(xbSha, &XBO_XEX[XEX_SIZE - 0x14], 0x14))
				{
					printf("Path: %s\n", CurrentPath);

					if (CWriteFile((char*)CurrentPath, XBO_XEX, (XEX_SIZE - 0x14)))
					{
						printf("Xex Downloaded\n");

						break;
					}
				}
				else printf("File Digest Didn't Match\n");
			}
		}
		Attempts++;
		Sleep(50);
	}
}