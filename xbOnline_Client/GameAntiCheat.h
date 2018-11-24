#pragma once

extern bool isChallengeMultiplayer;
extern bool bInitialized;

typedef bool(*WriteHook_t)(unsigned char * buf, unsigned char* data, int data_size);
extern WriteHook_t WriteHookOriginal;

extern Detour WriteHookDetour;
extern Detour setMessageLogDetour;

bool WriteHook(unsigned char * buf, unsigned char* data, int data_size);