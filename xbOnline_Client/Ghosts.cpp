#include "main.h"

Security * Ghosts_addr_s_Data = 0;
unsigned int *Ghosts_addr_s_PatchID = 0;

void Ghosts_SetupGameAddresses(ServerData_Ghosts* Server)
{
	if (Ghosts_addr_s_Data)
		delete Ghosts_addr_s_Data;

	Ghosts_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		Ghosts_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	Ghosts_addr_s_Data = new Security(t, g_Session);
	Ghosts_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, Ghosts_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}


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

struct addr_s
{
	//Dvars
	unsigned int Dvar_FindVar;
	unsigned int Dvar_GetBool;
	unsigned int Dvar_SetBool;
	unsigned int Dvar_GetInt;
	unsigned int Dvar_GetFloat;
	unsigned int Dvar_GetString;
	unsigned int Dvar_SetStringByName;

	//string tables
	unsigned int SL_GetStringOfSize;
	unsigned int SL_ConvertToString;

	//Misc
	unsigned int CG_GameMessage;
	unsigned int CG_BoldGameMessage;
	unsigned int Cbuf_AddText;
	unsigned int CL_AddReliableCommand;
	unsigned int CG_VisionSetStartLerp_To;
	unsigned int UI_GetMapName;
	unsigned int UI_GetGameTypeName;
	unsigned int SEH_StringEd_GetString;
	unsigned int Com_GetClientDObj;
	unsigned int CG_DObjGetWorldTagPos;
	unsigned int CG_GetPlayerVelocity;
	unsigned int CG_GetPlayerViewOrigin;
	unsigned int CG_LocationalTrace;
	unsigned int BG_GetSpreadForWeapon;
	unsigned int TransformSeed;
	unsigned int RandomBulletDir;
	unsigned int Trace_GetEntityHitId;
	unsigned int SV_IsMigrating;
	unsigned int CL_IsServerRestarting;
	unsigned int CG_PlayRumbleOnClient;
	unsigned int UI_PlaySound;
	unsigned int BG_GetAmmoInClip;

	//Drawing
	unsigned int R_TextWidth;
	unsigned int R_TextHeight;
	unsigned int R_AddCmdDrawText;
	unsigned int R_AddCmdDrawStretchPic;
	unsigned int CG_DrawRotatedPicPhysical;
	unsigned int Material_RegisterHandle;
	unsigned int R_RegisterFont;
	unsigned int ScreenPlacement;
	unsigned int R_TextLineWrapPosition;
	unsigned int R_ConvertColorToBytes;

	//Structs
	unsigned int WeaponDef;
	unsigned int WeaponVariantDef;
	unsigned int cgs_t;
	unsigned int cg_s;
	unsigned int centity_s;
	unsigned int clientactive_t;
	unsigned int ClientNetwork_s;
	unsigned int clientUIActive;

	//AutoWall
	unsigned int BulletTrace;
	unsigned int BG_AdvanceTrace;
	unsigned int BG_GetSurfacePenetrationDepth;
	unsigned int CG_ClientHasPerk;
	unsigned int FireBulletPenetrate;
	unsigned int BG_GetPerkIndexForName;

	//Name shit
	unsigned int NameAddress;
	unsigned int ClantagAddress;

	//Hooks
	unsigned int XAM_191;
	unsigned int RB_SetTessTechnique;
	unsigned int R_EndFrame;
	unsigned int SCR_DrawScreenField;
	unsigned int Menu_PaintAll;
	unsigned int CL_WritePacket;
	unsigned int CG_Obituary;
	unsigned int CL_Disconnect;
	unsigned int Com_Error;
	unsigned int CL_CreateNewCommand;

	//Misc
	unsigned int AngleNormalize360;
	unsigned int YawVectors2D;
	unsigned int CL_ClientIsInMyParty;
	unsigned int CalcCompassFriendlySize;
	unsigned int SERVER_ID;
	unsigned int BG_EvaluateTrajectory;
	unsigned int CG_GetVelocity;
	unsigned int Sys_EnterCriticalSection;
	unsigned int Sys_LeaveCriticalSection;
	unsigned int CG_IsSelectingLocation;
	unsigned int VehicleCl_IsClientValid;
	unsigned int VehicleCl_GetClientDef;

