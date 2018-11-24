#pragma once

#pragma pack(push, 1)
struct BO3_CHALL_RESP
{
	unsigned char Externel_IP[4];
	unsigned long long MachiebeID;
	unsigned char MacAddress[6];
	short unk;
	unsigned char Flags;
	char SerialNumber[0xD];
	char ConsoleID[0xC];
	short KenelVersion;
};
#pragma pack(pop)

void InitBlackOps3();
void setLogMessage_BO3(int CheatResp, const char* Message, int Message_Size);