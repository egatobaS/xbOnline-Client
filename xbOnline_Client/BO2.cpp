#include "main.h"

Security * addr_s_Data = 0;
Security * init_resp_s_Data = 0;

Detour sub_825D99C8Detour;

typedef int(*sub_825D99C8Stub)(XNADDR * pxna, int l);
extern sub_825D99C8Stub sub_825D99C8Original;

sub_825D99C8Stub sub_825D99C8Original;

unsigned int *addr_s_PatchID = 0;
unsigned int *init_resp_s_PatchID = 0;

int EncryptedDataLength = 0;
unsigned char* EncryptedData = 0;

//int Server_addr_s[80] = { 0x82496430,
//0x824964C0,
//0x824991B0,
//0x82496528,
//0x82496780,
//0x82496990,
//0x824991E8,
//0x825330B8,
//0x83EEF324,
//0x821E6518,
//0x821E6530,
//0x824015E0,
//0x822786E0,
//0x82241140,
//0x8241A0A8,
//0x82406578,
//0x8259B940,
//0x824E1BF0,
//0x8241DB80,
//0x82490610,
//0x82490058,
//0x824900F8,
//0x824522F8,
//0x82442F68,
//0x82414578,
//0x821D03F0,
//0x821F8E50,
//0x822544B0,
//0x8225C568,
//0x826BB4E0,
//0x82696250,
//0x82697FC0,
//0x826961B8,
//0x823F7160,
//0x82436010,
//0x822644A8,
//0x82428580,
//0x827D4F50,
//0x83AF7330,
//0x827D4E08,
//0x823F3E28,
//0x828B6FD8,
//0x82490390,
//0x828B8BA0,
//0x828B86C0,
//0x821C7F58,
//0x828AFC58,
//0x828B78F0,
//0x828B6EC0,
//0x82CBC168,
//0x828B7190,
//0x828B7E80,
//0x828C28A8,
//0x8224CDA8,
//0x826B0148,
//0x826B0278,
//0x821FA7F8,
//0x82258840,
//0x82690E50,
//0x845CA998,
//0x82BBAE44,
//0x82BBAE68,
//0x82BBC554,
//0x82C70F4C,
//0x82CAC2A8,
//0x841E1B30,
//0x82452E58,
//0x8293D884,
//0x8293D724,
//0x828B9F58,
//0x821EAB68,
//0x822816B8,
//0x824744E0,
//0x8225EAA8,
//0x821D27E8,
//0x828A5AA0,
//0x82717AE0,
//0x82278A00,
//0x8293E5C4,
//0x824143D0 };

enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct addr_s
{
	unsigned int Dvar_FindVar;// 0x82496430;
	unsigned int Dvar_GetBool;// 0x824964C0;
	unsigned int Dvar_SetBool;// 0x824991B0;
	unsigned int Dvar_GetInt;// 0x82496528;
	unsigned int Dvar_GetFloat;// 0x82496780;
	unsigned int Dvar_GetString;// 0x82496990;
	unsigned int Dvar_SetStringByName;// 0x824991E8;

	unsigned int SL_GetStringOfSize;// 0x825330B8;
	unsigned int StringTable;// 0x83EEF324;

	unsigned int CG_GameMessage;// 0x821E6518;
	unsigned int CG_BoldGameMessage;// 0x821E6530;
	unsigned int Cbuf_AddText;// 0x824015E0;
	unsigned int CL_AddReliableCommand;// 0x822786E0;
	unsigned int CG_VisionSetStartLerp_To;// 0x82241140;
	unsigned int MsgCRC_NetFieldChecksum;// 0x8241A0A8;
	unsigned int Com_SessionMode_IsZombiesGame;// 0x82406578;
	unsigned int Live_ControllerIndex_GetXuidString;// 0x8259B940;
	unsigned int Xenon_GetXNAddr;// 0x824E1BF0;
	unsigned int ByteArrayToString;// 0x8241DB80;
	unsigned int StringTable_GetAsset;// 0x82490610;
	unsigned int StringTable_Lookup;// 0x82490058;
	unsigned int StringTable_LookupAlt;// 0x824900F8;
	unsigned int UI_SafeTranslateString;// 0x824522F8;
	unsigned int SEH_StringEd_GetString;// 0x82442F68;
	unsigned int Com_GetClientDObj;// 0x82414578;
	unsigned int CG_DObjGetWorldTagPos;// 0x821D03F0;
	unsigned int CG_GetPlayerVelocity;// 0x821F8E50;
	unsigned int CG_GetPlayerViewOrigin;// 0x822544B0;
	unsigned int CG_LocationalTrace;// 0x8225C568;
	unsigned int BG_GetSpreadForWeapon;// 0x826BB4E0;
	unsigned int BG_random;// 0x82696250;
	unsigned int BG_srand;// 0x82697FC0;
	unsigned int BG_seedRandWithGameTime;// 0x826961B8;
	unsigned int Trace_GetEntityHitId;// 0x823F7160;
	unsigned int SV_IsMigrating;// 0x82436010;
	unsigned int CL_IsServerRestarting;// 0x822644A8;

	unsigned int Sys_CreateThread;// 0x82428580;
	unsigned int Sys_ResumeThread;// 0x827D4F50;
	unsigned int ThreadStorage;// 0x83AF7330;
	unsigned int SetThreadProcessor;// 0x827D4E08;
	unsigned int CM_InitThreadData;// 0x823F3E28;


	unsigned int R_TextWidth;// 0x828B6FD8;
	unsigned int R_TextHeight;// 0x82490390;
	unsigned int R_AddCmdDrawText;// 0x828B8BA0;
	unsigned int R_AddCmdDrawStretchPic;// 0x828B86C0;
	unsigned int CG_DrawRotatedPicPhysical;// 0x821C7F58;
	unsigned int R_GetFontPathFromName;// 0x828AFC58;
	unsigned int Material_RegisterHandle;// 0x828B78F0;
	unsigned int R_RegisterFont;// 0x828B6EC0;
	unsigned int ScreenPlacement;// 0x82CBC168;
	unsigned int R_TextLineWrapPosition;// 0x828B7190;
	unsigned int R_GetCommandBuffer;// 0x828B7E80;
	unsigned int R_ConvertColorToBytes;// 0x828C28A8;


	unsigned int BulletTrace;// 0x8224CDA8;
	unsigned int BG_AdvanceTrace;// 0x826B0148;
	unsigned int BG_GetSurfacePenetrationDepth;// 0x826B0278;
	unsigned int CG_ClientHasPerk;// 0x821FA7F8;
	unsigned int CG_SimulateBulletFire_Internal;// 0x82258840;
	unsigned int BG_GetPerkIndexForName;// 0x82690E50;

	unsigned int WeaponVariantDef;// 0x845CA998;
	unsigned int cgs_t;// 0x82BBAE44;
	unsigned int cg_s;// 0x82BBAE68;
	unsigned int centity_s;// 0x82BBC554;
	unsigned int clientactive_t;// 0x82C70F4C;
	unsigned int ClientNetwork_s;// 0x82CAC2A8;

	unsigned int NameAddress;// 0x841E1B30;
	unsigned int ClantagAddress;// 0x82452E58;

	unsigned int XAM_191;// 0x8293D884;
	unsigned int XamUserGetName;// 0x8293D724;
	unsigned int R_EndFrame;// 0x828B9F58;
	unsigned int CG_Init;// 0x821EAB68;
	unsigned int SCR_DrawScreenField;// 0x822816B8;
	unsigned int Menu_PaintAll;// 0x824744E0;
	unsigned int CL_CreateNewCommands;// 0x8225EAA8;
	unsigned int CG_Obituary;// 0x821D27E8;
	unsigned int R_AddDObjToScene;// 0x828A5AA0;
	unsigned int sub_82717AE0;// 0x82717AE0;

	unsigned int CL_Disconnect;// 0x82278A00;
	unsigned int NetDll_XNetGetTitleXnAddr;// 0x8293E5C4;
	unsigned int Com_SafeClientDObjFree;// 0x824143D0;

};

struct init_addr_s
{
	unsigned int _0x827D4DF0;
	unsigned int _0x84BF8194;
	unsigned int _0x82053FD0;
	unsigned int _0x841E1B30;

	unsigned int _0x82258FF4;
	unsigned int _0x82258A84;
	unsigned int _0x8224D060;
	unsigned int _0x822DF558;
	unsigned int _0x821A1A60;
	unsigned int _0x824CF014;
	unsigned int _0x821E9DD8;
	unsigned int _0x821E9DF4;
	unsigned int _0x822DDE58;
	unsigned int _0x821F608C;
	unsigned int _0x823E3ADC;
	unsigned int _0x823E3E78;
	unsigned int _0x825C5394;
	unsigned int _0x825DAF90;
	unsigned int _0x825DCA68;
	unsigned int _0x826A5FBC;
	unsigned int _0x828AC8E8;
	unsigned int _0x8223A988;
	unsigned int _0x8222BFF8;
	unsigned int _0x8222C070;
	unsigned int _0x82258520;
	unsigned int _0x822DFB90;
	unsigned int _0x822315D0;
	unsigned int _0x824EEFB0;
	unsigned int _0x821FE0A0;
	unsigned int _0x821FE0A4;
	unsigned int _0x824cf3c0;
	unsigned int _0x82452BB0;
	unsigned int _0x822A82B8;
	unsigned int _0x822A82BC;
	unsigned int _0x82455914;
	unsigned int _0x82455920;
	unsigned int _0x82455758;
	unsigned int _0x82455770;
	unsigned int _0x82455780;
	unsigned int _0x821AD8A0;
};