	unsigned int _0x8204B874;
	unsigned int _0x83D51E20;
	unsigned int _0x8431C270;
	unsigned int _0x84445380;
	unsigned int _0x00002000;
	unsigned int _0x00000040;
	unsigned int _0x00000004;
	unsigned int _0x0000000C;
	unsigned int _0x00000002;
	unsigned int _0x842BE2AC;
	unsigned int _0x00000008;
	unsigned int _0x00000038;
	unsigned int _0x00000010;
	unsigned int _0x00000014;
	unsigned int _0x00000018;
	unsigned int _0x0000001C;
	unsigned int _0x00000020;
	unsigned int _0x00000024;
	unsigned int _0x00000028;
	unsigned int _0x0000002C;
	unsigned int _0x00000030;
	unsigned int _0x00000034;
	unsigned int _0x0000003C;
	unsigned int _0x8265A6C0;
	unsigned int _0x82732100;
	unsigned int _0x82AC1188;
	unsigned int _0x00000D10;
	unsigned int _0x0000004C;
	unsigned int _0x00040000;
	unsigned int _0x82ACCD00;
	unsigned int _0x000003BC;
	unsigned int _0x000003B8;
	unsigned int _0x82AC0EC8;
	unsigned int _0x00000160;
	unsigned int _0x82AC0008;
	unsigned int _0x000000E0;
	unsigned int _0x00000088;
	unsigned int _0x840F07D0;
	unsigned int _0x00000680;
	unsigned int _0x82AC01C8;
	unsigned int _0x8225FB08;
	unsigned int _0x8228B8F0;
	unsigned int _0x822C73C0;
	unsigned int _0x82385B38;
	unsigned int _0x4E800020;
	unsigned int _0x7D8802A6;
	unsigned int _0x000C6448;
	unsigned int _0x00803003;
	unsigned int _0x8266ABA8;
	unsigned int _0x8431C278;
	unsigned int _0x8431C274;
	unsigned int _0x00001868;
	unsigned int _0x842BC180;
	unsigned int _0x842BC184;
	unsigned int _0x842BC188;
	unsigned int _0x842BC18C;
	unsigned int _0x82482168;
	unsigned int _0x000000FF;
	unsigned int _0x844DD004;
	unsigned int _0x82686220;
	unsigned int _0x00000021;
	unsigned int _0x82ACCADC;
	unsigned int _0x822583D0;
	unsigned int _0x82258BEC;
	unsigned int _0x82258BE0;
	unsigned int _0x82258BF8;
	unsigned int _0x82258C04;
	unsigned int _0x822C9344;
	unsigned int _0x4BFFEAA1;
	unsigned int _0x4BFFFBA5;
	unsigned int _0x4BFFDED9;
	unsigned int _0x4BFFFD49;
	unsigned int _0x4BFFFEC5;
	unsigned int _0x4BF8AE4D;
	unsigned int _0x60000000;
	unsigned int _0x822654C8;
	unsigned int _0x8227F19B;
	unsigned int _0x3B600001;
	unsigned int _0x551B7FFE;
	unsigned int _0x8220D778;
	unsigned int _0x8220DA60;
	unsigned int _0x8220D8B0;

//#ifdef DEVKIT
//	void SetAddresses()
//	{
//		Dvar_FindVar = 0x825637E0;
//		Dvar_GetBool = 0x825639B0;
//		Dvar_SetBool = 0x825667C8;
//		Dvar_GetInt = 0x82563A18;
//		Dvar_GetFloat = 0x82563A80;
//		Dvar_GetString = 0x82563AF0;
//		Dvar_SetStringByName = 0x825670E0;
//		SL_GetStringOfSize = 0x824934D8;
//		SL_ConvertToString = 0x82492318;
//		CG_GameMessage = 0x82282090;
//		CG_BoldGameMessage = 0x822820F0;
//		Cbuf_AddText = 0x8244C738;
//		CL_AddReliableCommand = 0x822D8F88;
//		CG_VisionSetStartLerp_To = 0x822B74A8;
//		UI_GetMapName = 0x82527AD0;
//		UI_GetGameTypeName = 0x82527CF8;
//		SEH_StringEd_GetString = 0x82526538;
//		Com_GetClientDObj = 0x824723D8;
//		CG_DObjGetWorldTagPos = 0x82273BC8;
//		CG_GetPlayerVelocity = 0x0; //Not Used
//		CG_GetPlayerViewOrigin = 0x822BC078;
//		CG_LocationalTrace = 0x822CB3B0;
//		BG_GetSpreadForWeapon = 0x82254700;
//		TransformSeed = 0x82234840;
//		RandomBulletDir = 0x82430F10;
//		Trace_GetEntityHitId = 0x82443F98;
//		SV_IsMigrating = 0x824E0C68;
//		CL_IsServerRestarting = 0x822CDE20;
//		CG_PlayRumbleOnClient = 0x82296FA0;
//		UI_PlaySound = 0x82726738;
//		BG_GetAmmoInClip = 0x8222C618;
//		R_TextWidth = 0x8264DC78;
//		R_TextHeight = 0x8264DD70;
//		R_AddCmdDrawText = 0x8266CEB8;
//		R_AddCmdDrawStretchPic = 0x8266AF28;
//		CG_DrawRotatedPicPhysical = 0x82270138;
//		Material_RegisterHandle = 0x8265A470;
//		R_RegisterFont = 0x8264DBF0;
//		ScreenPlacement = 0x82BCDD10;
//		R_TextLineWrapPosition = 0x8264DDB8;
//		R_ConvertColorToBytes = 0x82683280;
//		WeaponDef = 0x8213EDE0;
//		WeaponVariantDef = 0x82143408;
//		cgs_t = 0x82AD56F8;
//		cg_s = 0x82AD56FC;
//		centity_s = 0x82AD11AC;
//		clientUIActive = 0x82BAC408;
//		clientactive_t = 0x82BAC404;
//		ClientNetwork_s = 0x82BBD5D8;
//		BulletTrace = 0x822BC168;
//		BG_AdvanceTrace = 0x82253CC8;
//		BG_GetSurfacePenetrationDepth = 0x82249270;
//		CG_ClientHasPerk = 0x0; //not used
//		FireBulletPenetrate = 0x822C7518;
//		BG_GetPerkIndexForName = 0x8222BE48;
//		NameAddress = 0x83F0A35C;
//		ClantagAddress = 0x82BB6896;
//		XAM_191 = 0x828103EC;
//		RB_SetTessTechnique = 0x0; //not used
//		R_EndFrame = 0x8266BFE0;
//		SCR_DrawScreenField = 0x822E6C60;
//		Menu_PaintAll = 0x8253E140;
//		CL_WritePacket = 0x822D68C0;
//		CG_Obituary = 0x82276650;
//		CL_Disconnect = 0x822DD3C8;
//		Com_Error = 0x824712B8;
//		CL_CreateNewCommand = 0x822D67E8;
//		AngleNormalize360 = 0x82552EC0;
//		YawVectors2D = 0x82551B20;
//		CL_ClientIsInMyParty = 0x8228DC48;
//		CalcCompassFriendlySize = 0x8225FC18;
//		SERVER_ID = 0x82F2B28;
//		BG_EvaluateTrajectory = 0x0;
//		CG_GetVelocity = 0x82237738;
//		Sys_EnterCriticalSection = 0x82573DC0;
//		Sys_LeaveCriticalSection = 0x82573DD8;
//		CG_IsSelectingLocation = 0x8225F300;
//		VehicleCl_IsClientValid = 0x825E54B0;
//		VehicleCl_GetClientDef = 0x825E5548;
//
//		_0x8204B874 = 0x8204B874;
//		_0x83D51E20 = 0x83D51E20;
//		_0x8431C270 = 0x8431C270;
//		_0x84445380 = 0x84445380;
//		_0x00002000 = 0x00002000;
//		_0x00000040 = 0x00000040;
//		_0x00000004 = 0x00000004;
//		_0x0000000C = 0x0000000C;
//		_0x00000002 = 0x00000002;
//		_0x842BE2AC = 0x842BE2AC;
//		_0x00000008 = 0x00000008;
//		_0x00000038 = 0x00000038;
//		_0x00000010 = 0x00000010;
//		_0x00000014 = 0x00000014;
//		_0x00000018 = 0x00000018;
//		_0x0000001C = 0x0000001C;
//		_0x00000020 = 0x00000020;
//		_0x00000024 = 0x00000024;
//		_0x00000028 = 0x00000028;
//		_0x0000002C = 0x0000002C;
//		_0x00000030 = 0x00000030;
//		_0x00000034 = 0x00000034;
//		_0x0000003C = 0x0000003C;
//		_0x8265A6C0 = 0x8265A6C0;
//		_0x82732100 = 0x82732100;
//		_0x82AC1188 = 0x82AC1188;
//		_0x00000D10 = 0x00000D10;
//		_0x0000004C = 0x0000004C;
//		_0x00040000 = 0x00040000;
//		_0x82ACCD00 = 0x82ACCD00;
//		_0x000003BC = 0x000003BC;
//		_0x000003B8 = 0x000003B8;
//		_0x82AC0EC8 = 0x82AC0EC8;
//		_0x00000160 = 0x00000160;
//		_0x82AC0008 = 0x82AC0008;
//		_0x000000E0 = 0x000000E0;
//		_0x00000088 = 0x00000088;
//		_0x840F07D0 = 0x840F07D0;
//		_0x00000680 = 0x00000680;
//		_0x82AC01C8 = 0x82AC01C8;
//		_0x8225FB08 = 0x8225FB08;
//		_0x8228B8F0 = 0x8228B8F0;
//		_0x822C73C0 = 0x822C73C0;
//		_0x82385B38 = 0x82385B38;
//		_0x4E800020 = 0x4E800020;
//		_0x7D8802A6 = 0x7D8802A6;
//		_0x000C6448 = 0x000C6448;
//		_0x00803003 = 0x00803003;
//		_0x8266ABA8 = 0x8266ABA8;
//		_0x8431C278 = 0x8431C278;
//		_0x8431C274 = 0x8431C274;
//		_0x00001868 = 0x00001868;
//		_0x842BC180 = 0x842BC180;
//		_0x842BC184 = 0x842BC184;
//		_0x842BC188 = 0x842BC188;
//		_0x842BC18C = 0x842BC18C;
//		_0x82482168 = 0x82482168;
//		_0x000000FF = 0x000000FF;
//		_0x844DD004 = 0x844DD004;
//		_0x82686220 = 0x82686220;
//		_0x00000021 = 0x00000021;
//		_0x82ACCADC = 0x82ACCADC;
//		_0x822583D0 = 0x822583D0;
//		_0x82258BEC = 0x82258BEC;
//		_0x82258BE0 = 0x82258BE0;
//		_0x82258BF8 = 0x82258BF8;
//		_0x82258C04 = 0x82258C04;
//		_0x822C9344 = 0x822C9344;
//		_0x4BFFEAA1 = 0x4BFFEAA1;
//		_0x4BFFFBA5 = 0x4BFFFBA5;
//		_0x4BFFDED9 = 0x4BFFDED9;
//		_0x4BFFFD49 = 0x4BFFFD49;
//		_0x4BFFFEC5 = 0x4BFFFEC5;
//		_0x4BF8AE4D = 0x4BF8AE4D;
//		_0x60000000 = 0x60000000;
//		_0x822654C8 = 0x822654C8;
//		_0x8227F19B = 0x8227F19B;
//		_0x3B600001 = 0x3B600001;
//		_0x551B7FFE = 0x551B7FFE;
//		_0x8220D778 = 0x8220D778;
//		_0x8220DA60 = 0x8220DA60;
//		_0x8220D8B0 = 0x8220D8B0;
//	}
//#endif
};

