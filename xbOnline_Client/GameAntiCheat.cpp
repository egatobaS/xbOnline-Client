#include "main.h"

bool bInitialized = false;
bool isChallengeMultiplayer = false;

Detour WriteHookDetour;
Detour setMessageLogDetour;

WriteHook_t WriteHookOriginal;

bool WriteHook(unsigned char * buf, unsigned char* data, int data_size)
{
	if (buf) {

		if (data_size == 0x8 && *(char*)(data) == 0xFA) {
			memcpy(buf, &spoofedMachineID, 8);
		}

		if (data_size == 0x6) {
			memcpy(buf, spoofedMacAddress, 6);
		}
	}	
	return WriteHookOriginal(buf, data, data_size);
}