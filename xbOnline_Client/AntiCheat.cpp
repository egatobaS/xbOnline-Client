#include "main.h"

Detour _Reset_LiveIdDetour;

_Reset_LiveIdStub _Reset_LiveIdOriginal;

int _Reset_LiveId( int instance )
{
	int ret = _Reset_LiveIdOriginal( instance );

	memset( (void*)0x81A759D8, 0, 0x1000 );
	memset( (void*)0x81A779D8, 0, 0x1000 );

	return ret;
}

void AntiPasswordTheft( )
{
	//srand( time( NULL ) );
	//int randNum = rand( ) % 2;
	//
	//*(int*)0x81995BC8 = 0x3D2081A7;
	//*(int*)0x81995BD8 = 0x99690000 + ( randNum ? 0x59D8 : 0x79D8 );
	//*(int*)0x81996EE8 = 0x3D4081A7;
	//*(int*)0x81996EF8 = 0x9BCA0000 + ( randNum ? 0x59D8 : 0x79D8 );
	//*(int*)0x81998BEC = 0x3D4081A7;
	//*(int*)0x81998BF4 = 0x3BCA0000 + ( randNum ? 0x59D8 : 0x79D8 );
	//*(int*)0x81998F64 = 0x3D6081A7;
	//*(int*)0x81998F74 = 0x3BEB0000 + ( randNum ? 0x59D8 : 0x79D8 );
	//*(int*)0x81999294 = 0x3D6081A7;
	//*(int*)0x819992A4 = 0x3BAB0000 + ( randNum ? 0x59D8 : 0x79D8 );
	//*(int*)0x81995BCC = 0x3D0081A7;
	//*(int*)0x81995BDC = 0x99480000 + ( randNum ? 0x79D8 : 0x59D8 );
	//*(int*)0x81996EEC = 0x3D2081A7;
	//*(int*)0x81996EFC = 0x9BC90000 + ( randNum ? 0x79D8 : 0x59D8 );
	//*(int*)0x81998D38 = 0x3D6081A7;
	//*(int*)0x81998D3C = 0x396B0000 + ( randNum ? 0x79D8 : 0x59D8 );
	//*(int*)0x8199900C = 0x3D6081A7;
	//*(int*)0x81999014 = 0x396B0000 + ( randNum ? 0x79D8 : 0x59D8 );
	//*(int*)0x81999354 = 0x3D6081A7;
	//*(int*)0x8199935C = 0x396B0000 + ( randNum ? 0x79D8 : 0x59D8 );
	//*(int*)0x8199944C = 0x3D6081A7;
	//*(int*)0x81999454 = 0x396B0000 + ( randNum ? 0x79D8 : 0x59D8 );
	//_Reset_LiveIdOriginal = (_Reset_LiveIdStub)_Reset_LiveIdDetour.HookFunction( (DWORD)0x81996E00, (DWORD)_Reset_LiveId );
}