#pragma once


/*
Size: 0x209
*/
typedef struct _SHIELDDATA
{
	int SHIELD_KEY_VERSION;
	int SHIELD_KEY_ID;
	BYTE XE_CONSOLE_CERTIFICATE[0x1A8];
	char XE_CONSOLE_SERIAL[0xC];
	BYTE DRIVE_OSIG[0x25];
	BYTE CPU_KEY_HASH[0x14];
	BYTE Keyvault_Digest[0x14];
} SHIELDDATA, *PSHIELDDATA;

typedef NTSTATUS(*IoCreateFile_t)(
	PHANDLE            FileHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK   IoStatusBlock,
	PLARGE_INTEGER     AllocationSize,
	ULONG              FileAttributes,
	ULONG              ShareAccess,
	ULONG              Disposition,
	ULONG              CreateOptions,
	PVOID              EaBuffer,
	ULONG              EaLength,
	int				   CreateFileType,
	PVOID              InternalParameters,
	ULONG              Options);


extern IoCreateFile_t IoCreateFileOriginal;
extern Detour IoCreateFileDetour;

extern CRITICAL_SECTION KvProtectionSection;

void MessageBox();

NTSTATUS IoCreateFileHook(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG Disposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength, int	CreateFileType, PVOID InternalParameters, ULONG Options);

bool InitializeKVShield();
bool InitKeyvaultForSheild(BYTE* rawKeyvault);
int XeKeysConsolePrivateKeySign_Hook(PBYTE Digest, PBYTE XE_CONSOLE_CERTIFICATE);
DWORD XeKeysGetConsoleCertificate_Hook(unsigned char *cert);
DWORD XeKeysGetKey_Hook(unsigned int Key, PVOID KeyBuffer, PDWORD keyLength);