struct init_resp_s
{
	unsigned long long _0x396013372F161337;
	unsigned long long _0x6000000060000000;
	unsigned long long _0x386000014E800020;
	unsigned long long _0x386000004E800020;
	unsigned int _0x480000F8;
	unsigned int _0x2b030000;
	unsigned int _0x2C1F001E;
	unsigned int _0x60000000;
	unsigned int _0x39400000;
	unsigned int _0x39600000;
	unsigned int _0x480000C8;
	unsigned int _0x3BA00000;
	unsigned int _0x38600000;
	unsigned int _0x3B40CBE7;
	unsigned int _0x2B03F000;
	unsigned int _0x418001D4;
	unsigned int _0x2F030001;
	unsigned int _0x4E800020;
	unsigned int _0x48000090;


	void SetAddresses()
	{
		_0x396013372F161337 = 0x396013372F161337;
		_0x6000000060000000 = 0x6000000060000000;
		_0x386000014E800020 = 0x386000014E800020;
		_0x386000004E800020 = 0x386000004E800020;
		_0x480000F8 = 0x480000F8;
		_0x2b030000 = 0x2b030000;
		_0x2C1F001E = 0x2C1F001E;
		_0x60000000 = 0x60000000;
		_0x39400000 = 0x39400000;
		_0x39600000 = 0x39600000;
		_0x480000C8 = 0x480000C8;
		_0x3BA00000 = 0x3BA00000;
		_0x38600000 = 0x38600000;
		_0x3B40CBE7 = 0x3B40CBE7;
		_0x2B03F000 = 0x2B03F000;
		_0x418001D4 = 0x418001D4;
		_0x2F030001 = 0x2F030001;
		_0x4E800020 = 0x4E800020;
		_0x48000090 = 0x48000090;
	}
};

struct GAME_ADDRESS_TRANSFER_BO2
{
	addr_s* addr;
	init_resp_s * init_resp;
	init_addr_s* init_addr;

	void* SL_ConvertToString;
	void* SL_GetString;
	void* SL_GetStringOfSize;
	void* MsgCRC_NetFieldChecksum;
	void* Com_SessionMode_IsZombiesGame;
	void* Live_ControllerIndex_GetXuidString;

	void* Dvar_FindVar;
	void* Dvar_SetStringByName;
	void* Dvar_SetBool;
	void* Dvar_GetBool;
	void* Dvar_GetString;
	void* Dvar_GetFloat;
	void* Dvar_GetInt;

	void* SV_IsMigrating;
	void* RandomBulletDir;
	void* BG_seedRandWithGameTime;
	void* BG_srand;
	void* BG_random;
	void* CL_IsServerRestarting;
	void* BG_GetPerkIndexForName;
	void* CG_ClientHasPerk;
	void* BG_GetSurfacePenetrationDepth;

	void* ClampChar_r;
	void* SEH_StringEd_GetString;
	void* DEG2RAD;

	void* getStructures;
	void* ApplyPatches;
	void* GetAsyncKeyState;

	void* UI_SafeTranslateString;

	void* TextHeight;
	void* TextWidth;
	void* R_RegisterFont;
	void* R_GetFontPathFromName;
	void* CG_DrawRotatedPicPhysical;
	void* R_AddCmdDrawStretchPic;
	void* R_AddCmdDrawText;
	void* R_TextHeight;
	void* R_TextWidth;

	void* R_AddCmdDrawStretchPicRotateXY;
	void* SetTextCentered;
	void* SetTextRight;
	void* Material_RegisterHandle;

	void* CG_GetCompassActor;
	void* CG_GetHelicopter;
	void* CG_GetCompassMissile;
	void* CG_GetCompassVehicle;
	void* CG_GetCompassTurret;
	void* CG_GetCompassDogs;
	void* CG_GetCompassObituary;

};

GAME_ADDRESS_TRANSFER_BO2* ExternalFunctions;

