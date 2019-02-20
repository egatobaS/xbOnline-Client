#include "main.h"

BYTE Dumped_HV[0x40000];
CSimpleIniA ini;

int attemptCount = 0;
int kvSharedNumber = 0;
int CurrentPath = 0;

const unsigned char RetailKey[0x10] = { 0xE1, 0xBC, 0x15, 0x9C, 0x73, 0xB1, 0xEA, 0xE9, 0xAB, 0x31, 0x70, 0xF3, 0xAD, 0x47, 0xEB, 0xF3 };

const unsigned char MasterKey[272] = {
	0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xDD, 0x5F, 0x49, 0x6F, 0x99, 0x4D, 0x37, 0xBB, 0xE4, 0x5B, 0x98, 0xF2, 0x5D, 0xA6, 0xB8, 0x43,
	0xBE, 0xD3, 0x10, 0xFD, 0x3C, 0xA4, 0xD4, 0xAC, 0xE6, 0x92, 0x3A, 0x79, 0xDB, 0x3B, 0x63, 0xAF,
	0x38, 0xCD, 0xA0, 0xE5, 0x85, 0x72, 0x01, 0xF9, 0x0E, 0x5F, 0x5A, 0x5B, 0x08, 0x4B, 0xAD, 0xE2,
	0xA0, 0x2A, 0x42, 0x33, 0x85, 0x34, 0x53, 0x83, 0x1E, 0xE5, 0x5B, 0x8F, 0xBF, 0x35, 0x8E, 0x63,
	0xD8, 0x28, 0x8C, 0xFF, 0x03, 0xDC, 0xC4, 0x35, 0x02, 0xE4, 0x0D, 0x1A, 0xC1, 0x36, 0x9F, 0xBB,
	0x90, 0xED, 0xDE, 0x4E, 0xEC, 0x86, 0x10, 0x3F, 0xE4, 0x1F, 0xFD, 0x96, 0xD9, 0x3A, 0x78, 0x25,
	0x38, 0xE1, 0xD3, 0x8B, 0x1F, 0x96, 0xBD, 0x84, 0xF6, 0x5E, 0x2A, 0x56, 0xBA, 0xD0, 0xA8, 0x24,
	0xE5, 0x02, 0x8F, 0x3C, 0xA1, 0x9A, 0xEB, 0x93, 0x59, 0xD7, 0x1B, 0x99, 0xDA, 0xC4, 0xDF, 0x7B,
	0xD0, 0xC1, 0x9A, 0x12, 0xCC, 0x3A, 0x17, 0xBF, 0x6E, 0x4D, 0x78, 0x87, 0xD4, 0x2A, 0x7F, 0x6B,
	0x9E, 0x2F, 0xCD, 0x8D, 0x4E, 0xF5, 0xCE, 0xC2, 0xA0, 0x5A, 0xA3, 0x0F, 0x9F, 0xAD, 0xFE, 0x12,
	0x65, 0x74, 0x20, 0x6F, 0xF2, 0x5C, 0x52, 0xE4, 0xB0, 0xC1, 0x3C, 0x25, 0x0D, 0xAE, 0xD1, 0x82,
	0x7C, 0x60, 0xD7, 0x44, 0xE5, 0xCD, 0x8B, 0xEA, 0x6C, 0x80, 0xB5, 0x1B, 0x7A, 0x0C, 0x02, 0xCE,
	0x0C, 0x24, 0x51, 0x3D, 0x39, 0x36, 0x4A, 0x3F, 0xD3, 0x12, 0xCF, 0x83, 0x8D, 0x81, 0x56, 0x00,
	0xB4, 0x64, 0x79, 0x86, 0xEA, 0xEC, 0xB6, 0xDE, 0x8A, 0x35, 0x7B, 0xAB, 0x35, 0x4E, 0xBB, 0x87,
	0xEA, 0x1D, 0x47, 0x8C, 0xE1, 0xF3, 0x90, 0x13, 0x27, 0x97, 0x55, 0x82, 0x07, 0xF2, 0xF3, 0xAA,
	0xF9, 0x53, 0x47, 0x8F, 0x74, 0xA3, 0x8E, 0x7B, 0xAE, 0xB8, 0xFC, 0x77, 0xCB, 0xFB, 0xAB, 0x8A

};

unsigned char Install_Funct[120] = {
	0x7D, 0x68, 0x02, 0xA6, 0xF9, 0x61, 0xFF, 0xF8, 0xFB, 0xE1, 0xFF, 0xF0,
	0xFB, 0xC1, 0xFF, 0xE8, 0xFB, 0xA1, 0xFF, 0xE0, 0xFB, 0x81, 0xFF, 0xD8,
	0xFB, 0x61, 0xFF, 0xD0, 0xFB, 0x41, 0xFF, 0xC8, 0xFB, 0x21, 0xFF, 0xC0,
	0xF8, 0x21, 0xFF, 0x11, 0x3F, 0xE0, 0x38, 0x60, 0x63, 0xFF, 0x00, 0x14,
	0x3F, 0xC0, 0x80, 0x07, 0x63, 0xDE, 0xB8, 0x40, 0x3F, 0xA0, 0x80, 0x07,
	0x63, 0xBD, 0xE4, 0x58, 0x93, 0xFE, 0x00, 0x00, 0x93, 0xFD, 0x00, 0x00,
	0x38, 0x21, 0x00, 0xF0, 0xE9, 0x61, 0xFF, 0xF8, 0x7D, 0x68, 0x03, 0xA6,
	0xEB, 0x21, 0xFF, 0xC0, 0xEB, 0x41, 0xFF, 0xC8, 0xEB, 0x61, 0xFF, 0xD0,
	0xEB, 0x81, 0xFF, 0xD8, 0xEB, 0xA1, 0xFF, 0xE0, 0xEB, 0xC1, 0xFF, 0xE8,
	0xEB, 0xE1, 0xFF, 0xF0, 0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20
};

unsigned char Restore_Funct[128] = {
	0x7D, 0x68, 0x02, 0xA6, 0xF9, 0x61, 0xFF, 0xF8, 0xFB, 0xE1, 0xFF, 0xF0,
	0xFB, 0xC1, 0xFF, 0xE8, 0xFB, 0xA1, 0xFF, 0xE0, 0xFB, 0x81, 0xFF, 0xD8,
	0xFB, 0x61, 0xFF, 0xD0, 0xFB, 0x41, 0xFF, 0xC8, 0xFB, 0x21, 0xFF, 0xC0,
	0xF8, 0x21, 0xFF, 0x11, 0x3F, 0xE0, 0x80, 0x07, 0x63, 0xFF, 0xB8, 0x40,
	0x3F, 0xC0, 0x48, 0x00, 0x63, 0xDE, 0xBC, 0x71, 0x3F, 0xA0, 0x80, 0x07,
	0x63, 0xBD, 0xE4, 0x58, 0x3F, 0x80, 0x48, 0x00, 0x63, 0x9C, 0x90, 0x59,
	0x93, 0x9D, 0x00, 0x00, 0x93, 0xDF, 0x00, 0x00, 0x38, 0x21, 0x00, 0xF0,
	0xE9, 0x61, 0xFF, 0xF8, 0x7D, 0x68, 0x03, 0xA6, 0xEB, 0x21, 0xFF, 0xC0,
	0xEB, 0x41, 0xFF, 0xC8, 0xEB, 0x61, 0xFF, 0xD0, 0xEB, 0x81, 0xFF, 0xD8,
	0xEB, 0xA1, 0xFF, 0xE0, 0xEB, 0xC1, 0xFF, 0xE8, 0xEB, 0xE1, 0xFF, 0xF0,
	0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20
};

unsigned char PrivateKey[464] = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0B, 0x5E, 0xF1, 0x4F, 0x38, 0xB4, 0x52, 0x0D,
	0x6B, 0x17, 0x7F, 0x88, 0x73, 0x92, 0xA0, 0x91, 0xD8, 0x56, 0xAE, 0x57,
	0x99, 0xCB, 0x56, 0xCD, 0xF6, 0x2F, 0x22, 0xB8, 0x81, 0xC4, 0x3A, 0xB2,
	0x57, 0xAC, 0xD7, 0xB3, 0x96, 0x91, 0x52, 0x3F, 0x6D, 0x74, 0xB3, 0xD8,
	0x24, 0x55, 0xB4, 0x21, 0xC9, 0x12, 0x1F, 0x12, 0x88, 0xE7, 0x34, 0xCA,
	0x7F, 0xC2, 0xFE, 0x67, 0x09, 0x51, 0x52, 0x2A, 0xD0, 0x0F, 0xB2, 0x15,
	0x17, 0x59, 0x5C, 0x5A, 0x8D, 0x61, 0xB1, 0x83, 0xFA, 0x0E, 0xF5, 0xAC,
	0x85, 0xE6, 0x3A, 0x5B, 0xE0, 0xBC, 0x83, 0x90, 0x78, 0x0B, 0x3B, 0xDB,
	0x21, 0xDA, 0x36, 0x15, 0x12, 0x47, 0xE9, 0x87, 0xD0, 0x8F, 0xCA, 0xD2,
	0x37, 0x7C, 0x7D, 0xB3, 0x37, 0xDC, 0x01, 0x1D, 0xB8, 0xD4, 0x7F, 0xDB,
	0x68, 0x70, 0x55, 0x82, 0x9B, 0xC4, 0xD1, 0x27, 0x69, 0x62, 0x36, 0xB2,
	0xE6, 0x18, 0x23, 0x5B, 0x37, 0x35, 0x66, 0xB7, 0x45, 0x96, 0x8C, 0x11,
	0xE4, 0x5B, 0xC9, 0x39, 0xF2, 0x4E, 0xD0, 0x10, 0xF2, 0x04, 0x10, 0xA2,
	0xF1, 0x1F, 0x44, 0x49, 0x16, 0xD1, 0x47, 0xC0, 0x1F, 0x2E, 0xA3, 0xB4,
	0xE5, 0x02, 0xD5, 0x44, 0x62, 0xB1, 0x58, 0xC6, 0x78, 0x22, 0xB4, 0xC9,
	0x0E, 0xBC, 0x78, 0xB4, 0xEE, 0x3D, 0xB9, 0x4D, 0xCC, 0x2E, 0xCE, 0x16,
	0xDF, 0x14, 0x91, 0x42, 0xAB, 0x98, 0x2D, 0x7E, 0xED, 0x66, 0xA9, 0x5B,
	0x54, 0x0F, 0x31, 0x87, 0xF7, 0x52, 0x1D, 0xBE, 0x7A, 0x47, 0x8B, 0xA5,
	0xCE, 0xB2, 0xAC, 0xF8, 0xDF, 0x08, 0x3B, 0x32, 0xA6, 0x5D, 0xA7, 0x3F,
	0xC2, 0xB3, 0x57, 0x23, 0x78, 0x61, 0xB9, 0x26, 0xA2, 0x9F, 0x34, 0xCC,
	0x01, 0xAC, 0x2A, 0x7B, 0x75, 0x33, 0xB2, 0x89, 0x25, 0x98, 0x5E, 0xAB,
	0xC3, 0x4C, 0xAF, 0xE0, 0x30, 0xB0, 0x41, 0xF8, 0xA9, 0x3A, 0x61, 0x25,
	0x76, 0x7D, 0x21, 0x39, 0x6A, 0xDD, 0xA1, 0xAD, 0x95, 0x35, 0xE9, 0x01,
	0x78, 0x4E, 0x77, 0x43, 0xF0, 0xC8, 0x7B, 0xA5, 0xE9, 0xEF, 0x64, 0xAD,
	0x38, 0x6E, 0x21, 0x87, 0x5A, 0x74, 0x80, 0xF8, 0xC0, 0x3C, 0x00, 0x0F,
	0x94, 0xD0, 0xA4, 0xCF, 0x7C, 0xF2, 0x4D, 0xB7, 0xE8, 0x41, 0x2B, 0xCB,
	0x3A, 0x96, 0x38, 0x42, 0x19, 0xFB, 0xCA, 0xD6, 0x36, 0x45, 0x53, 0xC6,
	0x91, 0x51, 0x8B, 0x2B, 0x89, 0x0F, 0xF2, 0xDD, 0xDD, 0x34, 0xEF, 0x34,
	0x7A, 0x82, 0xAB, 0x57, 0xE8, 0x2A, 0x0D, 0xC2, 0x78, 0x9D, 0xD8, 0x49,
	0x39, 0x00, 0x44, 0x54, 0x82, 0xA6, 0x77, 0x9E, 0x20, 0x58, 0xE7, 0x73,
	0xB5, 0xC2, 0xF9, 0x74, 0xCE, 0x8E, 0x75, 0xAA, 0x62, 0xDC, 0xE5, 0x59,
	0xB4, 0xA5, 0xF6, 0x4E, 0x3A, 0xD0, 0xA2, 0x57, 0x91, 0xA1, 0xCF, 0xCC,
	0x97, 0xC1, 0xF7, 0x8F, 0x47, 0x28, 0x76, 0x01, 0x9A, 0x35, 0x62, 0x1D,
	0x38, 0xCD, 0xBB, 0x67, 0x0B, 0x3E, 0x35, 0x71, 0xA9, 0x83, 0xC1, 0xB5,
	0x6A, 0x98, 0x91, 0x2C, 0xD4, 0xAA, 0xFD, 0x2D, 0xAF, 0xA8, 0x65, 0xDF,
	0x66, 0xA5, 0x0B, 0x8D, 0x1B, 0xE1, 0xE4, 0xFF, 0xBC, 0x1A, 0x42, 0x1E,
	0xC7, 0x18, 0x8E, 0x53, 0x93, 0x7C, 0xE3, 0xC1, 0xC3, 0x24, 0xA9, 0xBA,
	0x10, 0xC7, 0x5F, 0x53, 0xC7, 0xCC, 0xE1, 0x6B
};

