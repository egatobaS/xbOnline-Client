#pragma once


typedef unsigned __int64	QWORD;

typedef QWORD near           *PQWORD;
typedef enum { // effects on jtag noted in comment
	HalHaltRoutine = 0x0, // hard poweroff (used by hotplug HDD) HalpPowerDownSystemNow
	HalRebootRoutine = 0x1, // hard reset (video error) HalpRebootSystem
	HalKdRebootRoutine = 0x2, // hard reset (used for dumpwritedump/frozen processor) HalpRebootSystem
	HalFatalErrorRebootRoutine = 0x3, // hard reset HalpRebootSystem
	HalResetSMCRoutine = 0x4, // power off (hard) HalpRebootSystem
	HalPowerDownRoutine = 0x5, // power off (nice) HalpPowerDownSystem
	HalRebootQuiesceRoutine = 0x6, // E79 (lost settings) HalpRebootQuiesceSystem
	HalForceShutdownRoutine = 0x7, // frozen console HalpRequestPowerDownDpc
	HalPowerCycleQuiesceRoutine = 0x8,
	HalMaximumRoutine = 0x9,
} FIRMWARE_REENTRY;


typedef struct _XEX_EXECUTION_ID {
	int MediaID;
	int Version;
	int BaseVersion;
	union {
		int TitleID;
		struct {
			short PublisherID;
			short GameID;
		};
	};
	char Platform;
	char ExecutableType;
	char DiscNum;
	char DiscsInSet;
	int SaveGameID;
} XEX_EXECUTION_ID, *PXEX_EXECUTION_ID;

#define EXPORTNUM(x)

typedef long			NTSTATUS;


#pragma pack(push, 1)
typedef struct _XE_CONSOLE_ID {
	union {
		struct {
			unsigned char refurbBits : 4;
			unsigned char ManufactureMonth : 4;
			unsigned int ManufactureYear : 4;
			unsigned int MacIndex3 : 8;
			unsigned int MacIndex4 : 8;
			unsigned int MacIndex5 : 8;
			unsigned int Crc : 4;
		} asBits;
		unsigned char abData[5];
	};
} XE_CONSOLE_ID, *PXE_CONSOLE_ID;
C_ASSERT(sizeof(XE_CONSOLE_ID) == 0x5);
#pragma pack(pop)

typedef struct _CONSOLE_PUBLIC_KEY {
	unsigned char PublicExponent[0x4];
	unsigned char Modulus[0x80];
} CONSOLE_PUBLIC_KEY, *PCONSOLE_PUBLIC_KEY;
C_ASSERT(sizeof(CONSOLE_PUBLIC_KEY) == 0x84);

typedef struct _XE_CONSOLE_CERTIFICATE {
	unsigned short CertSize;
	XE_CONSOLE_ID ConsoleId;
	unsigned char ConsolePartNumber[0xB];
	unsigned char Reserved[0x4];
	unsigned short  Privileges;
	unsigned int ConsoleType;
	char ManufacturingDate[0x8];
	CONSOLE_PUBLIC_KEY ConsolePublicKey;
	unsigned char Signature[0x100];
} XE_CONSOLE_CERTIFICATE, *PXE_CONSOLE_CERTIFICATE;
C_ASSERT(sizeof(XE_CONSOLE_CERTIFICATE) == 0x1A8);

typedef struct _XE_CONSOLE_SIGNATURE {
	XE_CONSOLE_CERTIFICATE Cert;
	unsigned char Signature[0x80];
} XE_CONSOLE_SIGNATURE, *PXE_CONSOLE_SIGNATURE;
C_ASSERT(sizeof(XE_CONSOLE_SIGNATURE) == 0x228);



#pragma pack(1)
typedef enum _ODD_POLICY {
	ODD_POLICY_FLAG_CHECK_FIRMWARE = 0x120,
} ODD_POLICY;

typedef union _INQUIRY_DATA {
	struct {
		unsigned char DeviceType : 5;
		unsigned char DeviceTypeQualifier : 3;
		unsigned char DeviceTypeModifier : 7;
		unsigned char RemovableMedia : 1;
		unsigned char Versions : 8;
		unsigned char ResponseDataFormat : 4;
		unsigned char HiSupport : 1;
		unsigned char NormACA : 1;
		unsigned char ReservedBit : 1;
		unsigned char AERC : 1;
		unsigned char AdditionalLength : 8;
		unsigned short Reserved : 16;
		unsigned char SoftReset : 1;
		unsigned char CommandQueue : 1;
		unsigned char Reserved2 : 1;
		unsigned char LinkedCommands : 1;
		unsigned char Synchronous : 1;
		unsigned char Wide16Bit : 1;
		unsigned char Wide32Bit : 1;
		unsigned char RelativeAddressing : 1;
		unsigned char VendorId[8];
		unsigned char ProductId[16];
		unsigned char ProductRevisionLevel[4];
	};
	unsigned char Data[0x24];
} INQUIRY_DATA, *pINQUIRY_DATA;
C_ASSERT(sizeof(INQUIRY_DATA) == 0x24);

typedef struct _XEIKA_ODD_DATA {
	unsigned char         Version;
	unsigned char         PhaseLevel;
	INQUIRY_DATA InquiryData;
} XEIKA_ODD_DATA, *PXEIKA_ODD_DATA;
C_ASSERT(sizeof(XEIKA_ODD_DATA) == 0x26);

typedef struct _XEIKA_DATA {
	XECRYPT_RSAPUB_2048 PublicKey;
	unsigned int               Signature;
	unsigned short                Version;
	XEIKA_ODD_DATA      OddData;
	unsigned char                Padding[4];
} XEIKA_DATA, *PXEIKA_DATA;
C_ASSERT(sizeof(XEIKA_DATA) == 0x140);