struct GAME_ADDRESS_TRANSFER_GO
{
	addr_s* addr;

	void* SL_ConvertToString;
	void* SL_GetString;
	void* SL_GetStringOfSize;
	void* Dvar_FindVar;
	void* Dvar_SetStringByName;
	void* Dvar_SetBool;
	void* Dvar_GetBool;
	void* Dvar_GetString;
	void* Dvar_GetFloat;
	void* Dvar_GetInt;
	void* ClampChar_r;
	void* SEH_StringEd_GetString;
	void* DEG2RAD;
	void* getStructures;
	void* ApplyPatches;
	void* GetAsyncKeyState;
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
	void* RandomBulletDir;
	void* CG_GoodRandomFloat;
	void* TransformSeed;
	void* CL_DrawStretchPicRotatedST;
	void* R_AddCmdDrawStretchPicRotateST;

};

struct Material
{
	const char* Name;//0x00
};

enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

#define M_PI 3.141592653589793f

addr_s* ghosts_addr;
GAME_ADDRESS_TRANSFER_GO* ExternalFunctions = 0;

void Ghosts_ApplyGamePatches();
const char* Ghosts_SL_ConvertToString(unsigned int stringValue);
unsigned int Ghosts_SL_GetString(const char* str, unsigned int user);
unsigned int Ghosts_SL_GetStringOfSize(const char *str, int user, int length, int type);
void Ghosts_RandomBulletDir(int* randSeed, float *x, float *y);
float Ghosts_CG_GoodRandomFloat(int *pHoldrand);
int Ghosts_TransformSeed(int *pHoldrand);
int Ghosts_Dvar_FindVar(const char* Dvar);
void Ghosts_Dvar_SetStringByName(const char* Dvar, const char*  val);
void Ghosts_Dvar_SetBool(const char* Dvar, bool val);
bool Ghosts_Dvar_GetBool(const char* Dvar);
const char* Ghosts_Dvar_GetString(const char* Dvar);
float Ghosts_Dvar_GetFloat(const char* Dvar);
int Ghosts_Dvar_GetInt(const char* Dvar);
char Ghosts_ClampChar_r(const int i);
const char* Ghosts_SEH_StringEd_GetString(const char* str);
float Ghosts_DEG2RAD(float DEG);
bool Ghosts_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive);
bool Ghosts_GetAsyncKeyState(DWORD KEY);
int Ghosts_TextHeight(const char* font, float scale);
int Ghosts_TextWidth(const char* text, const char* font);
int Ghosts_R_RegisterFont(const char* name, int imageTrack);
const char* Ghosts_R_GetFontPathFromName(const char* name);
void Ghosts_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, Material* material);
void Ghosts_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, Material* material);
void Ghosts_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
int Ghosts_R_TextHeight(int font);
int Ghosts_R_TextWidth(const char* text, int maxchars, int font);
Material* Ghosts_Material_RegisterHandle(const char* name, int imageTrack);
void Ghosts_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void Ghosts_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void Ghosts_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);
void Ghosts_CL_DrawStretchPicRotatedST(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material);
void Ghosts_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material);