unsigned char PublicKey[144] = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0B, 0x5E, 0xF1, 0x4F, 0x38, 0xB4, 0x52, 0x0D,
	0x6B, 0x17, 0x7F, 0x88, 0x73, 0x92, 0xA0, 0x91, 0xD8, 0x56, 0xAE, 0x57,
	0x99, 0xCB, 0x56, 0xCD, 0xF6, 0x2F, 0x22, 0xB8, 0x81, 0xC4, 0x3A, 0xB2,
	0x57, 0xAC, 0xD7, 0xB3, 0x96, 0x91, 0x52, 0x3F, 0x6D, 0x74, 0xB3, 0xD8,
	0x24, 0x55, 0xB4, 0x21, 0xC9, 0x12, 0x1F, 0x12, 0x88, 0xE7, 0x34, 0xCA,
	0x7F, 0xC2, 0xFE, 0x67, 0x09, 0x51, 0x52, 0x2A, 0xD0, 0x0F, 0xB2, 0x15,
	0x17, 0x59, 0x5C, 0x5A, 0x8D, 0x61, 0xB1, 0x83, 0xFA, 0x0E, 0xF5, 0xAC,
	0x85, 0xE6, 0x3A, 0x5B, 0xE0, 0xBC, 0x83, 0x90, 0x78, 0x0B, 0x3B, 0xDB,
	0x21, 0xDA, 0x36, 0x15, 0x12, 0x47, 0xE9, 0x87, 0xD0, 0x8F, 0xCA, 0xD2,
	0x37, 0x7C, 0x7D, 0xB3, 0x37, 0xDC, 0x01, 0x1D, 0xB8, 0xD4, 0x7F, 0xDB,
	0x68, 0x70, 0x55, 0x82, 0x9B, 0xC4, 0xD1, 0x27, 0x69, 0x62, 0x36, 0xB2
};

bool FCRT = false;

unsigned char Spoofed_CPUKey[16] = { 0 };
unsigned char CPUKeyDigest[0x14] = { 0 };
unsigned char KVDigest[0x14] = { 0 };
unsigned char MacAddress[6] = { 0 };

unsigned int XKEUpdateSequence = 0;

KEY_VAULT KeyVault = { 0 };

bool
xb_custom_kvp = true, xb_custom_xui = true, xb_custom_notify = true, xb_custom_time = true, xb_redeemhook = true, xb_cheats_cod4 = true, xb_cheats_waw = true, xb_cheats_mw2 = true,
xb_cheats_bo1 = true, xb_cheats_mw3 = true, xb_cheats_mw2_onhost = true, xb_cheats_bo2 = true, xb_cheats_ghosts = true, xb_cheats_aw = true, xb_cheats_bf4 = true, xb_bypass_cod4 = true, xb_bypass_waw = true,
xb_bypass_mw2 = true, xb_bypass_bo1 = true, xb_bypass_mw3 = true, xb_bypass_bo2 = true, xb_bypass_ghosts = true, xb_bypass_aw = true, xb_cheats_mw3_onhost = true, xb_cheats_csgo = true, xb_cheats_tf2 = true,
xb_cheats_bf3 = true;



#if defined(DEVKIT)

int(*XexUnloadImage)(HANDLE) = (int(*)(HANDLE))0x800A1AF8;
int(*XexpUnloadLoadInProgress)(int) = (int(*)(int))0x800A0730;
int(*XexpCompleteLoad)(HANDLE*, int) = (int(*)(HANDLE*, int))0x800A3BD0;
int(*XexpFinishExecutableLoad)(HANDLE, int) = (int(*)(HANDLE, int))0x800A17C8;
int(*XexpAcquireLoaderLock)(int, int, int*) = (int(*)(int, int, int*))0x8009EF08;
int(*XexpGetModuleHandle)(const char*, int, int, HANDLE*) = (int(*)(const char*, int, int, HANDLE*))0x800A0080;
int(*XexpParseModuleName)(const CHAR*, unkStruct1*, unkStruct2*) = (int(*)(const CHAR*, unkStruct1*, unkStruct2*))0x800A0010;
int(*XexpLoadFile)(unkStruct3*, unkStruct2*, unkStruct2*, HANDLE*) = (int(*)(unkStruct3*, unkStruct2*, unkStruct2*, HANDLE*))0x800A2F80;

#else

int(*XexUnloadImage)(HANDLE) = (int(__cdecl *)(HANDLE))0x8007C838;
int(*XexpUnloadLoadInProgress)(int) = (int(__cdecl *)(int))0x8007B588;
int(*XexpCompleteLoad)(HANDLE*, int) = (int(__cdecl *)(HANDLE*, int))0x8007CC78;
int(*XexpFinishExecutableLoad)(HANDLE, int) = (int(__cdecl *)(HANDLE, int))0x8007A778;
int(*XexpAcquireLoaderLock)(int, int, int*) = (int(__cdecl *)(int, int, int*))0x80078F20;
int(*XexpGetModuleHandle)(const char*, int, int, HANDLE*) = (int(__cdecl *)(const char*, int, int, HANDLE*))0x80079720;
int(*XexpParseModuleName)(const CHAR*, unkStruct1*, unkStruct2*) = (int(__cdecl *)(const CHAR*, unkStruct1*, unkStruct2*))0x800796B0;
int(*XexpLoadFile)(unkStruct3*, unkStruct2*, unkStruct2*, HANDLE*) = (int(__cdecl *)(unkStruct3*, unkStruct2*, unkStruct2*, HANDLE*))0x8007BD00;
void(*ResetDnsStringsEntry)(void) = (void(__cdecl *)(void))0x81734C48;

#endif

void(*XNotifyQueueUI)(unsigned int dwType, unsigned int dwUserIndex, unsigned int dwPriority, const wchar_t* pwszStringParam, unsigned long long qwParam) =
(void(*)(unsigned int, unsigned int, unsigned int, const wchar_t*, unsigned long long))ResolveFunction("xam.xex", 0x290);

void(*NetDll_XnpLoadMachineAccount)(unsigned int permAccessLevel, unsigned char* outBuffer) =
(void(*)(unsigned int, unsigned char*))ResolveFunction("xam.xex", 0x6A);

void(*NetDll_XnpSaveMachineAccount)(unsigned int permAccessLevel, unsigned char* outBuffer) =
(void(*)(unsigned int, unsigned char*))ResolveFunction("xam.xex", 0x6B);

typedef BOOL(*DLAUNCHGETOPTVALBYNAME)(char* optName, PDWORD val);
typedef BOOL(*DLAUNCHSETOPTVALBYNAME)(char* optName, PDWORD val);

static DLAUNCHGETOPTVALBYNAME dlaunchGetOptValByName = NULL;
static DLAUNCHSETOPTVALBYNAME dlaunchSetOptValByName = NULL;

typedef enum {
	DL_ORDINALS_LDAT = 1,
	DL_ORDINALS_STARTSYSMOD,
	DL_ORDINALS_SHUTDOWN,
	DL_ORDINALS_FORCEINILOAD,
	DL_ORDINALS_GETNUMOPTS,
	DL_ORDINALS_GETOPTINFO,
	DL_ORDINALS_GETOPTVAL,
	DL_ORDINALS_SETOPTVAL,
	DL_ORDINALS_GETOPTVALBYNAME,
	DL_ORDINALS_SETOPTVALBYNAME,
	DL_ORDINALS_GETDRIVELIST,
	DL_ORDINALS_GETDRIVEINFO,
} DL_ORDINALS;


void SetLiveBlock(bool set)
{
#if defined(DEVKIT)

	*(int*)(0x8182CE14) = set ? 0x38600001 : 0x4801A615;
	*(int*)(0x8182DD54) = set ? 0x38600001 : 0x480196D5;
	*(int*)(0x818DD5E4) = set ? 0x60000000 : 0x409A001C;
	*(int*)(0x818DD5EC) = set ? 0x4800000C : 0x409A000C;

	*(int*)(0x817D1EA4) = set ? 0x60000000 : 0x40800014;
	//*(int*)(0x81851CF0) = set ? 0x4E800020 : 0x7D8802A6;
	//*(int*)(0x81851E30) = set ? 0x4E800020 : 0x7D8802A6;

#else

	*(int*)(0x817384F4) = set ? 0x38600001 : 0x48008855; //Update
	*(int*)(0x81737D04) = set ? 0x38600001 : 0x48009045; //Update
	*(int*)(0x8177079C) = set ? 0x60000000 : 0x409A001C; //Update
	*(int*)(0x817707A4) = set ? 0x4800000C : 0x409A000C; //Update

	if (GetModuleHandle("launch.xex"))
	{
		if (!dlaunchSetOptValByName)dlaunchSetOptValByName = (DLAUNCHSETOPTVALBYNAME)ResolveFunction("launch.xex", DL_ORDINALS_SETOPTVALBYNAME);

		DWORD DoliveBlock = set;

		dlaunchSetOptValByName("liveblock", &DoliveBlock);
		dlaunchSetOptValByName("livestrong", &DoliveBlock);
	}
#endif	
}

