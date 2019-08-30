#include "main.h"

typedef int( *XeKeysConsolePrivateKeySignStub )( PBYTE Digest, PBYTE XE_CONSOLE_CERTIFICATE );
XeKeysConsolePrivateKeySignStub XeKeysConsolePrivateKeySignOriginal;
typedef int( *XeKeysGetConsoleCertificateStub )( unsigned char *cert );
XeKeysGetConsoleCertificateStub XeKeysGetConsoleCertificateOriginal;

IoCreateFile_t IoCreateFileOriginal;
Detour IoCreateFileDetour;

CRITICAL_SECTION KvProtectionSection, GettingKvData, DoCleanUp;

int( *XeKeysGetKeys )( unsigned int Key, PVOID KeyBuffer, PDWORD keyLength ) = ( int( *)( unsigned int Key, PVOID KeyBuffer, PDWORD keyLength ) )0x80108550;
int( *XeKeysGetConsoleCertificate )( unsigned char* r3 ) = ( int( *)( unsigned char* r3 ) )0x80108618;

CRYPTOKV CKV = { 0 };
XE_CONSOLE_CERTIFICATE CERT;

int WantKvLess = 0;
int IsKvAssigned = 0;
int IsKvLessModeAvalible = 0;

bool isCleanUpDone = false;
bool hasGottenKvData = false;

void PerformeOneTimeCleanUp( )
{
	EnterCriticalSection( &DoCleanUp );
	if ( !isCleanUpDone ) {
		isCleanUpDone = true;
		DoSysCleanup( );
	}
	LeaveCriticalSection( &DoCleanUp );
}

void GetKvData( int helloworld )
{
	EnterCriticalSection( &GettingKvData );

	if ( !hasGottenKvData )
	{
		hasGottenKvData = true;

		unsigned char CPUKey[ 0x10 ] = { 0 };
		unsigned char Geneology[ 0x10 ] = { 0 };

		Tramps->CallFunction( GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false );
		Tramps->CallFunction( xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false );

		Client* Connection = new Client( CPUKey, Geneology, XEX_Hash );

		if ( Connection->GetKvData( g_Session, CPUKey, (unsigned char*)0, (unsigned char*)0, &CKV, &IsKvAssigned, &IsKvLessModeAvalible, helloworld ) ) {

			memcpy( &CERT, CKV.XE_CONSOLE_CERTIFICATE, 0x1A8 );


			*(short*)( 0x81733D3C + 0x2 ) = ( ( (int)&CERT ) & 0xFFFF0000 ) >> 16;
			*(short*)( 0x81733D50 + 0x2 ) = ( (int)&CERT ) & 0x0000FFFF;

			//Write Our Server Console ID
			*(short*)( 0x818EDF14 + 0x2 ) = ( ( (int)&CERT.ConsoleId.abData ) & 0xFFFF0000 ) >> 16;
			*(short*)( 0x818EDF1C + 0x2 ) = ( (int)&CERT.ConsoleId.abData ) & 0x0000FFFF;

			//memset((PVOID)0x8E03A000, 0, 0x1A8);
			//memset((PVOID)0x8E038020, 0, 5);
			//memcpy((PVOID)0x8E03A000, CKV.XE_CONSOLE_CERTIFICATE, 0x1A8);
			//memcpy((PVOID)0x8E038020, (CKV.XE_CONSOLE_CERTIFICATE + 0x2), 5);



#if defined(DEVKIT)
			QWORD kvAddress = HvPeekQWORD( 0x00000002000162E0 );
#else
			QWORD kvAddress = HvPeekQWORD( 0x0000000200016240 );
#endif

			HvPokeBytes( kvAddress + 0x158, CKV.DEVICE_KEYSET, 0x140 );

			//CWriteFile("xbOnline:\\MyKeySet.bin", CKV.DEVICE_KEYSET, 0x140);

			SetMacAddress_NoKeyvault( CERT.ConsoleId.asBits.MacIndex3, CERT.ConsoleId.asBits.MacIndex4, CERT.ConsoleId.asBits.MacIndex5 );

			XeCryptSha( (BYTE*)0x8E038014, 0x3EC, NULL, NULL, NULL, NULL, (BYTE*)0x8E038000, XECRYPT_SHA_DIGEST_SIZE );

			XamCacheReset( XAM_CACHE_TICKETS );
		}
		delete Connection;
	}
	LeaveCriticalSection( &GettingKvData );
}

DWORD InitializeCryptoKV( )
{
	*(int*)( 0x80108618 ) = 0xed8802a6;
	*(int*)( 0x80109208 ) = 0xed8802a6;
	return 0;
}

DWORD XeKeysGetConsoleCertificate_Hook( unsigned char *cert )
{

	memcpy( cert, CKV.XE_CONSOLE_CERTIFICATE, 0x1A8 );
	return 0;
}

int XeKeysConsolePrivateKeySign_Hook( PBYTE Digest, PBYTE XE_CONSOLE_CERTIFICATE )
{
	BYTE Format[ 0x80 ] = { 0 };
	XeCryptBnDwLePkcs1Format( Digest, 0, Format, 0x80 );

	unsigned char CPUKey[ 0x10 ] = { 0 };
	unsigned char Geneology[ 0x10 ] = { 0 };

	Tramps->CallFunction( GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false );
	Tramps->CallFunction( xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false );

	Client* Connection = new Client( CPUKey, Geneology, XEX_Hash );

	if ( Connection->GetKvData( g_Session, CPUKey, (unsigned char*)Format, (unsigned char*)Format, NULL, &IsKvAssigned, &IsKvLessModeAvalible, 5 ) ) {

	}
	delete Connection;

	XeCryptBnQw_SwapDwQwLeBe( (QWORD*)Format, (QWORD*)( XE_CONSOLE_CERTIFICATE + 0x1A8 ), 0x10 );
	memcpy( XE_CONSOLE_CERTIFICATE, CKV.XE_CONSOLE_CERTIFICATE, 0x1A8 );
	return 0;
}


