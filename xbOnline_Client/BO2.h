#pragma once

#pragma pack(push, 1)
struct BO2_CHALL_RESP
{
	unsigned char deValue;
	unsigned int unk1;
	unsigned char unk;
	unsigned char IPAddress[4];
	unsigned int timestamp;
	unsigned char MacAddress[8];
	unsigned long long MachiebeID;
	unsigned char SerialNumber[8];
	unsigned char ConsoleID[8];
	unsigned int KenelVersion;
	unsigned int secValue;
};
#pragma pack(pop)


void BO2_SetupGameAddresses(ServerData_BlackOps2* Server);

void InitBlackOps2();
bool BO2_LiveAntiCheat_ProcessChallengeResponse(int controller, short funcID, int* params, __int64* result);
void setLogMessage_BO2(int CheatResp, const char* Message, int Message_Size);

bool BlackOps2_BuildFunctions();