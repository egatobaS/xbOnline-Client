#ifndef _SHA1_H
#define _SHA1_H

typedef unsigned long int uint32;
typedef unsigned short    uint16;
typedef unsigned char      uint8;

typedef struct
{
	uint32 total[2];
	uint32 state[5];
	uint8 buffer[64];
}
sha1_context;

void sha1_starts(sha1_context *ctx);
void sha1_update(sha1_context *ctx, uint8 *input, uint32 length);
void sha1_finish(sha1_context *ctx, uint8 digest[20]);
void sha1(void* inData, unsigned int lenght, unsigned char* outBuffer);

#endif /* sha1.h */