typedef struct _XEIKA_CERTIFICATE {
	unsigned short       Size;
	XEIKA_DATA Data;
	unsigned char       Padding[0x1146];
} XEIKA_CERTIFICATE, *PXEIKA_CERTIFICATE;
C_ASSERT(sizeof(XEIKA_CERTIFICATE) == 0x1288);

typedef struct _KEY_VAULT 
{														 // Key #
	unsigned char  HmacShaDigest[0x10];                  //            0x0000
	unsigned char  Confounder[0x08];                     //            0x0010
	unsigned char  ManufacturingMode;                    // 0x00       0x0018
	unsigned char  AlternateKeyVault;                    // 0x01       0x0019
	unsigned char  RestrictedPrivilegesFlags;            // 0x02       0x001A
	unsigned char  ReservedByte3;                        // 0x03       0x001B
	unsigned short  OddFeatures;                          // 0x04       0x001C
	unsigned short  OddAuthtype;                          // 0x05       0x001E
	unsigned int RestrictedHvextLoader;                // 0x06       0x0020
	unsigned int PolicyFlashSize;                      // 0x07       0x0024
	unsigned int PolicyBuiltinUsbmuSize;               // 0x08       0x0028
	unsigned int ReservedDword4;                       // 0x09       0x002C
	unsigned long long RestrictedPrivileges;                 // 0x0A       0x0030
	unsigned long long ReservedQword2;                       // 0x0B       0x0038
	unsigned long long ReservedQword3;                       // 0x0C       0x0040
	unsigned long long ReservedQword4;                       // 0x0D       0x0048
	unsigned char  ReservedKey1[0x10];                   // 0x0E       0x0050
	unsigned char  ReservedKey2[0x10];                   // 0x0F       0x0060
	unsigned char  ReservedKey3[0x10];                   // 0x10       0x0070
	unsigned char  ReservedKey4[0x10];                   // 0x11       0x0080
	unsigned char  ReservedRandomKey1[0x10];             // 0x12       0x0090
	unsigned char  ReservedRandomKey2[0x10];             // 0x13       0x00A0
	unsigned char  ConsoleSerialNumber[0xC];             // 0x14       0x00B0
	unsigned char  MoboSerialNumber[0xC];                // 0x15       0x00BC
	unsigned short  GameRegion;                           // 0x16       0x00C8
	unsigned char  Padding1[0x6];                        //            0x00CA
	unsigned char  ConsoleObfuscationKey[0x10];          // 0x17       0x00D0
	unsigned char  KeyObfuscationKey[0x10];              // 0x18       0x00E0
	unsigned char  RoamableObfuscationKey[0x10];         // 0x19       0x00F0
	unsigned char  DvdKey[0x10];                         // 0x1A       0x0100
	unsigned char  PrimaryActivationKey[0x18];           // 0x1B       0x0110
	unsigned char  SecondaryActivationKey[0x10];         // 0x1C       0x0128
	unsigned char  GlobalDevice2desKey1[0x10];           // 0x1D       0x0138
	unsigned char  GlobalDevice2desKey2[0x10];           // 0x1E       0x0148
	unsigned char  WirelessControllerMs2desKey1[0x10];   // 0x1F       0x0158
	unsigned char  WirelessControllerMs2desKey2[0x10];   // 0x20       0x0168
	unsigned char  WiredWebcamMs2desKey1[0x10];          // 0x21       0x0178
	unsigned char  WiredWebcamMs2desKey2[0x10];          // 0x22       0x0188
	unsigned char  WiredControllerMs2desKey1[0x10];      // 0x23       0x0198
	unsigned char  WiredControllerMs2desKey2[0x10];      // 0x24       0x01A8
	unsigned char  MemoryUnitMs2desKey1[0x10];           // 0x25       0x01B8
	unsigned char  MemoryUnitMs2desKey2[0x10];           // 0x26       0x01C8
	unsigned char  OtherXsm3DeviceMs2desKey1[0x10];      // 0x27       0x01D8
	unsigned char  OtherXsm3DeviceMs2desKey2[0x10];      // 0x28       0x01E8
	unsigned char  WirelessController3p2desKey1[0x10];   // 0x29       0x01F8
	unsigned char  WirelessController3p2desKey2[0x10];   // 0x2A       0x0208
	unsigned char  WiredWebcam3p2desKey1[0x10];          // 0x2B       0x0218
	unsigned char  WiredWebcam3p2desKey2[0x10];          // 0x2C       0x0228
	unsigned char  WiredController3p2desKey1[0x10];      // 0x2D       0x0238
	unsigned char  WiredController3p2desKey2[0x10];      // 0x2E       0x0248
	unsigned char  MemoryUnit3p2desKey1[0x10];           // 0x2F       0x0258
	unsigned char  MemoryUnit3p2desKey2[0x10];           // 0x30       0x0268
	unsigned char  OtherXsm3Device3p2desKey1[0x10];      // 0x31       0x0278
	unsigned char  OtherXsm3Device3p2desKey2[0x10];      // 0x32       0x0288
	XECRYPT_RSAPRV_1024 ConsolePrivateKey;      // 0x33       0x0298
	XECRYPT_RSAPRV_2048 XeikaPrivateKey;        // 0x34       0x0468
	XECRYPT_RSAPRV_1024 CardeaPrivateKey;       // 0x35       0x07F8
	XE_CONSOLE_CERTIFICATE ConsoleCertificate;  // 0x36       0x09C8
	XEIKA_CERTIFICATE XeikaCertificate;         // 0x37       0x0B70
	unsigned char  KeyVaultSignature[0x100];             // 0x44       0x1DF8
	unsigned char  CardeaCertificate[0x2108];            // 0x38       0x1EF8
} KEY_VAULT, *PKEY_VAULT;                                   //0x4000
C_ASSERT(sizeof(KEY_VAULT) == 0x4000);


#pragma pack()

