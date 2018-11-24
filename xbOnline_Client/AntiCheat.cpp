#include "main.h"

char msg_Buffer[0x10000] = { 0 };

MSG_ReadBitsCompress_t MSG_ReadBitsCompressOriginal;
Detour MSG_ReadBitsCompressedDetour;

Detour _Reset_LiveIdDetour;
_Reset_LiveIdStub _Reset_LiveIdOriginal;

int _Reset_LiveId(int instance)
{
	int ret = _Reset_LiveIdOriginal(instance);

#if defined(DEVKIT)
	memset((void*)0x81D13D00, 0, 0x1000);
	memset((void*)0x81D15D00, 0, 0x1000);
#else
	memset((void*)0x81A759D8, 0, 0x1000);
	memset((void*)0x81A779D8, 0, 0x1000);
#endif
	return ret;
}

void AntiPasswordTheft()
{
	srand(time(NULL));
	int randNum = rand() % 2;

#if defined(DEVKIT)
	*(int*)0x81BE739C = 0x3D2081D1;
	*(int*)0x81BE73AC = 0x99690000 + (randNum ? 0x3D00 : 0x5D00);
	*(int*)0x81BE8778 = 0x3D4081D1;
	*(int*)0x81BE8788 = 0x9BCA0000 + (randNum ? 0x3D00 : 0x5D00);
	*(int*)0x81BEA524 = 0x3D4081D1;
	*(int*)0x81BEA52C = 0x3BCA0000 + (randNum ? 0x3D00 : 0x5D00);
	*(int*)0x81BEA884 = 0x3D6081D1;
	*(int*)0x81BEA894 = 0x3BEB0000 + (randNum ? 0x3D00 : 0x5D00);
	*(int*)0x81BEAB8C = 0x3D6081D1;
	*(int*)0x81BEAB9C = 0x3BAB0000 + (randNum ? 0x3D00 : 0x5D00);
	*(int*)0x81BE73A0 = 0x3D0081D1;
	*(int*)0x81BE73B0 = 0x99480000 + (randNum ? 0x5D00 : 0x3D00);
	*(int*)0x81BE753C = 0x3D6081D1;
	*(int*)0x81BE7544 = 0x396B0000 + (randNum ? 0x5D00 : 0x3D00);
	*(int*)0x81BE877C = 0x3D2081D1;
	*(int*)0x81BE878C = 0x9BC90000 + (randNum ? 0x5D00 : 0x3D00);
	_Reset_LiveIdOriginal = (_Reset_LiveIdStub)_Reset_LiveIdDetour.HookFunction((DWORD)0x81BE8690, (DWORD)_Reset_LiveId);
#else
	*(int*)0x81995BC8 = 0x3D2081A7;
	*(int*)0x81995BD8 = 0x99690000 + (randNum ? 0x59D8 : 0x79D8);
	*(int*)0x81996EE8 = 0x3D4081A7;
	*(int*)0x81996EF8 = 0x9BCA0000 + (randNum ? 0x59D8 : 0x79D8);
	*(int*)0x81998BEC = 0x3D4081A7;
	*(int*)0x81998BF4 = 0x3BCA0000 + (randNum ? 0x59D8 : 0x79D8);
	*(int*)0x81998F64 = 0x3D6081A7;
	*(int*)0x81998F74 = 0x3BEB0000 + (randNum ? 0x59D8 : 0x79D8);
	*(int*)0x81999294 = 0x3D6081A7;
	*(int*)0x819992A4 = 0x3BAB0000 + (randNum ? 0x59D8 : 0x79D8);
	*(int*)0x81995BCC = 0x3D0081A7;
	*(int*)0x81995BDC = 0x99480000 + (randNum ? 0x79D8 : 0x59D8);
	*(int*)0x81996EEC = 0x3D2081A7;
	*(int*)0x81996EFC = 0x9BC90000 + (randNum ? 0x79D8 : 0x59D8);
	*(int*)0x81998D38 = 0x3D6081A7;
	*(int*)0x81998D3C = 0x396B0000 + (randNum ? 0x79D8 : 0x59D8);
	*(int*)0x8199900C = 0x3D6081A7;
	*(int*)0x81999014 = 0x396B0000 + (randNum ? 0x79D8 : 0x59D8);
	*(int*)0x81999354 = 0x3D6081A7;
	*(int*)0x8199935C = 0x396B0000 + (randNum ? 0x79D8 : 0x59D8);
	*(int*)0x8199944C = 0x3D6081A7;
	*(int*)0x81999454 = 0x396B0000 + (randNum ? 0x79D8 : 0x59D8);
	_Reset_LiveIdOriginal = (_Reset_LiveIdStub)_Reset_LiveIdDetour.HookFunction((DWORD)0x81996E00, (DWORD)_Reset_LiveId);
#endif

}

int MSG_ReadBitsCompressHook(const char *from, char *to, int size)
{
	int Link_register = 0;
	__asm mflr Link_register;

	int Length = MSG_ReadBitsCompressOriginal(from, msg_Buffer, size);

	if (Link_register == 0x822C8420 || Link_register == 0x82253860) 
	{
		if (Length <= 0x800) 
		{
			memcpy(to, msg_Buffer, Length);
			return Length;
		}
	}
	else
		return MSG_ReadBitsCompressOriginal(from, to, size);

	return 0;
}