bool xbVerifyPayload(BYTE* _payload, DWORD payloadLength)
{
	BYTE payloadDigest[0x4] = { 0x60, 0x1D, 0x32, 0x4B };
	BYTE expectedDigest[0x4] = { 0 };
	XeCryptSha(_payload, (payloadLength - 0xC10), NULL, NULL, NULL, NULL, expectedDigest, 0x4);

	if (memcmp(expectedDigest, payloadDigest, 4) == 0) {
		return true;
	}

	CWriteFile("xbOnline:\\Payload_Unknown.bin", _payload, payloadLength);
	return false;
}

bool xbVerifyDvdChallenger(BYTE* xex_module, DWORD moduleSize)
{
	BYTE payloadDigest[0x4] = { 0xA5,0x7E,0xA1,0x33 };
	BYTE expectedDigest[0x4] = { 0 };
	char XoscPath[0x80];

	XeCryptSha(xex_module, moduleSize, NULL, NULL, NULL, NULL, expectedDigest, 0x4);

	if (memcmp(expectedDigest, payloadDigest, 4) == 0) {
		return true;
	}

	sprintf(XoscPath, "xbOnline:\\Xosc_Unknown_%X02%X02%X02%X02.bin", expectedDigest[0], expectedDigest[1], expectedDigest[2], expectedDigest[3]);
	CWriteFile(XoscPath, xex_module, moduleSize);
	return false;
}

void RebootConsole()
{
	HalReturnToFirmware(HalRebootRoutine);
}

bool DriveOverRide()
{
	if (FileExists("xbOnline:\\disable_drivecheck.bin"))
		return true;
	else
		return false;
}

void ShowMessageBoxUI(LPCWSTR title, LPCWSTR String)
{
	MESSAGEBOX_RESULT g_mb_result = { 0 };
	XOVERLAPPED g_xol = { 0 }, msgbox = { 0 };

	WCHAR wszResultText[15] = { 0 };
	WCHAR BodyMessage[100] = { 0 };

	LPCWSTR Button[1] = { L"Okay!" };

	XShowMessageBoxUI(XUSER_INDEX_ANY, title, String, 1, Button, 0, XMB_ALERTICON, &g_mb_result, &g_xol);
}
FARPROC ResolveFunction(char* ModuleName, unsigned int Ordinal)
{
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (const char*)Ordinal);
}

void XNotifyThread(wchar_t* NotifyText)
{
	XNotifyQueueUI(14, 0, 2, NotifyText, NULL);
}

void XNotify(wchar_t* NotifyText)
{
	if (KeGetCurrentProcessType() != 1)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyThread, (LPVOID)NotifyText, 0, NULL);
	else
		XNotifyThread(NotifyText);
}

bool OpenedTray()
{
	unsigned char Message[0x10] = { 0 }, Response[0x10] = { 0 };
	Message[0] = 0xA;
	HalSendSMCMessage(Message, Response);

	return (Response[1] == 0x60);
}

unsigned int ResolveIntrinsicModule(HMODULE Module, unsigned int Export, unsigned int off1, unsigned int off2)
{
	unsigned short t1, t2;
	unsigned int *f;

	if (FAILED(XexGetProcedureAddress(Module, Export, &f)))
		return 0;

	t1 = f[off1] & 0xFFFF;
	t2 = f[off2] & 0xFFFF;

	return (t1 << 16) + t2;
}

Detour* _Hook = new Detour;
bool isNhoke = false;


void PatchInJump_2(unsigned int Address, void* Destination, bool Linked)
{
	if (!Address || !Destination) return;

	unsigned int DestinationAddress = (DWORD)(Destination);

	unsigned int Instructions[4];

	Instructions[0] = 0x3D600000 + ((DestinationAddress >> 16) & 0xFFFF); // lis r11, Destination

	if ((DestinationAddress & 0x8000))
	{
		Instructions[0]++; // No negatives please
	}

	Instructions[1] = 0x396B0000 + (DestinationAddress & 0xFFFF); // addi r11, r11, Destination

	Instructions[2] = 0x7D6903A6; // mtctr r11

	Instructions[3] = 0x4E800420 + Linked; // bctr bctrl

	memcpy((void*)Address, Instructions, sizeof(DWORD) * 4);
}

DWORD PatchModuleImport_F(PLDR_DATA_TABLE_ENTRY Module, PCHAR ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
{
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if (address == NULL) return S_FALSE;

	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL) return S_FALSE;

	DWORD result = 2;
	PCHAR stringTable = (PCHAR)(importDesc + 1);
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);
	for (DWORD x = 0; x < importDesc->ModuleCount; x++) {
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {
			DWORD value = *((DWORD*)importAdd[y]);

			if (value == address) {

				*(unsigned int*)(importAdd[y]) = PatchAddress;
				DWORD newCode[4];


				PatchInJump_2((DWORD)newCode, (void*)PatchAddress, false);

				isNhoke = true;
				memcpy((DWORD*)importAdd[y + 1], newCode, 16);
				result = S_OK;
			}
		}

		importTable = (XEX_IMPORT_TABLE_ORG*)(((PBYTE)importTable) + importTable->TableSize);
	}
	return result;
}

DWORD PatchModuleImport(PCHAR Module, PCHAR ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
{
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (moduleHandle == NULL) ? S_FALSE : PatchModuleImport_F(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);

}

#pragma code_seg(push, r1, ".ptext")
int __declspec(naked) An_EmptyFunction()
{
	__asm
	{
		mr r5, r5
		or r6, r6, r6
		slwi r5, r5, 0
		nop
		mr r30, r30
		slwi r5, r5, 0
		extlwi	  r4, r6, 16, 8
		extlwi	  r4, r6, 16, 8
		nop
		mr r30, r30
		mr r30, r30
		mr r30, r30
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r7, r7, 0
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r7, r7, 0
		slwi r5, r5, 0
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		extlwi	  r4, r6, 16, 8
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r21, r21, 0
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r7, r7, 0
		slwi r21, r21, 0
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r7, r7, 0
		extlwi	  r4, r6, 16, 8
		slwi r21, r21, 0
		mr r30, r30
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		slwi r21, r21, 0
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		rlwinm r6, r6, 24, 16, 23
		slwi r7, r7, 0
		slwi r5, r5, 0
		rlwinm r6, r6, 24, 16, 23
		mr r8, r8
		nop
		extlwi	  r4, r6, 16, 8
		mr r30, r30
		rlwinm r6, r6, 24, 16, 23
		slwi r7, r7, 0
		slwi r5, r5, 0
		rlwinm r6, r6, 24, 16, 23
		mr r8, r8
		nop
		blr

	}
}
#pragma code_seg(pop, r1)

int XexLoadImageFromMemory_(VOID* Image, DWORD ImageSize, const CHAR* ImageName, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle)
{
	unsigned char LocalBuffer[130] = { 0 };

	memcpy((void*)LocalBuffer, (void*)An_EmptyFunction, 130);

	memcpy((void*)An_EmptyFunction, (void*)Install_Funct, 120);

	An_EmptyFunction();

	unkStruct1 temp1;
	unkStruct2 temp2;
	unkStruct3 temp3;

	int XexLoadImageFromMemoryLock = 0;
	int ErrorRet = 0;

	HANDLE mhandle;

	if (ModuleHandle)
		*ModuleHandle = 0;

	XexpParseModuleName(ImageName, &temp1, &temp2);

	if (temp1.unk2)
		return 0xC0000039;

	if (!(LoadFlags & 8))
		LoadFlags |= 1;

	if (ErrorRet = XexpAcquireLoaderLock(1, LoadFlags, &XexLoadImageFromMemoryLock) < 0)
		return ErrorRet;

	if (!(LoadFlags & 8)) {

		if (*(int*)(_XexExecutableModuleHandle))
		{
			RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);
			return 0xC0000022;
		}
	}

	if (ErrorRet = XexpGetModuleHandle(ImageName, LoadFlags, 1, &mhandle) < 0) {

		RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);
		return ErrorRet;
	}

	if (!(*(int*)((int)mhandle + 0x34) & 0x1000))
	{
		XexUnloadImage(mhandle);
		RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);
		return 0xC0000035;
	}

	temp3.unk1 = 0;
	temp3.unk2 = 0;
	temp3.Image = (char*)Image;
	temp3.ImageSize = ImageSize;

	if (ErrorRet = XexpLoadFile(&temp3, &temp2, &temp2, &mhandle) < 0)
	{
		XexpUnloadLoadInProgress(*(int*)((int)mhandle + 0x4C));
		RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);
		return ErrorRet;
	}

	if (ErrorRet = XexpCompleteLoad(&mhandle, Version) < 0)
	{
		RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);
		return ErrorRet;
	}

	if (ModuleHandle)
		*ModuleHandle = (HMODULE)mhandle;

	if (!LoadFlags)
		XexpFinishExecutableLoad(mhandle, 0);

	RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)XexLoadImageFromMemoryLock);

	memcpy((void*)An_EmptyFunction, (void*)Restore_Funct, 128);

	An_EmptyFunction();

	memcpy((void*)An_EmptyFunction, (void*)LocalBuffer, 130);

	return ErrorRet;

}