typedef struct _XDASHLAUNCHDATA {
	DWORD dwVersion; // 0x0 sz:0x4
	DWORD dwCommand; // 0x4 sz:0x4
	DWORD dwUserIndex; // 0x8 sz:0x4
	BYTE Reserved[0x3F0]; // 0xC sz:0x3F0
} XDASHLAUNCHDATA, *PXDASHLAUNCHDATA; // size 1020
C_ASSERT(sizeof(XDASHLAUNCHDATA) == 0x3FC);

typedef struct _UNICODE_STRING {
	unsigned short Length;
	unsigned short MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _STRING
{
	short Length;
	short MaximumLength;
	char*  Buffer;
} STRING, *PSTRING;

typedef PSTRING			POBJECT_STRING;
typedef PSTRING			PANSI_STRING;
typedef CONST CHAR*		PCSZ;

typedef STRING			ANSI_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;  // 0x0 sz:0x8
	LIST_ENTRY InClosureOrderLinks;  // 0x8 sz:0x8
	LIST_ENTRY InInitializationOrderLinks; // 0x10 sz:0x8
	PVOID NtHeadersBase; // 0x18 sz:0x4
	PVOID ImageBase; // 0x1C sz:0x4
	unsigned int SizeOfNtImage; // 0x20 sz:0x4
	UNICODE_STRING FullDllName; // 0x24 sz:0x8
	UNICODE_STRING BaseDllName; // 0x2C sz:0x8
	unsigned int Flags; // 0x34 sz:0x4
	unsigned int SizeOfFullImage; // 0x38 sz:0x4
	PVOID EntryPoint; // 0x3C sz:0x4
	WORD LoadCount; // 0x40 sz:0x2
	WORD ModuleIndex; // 0x42 sz:0x2
	PVOID DllBaseOriginal; // 0x44 sz:0x4
	unsigned int CheckSum; // 0x48 sz:0x4
	unsigned int ModuleLoadFlags; // 0x4C sz:0x4
	unsigned int TimeDateStamp; // 0x50 sz:0x4
	PVOID LoadedImports; // 0x54 sz:0x4
	PVOID XexHeaderBase; // 0x58 sz:0x4
	union {
		STRING LoadFileName; // 0x5C sz:0x8
		struct {
			PVOID ClosureRoot; // 0x5C sz:0x4 LDR_DATA_TABLE_ENTRY
			PVOID TraversalParent; // 0x60 sz:0x4 LDR_DATA_TABLE_ENTRY
		} asEntry;
	} inf;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY; // size 100
C_ASSERT(sizeof(LDR_DATA_TABLE_ENTRY) == 0x64);


typedef struct _XEX_IMPORT_DESCRIPTOR {
	unsigned int Size; // 0x0 sz:0x4
	unsigned int NameTableSize; // 0x4 sz:0x4
	unsigned int ModuleCount; // 0x8 sz:0x4
					   // nametable is here of nametable size
					   // followed by modulecount number of xex import tables
} XEX_IMPORT_DESCRIPTOR, *PXEX_IMPORT_DESCRIPTOR; // size 12
C_ASSERT(sizeof(XEX_IMPORT_DESCRIPTOR) == 0xC);

typedef struct _HV_IMAGE_IMPORT_TABLE {
	BYTE NextImportDigest[0x14]; // 0x0 sz:0x14
	unsigned int ModuleNumber; // 0x14 sz:0x4
	unsigned int Version[2]; // 0x18 sz:0x8
	BYTE Unused; // 0x20 sz:0x1
	BYTE ModuleIndex; // 0x21 sz:0x1
	WORD ImportCount; // 0x22 sz:0x2
} HV_IMAGE_IMPORT_TABLE, *PHV_IMAGE_IMPORT_TABLE; // size 36
C_ASSERT(sizeof(HV_IMAGE_IMPORT_TABLE) == 0x24);

typedef struct _XEX_IMPORT_TABLE_ORG {
	unsigned int TableSize; // 0x0 sz:0x4
	HV_IMAGE_IMPORT_TABLE ImportTable; // 0x4 sz:0x24
} XEX_IMPORT_TABLE_ORG, *PXEX_IMPORT_TABLE_ORG; // size 40
C_ASSERT(sizeof(XEX_IMPORT_TABLE_ORG) == 0x28);

typedef struct _DETOUR_XEX_IMPORT_DESCRIPTOR {
	DWORD Size;
	DWORD NameTableSize;
	DWORD ModuleCount;
} DETOUR_XEX_IMPORT_DESCRIPTOR, *PDETOUR_XEX_IMPORT_DESCRIPTOR;

typedef struct _XBOX_HARDWARE_INFO {
	DWORD Flags;
	unsigned char NumberOfProcessors;
	unsigned char PCIBridgeRevisionID;
	unsigned char Reserved[6];
	unsigned short BldrMagic;
	unsigned short BldrFlags;
} XBOX_HARDWARE_INFO, *PXBOX_HARDWARE_INFO;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	} st;
	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _XBOX_KRNL_VERSION {
	WORD Major; // for 360 this is always 2
	WORD Minor; // usually 0
	WORD Build; // current version, for example 9199
	WORD Qfe;

} XBOX_KRNL_VERSION, *PXBOX_KRNL_VERSION;

typedef VOID(NTAPI *PIO_APC_ROUTINE) (
	IN PVOID ApcContext,
	IN PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG Reserved
	);

typedef enum _FSINFOCLASS {
	FileFsVolumeInformation = 0x1,
	FileFsLabelInformation = 0x2,
	FileFsSizeInformation = 0x3,
	FileFsDeviceInformation = 0x4,
	FileFsAttributeInformation = 0x5,
	FileFsControlInformation = 0x6,
	FileFsFullSizeInformation = 0x7,
	FileFsObjectIdInformation = 0x8,
	FileFsMaximumInformation = 0x9,
} FSINFOCLASS;

typedef struct _OBJECT_ATTRIBUTES {
	HANDLE RootDirectory;
	POBJECT_STRING ObjectName;
	ULONG Attributes;

} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;


