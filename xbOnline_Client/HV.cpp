#include "main.h"

__int64 addr = 0;

int HV_PEEK_POKE_EXP_ID = 0xDEADBEEF;

unsigned long long HVGetVersionsPeekQWORD(unsigned long long Address);


unsigned char HVGetVersionsPayload[204] = 
{
	0x3D, 0x60, 0x72, 0x62, 0x61, 0x6B, 0x74, 0x72, 0x7F, 0x03, 0x58, 0x40,
	0x41, 0x9A, 0x00, 0x08, 0x48, 0x00, 0x1C, 0xCA, 0x2B, 0x04, 0x00, 0x04,
	0x41, 0x99, 0x00, 0x94, 0x41, 0x9A, 0x00, 0x44, 0x38, 0xA0, 0x15, 0x4C,
	0x3C, 0xC0, 0x38, 0x80, 0x2B, 0x04, 0x00, 0x02, 0x40, 0x9A, 0x00, 0x0C,
	0x60, 0xC6, 0x00, 0x07, 0x48, 0x00, 0x00, 0x0C, 0x2B, 0x04, 0x00, 0x03,
	0x40, 0x9A, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x00, 0x90, 0xC5, 0x00, 0x00,
	0x7C, 0x00, 0x28, 0x6C, 0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC,
	0x4C, 0x00, 0x01, 0x2C, 0x38, 0x60, 0x00, 0x01, 0x4E, 0x80, 0x00, 0x20,
	0x7D, 0x88, 0x02, 0xA6, 0xF9, 0x81, 0xFF, 0xF8, 0xF8, 0x21, 0xFF, 0xF1,
	0x7C, 0xA8, 0x03, 0xA6, 0x7C, 0xE9, 0x03, 0xA6, 0x80, 0x86, 0x00, 0x00,
	0x90, 0x85, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C, 0x7C, 0x00, 0x2F, 0xAC,
	0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0xA5, 0x00, 0x04,
	0x38, 0xC6, 0x00, 0x04, 0x42, 0x00, 0xFF, 0xE0, 0x4E, 0x80, 0x00, 0x20,
	0x38, 0x21, 0x00, 0x10, 0xE9, 0x81, 0xFF, 0xF8, 0x7D, 0x88, 0x03, 0xA6,
	0x4E, 0x80, 0x00, 0x20, 0x2B, 0x04, 0x00, 0x05, 0x40, 0x9A, 0x00, 0x14,
	0x7C, 0xC3, 0x33, 0x78, 0x7C, 0xA4, 0x2B, 0x78, 0x7C, 0xE5, 0x3B, 0x78,
	0x48, 0x00, 0xA8, 0x82, 0x38, 0x60, 0x00, 0x02, 0x4E, 0x80, 0x00, 0x20
};


static HvxCall HvxExpansionInstall(unsigned int PhysicalAddress, unsigned int CodeSize)
{
	__asm {
		li			r0, 0x70
		sc
		blr
	}
}

static HvxCall HvxExpansionCall(unsigned int ExpansionId, unsigned long long Param1 = 0, unsigned long long Param2 = 0, unsigned long long Param3 = 0, unsigned long long Param4 = 0)
{
	__asm {
		li			r0, 0x71
		sc
		blr
	}
}

__int64 __declspec(naked) HvxGetVersion(unsigned int key, __int64 type, __int64 SourceAddress, __int64 DestAddress, __int64 lenInBytes)
{
	__asm
	{
		li r0, 0x0
		sc
		blr
	}
}