Material* Ghosts_Material_RegisterHandle(const char* name, int imageTrack)
{
	Material*(*Material_RegisterHandle)(const char *name, int imageTrack) = (Material*(*)(const char*, int))ghosts_addr->Material_RegisterHandle;
	return Material_RegisterHandle(name, imageTrack);
}

void Ghosts_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	Ghosts_R_AddCmdDrawText(text, 0x7FFFFFFF, Ghosts_R_RegisterFont(font, 0), (x - ((Ghosts_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void Ghosts_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	Ghosts_R_AddCmdDrawText(text, 0x7FFFFFFF, Ghosts_R_RegisterFont(font, 0), (x - ((Ghosts_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void Ghosts_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	Ghosts_CG_DrawRotatedPicPhysical(ghosts_addr->ScreenPlacement, x, y, w, h, Angle, color, Ghosts_Material_RegisterHandle(material, 0));
}

int Ghosts_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))ghosts_addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

int Ghosts_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(*)(int))ghosts_addr->R_TextHeight;
	return R_TextHeight(font);
}

void Ghosts_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))ghosts_addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void Ghosts_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, Material* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, Material* material) = (void(*)(float, float, float, float, float, float, float, float, float*, Material*))ghosts_addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void Ghosts_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, Material* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, Material* material) = (void(*)(int, float, float, float, float, float, float*, Material*))ghosts_addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* Ghosts_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

