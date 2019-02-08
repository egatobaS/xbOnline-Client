#include "main.h"

unsigned int * BF3_addr_s_PatchID = 0;
Security * BF3_addr_s_Data = 0;

typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator* (const float mul)
	{
		return Vector3(this->x *= mul, this->y *= mul, this->z *= mul);
	}

	const bool operator != (Vector3 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	float Distance(Vector3 const &Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z); }

	inline Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	const Vector3 &RoundHalfUpF()
	{
		return Vector3((float)floor(this->x + 0.5), (float)floor(this->y + 0.5), (float)floor(this->z + 0.5));
	}\
		const Vector3 &RoundHalfDown()
	{
		return Vector3((float)floor(this->x + 0.5), (float)floor(this->y + 0.5), (float)floor(this->z + 0.5));
	}
} Vector3, *PVector3;

struct GAME_ADDRESSES_BF3
{
	int _0x834162D8;
	int _0x83CFF480;
	int _0x834F63C8;
	int _0x83C44E30;
	int _0x83CFFAA0;
	int _0x8315F850;
	int _0x82D80000;
	int _0x191;
	int _0x83D00B58;
	int _0x83266AC0;
	int _0x831FAD00;
	int _0x834CC888;
	int _0x831FB1D8;
	int _0x83212338;
	int _0xDB0;
	int _0x836F4390;
	int _0x841289FC;
	int _0x8420E38C;
	int _0x835F4878;
	int _0x83D131D0;
	int _0x836D01E4;
	int _0x836FDAC8;
	int _0x834FC41C;
	int _0x834FB424;
	int _0x834FB3D0;
	int _0x83504BBC;
	int _0x835054C0;
	int _0x83505268;
	int _0x835054FC;
	int _0x8350498C;
	int _0x83504990;
	int _0x83504994;
	int _0x836bbf98;
	int _0x38600001;
	int _0x39600001;
	int _0x42400020;
	int _0x60000000;
	int _0x4800003C;
	int _0x917F02A4;
	int _0x38600000;
	int _0x39600000;
	int _0x4240004C;
	int _0x419A0B38;
	int _0x409A0DA4;
	int _0x419A003C;
	int _0x89590035;
	int _0x2B0A0000;
	int _0x419A01AC;
	int _0x4E800421;
	int _0x840603E0;
	int _0x84122028;
	int _0x835F48BC;
	int _0x835F48C8;
	int _0x835F48D0;
	int _0x835F48D8;
	int _0x835F48B0;
	int _0x835F48B4;
	int _0x39000000;
	int _0x38E0FFFF;
	int _0x38C00004;
	int _0x38A00000;
	int _0x7FC4F378;
	int _0x8406041F;
	int _0x8340E610;
};

struct GAME_ADDRESS_TRANSFER_BF3
{
	GAME_ADDRESSES_BF3* Addresses;

	void* GetDistance;
	void* VectorLength2D;
	void* CreateSystemThread;
	void* MmIsAddressValidPtr;
	void* GetAsyncKeyState;
	void* CWriteFile;
	void* FileExists;

	void* sendSpottingMessage;
	void* GetPlayerScore;
	void* AddDamageData;
	void* sub_835F4878;
	void* sub_83D131D0;
	void* GetAmmoPtr;
	void* CCMessage;
	void* ReloadMessageFunction;

};

GAME_ADDRESS_TRANSFER_BF3* ExternalFunctions;
GAME_ADDRESSES_BF3* Addresses;

enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};


void BF3_SetupGameAddresses(ServerData_BF3* Server)
{
	if (BF3_addr_s_Data)
		delete BF3_addr_s_Data;

	BF3_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		BF3_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	BF3_addr_s_Data = new Security(t, g_Session);
	BF3_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, BF3_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

int BF3_sub_835F4878(unsigned char* r3, unsigned char* r4)
{
	int(*sub_835F4878)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))Addresses->_0x835F4878;

	return sub_835F4878(r3, r4);
}


int BF3_sub_83D131D0(unsigned char* r3, unsigned char* r4)
{
	int(*sub_83D131D0)(unsigned char* r3, unsigned char* r4) = (int(*)(unsigned char* r3, unsigned char* r4))Addresses->_0x83D131D0;

	return sub_83D131D0(r3, r4);
}

int BF3_GetAmmoPtr(int x, int y, int z)
{
	int(*GetAmmoPtr)(int x, int y, int z) = (int(*)(int x, int y, int z))Addresses->_0x83266AC0;

	return GetAmmoPtr(x, y, z);
}

int BF3_CCMessage(int*a, int*b)
{
	int(*CCMessage)(int*, int*) = (int(*)(int*, int*))Addresses->_0x831FAD00;

	return CCMessage(a, b);
}

int BF3_ReloadMessageFunction(int r3, int r4, int r5)
{
	int(*ReloadMessageFunction)(int r3, int r4, int r5) = (int(*)(int r3, int r4, int r5))Addresses->_0x834CC888;

	return ReloadMessageFunction(r3, r4, r5);

}
int BF3_AddDamageData(int* a, int* b)
{
	int(*AddDamageData)(int*, int*) = (int(*)(int*, int*))Addresses->_0x831FB1D8;

	return AddDamageData(a, b);
}

int BF3_GetPlayerScore(int*a, int*b)
{
	int(*GetPlayerScore)(int*, int*) = (int(*)(int*, int*))Addresses->_0x83212338;

	return GetPlayerScore(a, b);
}