typedef enum
{
	XNCALLER_INVALID = 0x0,
	XNCALLER_TITLE = 0x1,
	XNCALLER_SYSAPP = 0x2,
	XNCALLER_XBDM = 0x3,
	XNCALLER_TEST = 0x4,
	NUM_XNCALLER_TYPES = 0x4,

} XNCALLER_TYPE;



enum { // category enumerator
	   //XCONFIG_CATEGORY_TYPES
	XCONFIG_STATIC_CATEGORY = 0x0,					//_XCONFIG_STATIC_SETTINGS
	XCONFIG_STATISTIC_CATEGORY = 0x1,				//_XCONFIG_STATISTIC_SETTINGS
	XCONFIG_SECURED_CATEGORY = 0x2,					//_XCONFIG_SECURED_SETTINGS
	XCONFIG_USER_CATEGORY = 0x3,					//_XCONFIG_USER_SETTINGS
	XCONFIG_XNET_MACHINE_ACCOUNT_CATEGORY = 0x4,	//_XCONFIG_XNET_SETTINGS
	XCONFIG_XNET_PARAMETERS_CATEGORY = 0x5,			//_XCONFIG_XNET_SETTINGS
	XCONFIG_MEDIA_CENTER_CATEGORY = 0x6,			//_XCONFIG_MEDIA_CENTER_SETTINGS
	XCONFIG_CONSOLE_CATEGORY = 0x7, 				//_XCONFIG_CONSOLE_SETTINGS
	XCONFIG_DVD_CATEGORY = 0x8, 					//_XCONFIG_DVD_SETTINGS
	XCONFIG_IPTV_CATEGORY = 0x9, 					//_XCONFIG_IPTV_SETTINGS
	XCONFIG_SYSTEM_CATEGORY = 0xa,					//_XCONFIG_SYSTEM_SETTINGS
	XCONFIG_DEVKIT_CATEGORY = 0xb,					//_XCONFIG_DEVKIT_CATEGORY
	XCONFIG_CATEGORY_MAX
};


typedef enum {
	XNOTIFYUI_TYPE_FRIENDONLINE = 0,
	XNOTIFYUI_TYPE_GAMEINVITE = 1,
	XNOTIFYUI_TYPE_FRIENDREQUEST = 2,
	XNOTIFYUI_TYPE_GENERIC = 3, // mail icon
	XNOTIFYUI_TYPE_MULTIPENDING = 4,
	XNOTIFYUI_TYPE_PERSONALMESSAGE = 5,
	XNOTIFYUI_TYPE_SIGNEDOUT = 6,
	XNOTIFYUI_TYPE_SIGNEDIN = 7,
	XNOTIFYUI_TYPE_SIGNEDINLIVE = 8,
	XNOTIFYUI_TYPE_SIGNEDINNEEDPASS = 9,
	XNOTIFYUI_TYPE_CHATREQUEST = 10,
	XNOTIFYUI_TYPE_CONNECTIONLOST = 11,
	XNOTIFYUI_TYPE_DOWNLOADCOMPLETE = 12,
	XNOTIFYUI_TYPE_SONGPLAYING = 13, // music icon
	XNOTIFYUI_TYPE_PREFERRED_REVIEW = 14, // happy face icon
	XNOTIFYUI_TYPE_AVOID_REVIEW = 15, // sad face icon
	XNOTIFYUI_TYPE_COMPLAINT = 16, // hammer icon
	XNOTIFYUI_TYPE_CHATCALLBACK = 17,
	XNOTIFYUI_TYPE_REMOVEDMU = 18,
	XNOTIFYUI_TYPE_REMOVEDGAMEPAD = 19,
	XNOTIFYUI_TYPE_CHATJOIN = 20,
	XNOTIFYUI_TYPE_CHATLEAVE = 21,
	XNOTIFYUI_TYPE_GAMEINVITESENT = 22,
	XNOTIFYUI_TYPE_CANCELPERSISTENT = 23,
	XNOTIFYUI_TYPE_CHATCALLBACKSENT = 24,
	XNOTIFYUI_TYPE_MULTIFRIENDONLINE = 25,
	XNOTIFYUI_TYPE_ONEFRIENDONLINE = 26,
	XNOTIFYUI_TYPE_ACHIEVEMENT = 27,
	XNOTIFYUI_TYPE_HYBRIDDISC = 28,
	XNOTIFYUI_TYPE_MAILBOX = 29, // mailbox icon
								 // missing a few
								 XNOTIFYUI_TYPE_EXCLAIM = 34, // exclamation mark icon
								 XNOTIFYUI_TYPE_GARBAGE = 68, // garbage can icon
} XNOTIFYQUEUEUI_TYPE;

enum {
	XCONFIG_SECURED_DATA = 0x0,
	XCONFIG_SECURED_MAC_ADDRESS = 0x1,
	XCONFIG_SECURED_AV_REGION = 0x2,
	XCONFIG_SECURED_GAME_REGION = 0x3,
	XCONFIG_SECURED_DVD_REGION = 0x4,
	XCONFIG_SECURED_RESET_KEY = 0x5,
	XCONFIG_SECURED_SYSTEM_FLAGS = 0x6,
	XCONFIG_SECURED_POWER_MODE = 0x7,
	XCONFIG_SECURED_ONLINE_NETWORK_ID = 0x8,
	XCONFIG_SECURED_POWER_VCS_CONTROL = 0x9,
	XCONFIG_SECURED_ENTRIES_MAX
};