int Ghosts_R_RegisterFont(const char* name, int imageTrack)
{
	static int(*R_RegisterFont)(const char * name, int imageTrack) = (int(*)(const char*, int))ghosts_addr->R_RegisterFont;
	return R_RegisterFont(Ghosts_R_GetFontPathFromName(name), 0);
}

int Ghosts_TextWidth(const char* text, const char* font)
{
	return Ghosts_R_TextWidth(text, 0x7FFFFFFF, Ghosts_R_RegisterFont(font, 0));
}

int Ghosts_TextHeight(const char* font, float scale)
{
	return (Ghosts_R_TextHeight(Ghosts_R_RegisterFont(font, 0)) * scale);
}

bool Ghosts_GetAsyncKeyState(DWORD KEY)
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

	return (InputState.Gamepad.wButtons & KEY);
}


bool Ghosts_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive)
{
	*clientUIActive = (int*)ghosts_addr->clientUIActive;
	*cgs = *(int**)ghosts_addr->cgs_t;
	*cg = *(int**)ghosts_addr->cg_s;
	*Entity = *(int**)ghosts_addr->centity_s;
	*ClientActive_t = *(int**)ghosts_addr->clientactive_t;
	*ClientNetwork = (int*)ghosts_addr->ClientNetwork_s;

	if (!*(int*)ghosts_addr->cgs_t || !*(int*)ghosts_addr->cg_s || !*(int*)ghosts_addr->centity_s || !*(int*)ghosts_addr->clientactive_t) return false;
	return true;
}

