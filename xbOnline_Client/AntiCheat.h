#pragma once

typedef int(*_Reset_LiveIdStub)(int instance);

extern _Reset_LiveIdStub _Reset_LiveIdOriginal;
extern Detour _Reset_LiveIdDetour;

int _Reset_LiveId(int instance);
void AntiPasswordTheft();