unsigned char AntiKvGrabbinExpansion[532] = {
	0x7D, 0x88, 0x02, 0xA6, 0xFB, 0xE1, 0xFF, 0xF0, 0xF9, 0x81, 0xFF, 0xF8,
	0x94, 0x21, 0xFF, 0x00, 0x7C, 0x9F, 0x23, 0x78, 0x2C, 0x1F, 0x00, 0x00,
	0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x01, 0x41, 0x82, 0x00, 0xC4,
	0x2C, 0x1F, 0x00, 0x02, 0x41, 0x82, 0x00, 0xC8, 0x2C, 0x1F, 0x00, 0x03,
	0x41, 0x82, 0x00, 0xCC, 0x2C, 0x1F, 0x00, 0x0A, 0x41, 0x82, 0x00, 0x64,
	0x2C, 0x1F, 0x00, 0x05, 0x41, 0x82, 0x01, 0x68, 0x2C, 0x1F, 0x00, 0x06,
	0x41, 0x82, 0x01, 0x68, 0x2C, 0x1F, 0x00, 0x07, 0x41, 0x82, 0x01, 0x68,
	0x2C, 0x1F, 0x00, 0x08, 0x41, 0x82, 0x01, 0x68, 0x2C, 0x1F, 0x00, 0x0B,
	0x40, 0x80, 0x00, 0x00, 0x80, 0x60, 0x00, 0x4C, 0x7C, 0x62, 0x1A, 0x14,
	0x80, 0x63, 0x00, 0x08, 0x7C, 0x69, 0x03, 0xA6, 0x7C, 0xC3, 0x33, 0x78,
	0x38, 0x80, 0x00, 0x01, 0x4E, 0x80, 0x04, 0x21, 0x7C, 0x66, 0x1B, 0x78,
	0x7C, 0xE9, 0x03, 0xA6, 0x2C, 0x1F, 0x00, 0x04, 0x41, 0x82, 0x00, 0x7C,
	0x2C, 0x1F, 0x00, 0x09, 0x41, 0x82, 0x01, 0x34, 0x48, 0x00, 0x00, 0x00,
	0x48, 0x00, 0x00, 0x05, 0x7C, 0xA6, 0x2B, 0x78, 0x3C, 0x80, 0x7C, 0x60,
	0x50, 0xA6, 0x54, 0x6A, 0x60, 0x84, 0x02, 0xA6, 0x50, 0xC4, 0x32, 0xE8,
	0x7C, 0x68, 0x02, 0xA6, 0x38, 0x63, 0x00, 0x30, 0x90, 0x83, 0x00, 0x00,
	0x7C, 0x00, 0x18, 0x6C, 0x7C, 0x00, 0x1F, 0xAC, 0x7C, 0x00, 0x04, 0xAC,
	0x4C, 0x00, 0x01, 0x2C, 0x7C, 0x60, 0x12, 0xA6, 0x48, 0x00, 0x01, 0x2C,
	0x48, 0x00, 0x00, 0x51, 0x88, 0x65, 0x00, 0x00, 0x48, 0x00, 0x01, 0x20,
	0x48, 0x00, 0x00, 0x45, 0xA0, 0x65, 0x00, 0x00, 0x48, 0x00, 0x01, 0x14,
	0x48, 0x00, 0x00, 0x39, 0x80, 0x65, 0x00, 0x00, 0x48, 0x00, 0x01, 0x08,
	0x48, 0x00, 0x00, 0x2D, 0xE8, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0xFC,
	0x48, 0x00, 0x00, 0x21, 0x8B, 0xE5, 0x00, 0x00, 0x9B, 0xE6, 0x00, 0x00,
	0x38, 0xA5, 0x00, 0x01, 0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xF0,
	0x38, 0x60, 0x00, 0x00, 0x48, 0x00, 0x00, 0xDC, 0x3C, 0x60, 0x00, 0x00,
	0x60, 0x63, 0x00, 0x76, 0x78, 0x63, 0x07, 0xC6, 0x3D, 0x40, 0x01, 0xEE,
	0x61, 0x4A, 0x00, 0x00, 0x79, 0x4A, 0x00, 0x20, 0x7C, 0x63, 0x53, 0x78,
	0x39, 0x20, 0x40, 0x00, 0x7D, 0x09, 0x1A, 0x14, 0x7C, 0x25, 0x18, 0x00,
	0x4D, 0x80, 0x00, 0x20, 0x7C, 0x25, 0x40, 0x00, 0x4D, 0x81, 0x00, 0x20,
	0x3C, 0x60, 0x80, 0x00, 0x60, 0x63, 0x01, 0x02, 0x78, 0x63, 0x07, 0xC6,
	0x3D, 0x40, 0x00, 0x01, 0x61, 0x4A, 0x09, 0xA0, 0x79, 0x4A, 0x00, 0x20,
	0x7C, 0x63, 0x53, 0x78, 0x7C, 0x65, 0x1B, 0x78, 0x4E, 0x80, 0x00, 0x20,
	0x7C, 0x65, 0x1B, 0x78, 0x38, 0xE0, 0x00, 0x08, 0x48, 0x00, 0x00, 0x1C,
	0x38, 0x84, 0x04, 0x00, 0x7F, 0x25, 0x20, 0x40, 0x40, 0x98, 0x00, 0x10,
	0x7C, 0x65, 0x1B, 0x78, 0x38, 0xA5, 0x00, 0x08, 0x38, 0xE0, 0x00, 0x08,
	0x4E, 0x80, 0x00, 0x20, 0x98, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x40,
	0xB0, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x38, 0x90, 0xC5, 0x00, 0x00,
	0x48, 0x00, 0x00, 0x30, 0xF8, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x28,
	0x8B, 0xE6, 0x00, 0x00, 0x9B, 0xE5, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C,
	0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C,
	0x38, 0xA5, 0x00, 0x01, 0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xE0,
	0x38, 0x60, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C, 0x7C, 0x00, 0x2F, 0xAC,
	0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0x21, 0x01, 0x00,
	0xEB, 0xE1, 0xFF, 0xF0, 0xE9, 0x81, 0xFF, 0xF8, 0x7D, 0x88, 0x03, 0xA6,
	0x4E, 0x80, 0x00, 0x20
};