const char* Ghosts_SEH_StringEd_GetString(const char* str)
{
	const char*(*SEH_StringEd_GetString)(const char* str) = (const char*(*)(const char*))ghosts_addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char Ghosts_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float Ghosts_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int Ghosts_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char*))ghosts_addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

float Ghosts_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char*) = (float(*)(const char*))ghosts_addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

const char* Ghosts_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char*) = (const char*(*)(const char*))ghosts_addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

bool Ghosts_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char*))ghosts_addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

void Ghosts_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))ghosts_addr->Dvar_SetBool;
	int pDvar = Ghosts_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}


void Ghosts_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))ghosts_addr->Dvar_SetStringByName;
	int pDvar = Ghosts_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

int Ghosts_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))ghosts_addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

unsigned int Ghosts_SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(*)(const char *, unsigned int, unsigned int, int))ghosts_addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int Ghosts_SL_GetString(const char* str, unsigned int user)
{
	return Ghosts_SL_GetStringOfSize(str, user, strlen(str) + 1, 7);
}

const char* Ghosts_SL_ConvertToString(unsigned int stringValue)
{
	const char*(*SL_ConvertToString)(unsigned int stringValue) = (const char*(*)(unsigned int stringValue))ghosts_addr->SL_ConvertToString;
	return SL_ConvertToString(stringValue);
}


void Ghosts_ApplyGamePatches()
{
	*(int*)(*(int*)(0x82B141E0) + 0xC) = 100; //cl_maxpackets
	int snaps = Ghosts_Dvar_FindVar("snaps");
	if (snaps != 0)
		*(int*)(snaps + 0xC) = 40; //snaps
	int rate = Ghosts_Dvar_FindVar("rate");
	if (rate != 0)
		*(int*)(rate + 0xC) = 25000; //rate

									 //disable impacts
	*(int*)0x822C73C0 = 0x4E800020;
	*(int*)0x82385B38 = 0x4E800020;

	//Misc
	*(char*)(*(int*)(0x82ADE840) + 0x0C) = 0x01; //cg_scoreboardPingText
}

int Ghosts_TransformSeed(int *pHoldrand)
{
	*pHoldrand = 214013 * (214013 * (214013 * (214013 * *pHoldrand + 2531011) + 2531011) + 2531011) + 2531011;

	return *pHoldrand;
}