typedef enum _XAM_CACHE_FILE_TYPE {
	XAM_CACHE_SYSTEM_UPDATE = 0xC,
	XAM_CACHE_GAMER_TILE = 0x3,
	XAM_CACHE_GAME_TILE = 0x1,
	XAM_CACHE_NUI_HIVE_SETTING = 0x1A,
	XAM_CACHE_ACHIEVEMENT_TILE = 0x2,
	XAM_CACHE_CUSTOM_GAMER_TILE = 0x5,
	XAM_CACHE_NUI_SESSION = 0x17,
	XAM_CACHE_XSTS_TOKEN = 0x1E,
	XAM_CACHE_GAMER_TAG = 0x10,
	XAM_CACHE_GAMER_TILE_SMALL = 0x4,
	XAM_CACHE_XLFS_UPLOADER = 0x1B,
	XAM_CACHE_PROFILE_SETTINGS = 0x13,
	XAM_CACHE_DASH_CACHESEEDFILE = 0x1C,
	XAM_CACHE_FRIEND_MUTE_LIST = 0x7,
	XAM_CACHE_NUI_BIOMETRIC = 0x18,
	XAM_CACHE_TITLE_NAMES = 0x9,
	XAM_CACHE_MESSENGER_BUDDIES = 0x11,
	XAM_CACHE_QOS_HISTORY = 0x12,
	XAM_CACHE_GAME_INVITE = 0xF,
	XAM_CACHE_TITLE_UPDATE = 0xB,
	XAM_CACHE_ZEST_AUTHENTICATION = 0x1D,
	XAM_CACHE_VALIDATE_CERT = 0x16,
	XAM_CACHE_TICKETS = 0x8,
	XAM_CACHE_ALL = 0x0,
	XAM_CACHE_SPA_FILE = 0xE,
	XAM_CACHE_NUI_TROUBLESHOOTER = 0x19,
	XAM_CACHE_LIVEID_DEVICE = 0x1F,
	XAM_CACHE_CERT_STORAGE = 0x15,
	XAM_CACHE_CUSTOM_GAMER_TILE_SMALL = 0x6,
	XAM_CACHE_AVATAR_GAMER_TILE = 0x14,
	XAM_CACHE_RECENT_PLAYERS = 0xA,
	XAM_CACHE_DASHBOARD_APP = 0xD
} XAM_CACHE_FILE_TYPE;

#define XBDMAPI

#define DMHRAPI XBDMAPI HRESULT __stdcall

typedef ULONG(__stdcall *PDM_ENTRYPROC)(ULONG, ULONG, ULONG);

typedef struct _DM_CMDCONT *PDM_CMDCONT;

typedef HRESULT(__stdcall *PDM_CMDCONTPROC)(PDM_CMDCONT pdmcc, LPSTR szResponse,
	DWORD cchResponse);

typedef struct _DM_CMDCONT 
{
	PDM_CMDCONTPROC HandlingFunction;
	DWORD DataSize;
	PVOID Buffer;
	DWORD BufferSize;
	PVOID CustomData;
	DWORD BytesRemaining;
} DM_CMDCONT;