#pragma optimize( "", off )

int* result = NULL;
XOVERLAPPED g_xol = { 0 };
MESSAGEBOX_RESULT g_mb_result = { 0 };
LPCWSTR Buttons[ 2 ] = { L"Yes", L"No" };

unsigned int KvTimerCount = 0;

DWORD WINAPI KVProtectionThread( LPVOID )
{
	MESSAGEBOX_RESULT g_mb_result = { 0 };
	XOVERLAPPED g_xol = { 0 };
	LPCWSTR Buttons[ 2 ] = { L"No - Deny Request", L"Yes - Accept Request" };

	while ( XShowMessageBoxUI( XUSER_INDEX_ANY, L"XBONLINE SECURITY NOTICE", L"Something has tried to access and remotely download your Keyvault (KV).\n\nIf this was not intentionally done by you, a rogue plugin or tool may be attempting to steal your Keyvault.\n\nDo not accept unless you are intentionally trying to download it yourself using a tool on your network\n\n\nWould you like to allow this request?", 2, Buttons, 0, XMB_ERRORICON, &g_mb_result, &g_xol ) == ERROR_ACCESS_DENIED )
		Sleep( 500 );
	while ( !XHasOverlappedIoCompleted( &g_xol ) )
		Sleep( 500 );

	if ( g_mb_result.dwButtonPressed == 1 )
		return 1;

	return 2;
}

DWORD BoxResult = 0;

void DoChecksFunction( int StackPtr, char* _Path )
{
	char* Path = ( char* )*(int*)( (int)_Path );

	if ( !Path )
		return;

	std::string FilePath = Path;

	bool isXbdm = false, isGame = false;

	int LR_3 = *(int*)( StackPtr + 0x90 - 0x8 );

	int LR_1 = 0;
	if ( LR_3 == 0x8006DFE0 )
		LR_1 = *(int*)( StackPtr + 0x90 + 0x90 - 0x8 );

	int LR_2 = 0;
	if ( LR_3 == 0x8006CACC || LR_3 == 0x8006DFE0 )
		LR_2 = *(int*)( StackPtr + 0x90 + 0x70 - 0x8 );

	int LR_4 = 0;
	if ( LR_3 == 0x8006D8AC )
		LR_4 = *(int*)( StackPtr + 0x90 + 0xB0 + 0x0E0 - 0x8 );

	if ( ( LR_1 & 0xFFF00000 ) == 0x91000000 && LR_1 < 0x91030000 )
		isXbdm = true;

	if ( ( LR_2 & 0xFFF00000 ) == 0x91000000 && LR_2 < 0x91030000 )
		isXbdm = true;

	if ( ( LR_3 & 0xFFF00000 ) == 0x91000000 && LR_3 < 0x91030000 )
		isXbdm = true;

	if ( ( LR_4 & 0xFFF00000 ) == 0x91000000 && LR_4 < 0x91030000 )
		isXbdm = true;


	if ( ( LR_1 & 0xFF000000 ) == 0x82000000 )
		isGame = true;

	if ( ( LR_2 & 0xFF000000 ) == 0x82000000 )
		isGame = true;

	if ( ( LR_3 & 0xFF000000 ) == 0x82000000 )
		isGame = true;

	if ( ( LR_4 & 0xFF000000 ) == 0x82000000 )
		isGame = true;


	std::transform( FilePath.begin( ), FilePath.end( ), FilePath.begin( ), tolower );


	if ( !isXbdm && !isGame && ( FilePath.find( "kv.bin" ) != -1 ) && ( FilePath.find( "xbonline" ) == -1 ) )
		memcpy( &Path[ FilePath.find( "kv.bin" ) ], "dummy.", 7 );

	if ( isXbdm && ( FilePath.find( "kv.bin" ) != -1 && FilePath.find( "xbonline" ) == -1 ) )
	{
		EnterCriticalSection( &KvProtectionSection );

		int CurrentTicketCount = GetTickCount( );

		int MsSinceLastRequest = CurrentTicketCount - KvTimerCount;

		if ( MsSinceLastRequest < 5000 && MsSinceLastRequest > 0 )
		{
			goto DontAsk;
		}
		HANDLE hThread1 = 0; DWORD threadId1 = 0;
		ExCreateThread( &hThread1, 0x10000, &threadId1, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)KVProtectionThread, 0, 0x2 );
		XSetThreadProcessor( hThread1, 4 );
		ResumeThread( hThread1 );
		WaitForSingleObject( hThread1, INFINITE );
		GetExitCodeThread( hThread1, &BoxResult );
		CloseHandle( hThread1 );

	DontAsk:

		if ( BoxResult == 2 )
			strcpy( Path, "\\notkv.bin" );

		KvTimerCount = GetTickCount( );
		LeaveCriticalSection( &KvProtectionSection );
	}
}

NTSTATUS IoCreateFileHook( PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG Disposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength, int	CreateFileType, PVOID InternalParameters, ULONG Options )
{
	int CoolStackVar;
	__asm mr CoolStackVar, r1;


	if ( ObjectAttributes && ObjectAttributes->ObjectName )
	{

		DoChecksFunction( CoolStackVar, (char*)&ObjectAttributes->ObjectName->Buffer );
	}

	return IoCreateFileOriginal( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, Disposition, CreateOptions, EaBuffer, EaLength, CreateFileType, InternalParameters, Options );
}

//==================================================================


/*
Will get all the properties of this keyfile in a single buffer
*/

#pragma optimize( "", on ) 