DWORD GetModuleImport(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal) {

	PDETOUR_XEX_IMPORT_DESCRIPTOR importTable;
	DWORD dwModuleCountIndex = 0;
	DWORD dwModuleIndex = 0;
	CHAR szModuleName[0x100];
	CHAR szHImportedModule[0x100];

	DWORD dwImportAddress = (DWORD)GetProcAddress((HMODULE)HImportedModule, (LPCSTR)Ordinal);

	if (dwImportAddress == NULL || HModule == NULL)
		return 0;

	importTable = (PDETOUR_XEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField((void*)*(DWORD *)((DWORD)HModule + 0x58), 0x000103FF);

	if (importTable == NULL)
		return 0;

	WideCharToMultiByte(CP_UTF8, NULL, (wchar_t*)*(DWORD*)((DWORD)HImportedModule + 0x30), -1, szHImportedModule, 0x100, NULL, NULL);

	for (DWORD dwModuleCount = 0; dwModuleCount < importTable->ModuleCount; dwModuleCount++)
	{
		DWORD i = dwModuleCountIndex;

		DWORD dwPointer = (DWORD)importTable + 0x0C + importTable->NameTableSize + dwModuleIndex;

		DWORD dwModuleSectionSize = *(DWORD *)dwPointer;

		dwPointer += 0x24 + 4;

		dwModuleIndex += dwModuleSectionSize;

		dwModuleSectionSize -= 0x24 + 4;

		dwModuleCountIndex += strlen((char*)((DWORD)importTable + 0x0C + i));

		strcpy(szModuleName, (char*)((DWORD)importTable + 0x0C + i));


		if (!strcmp(szModuleName, szHImportedModule))
		{

			for (DWORD dwSize = 0; dwSize < dwModuleSectionSize; dwSize += 8)
			{
				DWORD dwTempAddr = *(DWORD *)*(DWORD *)(dwPointer + dwSize);
				if (dwTempAddr == dwImportAddress)
					return *(DWORD *)(dwPointer + dwSize + 4);
			}
		}
	}
	return 0;
}
int XexLoadImageFromMemory_XamHook(VOID* Image, DWORD ImageSize, const CHAR* ImageName, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle)
{
	if (!memcmp(ImageName, "xosc9v2.xex", 11))
	{
		if (!xbVerifyDvdChallenger((BYTE*)Image, ImageSize))
		{
			XNotify(L"X-001, rebooting for protection...");
			SetLiveBlock(true);
			Sleep(5000);
			RebootConsole();
		}

	}
	return XexLoadImageFromMemory(Image, ImageSize, ImageName, LoadFlags, Version, ModuleHandle);
}
DWORD GetXamExportFromBaseAddress(DWORD dwModuleBaseAddr, int Ordinal)
{
	HANDLE hModule;
	XexPcToFileHeader((PVOID)dwModuleBaseAddr, (PLDR_DATA_TABLE_ENTRY*)&hModule);
	HANDLE hImportedModule = (HANDLE)GetModuleHandle("xam.xex");
	return GetModuleImport(hModule, hImportedModule, Ordinal);
}

unsigned int ApplyPatches(void* buffer)
{
	DWORD PatchCount = NULL;
	PDWORD PatchData = (PDWORD)buffer;
	while (*PatchData != 0xFFFFFFFF) {
		memcpy((PVOID)PatchData[0], &PatchData[2], PatchData[1] * sizeof(DWORD));
		PatchData += (PatchData[1] + 2);
		PatchCount++;
	}
	return PatchCount;
}


void GetFilePathFromHandle(HMODULE Handle, char* FilePath)
{
	wchar_t outPath[MAX_PATH] = { 0 };

	if (!Handle) return;

	wcscpy(outPath, (wchar_t*)(*(int*)(Handle + 0xA)));

	std::wcstombs(FilePath, outPath, MAX_PATH);
}

void GetBootedPath(HMODULE Handle, char* FinalPath)
{
	char Path[MAX_PATH] = { 0 };
	GetFilePathFromHandle((HMODULE)Handle, Path);

	std::string FilePath = Path;

	size_t f = FilePath.find("\\Device\\Harddisk0\\Partition1");

	if (f != 0xFFFFFFFF)
		FilePath.replace(f, std::string("\\Device\\Harddisk0\\Partition1").length(), "xbOnline:");

	f = FilePath.find("\\Device\\Mass0");

	if (f != 0xFFFFFFFF)
		FilePath.replace(f, std::string("\\Device\\Mass0").length(), "xbOnline:");

	strcpy(FinalPath, FilePath.c_str());
}

BOOL FileExists(LPCSTR lpFileName)
{
	if (GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}
	return TRUE;
}

HRESULT CreateSymbolicLink(PCHAR szDrive, PCHAR szDeviceName, BOOL System)
{
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	ANSI_STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);
	if (FileExists(szDrive)) return S_OK;
	NTSTATUS status = ObCreateSymbolicLink(&linkname, &devicename);
	return (status >= 0) ? S_OK : S_FALSE;
}

HRESULT Mount_Drive()
{

	if ((XboxHardwareInfo->Flags & 0x20) == 0x20) {
		if (CreateSymbolicLink(NAME_MOUNT, NAME_HDD, TRUE) != ERROR_SUCCESS) {
			return E_FAIL;
		}
	}
	else {
		if (CreateSymbolicLink(NAME_MOUNT, NAME_USB, TRUE) != ERROR_SUCCESS) {
			return E_FAIL;
		}
	}
	return ERROR_SUCCESS;

}

static wchar_t* charToWChar_Com(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
}


DWORD xbRedeem(unsigned char* Session, unsigned char* CPUKey, unsigned char* Geneology, unsigned char* XEX_Hash, int type)
{
	MESSAGEBOX_RESULT g_mb_result = { 0 };
	XOVERLAPPED g_xol = { 0 }, msgbox = { 0 };

	WCHAR wszResultText[15] = { 0 };
	WCHAR BodyMessage[100] = { 0 };

	LPCWSTR Buttons2[1] = { L"Okay!" };
	LPCWSTR Buttons1[2] = { L"Redeem", L"Cancel" };
	LPCWSTR Buttons[2] = { L"Check Time Remaining", L"Claim Token" };


	if (type == 0)
	{
		char TimeInfo[256] = { 0 };

		Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

		if (Connection->CheckTime(TimeInfo, &g_TimeleftInSeconds, &g_GlobalStatus))
		{
			g_Endtime = time(NULL) + g_TimeleftInSeconds;

			wchar_t* ptr = charToWChar_Com(TimeInfo);

			switch (g_GlobalStatus)
			{

			case EXPIRED:
				ShowMessageBoxUI(L"Time Expired!", L"Your time has expired on xbOnline. You can continue using the service by purchasing time from:\n\n\nhttps://xbonline.live\nOR\nhttps://livestore.sale\n\n\nWe hope you enjoyed your time with us!");
				XNotify(L"Your time has expired.\nPlease purchase some more from http://xbonline.live");
				break;
			case FREEMODE:
				XNotify(ptr);
				break;
			case BANNED:
				XNotify(L"Please contact xbOnline support\nLooks like you are banned from xbOnline.");
				break;
			case TIMELEFT:
				XNotify(ptr);
				break;
			case NOT_INDB:
				XNotify(L"Welcome New User\nPlease purchase some time from http://xbonline.live");
				break;
			default:
				break;
			}

			Sleep(2000);

			delete[] ptr;
		}
		delete Connection;
	}
	else if (type == 1)
	{
		Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

		if (Connection->Presence(g_Session, &g_TimeleftInSeconds, &g_GlobalStatus))
			g_Endtime = time(NULL) + g_TimeleftInSeconds;

		delete Connection;

		if (g_GlobalStatus == FREEMODE)
		{
			XNotify(L"Currently in Freemode.\nToken redeeming has been disabled.");
			return 0;
		}
		else if (g_GlobalStatus == BANNED)
		{
			XNotify(L"Please contact xbOnline support\nLooks like you are banned from xbOnline.");
			return 0;
		}
		else
		{
		TokenClaim:
			LPCWSTR Title = L"xbOnline Token Claim";
			LPCWSTR Description = L"Enter the 12-character token\nExample: D5C388A39CF0\n";
			while (XShowKeyboardUI(XUSER_INDEX_ANY, VKBD_DEFAULT, Title, Title, Description, wszResultText, 13, &msgbox) == ERROR_ACCESS_DENIED)
				Sleep(500);
			while (!XHasOverlappedIoCompleted(&msgbox))
				Sleep(500);

			if (wcslen(wszResultText) == 12)
			{
				long long Days = 0;

				TOKE_STATUS Status;

				char Token[256] = { 0 };

				wcstombs(Token, wszResultText, 12);

				Client* Connection = new Client(CPUKey, Geneology, XEX_Hash);

				if (Connection->CheckToken(Token, false, &Days, &Status))
				{
					if (Status == VALID_TOKEN)
					{
						if (Days > 6000)
							wsprintfW(BodyMessage, L"Token is valid for:\n\n%ws Day(s)", L"Lifetime");
						else
							wsprintfW(BodyMessage, L"Token is valid for:\n\n%d Day(s)", Days);

						while (XShowMessageBoxUI(XUSER_INDEX_ANY, L"xbOnline Info!", BodyMessage, 2, Buttons1, 0, XMB_ALERTICON, &g_mb_result, &g_xol) == ERROR_ACCESS_DENIED)
							Sleep(500);
						while (!XHasOverlappedIoCompleted(&g_xol))
							Sleep(500);

						if (g_mb_result.dwButtonPressed == 0) {

							Connection->UseToken(Token);

							if (g_GlobalStatus == TIMELEFT && !(*(int*)(g_Session)))
							{
								unsigned char CPUKey[0x10] = { 0 };
								unsigned char Geneology[0x10] = { 0 };

								Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

								Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

								Client Connection(CPUKey, Geneology, XEX_Hash);

								if (Connection.GetSession(g_Session, &g_TimeleftInSeconds, &g_GlobalStatus) && !GotAnewUpdate) {
									g_Endtime = time(NULL) + g_TimeleftInSeconds;
								}

								DownloadGameAddresses();
							}



							delete Connection;

							return 0;
						}
					}
					else
					{
						delete Connection;

						switch (Status)
						{
						case INVALID_TOKEN:
							XNotify(L"This is an invalid token.");
							break;
						case USED_TOKEN:
							XNotify(L"This token has been previously used.");
							break;
						default:
							break;
						}
						goto tryAgain;
					}
				}
				delete Connection;
			}
			else
			{
			tryAgain:
				LPCWSTR Buttons[2] = { L"Retry", L"Cancel" };
				while (XShowMessageBoxUI(XUSER_INDEX_ANY, L"xbOnline Information!", L"The token redeem failed, Do you want to try again?", 2, Buttons, 0, XMB_ALERTICON, &g_mb_result, &g_xol) == ERROR_ACCESS_DENIED)
					Sleep(500);
				while (!XHasOverlappedIoCompleted(&g_xol))
					Sleep(500);
				if (g_mb_result.dwButtonPressed == 0)
				{
					goto TokenClaim;
				}
			}
		}
	}

	return 0;
}

bool CWriteFile(const char* FilePath, const void* Data, unsigned int Size)
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

bool CReadFile(const char* FileName, MemoryBuffer &pBuffer)
{
	HANDLE hFile;  DWORD dwFileSize, dwNumberOfBytesRead;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	dwFileSize = GetFileSize(hFile, NULL);
	unsigned char* lpBuffer = (unsigned char*)malloc(dwFileSize);
	if (lpBuffer == NULL) {
		CloseHandle(hFile);
		return FALSE;
	}

	if (ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE) {
		free(lpBuffer);
		CloseHandle(hFile);
		return FALSE;
	}
	else if (dwNumberOfBytesRead != dwFileSize) {
		free(lpBuffer);
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);
	pBuffer.Add(lpBuffer, dwFileSize);
	free(lpBuffer);
	return TRUE;
}



bool XeKeysPkcs1Verify(const unsigned char* pbHash, const unsigned char* pbSig, XECRYPT_RSA* pRsa)
{
	BYTE scratch[0x100];
	DWORD val = pRsa->cqw << 3;
	if (val <= 0x200) {
		XeCryptBnQw_SwapDwQwLeBe((PQWORD)pbSig, (PQWORD)scratch, val >> 3);
		if (XeCryptBnQwNeRsaPubCrypt((PQWORD)scratch, (PQWORD)scratch, pRsa) == 0) return FALSE;
		XeCryptBnQw_SwapDwQwLeBe((PQWORD)scratch, (PQWORD)scratch, val >> 3);
		return XeCryptBnDwLePkcs1Verify((CONST PBYTE)pbHash, scratch, val);
	}
	else return FALSE;
}

bool VerifyKeyVault()
{
	XECRYPT_HMACSHA_STATE hmacSha;
	XeCryptHmacShaInit(&hmacSha, Spoofed_CPUKey, 0x10);
	XeCryptHmacShaUpdate(&hmacSha, (BYTE*)&KeyVault.OddFeatures, 0xD4);
	XeCryptHmacShaUpdate(&hmacSha, (BYTE*)&KeyVault.DvdKey, 0x1CF8);
	XeCryptHmacShaUpdate(&hmacSha, (BYTE*)&KeyVault.CardeaCertificate, 0x2108);
	XeCryptHmacShaFinal(&hmacSha, KVDigest, XECRYPT_SHA_DIGEST_SIZE);

	for (DWORD x = 0; x < 0x100; x++) {
		if (KeyVault.KeyVaultSignature[x] != NULL) {

			return TRUE;
		}
	}
	return XeKeysPkcs1Verify(KVDigest, KeyVault.KeyVaultSignature, (XECRYPT_RSA*)MasterKey);
}