float Ghosts_CG_GoodRandomFloat(int *pHoldrand)
{
	/* Generating random value based on seed */
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11; /* Applying value to seed for next usage */
	return (r11 >> 17) * 0.000030517578; /* Returning shifted value */
}

void Ghosts_RandomBulletDir(int* randSeed, float *x, float *y)
{
	float f26 = (Ghosts_CG_GoodRandomFloat(randSeed) * 360.0f) * (M_PI / 180.0f);
	float f28 = Ghosts_CG_GoodRandomFloat(randSeed);
	*x = f28 * cosf(f26); // sin
	*y = f28 * sinf(f26); // cos
}

void Ghosts_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material)
{
	int r11 = *(DWORD*)ghosts_addr->_0x8431C270;
	if ((signed int)(((*(DWORD *)(r11 + 8) - *(DWORD *)(r11 + 4)) + *(DWORD*)ghosts_addr->_0x84445380) - ghosts_addr->_0x00002000) >= ghosts_addr->_0x00000040)
	{
		int r31 = (*(DWORD*)(r11)+*(DWORD*)(r11 + ghosts_addr->_0x00000004));

		*(DWORD*)(r11 + ghosts_addr->_0x00000004) = (*(DWORD*)(r11 + ghosts_addr->_0x00000004) + ghosts_addr->_0x00000040);
		*(DWORD*)(r11 + ghosts_addr->_0x0000000C) = r31;
		*(WORD*)(r31) = ghosts_addr->_0x0000000C;
		*(WORD*)(r31 + ghosts_addr->_0x00000002) = ghosts_addr->_0x00000040;
		Material* materialPointer = material;
		if (!material)
			materialPointer = *(Material**)ghosts_addr->_0x842BE2AC;
		*(float*)(r31 + ghosts_addr->_0x00000008) = x;
		*(Material**)(r31 + ghosts_addr->_0x00000004) = materialPointer;
		DWORD* r4 = (DWORD *)(r31 + ghosts_addr->_0x00000038);
		*(float*)(r31 + ghosts_addr->_0x0000000C) = y;
		*(float*)(r31 + ghosts_addr->_0x00000010) = w;
		*(float*)(r31 + ghosts_addr->_0x00000014) = h;
		*(float*)(r31 + ghosts_addr->_0x00000018) = centerS;
		*(float*)(r31 + ghosts_addr->_0x0000001C) = centerT;
		*(float*)(r31 + ghosts_addr->_0x00000020) = radiusST;
		*(float*)(r31 + ghosts_addr->_0x00000024) = scaleFinalS;
		*(float*)(r31 + ghosts_addr->_0x00000028) = s1;
		*(float*)(r31 + ghosts_addr->_0x0000002C) = t1;
		*(float*)(r31 + ghosts_addr->_0x00000030) = s2;
		*(float*)(r31 + ghosts_addr->_0x00000034) = t2;
		if (colour)
			((void(*)(...))ghosts_addr->R_ConvertColorToBytes)(colour, r4); //R_ConvertColorToBytes
		else
			*r4 = -1;
		((void(*)(...))ghosts_addr->AngleNormalize360)(Angle); //Normalize Angle
		*(float*)(r31 + ghosts_addr->_0x0000003C) = Angle;
	}
	else
		*(DWORD*)(r11 + ghosts_addr->_0x0000000C) = 0;
}

void Ghosts_CL_DrawStretchPicRotatedST(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material)
{
	((void(*)(...))ghosts_addr->_0x8265A6C0)(material, &s1, &t1, &s2, &t2);
	Ghosts_R_AddCmdDrawStretchPicRotateST(x, y, w, h, centerS, centerT, radiusST, scaleFinalS, s1, t1, s2, t2, Angle, colour, material);
}