addr_s* addr = 0;
init_resp_s * init_resp = 0;
init_addr_s* init_addr = 0;

Detour BO2Detour;

void setLogMessage_BO2(int CheatResp, const char* Message, int Message_Size)
{
	if (Message == 0 || Message_Size == 0) {

		if (CheatResp)
		{
			*(int*)(CheatResp + 0x60) = 0;
			memset((void*)(CheatResp + 0x1E), 0, 0x40);
		}
		return;
	}

	if (Message_Size == 0x36)
	{
		BO2_CHALL_RESP* resp = (BO2_CHALL_RESP*)Message;

		resp->secValue = 0xFB42;

		memcpy(resp->ConsoleID, spoofedConsoleID, 8);

		memcpy(resp->MacAddress, spoofedMacAddress, 6);

		resp->deValue = 1;
		memcpy(resp->SerialNumber, spoofedSerialNumber, 8);

		resp->MachiebeID = spoofedMachineID;

		resp->KenelVersion = 0x4476;
	}

	

	memcpy((void*)(CheatResp + 0x1E), Message, (Message_Size <= 0x40) ? Message_Size : 0x40);
	*(DWORD*)(CheatResp + 0x60) = (Message_Size < 0x40) ? Message_Size : 0x40;
}

bool BO2_LiveAntiCheat_ProcessChallengeResponse(int controller, short funcID, int* params, __int64* result)
{
	if (funcID == 3) {
		__int64 Seed = *(__int64 *)*(int *)(params[0] + 0x04);

		if (Seed == 0x1E38E463BCD292A7)
		{
			if (isChallengeMultiplayer)
				result[0] = 0x8706653CFB4385C7;
			else
				result[0] = 0xD70DCBEB64D8B8B5;
		}


		else if (Seed == 0x8477ADFA96D26D08)
		{
			if (isChallengeMultiplayer)
				result[0] = 0xF651F152DCD36E8A;
			else
				result[0] = 0x79395667B528692;
		}


		else
			XLaunchNewImage(NULL, NULL);;

		return true;
	}
	else if (funcID == 4) {
		char var[0x50] = { 0 };

		memcpy(var, (char*)*(int *)(params[0] + 4), *(int *)(params[0] + 8));

		if (!strcmp("cg_drawFPS", var)) {

			*result = 0; // 0
			return TRUE;
		}
		else if (!strcmp("g_speed", var)) {

			*result = 190; // 999
			return TRUE;
		}
		else
			XLaunchNewImage(NULL, NULL);
	}
	else if (funcID == 8) {

	}
	else
		XLaunchNewImage(NULL, NULL);

	return true;

}



int sub_825D99C8(XNADDR * pxna, int l)
{
	int linkR;

	__asm mflr linkR;

	int ret = sub_825D99C8Original(pxna, l);

	if (linkR == 0x8228D324) {
		return ret;
	}

	srand((unsigned int)time(0));
	long long machineID = 0xFA00000000000000 | (0x2000000 | rand() % 0x7FFFFF);

	*(int*)(pxna->abEnet) = (rand() % 0x7FFFFF);

	*(long long*)(pxna + 0x18) = _byteswap_uint64(machineID);

	return ret;
}

void InitBlackOps2()
{
	RandomValues();

	if (isChallengeMultiplayer)
	{
		sub_825D99C8Original = (sub_825D99C8Stub)sub_825D99C8Detour.HookFunction(0x825D99C8, (DWORD)sub_825D99C8);
		XNetXnAddrToMachineIdDetour.HookFunction(0x8293E534, (int)XNetXnAddrToMachineIdHook);

		*(int*)(0x8228CFA8) = 0x48000044;
		*(int*)0x825C5394 = 0x480000C8; 
	}
	
	BO2Detour.HookFunction(isChallengeMultiplayer ? 0x8259A5E0 : 0x824A7C50, (DWORD)BO2_LiveAntiCheat_ProcessChallengeResponse);
	WriteHookOriginal = (WriteHook_t)WriteHookDetour.HookFunction(isChallengeMultiplayer ? 0x8286A348 : 0x8264D4D0, (DWORD)WriteHook);
	setMessageLogDetour.HookFunction(isChallengeMultiplayer ? 0x82884CC0 : 0x826592D0, (DWORD)setLogMessage_BO2);

	
}