HRESULT CreateCPUKeyBin(CHAR* FilePath)
{
	XeCryptRandom(Spoofed_CPUKey, 0x10);
	if (CWriteFile(FilePath, Spoofed_CPUKey, 0x10) != TRUE) {

		return E_FAIL;
	}
	return ERROR_SUCCESS;

}

void xbKeyvaultShareSanityCheck()
{
	/*if (!xbIsKeyFilePresent())
	{
		MESSAGEBOX_RESULT g_mb_result = { 0 };
		XOVERLAPPED g_xol = { 0 }, msgbox = { 0 };

		WCHAR wszResultText[15] = { 0 };
		WCHAR BodyMessage[100] = { 0 };


		LPCWSTR Buttons[2] = { L"Yes", L"No" };

		while (XShowMessageBoxUI(XUSER_INDEX_ANY, L"Advanced Keyvault Detection", L"We've detected that you are using a new keyvault, would you like to enable advanced keyvault sharing detection?\nThis ensures the keyvault you are using is not passed through a keyvault checker or another service.", 2, Buttons, 0, XMB_ALERTICON, &g_mb_result, &g_xol) == ERROR_ACCESS_DENIED)
			Sleep(501);

		while (!XHasOverlappedIoCompleted(&g_xol))
			Sleep(501);

		if (g_mb_result.dwButtonPressed == 0)
		{
			xbIsAdvancedKeySharingEnabled(true);
		}
		else if (g_mb_result.dwButtonPressed == 1)
		{
			xbIsAdvancedKeySharingEnabled(false);
		}
	}

	else
		xbGetSharedConsoleNumber();*/
}
bool xbIsKeyFilePresent()
{
	/*if (FileExists("xbOnline:\\Content\\NetworkData.cfg") || FileExists("xbOnline:\\Content\\NetworkData.bin"))
		return true;
	else
		return false;*/
	return false;
}
void xbIsAdvancedKeySharingEnabled(bool option)
{
	/*unsigned char blankData[0x18] = { 0 };
	if (option)
	{
		CreateDirectory("xbOnline:\\Content\\", NULL);
		CWriteFile("xbOnline:\\Content\\NetworkData.cfg", blankData, 0x18);
		xbSharedConsoleCheck(true);
	}

	else
	{
		CreateDirectory("xbOnline:\\Content\\", NULL);
		CWriteFile("xbOnline:\\Content\\NetworkData.bin", blankData, 0x18);
	}*/
}
void xbGetSharedConsoleNumber()
{
	/*MemoryBuffer currentHash;
	if (FileExists("xbOnline:\\Content\\NetworkData.cfg"))
	{
		CReadFile("xbOnline:\\Content\\NetworkData.cfg", currentHash);
		kvSharedNumber = *(int*)&currentHash.GetData()[0x14];
	}
	else
		kvSharedNumber = 0;*/

}
BOOL xbSharedConsoleCheck(bool FirstInitialization)
{
	//MESSAGEBOX_RESULT g_mb_result = { 0 };
	//XOVERLAPPED g_xol = { 0 }, msgbox = { 0 };

	//WCHAR wszResultText[15] = { 0 };
	//WCHAR BodyMessage[100] = { 0 };

	//LPCWSTR Buttons[1] = { L"Okay!"};
	//int currentSharedUserNumber = 0;

	////First Get our Machine Ticket
	//WORD Size = 0;
	//unsigned char MySpicyTicket[0x1EC] = { 0 };
	//unsigned char MySpicyHash[0x18] = { 0 };

	//MemoryBuffer currentHash;


	//ExGetXConfigSetting(4, 1, MySpicyTicket, 0x1EC, &Size);

	////Copy 0x4 bytes of online key & hash the spicy hash
	//XeCryptSha(MySpicyTicket + 0x6C, 4, NULL, NULL, NULL, NULL, MySpicyHash, 0x14);

	//
	//if (FileExists("xbOnline:\\Content\\NetworkData.cfg"))
	//{
	//	//Read Hash and Compare Agaist new one...
	//	CReadFile("xbOnline:\\Content\\NetworkData.cfg", currentHash);

	//	if (memcmp(currentHash.GetData(), MySpicyHash, 0x14) != 0)
	//	{
	//		currentSharedUserNumber = *(int*)&currentHash.GetData()[0x14]; currentSharedUserNumber++;
	//		memcpy(MySpicyHash + 0x14, &currentSharedUserNumber, 0x4);

	//		if(!FirstInitialization)
	//			XNotify(L"This keyvault has been SHARED or used on another service\nIf you have used a keyvault checker you can ignore this message!");
	//		
	//		CWriteFile("xbOnline:\\Content\\NetworkData.cfg", MySpicyHash, 0x18);
	//		xbGetSharedConsoleNumber();
	//	}
	//		
	//}
	//return false;
	return false;
}
HRESULT ProcessCPUKeyBin(char* FilePath)
{
	MemoryBuffer mbCpu;
	if (!CReadFile(FilePath, mbCpu)) {

		return CreateCPUKeyBin(FilePath);
	}

	if (mbCpu.GetDataLength() < 0x10) {

		return CreateCPUKeyBin(FilePath);
	}

	memcpy(Spoofed_CPUKey, mbCpu.GetData(), 0x10);
	XeCryptSha(Spoofed_CPUKey, 0x10, NULL, NULL, NULL, NULL, CPUKeyDigest, XECRYPT_SHA_DIGEST_SIZE);


#if defined(DEVKIT)
#else
	HvPokeDWORD(0x8000010200015EE8, 0x00001CC8);
#endif


	memcpy((PVOID)0x8E03AA30, &CPUKeyDigest, 0x10);

	return 0;
}


HRESULT ProcessKeyVault()
{
	VerifyKeyVault();

	FCRT = (KeyVault.OddFeatures & ODD_POLICY_FLAG_CHECK_FIRMWARE) != 0 ? TRUE : FALSE;

	return ERROR_SUCCESS;
}

HRESULT DoSysCleanup()
{
	unsigned char ticketBuffer[0x1B40] = { 0 };
	NetDll_XnpSaveMachineAccount(2, ticketBuffer);
	XamCacheReset(XAM_CACHE_XSTS_TOKEN);
	XamCacheReset(XAM_CACHE_XLFS_UPLOADER);
	XamCacheReset(XAM_CACHE_QOS_HISTORY);
	XamCacheReset(XAM_CACHE_VALIDATE_CERT);
	XamCacheReset(XAM_CACHE_TICKETS);
	XamCacheReset(XAM_CACHE_CERT_STORAGE);
	XamCacheReset(XAM_CACHE_LIVEID_DEVICE);
	return ERROR_SUCCESS;
}
HRESULT SetMacAddress()
{
	MacAddress[0] = 0x00;
	MacAddress[1] = 0x22;
	MacAddress[2] = 0x48;
	MacAddress[3] = KeyVault.ConsoleCertificate.ConsoleId.asBits.MacIndex3;
	MacAddress[4] = KeyVault.ConsoleCertificate.ConsoleId.asBits.MacIndex4;
	MacAddress[5] = KeyVault.ConsoleCertificate.ConsoleId.asBits.MacIndex5;

	BYTE curMacAddress[6];
	WORD settingSize = 6;

	ExGetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, curMacAddress, 6, &settingSize);

	if (memcmp(curMacAddress, MacAddress, 6) == 0) {
		DWORD temp = 0;
		XeCryptSha(MacAddress, 6, NULL, NULL, NULL, NULL, (BYTE*)&temp, 4);
		XKEUpdateSequence |= (temp & ~0xFF);
		return ERROR_SUCCESS;
	}

	if (NT_SUCCESS(ExSetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, MacAddress, 6))) {
		Sleep(3000);

		//Do Cleanup from last keyvault
		DoSysCleanup();
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
	}

	return E_FAIL;
}


HRESULT SetKeyVault(char* FilePath)
{
	MemoryBuffer mbkv;
	if (!CReadFile(FilePath, mbkv)) {
		return E_FAIL;
	}
	return SetKeyVault(mbkv.GetData());
}

typedef HRESULT(*pDmSetMemory)(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf, LPDWORD pcbRet);

pDmSetMemory DevSetMemory = NULL;

HRESULT SetMemory(PVOID Destination, PVOID Source, DWORD Length)
{
	if (DevSetMemory == NULL)
		DevSetMemory = (pDmSetMemory)ResolveFunction("xbdm.xex", 40);

	if (DevSetMemory == NULL) {
		memcpy(Destination, Source, Length);
		return ERROR_SUCCESS;
	}
	else {
		if (DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0x00, 0x2DA, 0x00))
			return ERROR_SUCCESS;
	}
	return E_FAIL;
}

HRESULT SetKeyVault(unsigned char* pKeyVault)
{
	memcpy(&KeyVault, pKeyVault, 0x4000);

	SetMemory((PVOID)0x8E03A000, &KeyVault.ConsoleCertificate, 0x1A8);

	SetMemory((PVOID)0x8E038020, &KeyVault.ConsoleCertificate.ConsoleId.abData, 5);

	BYTE newHash[XECRYPT_SHA_DIGEST_SIZE];

	XeCryptSha((BYTE*)0x8E038014, 0x3EC, NULL, NULL, NULL, NULL, newHash, XECRYPT_SHA_DIGEST_SIZE);

	SetMemory((PVOID)0x8E038000, newHash, XECRYPT_SHA_DIGEST_SIZE);
#if defined(DEVKIT)
	QWORD kvAddress = HvPeekQWORD(0x00000002000162E0);
#else
	QWORD kvAddress = HvPeekQWORD(0x0000000200016240);
#endif

	HvPeekBytes(kvAddress + 0xD0, KeyVault.ConsoleObfuscationKey, 0x40);
	memcpy(KeyVault.RoamableObfuscationKey, RetailKey, 0x10);
	HvPokeBytes(kvAddress, &KeyVault, 0x4000);
	return ERROR_SUCCESS;
}


HRESULT Process_KV()
{
	//Lets do our KV Detection Here!
	if (FileExists(PATH_KEYVAULT)) {
		if (SetKeyVault(PATH_KEYVAULT) == ERROR_SUCCESS) {
			VerifyKeyVault();
			return ERROR_SUCCESS;
		}
	}

	BYTE* kv = (BYTE*)malloc(0x4000);
	if (HvPeekBytes(HvPeekQWORD(0x0000000200016240), kv, 0x4000) == ERROR_SUCCESS) {
		if (SetKeyVault(kv) == ERROR_SUCCESS) {

			free(kv);
			return ERROR_SUCCESS;
		}
	}

	free(kv);
	return E_FAIL;
}