HRESULT InitializeHvPeekPokeAntiKv()
{
	int r31 = (int)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);

	memset((void*)r31, 0, 0x1000);

	*(int*)(r31 + 0) = 0x48585052; // HXPR 
	*(int*)(r31 + 0x8) = 0x1000;
	*(int*)(r31 + 0x130) = 0x48563064; //This is an expansionID FUCKING CUNT replace this with the ninja one per boot
	*(int*)(r31 + 0x134) = *(int*)(0x8E038610);
	*(long long*)(r31 + 0x148) = *(long long*)(0x8E038630);

	int r11 = (Payload_Size + 0xF) & 0xFFFFFFF0;

	*(int*)(r31 + 0x158) = 0x160;
	*(int*)(r31 + 0x15C) = (r11 + 0x10);
	*(int*)(r31 + 0x160) = 0x10;
	*(int*)(r31 + 0x164) = 0x10;
	*(int*)(r31 + 0x168) = r11;

	Tramps->CallFunction(memcpy_Function, (int)(r31 + 0x170), (int)AntiKvGrabbinExpansion, (int)0x214, (int)0, false);

	XNetRandom((unsigned char*)(r31 + 0x30), 0x100);

	sha1((unsigned char*)(r31 + 0x130), 0xED0, (unsigned char*)(r31 + 0xC));

	unsigned int physExpAdd = (unsigned int)MmGetPhysicalAddress((char*)r31);

	HRESULT result = (HRESULT)HvxExpansionInstall(physExpAdd, 0x1000);

	XPhysicalFree((void*)r31);

	return result;
}

