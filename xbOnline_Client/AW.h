#pragma once

#pragma pack(push, 1)
struct AW_CHALL_RESP
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

void InitAW();
bool AW_LiveAntiCheat_ProcessChallengeResponse(int controller, short m_functionID, int* Ptr, __int64* result);
void setLogMessage_AW(int CheatResp, const char* Message, int Message_Size);