WCHAR WideMessage[0x100] = { 0 };
PWCHAR charToWChar(PCHAR Text, ...)
{
	CHAR Buffer[0x1000] = { 0 }, MessageBuffer[0x100] = { 0 };

	memset(WideMessage, 0, sizeof(WCHAR) * 0x100);

	va_list pArgList;
	va_start(pArgList, Text);
	vsprintf(Buffer, Text, pArgList);
	va_end(pArgList);

	sprintf(MessageBuffer, Buffer);
	mbstowcs(WideMessage, MessageBuffer, strlen(MessageBuffer) + 1);

	ZeroMemory(Buffer, sizeof(Buffer));
	ZeroMemory(MessageBuffer, sizeof(MessageBuffer));

	return WideMessage;
}

DWORD MakeBranch(DWORD Address, DWORD Destination, BOOL Linked)
{
	return (0x48000000) | ((Destination - Address) & 0x03FFFFFF) | (DWORD)Linked;
}

BOOL GetSectionInfo(CONST PCHAR SectionName, PDWORD Address, PDWORD Length)
{
	DWORD SectionInfoOffset = 0x90E00000;
	while (!strcmp(".rdata", (PCHAR)SectionInfoOffset) == FALSE) SectionInfoOffset += 4;
	PIMAGE_SECTION_HEADER DefaultSections = (PIMAGE_SECTION_HEADER)SectionInfoOffset;

	BOOL Succeded = FALSE;
	for (DWORD i = 0; strlen((PCHAR)DefaultSections[i].Name); i++) {

		if (!strcmp(SectionName, (PCHAR)DefaultSections[i].Name) == TRUE) {
			*Address = 0x90E00000 + _byteswap_ulong(DefaultSections[i].VirtualAddress);
			*Length = _byteswap_ulong(DefaultSections[i].Misc.VirtualSize);
			Succeded = TRUE;
			break;
		}
	}
	return Succeded;
}

ULONGLONG ReadULongLong(BYTE* bytes, DWORD index)
{
	return  (*(long long*)(&bytes[index]));
}

int ReadULong(BYTE* bytes, DWORD index)
{
	return  (*(int*)(&bytes[index]));
}

void DoXEXHash(BYTE* DigestBuffer, void* Packet)
{
	INCOMING_PACKET_HEADER* Header = (INCOMING_PACKET_HEADER*)Packet;

	DWORD Address = 0, Lenght = 0, BaseAddress = 0;

	DWORD SectionInfoOffset = g_ModuleBaseAddress;
	while (!strcmp(".rdata", (PCHAR)SectionInfoOffset) == FALSE) SectionInfoOffset += 4;
	PIMAGE_SECTION_HEADER DefaultSections = (PIMAGE_SECTION_HEADER)SectionInfoOffset;

	BOOL Succeded = FALSE;

	for (DWORD i = 0; strlen((PCHAR)DefaultSections[i].Name); i++) {

		if (!strcmp(".text", (PCHAR)DefaultSections[i].Name) == TRUE)
		{
			Address = g_ModuleBaseAddress + _byteswap_ulong(DefaultSections[i].VirtualAddress);
			Lenght = _byteswap_ulong(DefaultSections[i].Misc.VirtualSize);

			int bctrl = 0;

			while (ReadULong((unsigned char*)((Address + Lenght) - 0x4), bctrl * -1) != 0x4E800420) {

				bctrl += 0x4;
			}

			Lenght -= bctrl;

			int SizeOfImports = 0;

			while (ReadULongLong((unsigned char*)((Address + Lenght) - 0x8), SizeOfImports * -1) == 0x7D6903A64E800420) {
				SizeOfImports += 0x10;
			}

			sha1_context ctx_sha1;

			sha1_starts(&ctx_sha1);
			sha1_update(&ctx_sha1, (uint8*)Address, (Lenght - SizeOfImports));
			Lenght = _byteswap_ulong(Lenght);
			BaseAddress = _byteswap_ulong(g_ModuleBaseAddress);
			sha1_update(&ctx_sha1, (uint8*)g_ModuleBaseAddress, 4);
			sha1_update(&ctx_sha1, (uint8*)&DefaultSections[i].VirtualAddress, 4);
			sha1_update(&ctx_sha1, (uint8*)&Lenght, 4);
			sha1_update(&ctx_sha1, (uint8*)g_ModuleBaseAddress, 0x45);
			sha1_update(&ctx_sha1, (uint8*)&BaseAddress, 4);
			sha1_update(&ctx_sha1, (uint8*)Header->Memory_EncryptionKey, 0x30);
			sha1_update(&ctx_sha1, (uint8*)Header->Geneology, 16);
			sha1_update(&ctx_sha1, (uint8*)Header->CPUKey, 16);
			sha1_finish(&ctx_sha1, DigestBuffer);


			Succeded = TRUE;
			break;
		}
	}
}

void xbCreateBoxKey(long long xbBoxRequestID, unsigned char* out)
{
	long long temp = xbBoxRequestID;

	unsigned char* Key = (unsigned char*)malloc(0xC0);

	memset(Key, 0x33, 0xC0);

	for (int i = 0; i < 11; i++)
	{
		long long Fuse = HvPeekQWORD(0x8000020000020000 + (i * 0x200));

		Tramps->CallFunction(memcpy_Function, (int)Key + (i * 8), (int)&Fuse, 8, 0, false);
		Tramps->CallFunction(memcpy_Function, (int)Key + 0x58 + (i * 8), (int)&Fuse, 8, 0, false);
	}

	Key[0xB1] = XboxHardwareInfo->NumberOfProcessors;
	Key[0xB2] = XboxHardwareInfo->PCIBridgeRevisionID;
	Key[0xB3] = (unsigned char)XboxHardwareInfo->BldrMagic;
	Key[0xB9] = HvPeekBYTE(0x30);
	Key[0xBA] = HvPeekBYTE(0x25);

	Tramps->CallFunction(memcpy_Function, (int)Key + 0xB4, (int)0x8E03AA55, 5, 0, false);

	unsigned char xorValue = Key[0x32];

	for (int i = 0; i < 0xC0; i++)
	{
		if (Key[i] <= 0)
			Key[i] = (0xFF - Key[0xBA]);
		else
			Key[i] ^= xorValue;
	}

	for (int i = 0; i < 0xC0; i += 0x10)
	{
		XeCryptSha(Key + i, 0x10, NULL, NULL, NULL, NULL, Key + i, 0x10);
		XeCryptSha(Key + i, 0x5, NULL, NULL, NULL, NULL, Key + i, 0x5);
		XeCryptSha(Key + i, 0x2, (unsigned char*)&temp, 8, NULL, NULL, Key + i, 0x10);
	}

	XeCryptRc4(Key, 0x10, Key, 0xC0);

	XeCryptSha((BYTE*)(Key + 0x14), 0xAC, NULL, NULL, NULL, NULL, out, 0x10);

	free(Key);
}

__inline bool FIsSpace(char ch)
{
	return ch == ' ' || ch == '\015' || ch == 0;
}


int SgnCompareRgch(const char *sz1, const char *sz2, int cch)
{
	while (cch-- && *sz1) {
		char ch1 = *sz1++;
		char ch2 = *sz2++;
		if (ch1 >= 'a' && ch2 <= 'z')
			ch1 -= 32;
		if (ch2 >= 'a' && ch2 <= 'z')
			ch2 -= 32;
		if (ch1 != ch2)
			return ch1 - ch2;
	}
	if (*sz1)
		return *sz1;
	return cch < 0 ? 0 : -*sz2;
}

bool FEqualRgch(const char *sz1, const char *sz2, int cch)
{
	return SgnCompareRgch(sz1, sz2, cch) == 0;
}



const char *PchGetParam(LPCSTR szCmd, LPCSTR szKey, bool fNeedValue)
{
	const char *pchTok;
	int cchTok;
	bool fQuote = FALSE;

	/* Skip the command */
	for (pchTok = szCmd; !FIsSpace(*pchTok); ++pchTok);

	while (*pchTok) {
		/* Skip leading spaces */
		while (*pchTok && FIsSpace(*pchTok))
			++pchTok;
		if (!*pchTok)
			return NULL;
		for (cchTok = 0; !FIsSpace(pchTok[cchTok]); ++cchTok) {
			if (pchTok[cchTok] == '=') {
				if (FEqualRgch(szKey, pchTok, cchTok))
					return pchTok + cchTok + 1; /* Skip the '=' */
				break;
			}
		}
		/* If we didn't see the '=' we need to check anyway */
		if (!fNeedValue && pchTok[cchTok] != '=' && FEqualRgch(szKey, pchTok,
			cchTok))
			return pchTok + cchTok;
		/* No match, so we need to skip past the value */
		pchTok += cchTok;
		while (*pchTok && (!FIsSpace(*pchTok) || fQuote))
			if (*pchTok++ == '"')
				fQuote = !fQuote;
	}
	return NULL;
}

void GetParam(LPCSTR szLine, LPSTR szBuf, int cchBuf)
{
	int cch = 0;
	bool fQuote = FALSE;

	while (cch < cchBuf - 1 && *szLine && (!FIsSpace(*szLine) || fQuote)) {
		if (*szLine == '"') {
			if (fQuote && szLine[1] == '"') {
				/* Double quote inside a string gets copied as a single
				* quote */
				szBuf[cch++] = '"';
				szLine += 2;
			}
			else {
				fQuote = !fQuote;
				++szLine;
			}
		}
		else
			szBuf[cch++] = *szLine++;
	}
	szBuf[cch] = 0;
}




DWORD DwHexFromSz(LPCSTR sz, LPCSTR *szOut)
{
	DWORD dw = 0;

	for (;;) {
		if (*sz >= '0' && *sz <= '9')
			dw = dw * 16 + (*sz - '0');
		else if (*sz >= 'A' && *sz <= 'F')
			dw = dw * 16 + (*sz - 'A' + 10);
		else if (*sz >= 'a' && *sz <= 'f')
			dw = dw * 16 + (*sz - 'a' + 10);
		else
			break;
		++sz;
	}
	if (szOut)
		*szOut = sz;
	return dw;
}


DWORD DwFromSz(LPCSTR sz, int *pcchUsed)
{
	DWORD dw = 0;
	LPCSTR szStart = sz;

	if (*sz == '0') {
		++sz;
		if (*sz == 'x')
			dw = DwHexFromSz(++sz, &sz);
		else
			while (*sz >= '0' && *sz <= '7')
				dw = dw * 8 + (*sz++ - '0');
	}
	else
		while (*sz >= '0' && *sz <= '9')
			dw = dw * 10 + (*sz++ - '0');
	if (pcchUsed)
		*pcchUsed = sz - szStart;
	return dw;
}

BOOL FGetDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw)
{
	int cch;
	char sz[32];
	LPCSTR pch = PchGetParam(szLine, szKey, TRUE);
	if (!pch)
		return FALSE;
	GetParam(pch, sz, sizeof sz);
	*pdw = DwFromSz(sz, &cch);
	return FIsSpace(sz[cch]);
}

BOOL FGetNamedDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw, LPSTR szResp)
{
	if (!FGetDwParam(szLine, szKey, pdw))
		return FALSE;

	return TRUE;
}