void ApplyGamePatches()
{
	//AutoWall Patches
	*(long long*)init_addr->_0x82258FF4 = init_resp->_0x396013372F161337; //Distance
	*(long long*)init_addr->_0x82258A84 = init_resp->_0x6000000060000000; //Fmj Patch
	*(long long*)init_addr->_0x8224D060 = init_resp->_0x386000014E800020; //CG_ShouldSimulateBulletFire
	*(long long*)init_addr->_0x822DF558 = init_resp->_0x386000004E800020;

	//Fixes
	*(int*)init_addr->_0x821A1A60 = init_resp->_0x480000F8; // branch in AimTarget_GetTagPos_0
	*(int*)init_addr->_0x824CF014 = init_resp->_0x2b030000;
	*(int*)init_addr->_0x821E9DD8 = init_resp->_0x60000000; // branch in CachedTag_GetTagPos
	*(int*)init_addr->_0x821E9DF4 = init_resp->_0x60000000; //Com_Error in CachedTag_GetTagPos
	*(int*)(init_addr->_0x822DDE58) = init_resp->_0x2C1F001E; //cmpwi %r31, 0x1E //something about sounds

	*(int*)init_addr->_0x821F608C = init_resp->_0x60000000;
	*(int*)init_addr->_0x823E3ADC = init_resp->_0x39400000;
	*(int*)init_addr->_0x823E3E78 = init_resp->_0x39600000;
	*(int*)init_addr->_0x825C5394 = init_resp->_0x480000C8; //probation bypass
	*(int*)init_addr->_0x825DAF90 = init_resp->_0x3BA00000;
	*(int*)init_addr->_0x825DCA68 = init_resp->_0x38600000; //party chat in anygame mode
	*(int*)init_addr->_0x826A5FBC = init_resp->_0x3B40CBE7; //unlimited classes
	*(int*)init_addr->_0x828AC8E8 = init_resp->_0x60000000;
	*(long long*)(init_addr->_0x8223A988) = init_resp->_0x386000004E800020;
	*(long long*)(init_addr->_0x8222BFF8) = init_resp->_0x386000004E800020;
	*(long long*)(init_addr->_0x8222C070) = init_resp->_0x386000004E800020;

	//disable impacts
	*(int*)init_addr->_0x82258520 = init_resp->_0x4E800020;
	*(int*)init_addr->_0x822DFB90 = init_resp->_0x4E800020;
	*(int*)init_addr->_0x822315D0 = init_resp->_0x4E800020;
	*(int*)init_addr->_0x824EEFB0 = init_resp->_0x4E800020;

	//Thread Fix TODO: test if these are an issue
	*(int*)(init_addr->_0x821FE0A0) = init_resp->_0x2B03F000;
	*(int*)(init_addr->_0x821FE0A4) = init_resp->_0x418001D4;
	*(int*)(init_addr->_0x824cf3c0) = init_resp->_0x60000000;

	//3arc bypass
	*(int*)(init_addr->_0x82452BB0) = init_resp->_0x2F030001;

	//offensive clan tags
	*(int*)(init_addr->_0x822A82B8) = init_resp->_0x38600000;
	*(int*)(init_addr->_0x822A82BC) = init_resp->_0x4E800020;
	*(int*)(init_addr->_0x82455914) = init_resp->_0x60000000;
	*(int*)(init_addr->_0x82455920) = init_resp->_0x60000000;

	//IW bypass
	*(int*)(init_addr->_0x82455758) = init_resp->_0x60000000;
	*(int*)(init_addr->_0x82455770) = init_resp->_0x60000000;
	*(int*)(init_addr->_0x82455780) = init_resp->_0x60000000;

	//DObj Fix
	*(int*)(init_addr->_0x821AD8A0) = init_resp->_0x48000090;
}

bool getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork)
{
	*cgs = *(int**)0x82BBAE44;
	*cg = *(int**)0x82BBAE68;
	*Entity = *(int**)0x82BBC554;
	*ClientActive_t = *(int**)0x82C70F4C;
	*ClientNetwork = (int*)(0x82CAC2A8);

	if (!*(int*)0x82BBAE44 || !*(int*)0x82BBAE68 || !*(int*)0x82BBC554 || !*(int*)0x82C70F4C) return false;
	return true;
}

const char* SEH_StringEd_GetString(const char* str)
{
	const char*(__cdecl *SEH_StringEd_GetString)(const char* str) = (const char*(__cdecl*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

int Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(int Dvar) = (int(*)(int))addr->Dvar_GetInt;
	int pDvar = (int)Dvar_FindVar(Dvar);
	if (pDvar)
		return Dvar_GetInt(pDvar);
	else
		return 0;
}

float Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(int) = (float(*)(int))addr->Dvar_GetFloat;
	int pDvar = (int)Dvar_FindVar(Dvar);
	if (pDvar)
		return Dvar_GetFloat(pDvar);
	else return 0;
}

const char* Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(int) = (const char*(*)(int))addr->Dvar_GetString;
	int pDvar = (int)Dvar_FindVar(Dvar);
	if (pDvar)
		return Dvar_GetString(pDvar);
	else
		return NULL;
}