HRESULT InitializeHvPeekPoke()
{
	int r31 = (int)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);

	memset((void*)r31, 0, 0x1000);

	*(int*)(r31 + 0) = 0x48585052; // HXPR 
	*(int*)(r31 + 0x8) = 0x1000;
	*(int*)(r31 + 0x130) = HV_PEEK_POKE_EXP_ID; //This is an expansionID FUCKING CUNT replace this with the ninja one per boot
	*(int*)(r31 + 0x134) = *(int*)(0x8E038610);
	*(long long*)(r31 + 0x148) = *(long long*)(0x8E038630);

	int r11 = (Payload_Size + 0xF) & 0xFFFFFFF0;

	*(int*)(r31 + 0x158) = 0x160;
	*(int*)(r31 + 0x15C) = (r11 + 0x10);
	*(int*)(r31 + 0x160) = 0x10;
	*(int*)(r31 + 0x164) = 0x10;
	*(int*)(r31 + 0x168) = r11;

	Tramps->CallFunction(memcpy_Function, (int)(r31 + 0x170), (int)BasePayload, (int)0x214, (int)0, false);

	XNetRandom((unsigned char*)(r31 + 0x30), 0x100);

	sha1((unsigned char*)(r31 + 0x130), 0xED0, (unsigned char*)(r31 + 0xC));

	unsigned int physExpAdd = (unsigned int)MmGetPhysicalAddress((char*)r31);

	HRESULT result = (HRESULT)HvxExpansionInstall(physExpAdd, 0x1000);

	XPhysicalFree((void*)r31);

#if defined(DEVKIT)
#else
	HvPokeDWORD(0x800001000000A568, 0x4E800020);
	HvPokeDWORD(0x800001000000A56C, 0x4E800020);
#endif

	return result;
}

HRESULT INSTALL_SPOOKY(int EXPANSION_ID, const char* PAYLOAD)
{
	int r31 = (int)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);

	memset((void*)r31, 0, 0x1000);

	*(int*)(r31 + 0) = 0x48585052; // HXPR 
	*(int*)(r31 + 0x8) = 0x1000;
	*(int*)(r31 + 0x130) = EXPANSION_ID; //This is an expansionID FUCKING CUNT replace this with the ninja one per boot
	*(int*)(r31 + 0x134) = *(int*)(0x8E038610);
	*(long long*)(r31 + 0x148) = *(long long*)(0x8E038630);

	int r11 = (Payload_Size + 0xF) & 0xFFFFFFF0;

	*(int*)(r31 + 0x158) = 0x160;
	*(int*)(r31 + 0x15C) = (r11 + 0x10);
	*(int*)(r31 + 0x160) = 0x10;
	*(int*)(r31 + 0x164) = 0x10;
	*(int*)(r31 + 0x168) = r11;

	Tramps->CallFunction(memcpy_Function, (int)(r31 + 0x170), (int)PAYLOAD, (int)0x214, (int)0, false);

	XNetRandom((unsigned char*)(r31 + 0x30), 0x100);

	sha1((unsigned char*)(r31 + 0x130), 0xED0, (unsigned char*)(r31 + 0xC));

	unsigned int physExpAdd = (unsigned int)MmGetPhysicalAddress((char*)r31);

	HRESULT result = (HRESULT)HvxExpansionInstall(physExpAdd, 0x1000);

	XPhysicalFree((void*)r31);

	return result;
}


unsigned char HvPeekBYTE(unsigned long long Address)
{
	return (unsigned char)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, PEEK_BYTE, Address);
}

unsigned short HvPeekWORD(unsigned long long Address)
{
	return (unsigned short)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, PEEK_WORD, Address);
}

unsigned int HvPeekDWORD(unsigned long long Address)
{
	return (unsigned int)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, PEEK_DWORD, Address);
}

unsigned long long HvPeekQWORD(unsigned long long Address)
{
	return HvxExpansionCall(HV_PEEK_POKE_EXP_ID, PEEK_QWORD, Address);
}

HRESULT HvPeekBytes(unsigned long long Address, void* Buffer, unsigned int Size)
{
	void* data = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
	HRESULT result = NULL;
	ZeroMemory(data, Size);

	result = (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, PEEK_BYTES, Address, (int)(MmGetPhysicalAddress(data)), Size);

	if (result == S_OK) Tramps->CallFunction(memcpy_Function, (int)Buffer, (int)data, (int)Size, 0, false);

	XPhysicalFree(data);

	return result;
}