extern "C"
{

	NTSYSAPI
		EXPORTNUM(607)
		DWORD
		NTAPI
		XeKeysExecute(
			IN		PBYTE pBuffer, // must be 0x80 byte aligned
			IN		DWORD size, // code block must be > 0x120 and no larger than 0x10000
			IN OUT	PBYTE salt, // args depend on the code block sent
			IN OUT	PXBOX_KRNL_VERSION krnlbuild,
			IN OUT	PDWORD r7,
			IN OUT	PDWORD r8
		);
	

	DWORD XeKeysGetConsoleID(PBYTE databuffer, unsigned char* szBuffer);

	int NetDll_XNetXnAddrToMachineId(XNCALLER_TYPE xnc, const XNADDR * pxnaddr, ULONGLONG * pqwMachineId);

	DWORD NetDll_XNetGetTitleXnAddr(XNCALLER_TYPE xnc, XNADDR * pxna);

	NTSTATUS NtQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileSystemInformation, DWORD Length, FSINFOCLASS FileSystemInformationClass);

	NTSTATUS NtOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, DWORD ShareAccess, DWORD OpenOptions);

	NTSTATUS NtClose(HANDLE Handle);

	NTSTATUS XexGetModuleHandle(PSZ moduleName, PHANDLE hand);

	extern PXBOX_KRNL_VERSION XboxKrnlVersion;;

	BOOL XamCacheReset(XAM_CACHE_FILE_TYPE FileType);

	int NetDll_ioctlsocket(XNCALLER_TYPE xnc, SOCKET s, long cmd, u_long FAR * argp);

	int NetDll_WSAStartupEx(XNCALLER_TYPE xnc, WORD wVersionRequested, LPWSADATA wsad, DWORD versionReq);

	int NetDll_XNetStartup(XNCALLER_TYPE xnc, XNetStartupParams* xnsp);

	int NetDll_XNetDnsLookup(XNCALLER_TYPE xnc,  const char * pszHost,  WSAEVENT hEvent, XNDNS ** ppxndns);
	int NetDll_XNetDnsRelease(XNCALLER_TYPE xnc,  XNDNS * pxndns);

	SOCKET NetDll_accept(XNCALLER_TYPE xnc, SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen);

		WSAEVENT
		NetDll_WSACreateEvent(
			void
		);

		BOOL
		NetDll_WSACloseEvent( WSAEVENT hEvent

		);
	int NetDll_bind(XNCALLER_TYPE xnc, SOCKET s, const struct sockaddr FAR *name, int namelen);

	int NetDll_connect(XNCALLER_TYPE xnc, SOCKET s, const struct sockaddr FAR *name, int namelen);

	int NetDll_closesocket(XNCALLER_TYPE xnc, SOCKET s);

	int NetDll_getpeername(XNCALLER_TYPE xnc, SOCKET s, struct sockaddr FAR *name, int FAR *namelen);

	int NetDll_getsockname(XNCALLER_TYPE xnc, SOCKET s, struct sockaddr FAR *name, int FAR *namelen);

	int NetDll_getsockopt(XNCALLER_TYPE xnc, SOCKET s, int level, int optname, char FAR *optval, int FAR *optlen);

	int NetDll_listen(XNCALLER_TYPE xnc, SOCKET s, int backlog);

	int NetDll_recv(XNCALLER_TYPE xnc, SOCKET s, char FAR *buf, int len, int flags);

	int NetDll_recvfrom(XNCALLER_TYPE xnc, SOCKET s, char FAR *buf, int len, int flags, struct sockaddr FAR *from, int FAR *fromlen);

	int NetDll_select(XNCALLER_TYPE xnc, int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout);

	int NetDll_send(XNCALLER_TYPE xnc, SOCKET s, const char FAR *buf, int len, int flags);

	int NetDll_sendto(XNCALLER_TYPE xnc, SOCKET s, const char FAR *buf, int len, int flags, const struct sockaddr FAR *to, int tolen);

	int NetDll_setsockopt(XNCALLER_TYPE xnc, SOCKET s, int level, int optname, char FAR *optval, int optlen);

	int NetDll_shutdown(XNCALLER_TYPE xnc, SOCKET s, int how);

	SOCKET NetDll_socket(XNCALLER_TYPE xnc, int af, int type, int protocol);

	void NetDll_XnpNoteSystemTime(XNCALLER_TYPE xnc);

	BOOL XexCheckExecutablePrivilege(DWORD priviledge);

	NTSTATUS XexLoadImage(LPCSTR szXexName, DWORD dwModuleTypeFlags, DWORD dwMinimumVersion, PHANDLE pHandle);

	NTSTATUS XexLoadExecutable(PCHAR szXexName, PHANDLE pHandle, DWORD dwModuleTypeFlags, DWORD dwMinimumVersion);

	NTSTATUS NtQueueApcThread(HANDLE ThreadHandle, PIO_APC_ROUTINE ApcRoutine, PVOID ApcRoutineContext, PIO_STATUS_BLOCK ApcStatusBlock, DWORD ApcReserved);

	extern PLDR_DATA_TABLE_ENTRY* XexExecutableModuleHandle;

	VOID InitializeObjectAttributes( POBJECT_ATTRIBUTES InitializedAttributes, PANSI_STRING ObjectName, ULONG Attributes, HANDLE RootDirectory);

	NTSTATUS WINAPI NtDeviceIoControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);

	void RtlInitAnsiString(PANSI_STRING DestinationString, PCSZ  SourceString);

	HRESULT ObCreateSymbolicLink(PSTRING SymbolicLinkName, PSTRING DeviceName);

	extern PXBOX_HARDWARE_INFO XboxHardwareInfo;

	PVOID  XexPcToFileHeader(PVOID address, PLDR_DATA_TABLE_ENTRY* ldatOut);

	DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, LPDWORD lpThreadId, PVOID apiThreadStartup, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlagsMod);

	void XapiThreadStartup(void(*StartRoutine)(void *), void* StartContext, unsigned int dwExitCode);

	DWORD  XexLoadImageFromMemory(VOID* Image, DWORD ImageSize, const CHAR* ImageName, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle);

	unsigned int XexGetProcedureAddress(HANDLE    Handle, unsigned int    Ordinal, void*     OutAddress);

	void* RtlImageXexHeaderField(void* XexHeaderBase, unsigned int ImageField);

	void DbgPrint(const char* s, ...);

	unsigned int XamGetCurrentTitleId();

	void KeSweepIcacheRange(void* Address, unsigned int cbBytes);

	void* MmGetPhysicalAddress(void* Address);

	bool MmIsAddressValid(void* Address);

	unsigned char KeGetCurrentProcessType(void);

	void HalSendSMCMessage(void* pCommandBuffer, void* pRecvBuffer);

	NTSTATUS ExGetXConfigSetting(unsigned short dwCategory, unsigned short dwSetting, void* pBuffer, unsigned short cbBuffer, unsigned short* szSetting);

	NTSTATUS  ExSetXConfigSetting(WORD dwCategory, WORD dwSetting, PVOID pBuffer, WORD szSetting);

	NTSTATUS XamGetExecutionId(PXEX_EXECUTION_ID* xid);

	void HalReturnToFirmware(FIRMWARE_REENTRY powerDownMode);
}

//Thanks to Nathan LeRoux 

#define accept(s, addr, addrlen)							NetDll_accept(XNCALLER_SYSAPP, s, addr, addrlen)
#define bind(s, name, namelen)								NetDll_bind(XNCALLER_SYSAPP, s, name, namelen)
#define connect(s, name, namelen)							NetDll_connect(XNCALLER_SYSAPP, s, name, namelen)
#define closesocket(s)										NetDll_closesocket(XNCALLER_SYSAPP, s)
#define getpeername(s, name, namelen)						NetDll_getpeername(XNCALLER_SYSAPP, s, name, namelen)
#define getsockname(s, name, namelen)						NetDll_getsockname(XNCALLER_SYSAPP, s, name, namelen)
#define listen(s, backlog)									NetDll_listen(XNCALLER_SYSAPP, s, backlog)
#define recv(s, buf, len, flags)							NetDll_recv(XNCALLER_SYSAPP, s, buf, len, flags)
#define recvfrom(s, buf, len, flags, from, fromlen)			NetDll_recvfrom(XNCALLER_SYSAPP, s, buf, len, flags, from, fromlen)
#define select(nfds, readfds, writefds, exceptfds, timeout)	NetDll_select(XNCALLER_SYSAPP, nfds, readfds, writefds, exceptfds, timeout)
#define send(s, buf, len, flags)							NetDll_send(XNCALLER_SYSAPP, s, buf, len, flags)
#define sendto(s, buf, len, flags, to, tolen)				NetDll_sendto(XNCALLER_SYSAPP, s, buf, len, flags, to, tolen)
#define setsockopt(s, level, optname, optval, optlen)		NetDll_setsockopt(XNCALLER_SYSAPP, s, level, optname, optval, optlen)
#define shutdown(s, how)									NetDll_shutdown(XNCALLER_SYSAPP, s, how)
#define socket(af, type, protocol)							NetDll_socket(XNCALLER_SYSAPP, af, type, protocol)
#define XnpNoteSystemTime()									NetDll_XnpNoteSystemTime(XNCALLER_SYSAPP)
#define XNetStartup(xnsp)									NetDll_XNetStartup(XNCALLER_SYSAPP, xnsp)
#define WSAStartup(x, y)									NetDll_WSAStartupEx(XNCALLER_SYSAPP, x, y, 2)
#define ioctlsocket(s, c, a)								NetDll_ioctlsocket(XNCALLER_SYSAPP, s, c, a)
#define WSACloseEvent						NetDll_WSACloseEvent
#define WSACreateEvent						NetDll_WSACreateEvent

