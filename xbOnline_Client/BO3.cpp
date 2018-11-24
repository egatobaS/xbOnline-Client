#include "main.h"

Detour BO3Bypass;

void setLogMessage_BO3(int CheatResp, const char* Message, int Message_Size)
{

	if (Message == 0 || Message_Size == 0) {

		*(int*)(CheatResp + 0x64) = 0;
		memset((void*)(CheatResp + 0x22), 0, 0x40);

		return;
	}

	if (Message_Size == 0x30)
	{
		BO3_CHALL_RESP* resp = (BO3_CHALL_RESP*)Message;

		resp->Flags = (isChallengeMultiplayer ? 3 : 2);

		memcpy(resp->ConsoleID, Text_ConsoleID, 0xC);

		memcpy(resp->MacAddress, spoofedMacAddress, 6);

		memcpy(resp->SerialNumber, Text_SerialNumber, 0xD);

		resp->MachiebeID = spoofedMachineID;

		resp->KenelVersion = 0x4476;

	}

	memcpy((void*)(CheatResp + 0x22), Message, (Message_Size <= 0x40) ? Message_Size : 0x40);
	*(DWORD*)(CheatResp + 0x64) = (Message_Size < 0x40) ? Message_Size : 0x40;
}



void InitBlackOps3()
{
	RandomValues();

	WriteHookOriginal = (WriteHook_t)WriteHookDetour.HookFunction(isChallengeMultiplayer ? 0x8279C958 : 0x8278E9B8, (DWORD)WriteHook);
	setMessageLogDetour.HookFunction(isChallengeMultiplayer ? 0x827B54C8 : 0x827A75C8, (DWORD)setLogMessage_BO3);
}
