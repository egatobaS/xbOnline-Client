#include "main.h"

Detour NetDll_XNetGetTitleXnAddrDetour;
Detour XNetXnAddrToMachineIdDetour;

long long spoofedMachineID = 0xFA0000000474FB5E;

unsigned char spoofedMacAddress[6] = { 0 };

unsigned char Text_SerialNumber[12] = { 0 };
unsigned char Text_ConsoleID[13] = { 0 };

unsigned char spoofedConsoleID[8] = { 0 };
unsigned char spoofedSerialNumber[8] = { 0 };

int Func_ptr[2] = { 0 };

SYS_FUNCTION_ADDRESS* StandartFunctions;

int * GetDetours()
{
	return (int*)new Detour();
}

void* HookFunction(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (unsigned int)c);
}

void BuildStartFunctions()
{
	if (StandartFunctions)
		delete StandartFunctions;

	StandartFunctions = new SYS_FUNCTION_ADDRESS;

	HVGetVersionsPokeDWORD(0x800001000000BED8, (int)ReverseInt((int)StandartFunctions));

	StandartFunctions->HookFunction = HookFunction;
	StandartFunctions->memcpy = memcpy;
	StandartFunctions->memset = memset;
	StandartFunctions->MmIsAddressValid = MmIsAddressValid;
	StandartFunctions->strcmp = strcmp;
	StandartFunctions->strcpy = strcpy;
	StandartFunctions->GetDetours = GetDetours;
	StandartFunctions->XNotify = XNotify;
}

int* __stdcall FetchGameFunctionptr()
{
	return Func_ptr;
}

void RandomValues()
{
	srand((unsigned int)time(0));
	spoofedMachineID = 0xFA00000000000000 | (0x2000000 | rand() % 0x7FFFFF);

	XeCryptRandom(spoofedMacAddress, 6);

	spoofedMacAddress[0] = 0x7C;

	XeCryptRandom(spoofedSerialNumber, 6);
	XeCryptRandom(spoofedConsoleID, 8);

	memcpy(Text_SerialNumber, hexStr(spoofedSerialNumber, 6).c_str(), 0xD);

	memcpy(Text_ConsoleID, hexStr(spoofedConsoleID, 7).c_str(), 0xC);

	Text_SerialNumber[0xC] = 0;

}

int XNetXnAddrToMachineIdHook(XNCALLER_TYPE xnc, XNADDR* pxnaddr, unsigned long long* qwMachineId)
{
	srand((unsigned int)time(0));
	*qwMachineId = 0xFA00000002000000 | (0x2000000 | rand() % 0x7FFFFF);
	return 0;
}

DWORD NetDll_XNetGetTitleXnAddrHook(XNCALLER_TYPE xnc, XNADDR * pxna)
{
	int ret = NetDll_XNetGetTitleXnAddr(xnc, pxna);

	srand((unsigned int)time(0));
	long long machineID = 0xFA00000000000000 | (0x2000000 | rand() % 0x7FFFFF);

	//*(int*)(pxna->abEnet) = (rand() % 0x7FFFFF);

	*(long long*)(pxna + 0x18) = _byteswap_uint64(machineID);

	return ret;
}


//struct vtb_addr {
//	int Address;
//	int ID;
//	int Magic;
//};
//
//inline unsigned int ReverseInt(unsigned int val)
//{
//	return ((val << 24)) | (((val << 8) & 0x00ff0000)) | (((val >> 8) & 0x0000ff00)) | (((val >> 24) & 0x000000ff));
//}
//
//class Cheat_vtb
//{
//public:
//	vtb_addr** vtb;
//
//	Cheat_vtb(int AddressCount, int* Addresses, int* IDs, char** Name);
//	void Destroy();
//
//private:
//	unsigned int CreateDirtyAddress(unsigned int in, int magic);
//	void RegisterFunction(int vtbID, int Address, int ID, char* Name);
//};
//
//unsigned int Cheat_vtb::CreateDirtyAddress(unsigned int in, int magic)
//{
//	in ^= magic;
//	return ((ReverseInt(in) & 0xFFFF) << 16) | ((ReverseInt(in) & 0xFFFF0000) >> 16);
//}
//
//void Cheat_vtb::RegisterFunction(int vtbID, int Address, int ID, char* Name)
//{
//	std::mt19937 rng;
//	rng.seed(std::random_device()());
//	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 500);
//
//	int Magic = dist6(rng);
//	int DirtyAddress = CreateDirtyAddress(Address, Magic);
//
//	vtb[vtbID]->Address = DirtyAddress;
//	vtb[vtbID]->ID = ID;
//	vtb[vtbID]->Magic = Magic;
//
//	printf("%s Stored [ Address: %X, DirtyAddress: %X, ID: %i, Magic: %i ]\n", Name, Address, DirtyAddress, ID, Magic);
//}
//
//Cheat_vtb::Cheat_vtb(int AddressCount, int* Addresses, int* IDs, char** Name)
//{
//	vtb = (vtb_addr**)malloc(AddressCount * sizeof(int));
//	*vtb = (vtb_addr*)malloc(AddressCount * sizeof(vtb_addr));
//
//	for (int i = 0; i < AddressCount; i++)
//		RegisterFunction(i, Addresses[i], IDs[i], Name[i]);
//
//	printf("~ VTB Creation ~\n");
//}
//
//void Cheat_vtb::Destroy()
//{
//	free(*vtb);
//	free(vtb);
//	printf("~ VTB Destruction ~\n");
//}