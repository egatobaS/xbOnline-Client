#include "main.h"

Detour AWDetour;

void setLogMessage_AW(int CheatResp, const char* Message, int Message_Size)
{
	if (Message_Size == 0x3A)
	{
		AW_CHALL_RESP* resp = (AW_CHALL_RESP*)Message;

		resp->Flags = (isChallengeMultiplayer ? 3 : 2);

		memcpy(resp->ConsoleID, Text_ConsoleID, 0xC);

		memcpy(resp->MacAddress, spoofedMacAddress, 6);

		memcpy(resp->SerialNumber, Text_SerialNumber, 0xD);

		resp->MachineID = spoofedMachineID;

		resp->KernelVersion = 0x4476;

	}

	if (Message == 0 || Message_Size == 0) {

		*(int*)(CheatResp + 0x64) = 0;
		memset((void*)(CheatResp + 0x22), 0, 0x40);

		return;
	}

	memcpy((void*)(CheatResp + 0x22), Message, (Message_Size <= 0x40) ? Message_Size : 0x40);
	*(DWORD*)(CheatResp + 0x64) = (Message_Size < 0x40) ? Message_Size : 0x40;
}

bool AW_LiveAntiCheat_ProcessChallengeResponse(int controller, short m_functionID, int* Ptr, __int64* result)
{
	if (m_functionID == 0xC8)
	{
		__int64 Seed = *(__int64 *)*(int *)(Ptr[0] + 0x04);

		if (Seed == 0xA5BFE) {

			if (isChallengeMultiplayer)
				result[0] = 0xA7388544;
			else
				result[0] = 0x2900A35F;

			return TRUE;
		}
		else
			XLaunchNewImage(NULL, NULL);
	}
	return true;
}

void InitAW()
{
	RandomValues();

	if (isChallengeMultiplayer)
	{
		XNetXnAddrToMachineIdDetour.HookFunction(0x827D3F54, (int)XNetXnAddrToMachineIdHook);
	}

	AWDetour.HookFunction(isChallengeMultiplayer ? 0x822CC740 : 0x8258C060, (DWORD)AW_LiveAntiCheat_ProcessChallengeResponse);
	setMessageLogDetour.HookFunction(isChallengeMultiplayer ? 0x821DF510 : 0x82647700, (DWORD)setLogMessage_AW);
	WriteHookOriginal = (WriteHook_t)WriteHookDetour.HookFunction(isChallengeMultiplayer ? 0x821B6360 : 0x826BE250, (DWORD)WriteHook);
}