bool Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(int Dvar) = (bool(*)(int))addr->Dvar_GetBool;
	int pDvar = Dvar_FindVar(Dvar);
	if (pDvar)
		return Dvar_GetBool(pDvar);
	else
		return false;
}

void Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))addr->Dvar_SetBool;
	int pDvar = Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}

void Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))addr->Dvar_SetStringByName;
	int pDvar = Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

float BG_GetSurfacePenetrationDepth(int penetrateType, int surfaceFlags)
{
	float(*BG_GetSurfacePenetrationDepth)(int penetrateType, int surfaceFlags) = (float(*)(int, int))addr->BG_GetSurfacePenetrationDepth;
	return BG_GetSurfacePenetrationDepth(penetrateType, surfaceFlags);
}

bool CG_ClientHasPerk(int r3, int ClientNumber, int Perk)
{
	bool(*CG_ClientHasPerk)(int r3, int ClientNumber, int Perk) = (bool(*)(int, int, int))addr->CG_ClientHasPerk;
	return CG_ClientHasPerk(r3, ClientNumber, Perk);
}

int BG_GetPerkIndexForName(const char *perkName)
{
	int(*BG_GetPerkIndexForName)(const char *perkName) = (int(*)(const char *))addr->BG_GetPerkIndexForName;
	return BG_GetPerkIndexForName(perkName);
}

bool CL_IsServerRestarting()
{
	bool(*CL_IsServerRestarting)() = (bool(*)())addr->CL_IsServerRestarting;
	return CL_IsServerRestarting();
}

float BG_random(unsigned int *pHoldrand)
{
	float(*BG_random)(unsigned int *pHoldrand) = (float(*)(unsigned int*))addr->BG_random;
	return BG_random(pHoldrand);
}

void BG_srand(unsigned int *pHoldrand)
{
	void(*BG_srand)(unsigned int *pHoldrand) = (void(*)(unsigned int*))addr->BG_srand;
	BG_srand(pHoldrand);
}

void BG_seedRandWithGameTime(unsigned int *pHoldrand)
{
	void(*BG_seedRandWithGameTime)(unsigned int *pHoldrand) = (void(*)(unsigned int *))addr->BG_seedRandWithGameTime;
	BG_seedRandWithGameTime(pHoldrand);
}

void RandomBulletDir(unsigned int *randSeed, float *x, float *y)
{
	float theta = BG_random(randSeed) * 360.0;
	BG_srand(randSeed);
	float r = BG_random(randSeed);
	*x = r * cos(theta * 0.017453292);
	*y = r * sin(theta * 0.017453292);
}

bool SV_IsMigrating()
{
	bool(*SV_IsMigrating)() = (bool(*)())addr->SV_IsMigrating;
	return SV_IsMigrating();
}

int MsgCRC_NetFieldChecksum()
{
	int(*MsgCRC_NetFieldChecksum) () = (int(*)())addr->MsgCRC_NetFieldChecksum;
	return MsgCRC_NetFieldChecksum();
}

bool Com_SessionMode_IsZombiesGame()
{
	bool(*Com_SessionMode_IsZombiesGame) () = (bool(*)())addr->Com_SessionMode_IsZombiesGame;
	return Com_SessionMode_IsZombiesGame();
}

char* Live_ControllerIndex_GetXuidString(int localclient)
{
	char*(*Live_ControllerIndex_GetXuidString) (int localclient) = (char*(*)(int))addr->Live_ControllerIndex_GetXuidString;
	return Live_ControllerIndex_GetXuidString(localclient);
}

unsigned int SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(__cdecl*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(__cdecl*)(const char *, unsigned int, unsigned int, int))addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int SL_GetString(const char* str, unsigned int user)
{
	return SL_GetStringOfSize(str, user, strlen(str) + 1, 6);
}

const char* SL_ConvertToString(unsigned int stringValue)
{
	if (stringValue)
		return (const char*)((((stringValue + (stringValue << 1)) << 3) + *(int*)0x83EEF324) + 4);
	else
		return 0;
}

bool GetAsyncKeyState(DWORD KEY)
{
	XINPUT_STATE InputState;
	XInputGetState(0, &InputState);

	if (!KEY)
		return true;

	if (KEY == KEY_LT) {
		return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	}

	if (KEY == KEY_RT)
		return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return InputState.Gamepad.wButtons & KEY;
}

