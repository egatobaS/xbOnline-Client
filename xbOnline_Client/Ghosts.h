#pragma once

#pragma pack(push, 1)
struct GHOSTS_CHALL_RESP
{
	unsigned char IPAddress[4];
	unsigned long long MachineID;
	unsigned char MacAddress[8];
	unsigned int unk1_zero;
	unsigned int unk2_zero;
	short someFlag;
	unsigned char Flags;
	char SerialNumber[0xD];
	char ConsoleID[0xC];
	short KernelVersion;
};
#pragma pack(pop)

struct MemoryHashInfo
{
	enum : int
	{
		CT_TYPE_INVALID = 0x0,
		CT_TYPE_CRC32 = 0x1,
		CT_TYPE_MD4 = 0x2,
		CT_TYPE_SHA_TOMCRYPT = 0x3,
		CT_TYPE_8WAY = 0x4,
		CT_TYPE_CRC32_SPLIT = 0x5,
	} type;

	unsigned int start;
	unsigned int length;
	unsigned int position;
	unsigned int blockSize;
	unsigned int index;
	unsigned int startProcessingTime;
	unsigned int cumulativeProcessingTime;
	unsigned __int64 state;
	union
	{
		union
		{
			char dummy[1];
			struct
			{
				unsigned __int64 length;
				unsigned int state[8];
				unsigned int curlen;
				char buf[64];
			} sha256;

			struct
			{
				unsigned __int64 length;
				unsigned int state[5];
				unsigned int curlen;
				char buf[64];
			} sha1;

			struct
			{
				unsigned __int64 length;
				unsigned int state[4];
				unsigned int curlen;
				char buf[64];
			} md5;

			struct tiger_state
			{
				unsigned __int64 state[3];
				unsigned __int64 length;
				unsigned int curlen;
				char buf[64];
			} tiger;

			void *data;

		} hashState;
		struct
		{
			unsigned __int64 initialKey;
			unsigned __int64 cumulativeState;
		} eightWayState;

	} ___u9;

};

typedef bool(*Ghosts_LiveAntiCheat_ProcessChallengeResponse_t)(int r3);
extern Ghosts_LiveAntiCheat_ProcessChallengeResponse_t Ghosts_LiveAntiCheat_ProcessChallengeResponseOriginal;

void InitGhosts();
bool Ghosts_LiveAntiCheat_ProcessChallengeResponse(int Challenge);
void setLogMessage_Ghosts(int CheatResp, const char* Message, int Message_Size);

void Ghosts_SetupGameAddresses(ServerData_Ghosts* Server);

bool Ghosts_BuildFunctions();