HRESULT HvPokeBYTE(unsigned long long Address, unsigned char Value)
{
	return (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, POKE_BYTE, Address, Value);
}

HRESULT HvPokeWORD(unsigned long long Address, unsigned short Value)
{
	return (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, POKE_WORD, Address, Value);
}

HRESULT HvPokeDWORD(unsigned long long Address, unsigned int Value)
{
	return (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, POKE_DWORD, Address, Value);
}

HRESULT HvPokeQWORD(unsigned long long Address, unsigned long long Value)
{
	return (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, POKE_QWORD, Address, Value);
}

HRESULT HvPokeBytes(unsigned long long Address, const void* Buffer, unsigned int Size)
{
	VOID* data = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);

	Tramps->CallFunction(memcpy_Function, (int)data, (int)Buffer, (int)Size, 0, false);

	HRESULT result = (HRESULT)HvxExpansionCall(HV_PEEK_POKE_EXP_ID, POKE_BYTES, Address, (int)MmGetPhysicalAddress(data), Size);

	XPhysicalFree(data);
	return result;
}
 
unsigned int HVGetVersionsPeekDWORD(unsigned long long Address)
{
	unsigned int *data = (unsigned int *)XPhysicalAlloc(4, MAXULONG_PTR, 0, PAGE_READWRITE); ;

	__int64 dest = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned int*)data);

	HvxGetVersion(0x72627472, 5, Address, dest, 4);

	unsigned int retData = *(unsigned int*)data;

	XPhysicalFree(data);

	return retData;
}

void BypassSpoofing()
{
#if defined(DEVKIT)
	int FirstCall = HvPeekDWORD(0x8000010200015EC0);
#else
	int FirstCall = HvPeekDWORD(0x8000010200015E60);
#endif
	if (FirstCall)
		HvPokeBytes(FirstCall, HVGetVersionsPayload, 204);
}

unsigned long long HVGetVersionsPeekQWORD(unsigned long long Address)
{
	BypassSpoofing();

	unsigned long long *data = (unsigned long long *)XPhysicalAlloc(8, MAXULONG_PTR, 0, PAGE_READWRITE); ;

	__int64 dest = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned long long*)data);

	HvxGetVersion(0x72627472, 5, Address, dest, 8);

	unsigned long long retData = *(unsigned long long*)data;

	XPhysicalFree(data);

	return retData;
}

void HVGetVersionsPeekBytes(unsigned long long Address, unsigned int length, unsigned char* OutData)
{
	BypassSpoofing();

	unsigned char * data = (unsigned char*)XPhysicalAlloc(length, MAXULONG_PTR, NULL, PAGE_READWRITE);

	addr = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned int*)data);

	HvxGetVersion(0x72627472, 5, Address, addr, length);

	Tramps->CallFunction(memcpy_Function, (int)OutData, (int)data, (int)length, 0, false);

	XPhysicalFree(data);
}

void HVGetVersionsPokeBytes(unsigned long long Address, unsigned char *Data, unsigned int length)
{
	BypassSpoofing();

	__int64 src = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress(Data);

	HvxGetVersion(0x72627472, 5, src, Address, length);
}

void HVGetVersionsPokeDWORD(unsigned long long Address, int Data)
{
	BypassSpoofing();

	unsigned char * data = (unsigned char*)XPhysicalAlloc(4, MAXULONG_PTR, NULL, PAGE_READWRITE);

	*(int*)(data) = Data;

	__int64 src = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress(data);

	HvxGetVersion(0x72627472, 5, src, Address, 4);

	XPhysicalFree(data);

}
unsigned long long HvGetFuseLine(unsigned char fuseIndex)
{
	if (fuseIndex > 11) return 0;
		return HVGetVersionsPeekQWORD(0x8000020000020000 + (fuseIndex * 0x200));
}