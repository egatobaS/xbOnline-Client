#include "main.h"

Detour GhostDetour;

Ghosts_LiveAntiCheat_ProcessChallengeResponse_t Ghosts_LiveAntiCheat_ProcessChallengeResponseOriginal;

void setLogMessage_Ghosts(int CheatResp, const char* Message, int Message_Size)
{

	if (Message == 0 || Message_Size == 0) {

		*(int*)(CheatResp + 0x60) = 0;
		memset((void*)(CheatResp + 0x1E), 0, 0x40);

		return;
	}

	if (Message_Size == 0x3A)
	{
		GHOSTS_CHALL_RESP* resp = (GHOSTS_CHALL_RESP*)Message;

		resp->Flags = (isChallengeMultiplayer ? 3 : 2);

		memcpy(resp->ConsoleID, Text_ConsoleID, 0xC);

		memcpy(resp->MacAddress, spoofedMacAddress, 6);

		memcpy(resp->SerialNumber, Text_SerialNumber, 0xD);

		resp->MachineID = spoofedMachineID;

		resp->KernelVersion = 0x4476;

	}

	memcpy((void*)(CheatResp + 0x1E), Message, (Message_Size <= 0x40) ? Message_Size : 0x40);
	*(DWORD*)(CheatResp + 0x60) = (Message_Size < 0x40) ? Message_Size : 0x40;
}

bool Ghosts_LiveAntiCheat_ProcessChallengeResponse(int Challenge)
{
	MemoryHashInfo *memoryHashInfo = (MemoryHashInfo *)*(int *)((int)Challenge + 0x34);

	if (*(short *)(Challenge + 0x08) == 0xC8)
	{
		if (memoryHashInfo)
		{
			if ((memoryHashInfo->position == 0 && memoryHashInfo->state != 0x3039) || memoryHashInfo->type != 1)
				XLaunchNewImage(NULL, NULL);

			memoryHashInfo->cumulativeProcessingTime = 2337 + (GetTickCount() % 1337);

			memoryHashInfo->state = 0;

			*(int *)((int)&memoryHashInfo->state + 4) = isChallengeMultiplayer ? 0x77DF0D80 : 0x2D20A455;

			memoryHashInfo->position = memoryHashInfo->length;
		}
	}
	else
		XLaunchNewImage(NULL, NULL);

	return Ghosts_LiveAntiCheat_ProcessChallengeResponseOriginal(Challenge);
}

void InitGhosts()
{
	RandomValues();

	if (isChallengeMultiplayer)
	{
		NetDll_XNetGetTitleXnAddrDetour.HookFunction(0x827D3F54, (DWORD)NetDll_XNetGetTitleXnAddrHook);
		XNetXnAddrToMachineIdDetour.HookFunction(0x82810D7C, (int)XNetXnAddrToMachineIdHook);
	}

	Ghosts_LiveAntiCheat_ProcessChallengeResponseOriginal = (Ghosts_LiveAntiCheat_ProcessChallengeResponse_t)GhostDetour.HookFunction(isChallengeMultiplayer ? 0x82629F98 : 0x825131D8, (DWORD)Ghosts_LiveAntiCheat_ProcessChallengeResponse);
	setMessageLogDetour.HookFunction(isChallengeMultiplayer ? 0x827BE130 : 0x82647700, (DWORD)setLogMessage_Ghosts);
	WriteHookOriginal = (WriteHook_t)WriteHookDetour.HookFunction(isChallengeMultiplayer ? 0x827A0108 : 0x826320B0, (DWORD)WriteHook);
}