#pragma optimize("", off)
bool FindSectionInfo(char * sectionName, int * virtualAddress, int * virtualLength)
{
	int sectionInfoOffset = 0x91000000;
	while (strcmp(".rdata", (char*)sectionInfoOffset)) sectionInfoOffset += 4;
	IMAGE_SECTION_HEADER *defaultSections = (IMAGE_SECTION_HEADER*)sectionInfoOffset;

	bool succeded = false;
	*virtualAddress = *virtualLength = 0;
	for (int i = 0; strlen((char*)defaultSections[i].Name); i++)
		if (!strcmp(sectionName, (char*)defaultSections[i].Name))
		{
			*virtualAddress = _byteswap_ulong(defaultSections[i].VirtualAddress);
			*virtualLength = _byteswap_ulong(defaultSections[i].Misc.VirtualSize);
			succeded = true;
			break;
		}

	return succeded;
}
#pragma optimize("", on)

void * AlignedMemorySearch(char * sectionName, void * scanData, int dataLength)
{
	int sectionOffset, sectionLength;

	if (FindSectionInfo(sectionName, &sectionOffset, &sectionLength))
	{
		void * currentAddress = (void*)(0x91000000 + sectionOffset);
		while (currentAddress <= (void*)(0x91000000 + sectionOffset + sectionLength - dataLength))
			if (!memcmp(currentAddress, scanData, dataLength))
				return currentAddress;
			else
				currentAddress = (void*)((int)currentAddress + 4);
	}
	return 0;
}
bool GetIniBoolValue(char* section, char* item)
{
	return ini.GetBoolValue(section, item);
}
void SetIniBoolValue(char* section, char* item, char* logic)
{
	ini.SetValue(section, item, logic);
}
void SaveIni()
{
	ini.SaveFile("xbOnline:\\xbOnline.ini");
}
void LoadINI()
{
	if (!ini.LoadFile("xbOnline:\\xbOnline.ini"))
	{
		xb_custom_xui = ini.GetBoolValue("Hud", "xb_custom_xui");
		xb_custom_notify = ini.GetBoolValue("Hud", "xb_custom_notify");
		xb_custom_time = ini.GetBoolValue("Hud", "xb_custom_time");
		xb_redeemhook = ini.GetBoolValue("Hud", "xb_redeemhook");

		xb_cheats_cod4 = ini.GetBoolValue("Cheats", "xb_cheats_cod4");
		xb_cheats_waw = ini.GetBoolValue("Cheats", "xb_cheats_waw");
		xb_cheats_mw2 = ini.GetBoolValue("Cheats", "xb_cheats_mw2");
		xb_cheats_bo1 = ini.GetBoolValue("Cheats", "xb_cheats_bo1");
		xb_cheats_mw3 = ini.GetBoolValue("Cheats", "xb_cheats_mw3");
		xb_cheats_bo2 = ini.GetBoolValue("Cheats", "xb_cheats_bo2");
		xb_cheats_ghosts = ini.GetBoolValue("Cheats", "xb_cheats_ghosts");
		xb_cheats_aw = ini.GetBoolValue("Cheats", "xb_cheats_aw");
		xb_cheats_bf4 = ini.GetBoolValue("Cheats", "xb_cheats_bf4");

		xb_bypass_cod4 = ini.GetBoolValue("Bypasses", "xb_bypass_cod4");
		xb_bypass_waw = ini.GetBoolValue("Bypasses", "xb_bypass_waw");
		xb_bypass_mw2 = ini.GetBoolValue("Bypasses", "xb_bypass_mw2");
		xb_bypass_bo1 = ini.GetBoolValue("Bypasses", "xb_bypass_bo1");
		xb_bypass_mw3 = ini.GetBoolValue("Bypasses", "xb_bypass_mw3");
		xb_bypass_bo2 = ini.GetBoolValue("Bypasses", "xb_bypass_bo2");
		xb_bypass_ghosts = ini.GetBoolValue("Bypasses", "xb_bypass_ghosts");
		xb_bypass_aw = ini.GetBoolValue("Bypasses", "xb_bypass_aw");

		xb_cheats_bf4 = ini.GetBoolValue("Cheats", "xb_cheats_bf4");

		if (!xb_cheats_bf4 && ini.GetSectionSize("Cheats") < 9)
			ini.SetValue("Cheats", "xb_cheats_bf4", "true");

		xb_cheats_bf4 = ini.GetBoolValue("Cheats", "xb_cheats_bf4");

		xb_cheats_mw2_onhost = ini.GetBoolValue("Cheats", "xb_cheats_mw2_onhost");

		if (!xb_cheats_mw2_onhost && ini.GetSectionSize("Cheats") < 10)
			ini.SetValue("Cheats", "xb_cheats_mw2_onhost", "true");

		xb_cheats_mw2_onhost = ini.GetBoolValue("Cheats", "xb_cheats_mw2_onhost");

		xb_cheats_mw3_onhost = ini.GetBoolValue("Cheats", "xb_cheats_mw3_onhost");

		if (!xb_cheats_mw3_onhost && ini.GetSectionSize("Cheats") < 11)
			ini.SetValue("Cheats", "xb_cheats_mw3_onhost", "true");

		xb_cheats_mw3_onhost = ini.GetBoolValue("Cheats", "xb_cheats_mw3_onhost");

		xb_cheats_csgo = ini.GetBoolValue("Cheats", "xb_cheats_csgo");

		if (!xb_cheats_csgo && ini.GetSectionSize("Cheats") < 12)
			ini.SetValue("Cheats", "xb_cheats_csgo", "true");

		xb_cheats_csgo = ini.GetBoolValue("Cheats", "xb_cheats_csgo");

		xb_cheats_tf2 = ini.GetBoolValue("Cheats", "xb_cheats_tf2");

		if (!xb_cheats_tf2 && ini.GetSectionSize("Cheats") < 13)
			ini.SetValue("Cheats", "xb_cheats_tf2", "true");

		xb_cheats_tf2 = ini.GetBoolValue("Cheats", "xb_cheats_tf2");

		xb_cheats_bf3 = ini.GetBoolValue("Cheats", "xb_cheats_bf3");

		if (!xb_cheats_bf3 && ini.GetSectionSize("Cheats") < 14)
			ini.SetValue("Cheats", "xb_cheats_bf3", "true");

		xb_cheats_bf3 = ini.GetBoolValue("Cheats", "xb_cheats_bf3");



		xb_custom_kvp = ini.GetBoolValue("Bypasses", "xb_custom_kvp");

		DbgPrint("Section Legnth: %i\n", ini.GetSectionSize("Bypasses"));


		if (!xb_custom_kvp && ini.GetSectionSize("Bypasses") < 9)
			ini.SetValue("Bypasses", "xb_custom_kvp", "true");

		xb_custom_kvp = ini.GetBoolValue("Bypasses", "xb_custom_kvp");

		ini.SaveFile("xbOnline:\\xbOnline.ini");

	}
	else
	{
		ini.SetValue("Hud", "xb_custom_xui", "true");
		ini.SetValue("Hud", "xb_custom_notify", "true");
		ini.SetValue("Hud", "xb_custom_time", "true");
		ini.SetValue("Hud", "xb_redeemhook", "true");

		ini.SetValue("Cheats", "xb_cheats_cod4", "true");
		ini.SetValue("Cheats", "xb_cheats_waw", "true");
		ini.SetValue("Cheats", "xb_cheats_mw2", "true");
		ini.SetValue("Cheats", "xb_cheats_bo1", "true");
		ini.SetValue("Cheats", "xb_cheats_mw3", "true");
		ini.SetValue("Cheats", "xb_cheats_bo2", "true");
		ini.SetValue("Cheats", "xb_cheats_ghosts", "true");
		ini.SetValue("Cheats", "xb_cheats_aw", "true");
		ini.SetValue("Cheats", "xb_cheats_bf4", "true");
		ini.SetValue("Cheats", "xb_cheats_mw2_onhost", "true");
		ini.SetValue("Cheats", "xb_cheats_mw3_onhost", "true");
		ini.SetValue("Cheats", "xb_cheats_csgo", "true");
		ini.SetValue("Cheats", "xb_cheats_tf2", "true");
		ini.SetValue("Cheats", "xb_cheats_bf3", "true");

		ini.SetValue("Bypasses", "xb_bypass_cod4", "true");
		ini.SetValue("Bypasses", "xb_bypass_waw", "true");
		ini.SetValue("Bypasses", "xb_bypass_mw2", "true");
		ini.SetValue("Bypasses", "xb_bypass_bo1", "true");
		ini.SetValue("Bypasses", "xb_bypass_mw3", "true");
		ini.SetValue("Bypasses", "xb_bypass_bo2", "true");
		ini.SetValue("Bypasses", "xb_bypass_ghosts", "true");
		ini.SetValue("Bypasses", "xb_bypass_aw", "true");
		ini.SetValue("Bypasses", "xb_custom_kvp", "true");

		ini.SaveFile("xbOnline:\\xbOnline.ini");
	}
}

void CreateXboxThread(void* ptr, void* p)
{
	HANDLE hThread1 = 0; DWORD threadId1 = 0;
	ExCreateThread(&hThread1, 0x10000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)ptr, p, 0x2);
	XSetThreadProcessor(hThread1, 4);
	ResumeThread(hThread1);
	CloseHandle(hThread1);
}

std::string hexStr(unsigned char *data, int len)
{
	std::stringstream ss;
	ss << std::hex;
	for (int i = 0; i < len; ++i)
		ss << std::uppercase << std::setw(2) << std::setfill('0') << (int)data[i];
	return ss.str();
}


bool DownloadFile(const char* Server, const char* FileName, unsigned char** Out, int* length)
{
	*Out = (unsigned char*)0;

	HRESULT ret = 0;

	HttpClient* pHttpClient = new HttpClient;

	ret = pHttpClient->GET(Server, FileName);

	if (ret == E_PENDING) {

		while (pHttpClient->GetStatus() == HttpClient::HTTP_STATUS_BUSY)
			Sleep(500);
	}

	if (pHttpClient->GetStatus() != HttpClient::HTTP_STATUS_DONE) {

		delete pHttpClient;
		return false;
	}

	BYTE* pContent = pHttpClient->GetResponseContentData();
	DWORD nLength = pHttpClient->GetResponseContentDataLength();

	if ((pContent > 0) && (nLength > 0))
	{
		*length = nLength;

		nLength += 0x10000 - (nLength % 0x10000);

		*Out = (unsigned char*)XMemAlloc(nLength, XAPO_ALLOC_ATTRIBUTES);

		if (*Out > 0 && pContent && nLength)
		{
			memcpy(*Out, pContent, nLength);

			delete pHttpClient;
			return true;
		}
	}

	delete pHttpClient;
	return false;
}

unsigned int ReverseInt(unsigned int val)
{
	int retVal = val - g_ModuleBaseAddress;

	return ((retVal << 24)) | (((retVal << 8) & 0x00ff0000)) | (((retVal >> 8) & 0x0000ff00)) | (((retVal >> 24) & 0x000000ff));
}

void CryptData(unsigned char* in, int inLength, unsigned char** out, int* outLength)
{
	int Size = inLength;

	while ((Size % 0x80) != 0)
		Size++;

	unsigned char* cryptBuffer = (unsigned char*)malloc(Size);

	XeCryptRandom(cryptBuffer, Size);

	memcpy(cryptBuffer, in, (inLength));

	XeCryptBnQwNeRsaPubCrypt((const QWORD*)(&cryptBuffer[0]), (QWORD*)(&cryptBuffer[0]), (const XECRYPT_RSA*)PublicKey);

	*outLength = Size;
	*out = cryptBuffer;
}

