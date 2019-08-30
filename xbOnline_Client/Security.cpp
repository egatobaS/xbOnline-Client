#include "main.h"

PLIST_ENTRY PsLoadedModuleList = (PLIST_ENTRY)ResolveIntrinsicModule( GetModuleHandle( "xboxkrnl.exe" ), 412, 9, 11 );

Detour MmIsAddressValidDetour, MmDbgReadCheckDetour;

MmIsAddressValid_t MmIsAddressValidOriginal;
//XeKeyGetKeys_t XeKeysGetKeyOriginal;
MmDbgReadCheck_t MmDbgReadCheckOriginal;

PLIST_ENTRY OurModule = 0;
Detour DmWalkLoadedModulesExDetour;
DmWalkLoadedModulesExStub DmWalkLoadedModulesExOrginal;

void GetCPUKey( unsigned char* Out )
{
	unsigned char* Data = (unsigned char*)XPhysicalAlloc( 0x10, MAXULONG_PTR, NULL, PAGE_READWRITE );

	unsigned long long f1p1 = HVGetVersionsPeekQWORD( 0x8000020000020600 ) | HVGetVersionsPeekQWORD( 0x8000020000020800 );
	unsigned long long f1p2 = HVGetVersionsPeekQWORD( 0x8000020000020A00 ) | HVGetVersionsPeekQWORD( 0x8000020000020C00 );

	Tramps->CallFunction( memcpy_Function, (int)Out + 0, (int)&f1p1, 8, 0, false );
	Tramps->CallFunction( memcpy_Function, (int)Out + 8, (int)&f1p2, 8, 0, false );

	XPhysicalFree( Data );
}


BOOL MmIsAddressValidHook( unsigned int Address )
{
	if ( Address <= g_ModuleBaseAddress && Address >= ( g_ModuleBaseAddress + g_EntryTable.SizeOfNtImage ) )
		return FALSE;

	if ( ( Address & 0xFFF00000 ) == 0x90E00000 ) {

		return E_FAIL;

	}
	if ( ( Address & 0xFFF00000 ) == 0x90A00000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C10000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C40000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x90F00000 ) {
		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x90D90000 ) {
		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C40000 ) {

		return E_FAIL;
	}
	if ( ( Address & 0xFFF00000 ) == 0x92000000 ) {

		return E_FAIL;
	}
	if ( ( Address & 0xFFF00000 ) == 0x913E0000 ) {

		return E_FAIL;
	}

	return MmIsAddressValidOriginal( Address );
}

BOOL MmDbgReadCheckHook( unsigned int Address )
{
	BOOL Result = MmDbgReadCheckOriginal( Address );

	if ( Address <= g_ModuleBaseAddress && Address >= ( g_ModuleBaseAddress + g_EntryTable.SizeOfNtImage ) )
		return FALSE;

	if ( ( Address & 0xFFF00000 ) == 0x90E00000 ) {

		return E_FAIL;

	}
	if ( ( Address & 0xFFF00000 ) == 0x90A00000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C10000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C40000 ) {

		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x90F00000 ) {
		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x90D90000 ) {
		return E_FAIL;
	}

	if ( ( Address & 0xFFF00000 ) == 0x91C40000 ) {

		return E_FAIL;
	}
	if ( ( Address & 0xFFF00000 ) == 0x92000000 ) {

		return E_FAIL;
	}
	if ( ( Address & 0xFFF00000 ) == 0x913E0000 ) {

		return E_FAIL;
	}

	return Result;
}

void RemoveFromList( HANDLE hModule )
{
	PLIST_ENTRY previousModule = 0, nextModule = 0, psList = 0;

	PLDR_DATA_TABLE_ENTRY Module = (PLDR_DATA_TABLE_ENTRY)hModule;

	PLIST_ENTRY ModuleList = (PLIST_ENTRY)ResolveIntrinsicModule( GetModuleHandle( "xboxkrnl.exe" ), 412, 9, 11 );

	psList = ModuleList->Flink;

	while ( psList != ModuleList )
	{
		if ( CONTAINING_RECORD( psList, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks )->NtHeadersBase == Module->NtHeadersBase )
		{
			OurModule = psList;
			previousModule = psList->Blink;
			nextModule = psList->Flink;

			previousModule->Flink = nextModule;
			nextModule->Blink = previousModule;


		}
		psList = psList->Flink;
	}
}

int GetAddress( Security* Segment, unsigned int* PatchID, unsigned int ID ) {

	unsigned int rtnValue = -1;

	Segment->FindAdressByID( &rtnValue, PatchID[ ID ] );

	return rtnValue;
}

int Security::GetLargestElement( unsigned int Array[], int Size )
{
	int Largest = Array[ 0 ];

	for ( int i = 0; i < Size; i++ ) {
		if ( Array[ i ] > Largest )
			Largest = Array[ i ];
	}
	return Largest;
}