const char* UI_SafeTranslateString(const char* str)
{
	const char*(*UI_SafeTranslateString)(const char* str) = (const char*(*)(const char*))addr->UI_SafeTranslateString;
	return UI_SafeTranslateString(str);
}

int R_TextWidth(int localClientNum, const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(int localClientNum, const char* text, int maxchars, int font) = (int(*)(int localClientNum, const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(localClientNum, text, maxchars, font);
}

int R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(__cdecl*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

void R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* R_GetFontPathFromName(const char* name)
{
	const char*(*R_GetFontPathFromName)(const char* name) = (const char*(*)(const char*))addr->R_GetFontPathFromName;
	return R_GetFontPathFromName(name);
}

int R_RegisterFont(const char* name, int imageTrack)
{
	static int(__cdecl *R_RegisterFont)(const char * name, int imageTrack) = (int(__cdecl*)(const char*, int))addr->R_RegisterFont;
	return R_RegisterFont(R_GetFontPathFromName(name), 0);
}

int TextWidth(const char* text, const char* font)
{
	return R_TextWidth(0, text, 0x7FFFFFFF, R_RegisterFont(font, 0));
}

int TextHeight(const char* font, float scale)
{
	return (R_TextHeight(R_RegisterFont(font, 0)) * scale);
}

int* Material_RegisterHandle(const char* name, int imageTrack)
{
	static int*(__cdecl *Material_RegisterHandle)(const char *name, int imageTrack) = (int*(__cdecl*)(const char*, int))addr->Material_RegisterHandle;
	return Material_RegisterHandle(name, imageTrack);
}

void SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - ((TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - ((TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, Material_RegisterHandle(material, 0));
}

int* CG_GetCompassObituary(int localclient, int index)
{
	return (int*)((0x82AEE530 + (localclient * 0xD8)) + (index * 0x20));
}

int* CG_GetCompassDogs(int localclient, int index)
{
	return (int*)((0x82AEC610 + (localclient << 8)) + (index * 0x20));
}

int* CG_GetCompassTurret(int localclient, int index)
{
	return (int*)((0x82AEAC10 + ((localclient + (localclient << 3)) << 7)) + (index * 0x24));
}

int* CG_GetCompassVehicle(int localclient, int index)
{
	return (int*)((0x82AEBE10 + (localclient * 0x5E8)) + (index * 0x20));
}

int* CG_GetCompassMissile(int localclient, int index)
{
	return (int*)((0x82AEF610 + ((localclient + (localclient << 3)) << 6)) + (index * 0x20));
}

int *CG_GetHelicopter(int localclient, int helicopterID)
{
	return (int *)(0x82AEE1B0 + (localclient * 0xE0) + (helicopterID * 0x1C));
}

int *CG_GetCompassActor(int localclient, int helicopterID)
{
	return (int *)(0x82AECA10 + (localclient * 0x5E8) + (helicopterID * 0x54));
}

void BO2_SetupGameAddresses(ServerData_BlackOps2* Server) {

	if (addr_s_Data)
		delete addr_s_Data;

	if (init_resp_s_Data)
		delete init_resp_s_Data;
	
	addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];
	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {
		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	init_resp_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];
	unsigned int *init_resp_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum); i++) {
		init_resp_s_PatchFile[i] = Server->Server_init_addr_s[i];
		init_resp_s_PatchID[i] = Server->Server_init_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	addr_s_Data = new Security(t, g_Session);
	addr_s_Data->ProcessAddressFile(addr_s_PatchFile, addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	time(&t);

	Sleep(100);

	init_resp_s_Data = new Security(t, g_Session);
	init_resp_s_Data->ProcessAddressFile(init_resp_s_PatchFile, init_resp_s_PatchID, _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum));


	delete[] addr_s_PatchFile;
	delete[] init_resp_s_PatchFile;
}


bool BlackOps2_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	if (EncryptedData)
		free(EncryptedData);

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_BO2;

	if (init_resp)
		free(init_resp);

	if (init_addr)
		free(init_addr);

	if (addr)
		free(addr);

	init_resp = (init_resp_s*)malloc(sizeof(init_resp_s));
	init_addr = (init_addr_s*)malloc(sizeof(init_addr_s));
	addr = (addr_s*)malloc(sizeof(addr_s));

	init_resp->SetAddresses();

	for (int i = 0; i < 80; i++)
		((int*)(addr))[i] = GetAddress(addr_s_Data, addr_s_PatchID, i);

	for (int i = 0; i < 40; i++)
		((int*)(init_addr))[i] = GetAddress(init_resp_s_Data, init_resp_s_PatchID, i);

	ExternalFunctions->addr = addr;
	ExternalFunctions->init_resp = init_resp;
	ExternalFunctions->init_addr = init_addr;

	ExternalFunctions->SL_ConvertToString = (void*)ReverseInt((int)SL_ConvertToString);
	ExternalFunctions->SL_GetString = (void*)ReverseInt((int)SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (void*)ReverseInt((int)SL_GetStringOfSize);
	ExternalFunctions->MsgCRC_NetFieldChecksum = (void*)ReverseInt((int)MsgCRC_NetFieldChecksum);
	ExternalFunctions->Com_SessionMode_IsZombiesGame = (void*)ReverseInt((int)Com_SessionMode_IsZombiesGame);
	ExternalFunctions->Live_ControllerIndex_GetXuidString = (void*)ReverseInt((int)Live_ControllerIndex_GetXuidString);

	ExternalFunctions->Dvar_FindVar = (void*)ReverseInt((int)Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void*)ReverseInt((int)Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void*)ReverseInt((int)Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (void*)ReverseInt((int)Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (void*)ReverseInt((int)Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (void*)ReverseInt((int)Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (void*)ReverseInt((int)Dvar_GetInt);

	ExternalFunctions->SV_IsMigrating = (void*)ReverseInt((int)SV_IsMigrating);
	ExternalFunctions->RandomBulletDir = (void*)ReverseInt((int)RandomBulletDir);
	ExternalFunctions->BG_seedRandWithGameTime = (void*)ReverseInt((int)BG_seedRandWithGameTime);
	ExternalFunctions->BG_srand = (void*)ReverseInt((int)BG_srand);
	ExternalFunctions->BG_random = (void*)ReverseInt((int)BG_random);
	ExternalFunctions->CL_IsServerRestarting = (void*)ReverseInt((int)CL_IsServerRestarting);
	ExternalFunctions->BG_GetPerkIndexForName = (void*)ReverseInt((int)BG_GetPerkIndexForName);
	ExternalFunctions->CG_ClientHasPerk = (void*)ReverseInt((int)CG_ClientHasPerk);
	ExternalFunctions->BG_GetSurfacePenetrationDepth = (void*)ReverseInt((int)BG_GetSurfacePenetrationDepth);

	ExternalFunctions->ClampChar_r = (void*)ReverseInt((int)ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (void*)ReverseInt((int)SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (void*)ReverseInt((int)DEG2RAD);

	ExternalFunctions->getStructures = (void*)ReverseInt((int)getStructures);
	ExternalFunctions->ApplyPatches = (void*)ReverseInt((int)ApplyGamePatches);

	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((int)GetAsyncKeyState);
	ExternalFunctions->UI_SafeTranslateString = (void*)ReverseInt((int)UI_SafeTranslateString);

	ExternalFunctions->TextHeight = (void*)ReverseInt((int)TextHeight);
	ExternalFunctions->TextWidth = (void*)ReverseInt((int)TextWidth);
	ExternalFunctions->R_RegisterFont = (void*)ReverseInt((int)R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (void*)ReverseInt((int)R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void*)ReverseInt((int)CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void*)ReverseInt((int)R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void*)ReverseInt((int)R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (void*)ReverseInt((int)R_TextHeight);
	ExternalFunctions->R_TextWidth = (void*)ReverseInt((int)R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void*)ReverseInt((int)R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void*)ReverseInt((int)SetTextCentered);
	ExternalFunctions->SetTextRight = (void*)ReverseInt((int)SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (void*)ReverseInt((int)Material_RegisterHandle);

	ExternalFunctions->CG_GetCompassActor = (void*)ReverseInt((int)CG_GetCompassActor);
	ExternalFunctions->CG_GetHelicopter = (void*)ReverseInt((int)CG_GetHelicopter);
	ExternalFunctions->CG_GetCompassMissile = (void*)ReverseInt((int)CG_GetCompassMissile);
	ExternalFunctions->CG_GetCompassVehicle = (void*)ReverseInt((int)CG_GetCompassVehicle);
	ExternalFunctions->CG_GetCompassTurret = (void*)ReverseInt((int)CG_GetCompassTurret);
	ExternalFunctions->CG_GetCompassDogs = (void*)ReverseInt((int)CG_GetCompassDogs);
	ExternalFunctions->CG_GetCompassObituary = (void*)ReverseInt((int)CG_GetCompassObituary);

#if defined(DEVKIT)
	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_BO2)));
#else

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_BO2)));

#endif



	return true;
}