#define xbOnline_BoxKey1 0xEF285E1E83EE706F
#define xbOnline_BoxKey2 0x8C3A7AC55499DC0B
#define xbOnline_BoxKey3 0x152909959E699605
#define xbOnline_BoxKey4 0x5B6A06359404B2F5

struct unkStruct1
{
	int unk1;
	int unk2;

};

struct unkStruct2
{
	int unk1;
	int unk2;
};


struct unkStruct3
{
	long long unk1;		//0x70
	int unk2;			//0x78
	char* Image;		//0x7C
	int ImageSize;		//0x80
};

class MemoryBuffer
{

public:
	MemoryBuffer(DWORD dwSize = 512) {
		m_pBuffer = NULL;
		m_dwDataLength = 0;
		m_dwBufferSize = 0;

		if ((dwSize < UINT_MAX) && (dwSize != 0)) {
			m_pBuffer = (BYTE*)malloc(dwSize + 1);    // one more char, in case when using string funcions
			if (m_pBuffer) {
				m_dwBufferSize = dwSize;
				m_pBuffer[0] = 0;
			}
		}
	};

	~MemoryBuffer() {
		if (m_pBuffer) free(m_pBuffer);

		m_pBuffer = NULL;
		m_dwDataLength = 0;
		m_dwBufferSize = 0;
	};

	// Add chunk of memory to buffer
	BOOL Add(CONST PVOID p, DWORD dwSize) {
		if (CheckSize(dwSize)) {
			memcpy(m_pBuffer + m_dwDataLength, p, dwSize);
			m_dwDataLength += dwSize;
			*(m_pBuffer + m_dwDataLength) = 0;    // fill end zero
			return TRUE;
		}
		else {
			return FALSE;
		}
	};

	// Get the data in buffer
	PBYTE GetData() CONST {
		return m_pBuffer;
	};

	// Get the length of data in buffer
	DWORD GetDataLength() CONST {
		return m_dwDataLength;
	};

	// Rewind the data pointer to the begining
	VOID Rewind() {
		m_dwDataLength = 0; m_pBuffer[0] = 0;
	};