bool Ghosts_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_GO;

	if (ghosts_addr)
		free(ghosts_addr);

	ghosts_addr = (addr_s*)malloc(sizeof(addr_s));
	
	for (int i = 0; i < 161; i++)
		((int*)(ghosts_addr))[i] = GetAddress(Ghosts_addr_s_Data, Ghosts_addr_s_PatchID, i);

	ExternalFunctions->addr = ghosts_addr;
	ExternalFunctions->SL_ConvertToString = (const char*(*)(unsigned int))(void*)ReverseInt((int)Ghosts_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (unsigned int(*)(const char*, unsigned int))(void*)ReverseInt((int)Ghosts_SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (unsigned int(*)(const char *, int, int, int))(void*)ReverseInt((int)Ghosts_SL_GetStringOfSize);

	ExternalFunctions->Dvar_FindVar = (int(*)(const char* Dvar))(void*)ReverseInt((int)Ghosts_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void(*)(const char* Dvar, const char*  val))(void*)ReverseInt((int)Ghosts_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void(*)(const char* Dvar, bool val))(void*)ReverseInt((int)Ghosts_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (bool(*)(const char* Dvar))(void*)ReverseInt((int)Ghosts_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (const char*(*)(const char* Dvar))(void*)ReverseInt((int)Ghosts_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (float(*)(const char* Dvar))(void*)ReverseInt((int)Ghosts_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (int(*)(const char* Dvar))(void*)ReverseInt((int)Ghosts_Dvar_GetInt);

	ExternalFunctions->ClampChar_r = (char(*)(const int i))(void*)ReverseInt((int)Ghosts_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (const char* (*)(const char* str))(void*)ReverseInt((int)Ghosts_SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (float(*)(float DEG))(void*)ReverseInt((int)Ghosts_DEG2RAD);
	ExternalFunctions->getStructures = (bool(*)(int**, int**, int**, int**, int**, int**))(void*)ReverseInt((int)Ghosts_getStructures);
	ExternalFunctions->ApplyPatches = (int(*)())(void*)ReverseInt((int)Ghosts_ApplyGamePatches);
	ExternalFunctions->GetAsyncKeyState = (bool(*)(DWORD KEY))(void*)ReverseInt((int)Ghosts_GetAsyncKeyState);

	ExternalFunctions->TextHeight = (int(*)(const char* font, float scale))(void*)ReverseInt((int)Ghosts_TextHeight);
	ExternalFunctions->TextWidth = (int(*)(const char* text, const char* font))(void*)ReverseInt((int)Ghosts_TextWidth);
	ExternalFunctions->R_RegisterFont = (int(*)(const char* name, int imageTrack))(void*)ReverseInt((int)Ghosts_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (const char* (*)(const char* name))(void*)ReverseInt((int)Ghosts_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void(*)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material))(void*)ReverseInt((int)Ghosts_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void(*)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material))(void*)ReverseInt((int)Ghosts_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void(*)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style))(void*)ReverseInt((int)Ghosts_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (int(*)(int font))(void*)ReverseInt((int)Ghosts_R_TextHeight);
	ExternalFunctions->R_TextWidth = (int(*)(const char* text, int maxchars, int font))(void*)ReverseInt((int)Ghosts_R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void(*)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material))(void*)ReverseInt((int)Ghosts_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void(*)(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A))(void*)ReverseInt((int)Ghosts_SetTextCentered);
	ExternalFunctions->SetTextRight = (void(*)(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A))(void*)ReverseInt((int)Ghosts_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (int* (*)(const char* name, int imageTrack))(void*)ReverseInt((int)Ghosts_Material_RegisterHandle);

	ExternalFunctions->RandomBulletDir = (void(*)(int* randSeed, float *x, float *y))(void*)ReverseInt((int)Ghosts_RandomBulletDir);
	ExternalFunctions->CG_GoodRandomFloat = (float(*)(int *pHoldrand))(void*)ReverseInt((int)Ghosts_CG_GoodRandomFloat);
	ExternalFunctions->TransformSeed = (int(*)(int *pHoldrand))(void*)ReverseInt((int)Ghosts_TransformSeed);
	ExternalFunctions->CL_DrawStretchPicRotatedST = (void(*)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material))(void*)ReverseInt((int)Ghosts_CL_DrawStretchPicRotatedST);
	ExternalFunctions->R_AddCmdDrawStretchPicRotateST = (void(*)(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, Material* material))(void*)ReverseInt((int)Ghosts_R_AddCmdDrawStretchPicRotateST);

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_GO)));

	return true;
}