void DecryptData(unsigned char* in, int inLength, unsigned char* out)
{
	for (int i = 0; i < (inLength / 0x80); i++)
		XeCryptBnQwNeRsaPrvCrypt((const QWORD*)(&in[(i * 0x80)]), (QWORD*)(&out[(i * 0x80)]), (const XECRYPT_RSA*)PrivateKey);
}


void RC4(BYTE* content, int content_length, BYTE* key, int key_length, unsigned char Byte)
{
	BYTE* buffer = (BYTE*)malloc(0x100);
	BYTE* buffer2 = (BYTE*)malloc(0x100);
	char temp;
	int num2;

	for (num2 = 0; num2 < 0x100; num2++)
	{
		buffer[num2] = (char)num2;
		buffer2[num2] = key[num2 % key_length];
	}

	int index = 0;
	for (num2 = 0; num2 < 0x100; num2++)
	{
		index = ((index + buffer[num2]) + buffer2[num2]) % Byte; //Changed to 0x80 from 0x100
		temp = buffer[num2];
		buffer[num2] = buffer[index];
		buffer[index] = temp;
	}

	num2 = index = 0;
	for (int i = 0; i < content_length; i++)
	{
		num2 = (num2 + 1) % Byte; //Changed to 0x80 from 0x100
		index = (index + buffer[num2]) % Byte; //Changed to 0x80 from 0x100
		temp = buffer[num2];
		buffer[num2] = buffer[index];
		buffer[index] = temp;
		int t = (buffer[num2] + buffer[index]) % Byte; //Changed to 0x80 from 0x100
		content[i] ^= buffer[t];
	}
	free(buffer);
	free(buffer2);
}


void Custom_Printf(const char* format, ...)
{
#if defined(DEVKIT)
	//va_list args;
	//va_start(args, format);
	//vfprintf(stdout, format, args);
	//va_end(args);
#else
	//va_list args;
	//va_start(args, format);
	//vfprintf(stdout, format, args);
	//va_end(args);
#endif
}

void DEVKIT_Printf(const char* format, ...)
{
#if defined(DEVKIT)
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
#else
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
#endif
}

BOOL DoesContainText(PWCHAR str, PWCHAR suffix)
{
	size_t str_len = wcslen(str);
	size_t suffix_len = wcslen(suffix);

	if (suffix_len > str_len)
		return 0;

	return (wcscmp(str + str_len - suffix_len, suffix) == 0);
}

PWCHAR CharToWChar(const char* Text)
{
	INT TextLen = strlen(Text) + 1;
	PWCHAR Buffer = new WCHAR[TextLen];

	mbstowcs(Buffer, Text, TextLen);
	return Buffer;
}

PWCHAR LinkWChar(PWCHAR Text, ...)
{
	WCHAR Buffer[0x1000], MessageBuffer[0x100];;

	va_list pArgList;
	va_start(pArgList, Text);
	vswprintf(Buffer, Text, pArgList);
	va_end(pArgList);

	swprintf(MessageBuffer, Buffer);

	return MessageBuffer;
}


std::string SplitLastOf(PWCHAR Text, PCHAR FindLastOf)
{
	size_t found;

	std::wstring sText(Text);
	std::string str(sText.begin(), sText.end());

	found = str.find_last_of(FindLastOf);

	if (found < 0)
		return str;

	return str.erase(0, found + 1);
}
int ResolveFunction_0(HMODULE hHandle, unsigned int dwOrdinal) {
	int ptr = 0;
	if (hHandle == 0)
		return 0;

	// pointer may change per dash. ect: 17526
	((NTSTATUS(*)(...))XexGetProcAddressPointer)((HANDLE)hHandle, dwOrdinal, &ptr);

	return int(ptr);
}
// for getting the handle
bool GetHandle(void* pvAddress, PHANDLE hModule)
{
	CRITICAL_SECTION section;
	InitializeCriticalSection(&section);

	PLDR_DATA_TABLE_ENTRY entry;

	if (pvAddress <= 0)
		return false;

	if (*hModule != 0) // don't bother re-applying it.
		return true;

	((PVOID(*)(...))XexPcToFileHeaderPointer)(pvAddress, &entry);

	*hModule = (PHANDLE)entry;

	LeaveCriticalSection(&section);
	return true;
}
//VOID GetMachineAccountKey()
//{
//
//	unsigned char* MachineAccountBuffer = (unsigned char*)malloc(0x14A4);
//	unsigned char* CryptKey = (unsigned char*)malloc(0x4);
//
//	NetDll_XnpLoadMachineAccount(2, MachineAccountBuffer);
//
//	memcpy(CryptKey, MachineAccountBuffer + 0x64, 0x10);
//
//	CryptKey[0x4] = 0x7;
//	CryptKey[0x9] = 0x2;
//
//	XeCrypt
//(CryptKey, 0x10, NULL, NULL, NULL, NULL, CryptKey, 0x4);
//
//
//
//	CWriteFile("xbOnline:\\Cache\\xbData.bin", CryptKey, 0x4);
//
//	free(MachineAccountBuffer);
//	free(CryptKey);
//
//}
VOID GetMachineAccountKey()
{

	unsigned char* MachineAccountBuffer = (unsigned char*)malloc(0x1B40);

	NetDll_XnpLoadMachineAccount(2, MachineAccountBuffer);


	CWriteFile("xbOnline:\\Cache\\xbData.bin", MachineAccountBuffer, 0x1B40);

	free(MachineAccountBuffer);
}

FILETIME GetFileTime(const CHAR * FileName)
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
long long GetUnix(FILETIME ft)
{
	// takes the last modified date
	LARGE_INTEGER date, adjust;
	date.HighPart = ft.dwHighDateTime;
	date.LowPart = ft.dwLowDateTime;

	// 100-nanoseconds = milliseconds * 10000
	adjust.QuadPart = 11644473600000 * 10000;

	// removes the diff between 1970 and 1601
	date.QuadPart -= adjust.QuadPart;

	// converts back from 100-nanoseconds to seconds
	return date.QuadPart / 10000000;
}


bool TimeSanityCheck(long long timenow)
{
	if (timenow > 1539133294)
		return true;
	return false;
}
void getKeyvaultLife()
{
	if (FileExists("xbOnline:\\KV.bin"))
	{
		char message[354] = { 0 };
	tryagain:

		FILETIME fTime = GetFileTime("xbOnline:\\KV.bin");
		int currentTime = time(0);

		if (attemptCount < 4)
		{
			if (!TimeSanityCheck(currentTime))
			{
				attemptCount++;
				goto tryagain;
			}



			long long time = (currentTime + (currentTime - GetUnix(fTime))) - currentTime;

			long long years = time / 60 / 60 / 24 / 365;
			long long days = (time / 60 / 60 / 24) % 365;
			long long hours = (time / 60 / 60) % 24;
			long long minutes = (time / 60) % 60;
			long long seconds = time % 60;

			//_snwprintf(Out, 1024, L"%lli Yrs, %lli Days, %lli Hrs, %lli Min", years, days, hours, minutes);
			_snprintf(message, 354, "Just letting you know you've been using this KV for:\n\n%lli Years, %lli Days, %lli Hours, %lli Mins!\n\n\n\n\n\nEnjoy your time with us!", years, days, hours, minutes);

			wchar_t* Msg = charToWChar_Com(message);

			MESSAGEBOX_RESULT g_mb_result = { 0 };
			XOVERLAPPED g_xol = { 0 };

			LPCWSTR Button[1] = { L"Okay!" };

			while (XShowMessageBoxUI(XUSER_INDEX_ANY, L"Your Keyvault Status", Msg, 1, Button, 0, XMB_ALERTICON, &g_mb_result, &g_xol) == ERROR_ACCESS_DENIED)
				Sleep(500);
			while (!XHasOverlappedIoCompleted(&g_xol))
				Sleep(500);

			//Delete DELETE NEIN NEIN NEIN
			delete Msg;
		}
	}
}


int NTGetFileLength(LPCSTR FileName)
{
	long st = 0;
	HANDLE FileHandle;

	FILE_NETWORK_OPEN_INFORMATION fni;

	ANSI_STRING as;
	IO_STATUS_BLOCK iosb;
	IO_STATUS_BLOCK io;
	OBJECT_ATTRIBUTES attr;

	RtlInitAnsiString(&as, FileName);
	attr.Attributes = OBJ_CASE_INSENSITIVE;
	attr.ObjectName = &as;
	attr.RootDirectory = NULL;

	st = NtCreateFile(&FileHandle, GENERIC_READ | SYNCHRONIZE, &attr, &iosb, NULL, 0, 0, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT);

	if (FAILED(st))
		return -1;

	st = NtQueryInformationFile(FileHandle, &io, &fni, sizeof(fni), FileNetworkOpenInformation);

	if (FAILED(st))
	{
		NtClose(FileHandle);
		return -1;
	}
	NtClose(FileHandle);

	return fni.EndOfFile.LowPart;
}

bool NTReadFile(LPCSTR FileName, PVOID Buffer, ULONG Length)
{
	long st = 0;
	HANDLE FileHandle;

	ANSI_STRING as;
	IO_STATUS_BLOCK iosb;
	IO_STATUS_BLOCK io;
	OBJECT_ATTRIBUTES attr;

	RtlInitAnsiString(&as, FileName);
	attr.Attributes = OBJ_CASE_INSENSITIVE;
	attr.ObjectName = &as;
	attr.RootDirectory = NULL;

	st = NtCreateFile(&FileHandle, GENERIC_READ | SYNCHRONIZE, &attr, &iosb, NULL, 0, 0, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT);

	if (FAILED(st))
		return false;

	st = NtReadFile(FileHandle, NULL, NULL, NULL, &io, Buffer, Length, NULL);

	if (FAILED(st))
	{
		NtClose(FileHandle);
		return false;
	}

	NtClose(FileHandle);

	return true;
}

bool NTWriteFile(LPCSTR FilePath, PVOID Data, DWORD Size)
{
	HANDLE fHandle = NULL;
	STRING aFileName = { 0 };
	IO_STATUS_BLOCK Status = { 0 };
	RtlInitAnsiString(&aFileName, FilePath);
	OBJECT_ATTRIBUTES Attributes = { 0, &aFileName, FILE_ATTRIBUTE_NORMAL };

	if (NtCreateFile(&fHandle, GENERIC_WRITE | SYNCHRONIZE | FILE_READ_ATTRIBUTES, &Attributes, &Status, NULL, 0, FILE_SHARE_READ, TRUNCATE_EXISTING, 0x20) != ERROR_SUCCESS)
		return false;

	if (NtWriteFile(fHandle, NULL, NULL, NULL, &Status, Data, Size, NULL) != ERROR_SUCCESS) {
		NtClose(fHandle);
		return false;
	}

	NtClose(fHandle);
	return true;
}

long FCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, LPCSTR FileName, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions)
{
	char oszName[MAX_PATH];
	ANSI_STRING as;
	IO_STATUS_BLOCK iosb;
	OBJECT_ATTRIBUTES attr;



	strcpy_s(oszName, sizeof(oszName), FileName);

	RtlInitAnsiString(&as, oszName);
	attr.Attributes = OBJ_CASE_INSENSITIVE;
	attr.ObjectName = &as;
	attr.RootDirectory = NULL;

	return NtCreateFile(FileHandle, DesiredAccess, &attr, &iosb, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions);
}
