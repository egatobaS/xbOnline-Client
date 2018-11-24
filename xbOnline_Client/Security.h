#pragma once

typedef BOOL(*MmIsAddressValid_t)(int Address);
extern MmIsAddressValid_t MmIsAddressValidOriginal;

typedef BOOL(*MmDbgReadCheck_t)(int Address);
extern MmDbgReadCheck_t MmDbgReadCheckOriginal;

extern Detour MmIsAddressValidDetour, MmDbgReadCheckDetour;

BOOL MmDbgReadCheckHook(unsigned int Address);
BOOL MmIsAddressValidHook(unsigned int Address);

void RemoveFromList(HANDLE hModule);

void GetCPUKey(unsigned char* Out);


class Security
{
public:

	Security(time_t stamp, unsigned char* Session);
	~Security();

	bool FindAdressByID(unsigned int *Address, unsigned char IDNum);
	bool ProcessAddressFile(unsigned int AddressFile[], unsigned int IDs[], int Size);

private:

	unsigned char* aesKey;
	unsigned char* Session;

	int GlobalPos;
	int AddressCount;
	int LargestMember;

	std::vector<long long>Address;

	bool AddAddress(int Address, int ID);

	int GetLargestElement(unsigned int Array[], int Size);

	time_t currentStamp();
	time_t GetAdjustedMinute();
	time_t GetCurrentMinute(time_t time);

	time_t* CurrentStampFromServer;
	time_t* CurrentMinuteFromServer;

	time_t* CurrentStampFromConsole;
	time_t* CurrentMinuteFromConsole;
};

int GetAddress(Security* Segment, unsigned int* PatchID, unsigned int ID);

extern Detour DmWalkLoadedModulesExDetour;

typedef int(*DmWalkLoadedModulesExStub)(int Base, int r3);

extern DmWalkLoadedModulesExStub DmWalkLoadedModulesExOrginal;

int DmWalkLoadedModulesEx(int r3, int r4);

extern PLIST_ENTRY OurModule;