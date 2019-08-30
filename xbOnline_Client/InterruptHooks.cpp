#include "main.h"

#include <stdint.h>

DWORD KeTimeStampBundleOriginal = 0;

DWORD XamChallengeSize = 0x0, XoscChallengeSize = 0x0;
BYTE LastChallengeBufferXosc[ 0x1000 ] = { 0 };
BYTE LastChallengeBufferXam[ 0x1000 ] = { 0 };

DWORD CheckXamChallengeSize = 0x0, CheckXoscChallengeSize = 0x0;
BYTE CheckLastChallengeBufferXosc[ 0x1000 ] = { 0 };
BYTE CheckLastChallengeBufferXam[ 0x1000 ] = { 0 };

#define KiDebugRoutine 0x801A58C4 //retail
#define KeTimeStampBundle 0x815F046C //retail
#define CrashAddr 0x8174E1C0 //retail

typedef int( *DmTrapHandler_t )( PKTRAP_FRAME ptf, PEXCEPTION_RECORD pef, PCONTEXT pcr, BOOL fSecondChance );
DmTrapHandler_t HandlerOriginal;

typedef int( *XeKeysConsolePrivateKeySignStub_t )( unsigned long long r3, unsigned long long r4 );
XeKeysConsolePrivateKeySignStub_t XeKeysConsolePrivateKeySignOriginal_t = (XeKeysConsolePrivateKeySignStub_t)0x80109208;

typedef int( *XeKeysGetConsoleCertificateStub_t )( unsigned long long r3 );
XeKeysGetConsoleCertificateStub_t XeKeysGetConsoleCertificateOriginal_t = (XeKeysGetConsoleCertificateStub_t)0x80108618;

uint32_t PowerPCMask32( uint32_t MB, uint32_t ME )
{
	uint32_t MaskMB = UINT32_MAX >> MB;
	uint32_t MaskME = UINT32_MAX << ( 31 - ME );
	return ( MB <= ME ) ? MaskMB & MaskME : MaskMB | MaskME;
}

uint32_t rlwinm( uint32_t RS, int SH, int MB, int ME )
{
	return ( ( RS << SH ) | ( RS >> ( 32 - SH ) ) ) & PowerPCMask32( MB, ME );
}

uint32_t extrwi( uint32_t RS, int N, int B )
{
	return rlwinm( RS, B + N, 32 - N, 31 );
}

BOOL Handler( PKTRAP_FRAME ptf, PEXCEPTION_RECORD pef, PCONTEXT pcr, BOOL fSecondChance )
{
	if ( pef->ExceptionCode == 0xC000001D && pef->ExceptionAddress )
	{
		if ( pef->ExceptionAddress == (PVOID)0x80108618 )
		{
			if ( IsKvLessModeAvalible && !IsKvAssigned ) {

				PerformeOneTimeCleanUp( );

				pcr->Gpr12 = pcr->Lr;
				pcr->Iar += 4;
			}
			else {

				pcr->Gpr12 = pcr->Lr;
				pcr->Iar = (DWORD)XeKeysGetConsoleCertificate_Hook;

			}
		}

		if ( pef->ExceptionAddress == (PVOID)0x80109208 )
		{
			GetKvData( 4 );

			if ( IsKvLessModeAvalible && !IsKvAssigned ) {

				PerformeOneTimeCleanUp( );

				pcr->Gpr12 = pcr->Lr;
				pcr->Iar += 4;

			}
			else {

				pcr->Gpr12 = pcr->Lr;
				pcr->Iar = (DWORD)XeKeysConsolePrivateKeySign_Hook;
			}
		}
		return 1;
	}

	if ( pef->ExceptionCode == 0xC0000005 && pef->ExceptionAddress )
	{
		ULONGLONG* registers = &pcr->Gpr0;

		DWORD Inst = *(DWORD*)pef->ExceptionAddress;

		DWORD InstOpcode = extrwi( Inst, 6, 0 );
		//DWORD InstOutput = extrwi(Inst, 5, 6);
		DWORD InstInput = extrwi( Inst, 5, 11 );
		//DWORD InstOffset = extrwi(Inst, 16, 16);

		if ( InstOpcode == 32 )
		{
			if ( registers[ InstInput ] == 0x0EADBEEF )
			{
				registers[ InstInput ] = KeTimeStampBundleOriginal;

				if ( (DWORD)pef->ExceptionAddress == CrashAddr )
				{
					if ( *(int*)( pcr->Gpr27 + 0x40 ) == 0x4E4E4488 )
					{
						unsigned char* challengeBuffer = (unsigned char*)pcr->Gpr27;

						bool isTamperedDetected = false;

						for ( int i = 0; i < 0xD8; i++ ) {

							if ( challengeBuffer[ i + 0x40 ] != LastChallengeBufferXam[ i + 0x28 ] ) {

								challengeBuffer[ i + 0x40 ] = LastChallengeBufferXam[ i + 0x28 ];

								isTamperedDetected = true;
							}
						}
					}
	
					if ( *(int*)( pcr->Gpr27 + 0x14 ) == 0x00000000 && 
						 *(int*)( pcr->Gpr27 + 0x38 ) == 0xAAAAAAAA && 
						 *(int*)( pcr->Gpr27 + 0x54 ) == 0x20448800 &&
						 *(int*)( pcr->Gpr27 + 0xA0 ) == 0xAAAAAAAA )
					{
						unsigned char* challengeBuffer = (unsigned char*)pcr->Gpr27;

						bool isTamperedDetected = false;

						for ( int i = 0; i < 0x400; i++ ) {

							if ( challengeBuffer[ i + 0x14 ] != LastChallengeBufferXosc[ i ] ) {

								challengeBuffer[ i + 0x14 ] = LastChallengeBufferXosc[ i ];

								isTamperedDetected = true;
							}
						}
					}
				}
				return 1;
			}
		}
	}

	return HandlerOriginal( ptf, pef, pcr, fSecondChance );
}


void SetUpHandler( )
{
	KeTimeStampBundleOriginal = *(int*)KeTimeStampBundle;
	HandlerOriginal = (DmTrapHandler_t)( *(int*)( KiDebugRoutine ) );
	*(int*)( KiDebugRoutine ) = (int)Handler;
	__emit( 0x4C00012C );

	*(int*)( KeTimeStampBundle ) = 0x0EADBEEF;
	__emit( 0x4C00012C );

}