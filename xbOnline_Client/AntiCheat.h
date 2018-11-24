#pragma once

typedef int(*MSG_ReadBitsCompress_t)(const char *from, char *to, int size);
typedef int(*_Reset_LiveIdStub)(int instance);

extern MSG_ReadBitsCompress_t MSG_ReadBitsCompressOriginal;
extern _Reset_LiveIdStub _Reset_LiveIdOriginal;
extern Detour _Reset_LiveIdDetour;
extern Detour MSG_ReadBitsCompressedDetour;


int _Reset_LiveId(int instance);
void AntiPasswordTheft();

int MSG_ReadBitsCompressHook(const char *from, char *to, int size);