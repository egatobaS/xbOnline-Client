#pragma once

#define PAYLOAD_BUFFER_SIZE 0x1000

typedef struct HV_PAYLOAD_HEADER
{
	unsigned short Magic;
	unsigned short Version;
	unsigned int Flags;
	unsigned int EntryPoint;
	unsigned int Size;
	unsigned char Hmac_key[0x10];
	unsigned char Sig[0x100];

}HV_PAYLOAD_HEADER, *PHV_PAYLOAD_HEADER;

enum KeysExecuteError
{
	EXECUTE_SUCCESS,
	EXECUTE_INVALID_PAYLOAD_SIZE,
	EXECUTE_INVALID_BUFFER_SIZE,
	EXECUTE_INVALID_BUFFER_ADDRESS,
	EXECUTE_INVALID_RETURN
};

long long ExecuteCode(unsigned char* in, unsigned int inLen, unsigned char* out, unsigned int outLen);
int CreatePayload(unsigned char* Payload, unsigned int Size, unsigned char* PayloadOut);

#if defined(DEVKIT)
void EncryptedDecryptPacket(unsigned char* Buffer, int length);
void EncryptedDecryptPacket_Second(unsigned char* Buffer, int length);
#else
#endif	
