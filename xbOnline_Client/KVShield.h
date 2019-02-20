#pragma once

typedef struct _SHIELDDATA
{
	BYTE XE_CONSOLE_CERTIFICATE[0x1A8];
	char XE_CONSOLE_SERIAL[0xC];
	BYTE XE_PRIVATE_CERTIFICATE[0x1D0];
	BYTE DRIVE_OSIG[0x25];
	BYTE OddFeatures[0xD4];
	BYTE DVDKey[0x1CF8];
	BYTE CardeaCertificate[0x2108];
	BYTE CPU_KEY_HASH[0x14];
	BYTE Keyvault_Digest[0x14];
	BYTE WIRELESS_CONTROLLER_KeyMS[0x20];
	BYTE WIRELESS_CONTROLLER_Key3P[0x20];
	BYTE WIRED_CONTROLLER_KeyMS[0x20];
	BYTE WIRED_CONTROLLER_Key3P[0x20];
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

NTSTATUS IoCreateFileHook(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG Disposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength, int	CreateFileType, PVOID InternalParameters, ULONG Options);

bool InitializeKVShield();
bool InitKeyvaultForSheild(BYTE* rawKeyvault);
int XeKeysConsolePrivateKeySign_Hook(PBYTE Digest, PBYTE XE_CONSOLE_CERTIFICATE);
DWORD XeKeysGetConsoleCertificate_Hook(unsigned char *cert);
DWORD XeKeysGetKey_Hook(unsigned int Key, PVOID KeyBuffer, PDWORD keyLength);