int BF3_sendSpottingMessage(int* thisClientSpottingComponent, int* MyClientPlayer, int *controllablesToSpot, int type)
{
	int(*sendSpottingMessage)(int* thisClientSpottingComponent, int* MyClientPlayer, int*controllablesToSpot, int type) = (int(*)(int* thisClientSpottingComponent, int* MyClientPlayer, int*controllablesToSpot, int type))Addresses->_0x8340E610;

	return sendSpottingMessage(thisClientSpottingComponent, MyClientPlayer, controllablesToSpot, type);
}

DWORD BF3_ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HANDLE hModule; DWORD Address;
	XexGetModuleHandle(ModuleName, &hModule);
	XexGetProcedureAddress(hModule, Ordinal, &Address);
	return Address;
}

DWORD BF3_XNotifyThread(wchar_t *Message)
{
	while (((int(*)(DWORD exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData))BF3_ResolveFunction("xam.xex", 0x290))(34, 0xFF, 2, Message, 0) == ERROR_ACCESS_DENIED)
		Sleep(10);

	return 0;
}

int * BF3_GetDetours()
{
	return (int*)new Detour();
}

VOID BF3_XNotify(CONST PWCHAR NotifyText)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)BF3_XNotifyThread, NotifyText, 0);
}

void* BF3_HookFunction(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (unsigned int)c);
}


float BF3_GetDistance(Vector3 c1, Vector3 c2)
{
	Vector3 Sub = c1 - c2;
	return (sqrt((float)((Sub.x * Sub.x) + (Sub.y * Sub.y) + (Sub.z * Sub.z))) / 55.0f);
}

float BF3_VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

const DWORD MMIORangeTable[] =
{
	0x7FC80000,
	0x7FC9FFFF,
	0x7FD00000,
	0x7FDFFFFF,
	0x7FEA0000,
	0x7FEAFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x8FFF0000,
	0x8FFF0FFF,
	0x8FFF1000,
	0x8FFF1FFF,
	0x00000000,
	0x00000000,

};

BOOL BF3_FIsMmIoAddress(PVOID addr)
{
	int i = 0;

	for (i = 0; MMIORangeTable[i]; i += 2) {
		if (((DWORD)addr > MMIORangeTable[i]) && ((DWORD)addr < MMIORangeTable[i + 1]))
			return TRUE;
	}

	return FALSE;
}

bool BF3_MmIsAddressValidPtr(void* ptr)
{
	if (((int)ptr > 0x30000000))
		return (!BF3_FIsMmIoAddress(ptr) && MmIsAddressValid(ptr));

	return false;
}

BOOL BF3_FileExists(LPCSTR lpFileName)
{
	if (GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}
	return TRUE;
}

void BF3_CreateSystemThread(void* Function, void* Param)
{
	HANDLE hThread1 = 0; DWORD threadId1 = 0;
	ExCreateThread(&hThread1, 0x10000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)Function, Param, 0x2);
	XSetThreadProcessor(hThread1, 4);
	ResumeThread(hThread1);
	CloseHandle(hThread1);
}

int BF3_GetAsyncKeyState(DWORD KEY)
{
	XINPUT_STATE InputState;
	XInputGetState(0, &InputState);

	if (!KEY)
		return true;

	if (KEY == KEY_LT) {
		return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	}

	if (KEY == KEY_RT)
		return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return InputState.Gamepad.wButtons & KEY;
}

bool BF3_CWriteFile(const char* FilePath, const void* Data, unsigned int Size)
{
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	DWORD writeSize = Size;
	if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE) {
		return FALSE;
	}
	CloseHandle(fHandle);
	return TRUE;
}

bool BattleField3_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_BF3;

	if (Addresses)
		free(Addresses);

	Addresses = (GAME_ADDRESSES_BF3*)malloc(sizeof(GAME_ADDRESSES_BF3));

	memset(Addresses, 0, sizeof(GAME_ADDRESSES_BF3));


	for (int i = 0; i < 64; i++)
		((int*)(Addresses))[i] = GetAddress(BF3_addr_s_Data, BF3_addr_s_PatchID, i);

	ExternalFunctions->Addresses = Addresses;


	ExternalFunctions->GetDistance = (void*)ReverseInt((int)BF3_GetDistance);
	ExternalFunctions->VectorLength2D = (void*)ReverseInt((int)BF3_VectorLength2D);
	ExternalFunctions->CreateSystemThread = (void*)ReverseInt((int)BF3_CreateSystemThread);
	ExternalFunctions->MmIsAddressValidPtr = (void*)ReverseInt((int)BF3_MmIsAddressValidPtr);
	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((int)BF3_GetAsyncKeyState);
	ExternalFunctions->CWriteFile = (void*)ReverseInt((int)BF3_CWriteFile);
	ExternalFunctions->FileExists = (void*)ReverseInt((int)BF3_FileExists);
	ExternalFunctions->sendSpottingMessage = (void*)ReverseInt((int)BF3_sendSpottingMessage);
	ExternalFunctions->GetPlayerScore = (void*)ReverseInt((int)BF3_GetPlayerScore);
	ExternalFunctions->AddDamageData = (void*)ReverseInt((int)BF3_AddDamageData);
	ExternalFunctions->sub_835F4878 = (void*)ReverseInt((int)BF3_sub_835F4878);
	ExternalFunctions->sub_83D131D0 = (void*)ReverseInt((int)BF3_sub_83D131D0);
	ExternalFunctions->GetAmmoPtr = (void*)ReverseInt((int)BF3_GetAmmoPtr);
	ExternalFunctions->CCMessage = (void*)ReverseInt((int)BF3_CCMessage);
	ExternalFunctions->ReloadMessageFunction = (void*)ReverseInt((int)BF3_ReloadMessageFunction);


	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_BF3)));

	return true;
}