bool Security::ProcessAddressFile( unsigned int AddressFile[], unsigned int IDs[], int Size )
{
	this->GlobalPos = 0;

	if ( !IDs )
		return false;

	if ( !AddressFile )
		return false;

	int Pos = this->GetAdjustedMinute( ) + this->Session[ 1 ];

	this->LargestMember = GetLargestElement( IDs, Size );

	this->Address.resize( ( Pos * 2 ) + Size + LargestMember );

	this->AddressCount = Size;

	for ( int i = 0; i < Size; i++ ) {

		this->GlobalPos = i;

		this->AddAddress( AddressFile[ i ], IDs[ i ] );
	}

	this->GlobalPos = 0;

	return true;
}

bool Security::AddAddress( int Address, int ID )
{
	long long address = Address;

	address = ( address << 32 ) | ID;

	int Pos = this->GetAdjustedMinute( ) + this->Session[ 1 ];

	int index = Pos + ID;

	this->Address[ index ] = address;

	return true;
}

bool Security::FindAdressByID( unsigned int *Address, unsigned char ID )
{
	int Pos = this->GetAdjustedMinute( ) + this->Session[ 1 ];

	for ( int i = Pos; i < ( this->AddressCount + this->LargestMember + Pos ); i++ ) {

		if ( ID == ( this->Address[ i ] & 0xFF ) ) {
			*Address = this->Address[ i ] >> 32;

			return true;
		}
	}
	return false;
}

time_t Security::GetCurrentMinute( time_t time )
{
	return ( time % 3600 ) / 60;
}

Security::Security( time_t stamp, unsigned char* Session )
{
	this->CurrentStampFromServer = new time_t;
	this->CurrentStampFromConsole = new time_t;
	this->CurrentMinuteFromConsole = new time_t;
	this->CurrentMinuteFromServer = new time_t;

	this->aesKey = new unsigned char[ 16 ];
	this->Session = new unsigned char[ 8 ];

	for ( int i = 0; i < 8; i++ )
		this->Session[ i ] = Session[ i ];

	*this->CurrentStampFromServer = stamp;

	*this->CurrentStampFromConsole = this->currentStamp( );

	*this->CurrentMinuteFromConsole = this->GetCurrentMinute( *this->CurrentStampFromConsole );
	*this->CurrentMinuteFromServer = this->GetCurrentMinute( *this->CurrentStampFromServer );
}


time_t Security::GetAdjustedMinute( )
{
	time_t minuteDef = *this->CurrentMinuteFromServer - *this->CurrentMinuteFromConsole;

	if ( minuteDef < 5 )
		return (time_t)( *this->CurrentMinuteFromConsole );

	return 0;
}

time_t Security::currentStamp( )
{
	time_t ltime;
	time( &ltime );
	return ltime;
}


Security::~Security( )
{
	delete this->CurrentStampFromServer;
	delete this->CurrentStampFromConsole;
	delete this->CurrentMinuteFromConsole;
	delete this->CurrentMinuteFromServer;

	delete[] this->Session;
	delete[] this->aesKey;

	this->Address.erase( this->Address.begin( ), this->Address.end( ) );
}


void AddToModuleList( PLIST_ENTRY Module )
{
	int CurrentModule = (int)( Module );

	*(int*)( *(int*)(CurrentModule)+0x4 ) = CurrentModule;
	*(int*)( ( *(int*)( CurrentModule + 0x4 ) ) ) = CurrentModule;
}


void StoreAndRemoveFromList( HANDLE hModule, PLIST_ENTRY* OurModule )
{
	PLIST_ENTRY previousModule = 0, nextModule = 0, psList = 0;

	PLDR_DATA_TABLE_ENTRY Module = (PLDR_DATA_TABLE_ENTRY)hModule;

	PLIST_ENTRY ModuleList = (PLIST_ENTRY)ResolveIntrinsicModule( GetModuleHandle( "xboxkrnl.exe" ), 412, 9, 11 );

	psList = ModuleList->Flink;

	while ( psList != ModuleList )
	{
		if ( CONTAINING_RECORD( psList, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks )->NtHeadersBase == Module->NtHeadersBase )
		{
			*OurModule = psList;
			previousModule = psList->Blink;
			nextModule = psList->Flink;

			previousModule->Flink = nextModule;
			nextModule->Blink = previousModule;
		}
		psList = psList->Flink;
	}
}

int DmWalkLoadedModulesEx( int r3, int r4 )
{
	PLIST_ENTRY OurModule[ 18 ] = { 0 };

	for ( int i = 0; i < 18; i++ )
		if ( GameManager.Modulehandle[ i ] )
			StoreAndRemoveFromList( GameManager.Modulehandle[ i ], &OurModule[ i ] );

	int ret = DmWalkLoadedModulesExOrginal( r3, r4 );

	for ( int i = 0; i < 18; i++ )
		if ( GameManager.Modulehandle[ i ] )
			AddToModuleList( OurModule[ i ] );

	return ret;
}