	// Automatically adjust increase buffer size if necessary
	BOOL CheckSize(DWORD dwSize) {
		if (m_dwBufferSize >= (m_dwDataLength + dwSize)) {
			return TRUE;    // Enough space
		}
		else {
			// Try to double it
			DWORD dwNewSize = max(m_dwDataLength + dwSize, m_dwBufferSize * 2);
			BYTE* pNewBuffer = (PUCHAR)realloc(m_pBuffer, dwNewSize + 1);
			if (pNewBuffer) {
				m_pBuffer = pNewBuffer;
				m_dwBufferSize = dwNewSize;
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}

private:
	PBYTE m_pBuffer;
	DWORD m_dwDataLength;
	DWORD m_dwBufferSize;
};

#if defined(DEVKIT)
#define _XexExecutableModuleHandle 0x802080D4
#else
#define _XexExecutableModuleHandle 0x801A5DD4
#endif

#define NAME_CPUKEYB "cpukey.bin"
#define NAME_CPUKEYT "cpukey.txt"
#define NAME_KEYVAULT "kv.bin"

#define NAME_HDD "\\Device\\Harddisk0\\Partition1"
#define NAME_USB "\\Device\\Mass0"
#define NAME_MOUNT "xbOnline:\\"
#define MODULE_KERNEL "xboxkrnl.exe"
#define MODULE_XAM "xam.xex"

#define OI_NINJA "Oi Leave the thread fix alone fgts"

#define PATH_CPUKEYB NAME_MOUNT NAME_CPUKEYB
#define PATH_KEYVAULT NAME_MOUNT NAME_KEYVAULT

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

void SetLiveBlock(bool enable);

extern unsigned char PublicKey[144];

extern unsigned char PrivateKey[464];

extern int(*XexUnloadImage)(HANDLE);

extern const unsigned char RetailKey[0x10];

extern const unsigned char MasterKey[272];
extern bool FCRT;

extern unsigned char Spoofed_CPUKey[16];
extern unsigned char CPUKeyDigest[0x14];
extern unsigned char KVDigest[0x14];
extern unsigned char MacAddress[6];

extern int kvSharedNumber;
extern int CurrentPath;

extern unsigned int XKEUpdateSequence;

extern KEY_VAULT KeyVault;

extern bool
xb_custom_xui, xb_custom_notify, xb_custom_time, xb_redeemhook, xb_cheats_cod4, xb_cheats_waw, xb_cheats_mw2,
xb_cheats_bo1, xb_cheats_mw3, xb_cheats_bo2, xb_cheats_ghosts, xb_cheats_aw, xb_cheats_bf4, xb_bypass_cod4, xb_bypass_waw,
xb_cheats_mw2_onhost, xb_bypass_mw2, xb_bypass_bo1, xb_bypass_mw3, xb_bypass_bo2, xb_bypass_ghosts, xb_bypass_aw, xb_cheats_mw3_onhost, xb_cheats_csgo, xb_cheats_tf2;

BOOL FileExists(LPCSTR lpFileName);

int XexLoadImageFromMemory_XamHook(VOID* Image, DWORD ImageSize, const CHAR* ImageName, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle);
bool xbVerifyPayload(BYTE* _payload, DWORD payloadLength);
bool DriveOverRide();
void LoadINI();
void SetIniBoolValue(char* section, char* item, char* logic);
void SaveIni();
bool OpenedTray();
void RebootConsole();
HRESULT Process_KV();
HRESULT Mount_Drive();
bool VerifyKeyVault();
void xbKeyvaultShareSanityCheck();
void xbIsAdvancedKeySharingEnabled(bool option);
bool xbIsKeyFilePresent();
BOOL xbSharedConsoleCheck(bool FirstInitialization);
void xbGetSharedConsoleNumber();
HRESULT SetMacAddress();
unsigned int ReverseInt(unsigned int val);
void CreateXboxThread(void* ptr, void* p);
HRESULT ProcessKeyVault();
void DoXEXHash(BYTE* DigestBuffer, void* Packet);
void XNotify(wchar_t* NotifyText);
HRESULT SetKeyVault(char* FilePath);
PWCHAR charToWChar(PCHAR Text, ...);
void XNotifyThread(wchar_t* NotifyText);
HRESULT SetMemory(PVOID Destination, PVOID Source, DWORD Length);
HRESULT CreateSymbolicLink(PCHAR szDrive, PCHAR szDeviceName, BOOL System);
PWCHAR LinkWChar(PWCHAR Text, ...);
std::string SplitLastOf(PWCHAR Text, PCHAR FindLastOf);
PWCHAR CharToWChar(const char* Text);
BOOL DoesContainText(PWCHAR str, PWCHAR suffix);
void RC4(BYTE* content, int content_length, BYTE* key, int key_length, unsigned char Byte);
void CryptData(unsigned char* in, int inLength, unsigned char** out, int* outLength);
void DecryptData(unsigned char* in, int inLength, unsigned char* out);
bool DownloadFile(const char* Server, const char* FileName, unsigned char** Out, int* length);
unsigned int ApplyPatches(void* buffer);
HRESULT ProcessCPUKeyBin(char* FilePath);
std::string hexStr(unsigned char *data, int len);
void GetBootedPath(HMODULE Handle, char* FinalPath);
HRESULT SetKeyVault(unsigned char* pKeyVault);
BOOL FGetDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw);
BOOL FGetNamedDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw, LPSTR szResp);
void * AlignedMemorySearch(char * sectionName, void * scanData, int dataLength);
void xbCreateBoxKey(long long xbBoxRequestID, unsigned char* out);
BOOL GetSectionInfo(CONST PCHAR SectionName, PDWORD Address, PDWORD Length);
void GetFilePathFromHandle(HMODULE Handle, char* FilePath);
bool CReadFile(const char* FileName, MemoryBuffer &pBuffer);
DWORD MakeBranch(DWORD Address, DWORD Destination, BOOL Linked);
FARPROC ResolveFunction(char* ModuleName, unsigned int Ordinal);
FARPROC ResolveFunction(char* ModuleName, unsigned int Ordinal);
DWORD GetXamExportFromBaseAddress(DWORD dwModuleBaseAddr, int Ordinal);
void PatchInJump_2(unsigned int Address, void* Destination, bool Linked);
bool CWriteFile(const char* FilePath, const void* Data, unsigned int Size);
DWORD NetDll_XnpLogonSetChallengeResponse(SOCKET s, PBYTE ChallengeBuffer, size_t BufferSize);
DWORD PatchModuleImport(PCHAR Module, PCHAR ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
bool XeKeysPkcs1Verify(const unsigned char* pbHash, const unsigned char* pbSig, XECRYPT_RSA* pRsa);
unsigned int ResolveIntrinsicModule(HMODULE Module, unsigned int Export, unsigned int off1, unsigned int off2);
DWORD xbRedeem(unsigned char* Session, unsigned char* CPUKey, unsigned char* Geneology, unsigned char* XEX_Hash, int type);
DWORD PatchModuleImport_F(PLDR_DATA_TABLE_ENTRY Module, PCHAR ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
int XexLoadImageFromMemory_(VOID* Image, DWORD ImageSize, const CHAR* ImageName, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle);
void ShowMessageBoxUI(LPCWSTR title, LPCWSTR String);
int ResolveFunction_0(HMODULE hHandle, unsigned int dwOrdinal);
bool GetHandle(void* pvAddress, PHANDLE hModule);
VOID GetMachineAccountKey();
#define XAPO_ALLOC_ATTRIBUTES MAKE_XALLOC_ATTRIBUTES (      \
            0,                           /* ObjectType */           \
            FALSE,                       /* HeapTracksAttributes */ \
            TRUE,                       /* MustSucceed */          \
            FALSE,                       /* FixedSize */            \
            eXALLOCAllocatorId_XBOXKERNEL,  /* AllocatorId */          \
            XALLOC_ALIGNMENT_DEFAULT,    /* Alignment */            \
            XALLOC_MEMPROTECT_WRITECOMBINE, /* MemoryProtect */        \
            TRUE,                       /* ZeroInitialize */       \
            XALLOC_MEMTYPE_HEAP          /* MemoryType */           \
)

extern "C"
{

	extern PXBOX_HARDWARE_INFO XboxHardwareInfo;
}

void Custom_Printf(const char* format, ...);
void DEVKIT_Printf(const char* format, ...);

#define printf Custom_Printf
#define DEVKIT_printf DEVKIT_Printf

extern BYTE Dumped_HV[0x40000];
bool GetIniBoolValue(char* section, char* item);


void NetPrintf(const char* format, ...);
void SendOverNetWork(const char* Message);
void getKeyvaultLife();
static wchar_t* charToWChar_Com(const char* text);