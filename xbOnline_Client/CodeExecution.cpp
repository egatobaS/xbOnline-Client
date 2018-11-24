#include "main.h"

unsigned int cSize = 0x120;

unsigned char Hmac_key[0x10] = { 0x81, 0x68, 0x4D, 0x8C, 0x90, 0xFD, 0xBF, 0x3C, 0x04, 0x2C, 0x27, 0x44, 0x79, 0xC9, 0xF5, 0x25 };
unsigned char BLKey[0x10] = { 0xDD, 0x88, 0xAD, 0x0C, 0x9E, 0xD6, 0x69, 0xE7, 0xB5, 0x67, 0x94, 0xFB, 0x68, 0x56, 0x3E, 0xFA };

/*
XeKeysExecute Payload header by TEIR1plus2
Source: https://www.se7ensins.com/forums/threads/using-xekeysexecute-to-run-custom-code.1652215/
*/

static long long _declspec(naked) HvKeysExecute(unsigned char* Payload, unsigned int BufferSize, long long Arg1, void* Arg2, long long Arg3, void* Arg4)
{
	__asm
	{
		li    r0, 0x40
		sc
		blr
	}
}

int CreatePayload(unsigned char* Payload, unsigned int Size, unsigned char* PayloadOut)
{
	rc4_state RC4 = { 0 };

	unsigned char RC4_KEY[0x10] = { 0 }, PAY_LOAD[PAYLOAD_BUFFER_SIZE] = { 0 };

	if ((Size + cSize > PAYLOAD_BUFFER_SIZE) || (Size + cSize < 0x120))
		return EXECUTE_INVALID_PAYLOAD_SIZE;

	if (PAYLOAD_BUFFER_SIZE == 0)
		return EXECUTE_INVALID_BUFFER_SIZE;

	unsigned char* bPayload = new unsigned char[PAYLOAD_BUFFER_SIZE];

	memset(bPayload, 0, PAYLOAD_BUFFER_SIZE);

	PHV_PAYLOAD_HEADER Header = (PHV_PAYLOAD_HEADER)bPayload;

	Header->Magic = 0x4D4D;
	Header->Version = 0x4099;
	Header->Flags = 0;
	Header->Size = cSize + Size;
	Header->EntryPoint = 0x120;

	Tramps->CallFunction(memcpy_Function, (int)Header->Hmac_key, (int)Hmac_key, 0x10, 0, false);
	Tramps->CallFunction(memcpy_Function, (int)bPayload + 0x120, (int)Payload, Size, 0, false);

	lrad_hmac_sha1(Header->Hmac_key, 0x10, BLKey, 0x10, RC4_KEY);
	rc4_init(&RC4, RC4_KEY, 0x10);
	rc4_crypt(&RC4, bPayload + 0x20, bPayload + 0x20, Header->Size - 0x20);

	Tramps->CallFunction(memcpy_Function, (int)PayloadOut, (int)bPayload, PAYLOAD_BUFFER_SIZE, 0, false);

	delete bPayload;

	return 0;
}

/*
mflr %r11
std %r11, -8(%r1)
std %r31, -0x10(%r1)
std %r30, -0x18(%r1)
std %r29, -0x20(%r1)
std %r28, -0x28(%r1)
std %r27, -0x30(%r1)
std %r26, -0x38(%r1)
std %r25, -0x40(%r1)
stdu %r1, -0xF0(%r1)

mr %r3, %r4
mr %r4, %r5
mr %r5, %r6
mr %r6, %r7
mr %r7, %r8

mr %r3, %r3
mr %r4, %r4
li %r5, 0
li %r6, 0
li %r7, 0
li %r8, 0
li %r9, 0
li %r10, 0
bla 0x22DB8

addi %r1, %r1, 0xF0
ld %r11, -8(%r1)
mtlr %r11
ld %r25, -0x40(%r1)
ld %r26, -0x38(%r1)
ld %r27, -0x30(%r1)
ld %r28, -0x28(%r1)
ld %r29, -0x20(%r1)
ld %r30, -0x18(%r1)
ld %r31, -0x10(%r1)
li %r3, 0
blr


*/

long long ExecuteCode(unsigned char* in, unsigned int inLen, unsigned char* out, unsigned int outLen)
{
	if (!in || !out)
		return -1;

	unsigned char* ChallengeData = (unsigned char*)XPhysicalAlloc(0x1000, MAXULONG_PTR, NULL, PAGE_READWRITE);
	unsigned char* OutBuffer = (unsigned char*)XPhysicalAlloc(outLen, MAXULONG_PTR, NULL, PAGE_READWRITE);

	memset(OutBuffer, 0, outLen);

	Tramps->CallFunction(memcpy_Function, (int)OutBuffer, (int)out, outLen, 0, false);

	HVGetVersionsPokeDWORD(0x800001000000617C, 0x38600001);

	CreatePayload(in, inLen, ChallengeData);

	long long physPayload = 0x8000000000000000ULL + (DWORD)MmGetPhysicalAddress(ChallengeData), physCheck = (((physPayload + 0x1000) - 1) ^ physPayload) & 0xFFFF0000;

	if (physCheck) {
		XPhysicalFree(ChallengeData);
		XPhysicalFree(OutBuffer);
		return -1;
	}

	if ((physPayload & 0xFFFFFFFF) > 0x1FFBFFFF) {

		XPhysicalFree(ChallengeData);
		XPhysicalFree(OutBuffer);
		return -1;
	}

	long long retbuf = (0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress(OutBuffer));

	long long ret = (long long)HvKeysExecute((unsigned char*)physPayload, 0x1000, retbuf, (void*)outLen, 0, 0);
	
	for (unsigned int i = 0; i < outLen; i++)
		out[i] = OutBuffer[i];

	XPhysicalFree(ChallengeData);
	XPhysicalFree(OutBuffer);

	return ret;
}

#if defined(DEVKIT)
void EncryptedDecryptPacket(unsigned char* Buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		Buffer[i] = (unsigned char)(Buffer[i] ^ length);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xE4);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x61);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x91);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xD6);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x1);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xCF);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xFF);
	}
}

void EncryptedDecryptPacket_Second(unsigned char* Buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x30);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x24);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x44);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x34);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0x25);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xCE);
		Buffer[i] = (unsigned char)(Buffer[i] ^ 0xF1);
	}
}
#else
#endif	

