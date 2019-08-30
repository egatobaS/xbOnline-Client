#include "main.h"

void AW_CL_DrawStretchPicRotatedST(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, int* material);
void AW_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, int* material);
float AngleNormalize360(float angle);
int R_GetCommandBuffer(int renderCmd, int bytes);
void AW_RandomBulletDir(int* randSeed, float *x, float *y);
double AW_CG_GoodRandomFloat(int *pHoldrand);
int AW_TransformSeed(int *pHoldrand);
void ApplyGamePatches();
const char* AW_SL_ConvertToString(unsigned int stringValue);
unsigned int AW_SL_GetString(const char* str, unsigned int user);
unsigned int AW_SL_GetStringOfSize(const char *str, int user, int length, int type);
int AW_Dvar_FindVar(const char* Dvar);
void AW_Dvar_SetStringByName(const char* Dvar, const char*  val);
void AW_Dvar_SetBool(const char* Dvar, bool val);
bool AW_Dvar_GetBool(const char* Dvar);
const char* AW_Dvar_GetString(const char* Dvar);
float AW_Dvar_GetFloat(const char* Dvar);
int AW_Dvar_GetInt(const char* Dvar);
float AW_DEG2RAD(float DEG);
char AW_ClampChar_r(const int i);
const char* AW_SEH_StringEd_GetString(const char* str);
bool AW_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive);
bool AW_GetAsyncKeyState(DWORD KEY);
int AW_TextHeight(const char* font, float scale);
int AW_TextWidth(const char* text, const char* font);
int AW_R_RegisterFont(const char* name, int imageTrack);
const char* AW_R_GetFontPathFromName(const char* name);
void AW_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material);
void AW_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material);
void AW_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
int AW_R_TextHeight(int font);
int AW_R_TextWidth(const char* text, int maxchars, int font);
void AW_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);
void AW_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void AW_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
int* AW_Material_RegisterHandle(const char* name, int imageTrack);
void AW_ApplyGamePatches();

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

		resp->KernelVersion = 0x4488;

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


Security * aw_addr_s_Data = 0;

unsigned int *aw_addr_s_PatchID = 0;


struct aw_addr_s
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
	unsigned int PlayRumbleInternal;
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
	unsigned int DB_FindXAssetHeader;
	unsigned int ScreenPlacement;
	unsigned int R_TextLineWrapPosition;
	unsigned int R_ConvertColorToBytes;
	unsigned int R_AddCmdDrawQuadPic;

	//Structs
	unsigned int WeaponDef;
	unsigned int WeaponVariantDef;
	unsigned int cgs_t;
	unsigned int cg_s;
	unsigned int centity_s;
	unsigned int clientactive_t;
	unsigned int ClientNetwork_s;
	unsigned int clientUIActive;
	unsigned int uicontext;

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
	unsigned int CL_CreateNewCommand;
	unsigned int CG_Obituary;
	unsigned int CL_Disconnect;
	unsigned int Com_Error;

	//Misc
	unsigned int YawVectors2D;
	unsigned int CL_ClientIsInMyParty;
	unsigned int CalcCompassFriendlySize;
	unsigned int SERVER_ID;
	unsigned int BG_EvaluateTrajectory;
	unsigned int CG_GetVelocity;
	unsigned int Sys_EnterCriticalSection;
	unsigned int Sys_LeaveCriticalSection;
	unsigned int xboxkrnl_125;
	unsigned int xboxkrnl_130;
	unsigned int CG_IsSelectingLocation;
	unsigned int VehicleCl_IsClientValid;
	unsigned int VehicleCl_GetClientDef;


	unsigned int _0x82AADAB0;
	unsigned int _0x00001130;
	unsigned int _0x00000064;
	unsigned int _0x04000000;
	unsigned int _0x82AAD7F0;
	unsigned int _0x00000160;
	unsigned int _0x0000002C;
	unsigned int _0x000000E0;
	unsigned int _0x82AAC930;
	unsigned int _0x000001F4;
	unsigned int _0x84474DB0;
	unsigned int _0x00000088;
	unsigned int _0x84475630;
	unsigned int _0x82AACAF0;
	unsigned int _0x00000680;
	unsigned int _0x00000034;
	unsigned int _0x000007FF;
	unsigned int _0x82608AD8;
	unsigned int _0x82636998;
	unsigned int _0x00008000;
	unsigned int _0x00000200;
	unsigned int _0x4E800020;
	unsigned int _0x7D8802A6;
	unsigned int _0x84334BE8;
	unsigned int _0x0000001C;
	unsigned int _0x82058EB0;
	unsigned int _0x00803003;
	unsigned int _0x000468F0;
	unsigned int _0x00000030;
	unsigned int _0x842F2E88;
	unsigned int _0x82293788;
	unsigned int _0x846EB0F0;
	unsigned int _0x846A9EB4;
	unsigned int _0x000018D8;
	unsigned int _0x8464ED04;
	unsigned int _0x821440B0;
	unsigned int _0x83B2E774;
	unsigned int _0x8495F580;
	unsigned int _0x8227EAD8;
	unsigned int _0x00000021;
	unsigned int _0x826404D0;
	unsigned int _0x82640418;
	unsigned int _0x8264040C;
	unsigned int _0x82640424;
	unsigned int _0x82640430;
	unsigned int _0x82648AD8;
	unsigned int _0x829AAEB4;
	unsigned int _0x0000000C;
	unsigned int _0x60000000;
	unsigned int _0x4BFFFD39;
	unsigned int _0x4BFFFC59;
	unsigned int _0x4BFFE4E5;
	unsigned int _0x4BFFF6E5;
	unsigned int _0x4BFFF5E1;
	unsigned int _0x825D22F8;
	unsigned int _0x82535D78;
	unsigned int _0x826352A8;
	unsigned int _0x825D88E8;
	unsigned int _0x5519EFFE;
	unsigned int _0x419A0044;
	unsigned int _0x8268F5E8;
	unsigned int _0x8268F504;
	unsigned int _0x8268FED0;
	unsigned int _0x4BFA8E89;
	unsigned int _0x4BFAA33D;
	unsigned int _0x00000040;
	unsigned int _0x00000066;
	unsigned int _0x0000001F;
	unsigned int _0x000004D6;
	unsigned int _0x3B800001;
	unsigned int _0x00000005;
	unsigned int _0x83B309EC;
	unsigned int _0x82B0D2E8;
	unsigned int _0x84652444;
	unsigned int _0x00000008;
	unsigned int _0x00000010;
	unsigned int _0x00000014;
	unsigned int _0x00000018;
	unsigned int _0x00000020;
	unsigned int _0x00000024;
	unsigned int _0x00000028;
	unsigned int _0x00000038;
	unsigned int _0x0000003C;
	unsigned int _0x822A0FC8;


	//void SetAddresses()
	//{
	//	Dvar_FindVar = 0x82364638;
	//	Dvar_GetBool = 0x82364D40;
	//	Dvar_SetBool = 0x82366648;
	//	Dvar_GetInt = 0x82364CF0;
	//	Dvar_GetFloat = 0x82364C98;
	//	Dvar_GetString = 0x82364C30;
	//	Dvar_SetStringByName = 0x823677D8;
	//	SL_GetStringOfSize = 0x8242FD70;
	//	SL_ConvertToString = 0x0; //inline
	//	CG_GameMessage = 0x826130F8;
	//	CG_BoldGameMessage = 0x82613090;
	//	Cbuf_AddText = 0x82472B80;
	//	CL_AddReliableCommand = 0x825AB430;
	//	CG_VisionSetStartLerp_To = 0x0; //
	//	UI_GetMapName = 0x8246F5C0;
	//	UI_GetGameTypeName = 0x8246FA48;
	//	SEH_StringEd_GetString = 0x82452D58;
	//	Com_GetClientDObj = 0x8260DAB8;
	//	CG_DObjGetWorldTagPos = 0x82623E10;
	//	CG_GetPlayerVelocity = 0x0; //Not Used
	//	CG_GetPlayerViewOrigin = 0x825D39C0;
	//	CG_LocationalTrace = 0x825C1D20;
	//	BG_GetSpreadForWeapon = 0x82647658;
	//	TransformSeed = 0x0; //inline
	//	RandomBulletDir = 0x0;
	//	Trace_GetEntityHitId = 0x0; //inline
	//	SV_IsMigrating = 0x0; //inline
	//	CL_IsServerRestarting = 0x0; //not present
	//	PlayRumbleInternal = 0x825FD2D8; //PlayRumbleInternal 0x825D5928
	//	UI_PlaySound = 0x8221DC40;
	//	BG_GetAmmoInClip = 0x820F0168;
	//	R_TextWidth = 0x822AC770;
	//	R_TextHeight = 0x821BBF00;
	//	R_AddCmdDrawText = 0x82295F60;
	//	R_AddCmdDrawStretchPic = 0x822951E8;
	//	CG_DrawRotatedPicPhysical = 0x826289C0;
	//	Material_RegisterHandle = 0x0; //inline
	//	R_RegisterFont = 0x0; //inline
	//	DB_FindXAssetHeader = 0x82544098;
	//	R_AddCmdDrawQuadPic = 0x82294BC8;
	//	ScreenPlacement = 0x82B94570;
	//	R_TextLineWrapPosition = 0x822AC570;
	//	R_ConvertColorToBytes = 0x8227FA00;
	//	WeaponDef = 0x820F01D0;
	//	WeaponVariantDef = 0x0; //not used
	//	cgs_t = 0x82ACFE34;
	//	cg_s = 0x82AD0298;
	//	centity_s = 0x82ACFE30;
	//	clientUIActive = 0x82B0D310;
	//	clientactive_t = 0x82B0D308;
	//	ClientNetwork_s = 0x82B7E608;
	//	BulletTrace = 0x825CDA20;
	//	BG_AdvanceTrace = 0x826415E8;
	//	BG_GetSurfacePenetrationDepth = 0x8264BEF0;
	//	CG_ClientHasPerk = 0x0; //not used
	//	FireBulletPenetrate = 0x825D2420;
	//	BG_GetPerkIndexForName = 0x82795560;
	//	NameAddress = 0x843DECB4;
	//	ClantagAddress = 0x82B777C2;
	//	XAM_191 = 0x827D35B4;
	//	RB_SetTessTechnique = 0x0; //not used
	//	R_EndFrame = 0x822967C8;
	//	SCR_DrawScreenField = 0x825A55C8;
	//	Menu_PaintAll = 0x823884D8;
	//	CL_WritePacket = 0x825B7358;
	//	CL_CreateNewCommand = 0x825B79D8;
	//	CG_Obituary = 0x8261DC70;
	//	CL_Disconnect = 0x825B0078;
	//	Com_Error = 0x82450EF8;

	//	YawVectors2D = 0x82378B98;
	//	CL_ClientIsInMyParty = 0x8258C960;
	//	CalcCompassFriendlySize = 0x826368B0;
	//	SERVER_ID = 0x82B4F1D4;
	//	BG_EvaluateTrajectory = 0x82670560;
	//	CG_GetVelocity = 0x820FE910;
	//	Sys_EnterCriticalSection = 0x0; //inline
	//	Sys_LeaveCriticalSection = 0x0; //inline
	//	xboxkrnl_125 = 0x827D3694;
	//	xboxkrnl_130 = 0x827D36A4;
	//	CG_IsSelectingLocation = 0x0; //inline 0x823AA3C8
	//	VehicleCl_IsClientValid = 0x822FCA50;
	//	VehicleCl_GetClientDef = 0x0; //inline
	//	uicontext = 0x841B0280;




	//	_0x82AADAB0 = 0x82AADAB0;
	//	_0x00001130 = 0x00001130;
	//	_0x00000064 = 0x00000064;
	//	_0x04000000 = 0x04000000;
	//	_0x82AAD7F0 = 0x82AAD7F0;
	//	_0x00000160 = 0x00000160;
	//	_0x0000002C = 0x0000002C;
	//	_0x000000E0 = 0x000000E0;
	//	_0x82AAC930 = 0x82AAC930;
	//	_0x000001F4 = 0x000001F4;
	//	_0x84474DB0 = 0x84474DB0;
	//	_0x00000088 = 0x00000088;
	//	_0x84475630 = 0x84475630;
	//	_0x82AACAF0 = 0x82AACAF0;
	//	_0x00000680 = 0x00000680;
	//	_0x00000034 = 0x00000034;
	//	_0x000007FF = 0x000007FF;
	//	_0x82608AD8 = 0x82608AD8;
	//	_0x82636998 = 0x82636998;
	//	_0x00008000 = 0x00008000;
	//	_0x00000200 = 0x00000200;
	//	_0x4E800020 = 0x4E800020;
	//	_0x7D8802A6 = 0x7D8802A6;
	//	_0x84334BE8 = 0x84334BE8;
	//	_0x0000001C = 0x0000001C;
	//	_0x82058EB0 = 0x82058EB0;
	//	_0x00803003 = 0x00803003;
	//	_0x000468F0 = 0x000468F0;
	//	_0x00000030 = 0x00000030;
	//	_0x842F2E88 = 0x842F2E88;
	//	_0x82293788 = 0x82293788;
	//	_0x846EB0F0 = 0x846EB0F0;
	//	_0x846A9EB4 = 0x846A9EB4;
	//	_0x000018D8 = 0x000018D8;
	//	_0x8464ED04 = 0x8464ED04;
	//	_0x821440B0 = 0x821440B0;
	//	_0x83B2E774 = 0x83B2E774;
	//	_0x8495F580 = 0x8495F580;
	//	_0x8227EAD8 = 0x8227EAD8;
	//	_0x00000021 = 0x00000021;
	//	_0x826404D0 = 0x826404D0;
	//	_0x82640418 = 0x82640418;
	//	_0x8264040C = 0x8264040C;
	//	_0x82640424 = 0x82640424;
	//	_0x82640430 = 0x82640430;
	//	_0x82648AD8 = 0x82648AD8;
	//	_0x829AAEB4 = 0x829AAEB4;
	//	_0x0000000C = 0x0000000C;
	//	_0x60000000 = 0x60000000;
	//	_0x4BFFFD39 = 0x4BFFFD39;
	//	_0x4BFFFC59 = 0x4BFFFC59;
	//	_0x4BFFE4E5 = 0x4BFFE4E5;
	//	_0x4BFFF6E5 = 0x4BFFF6E5;
	//	_0x4BFFF5E1 = 0x4BFFF5E1;
	//	_0x825D22F8 = 0x825D22F8;
	//	_0x82535D78 = 0x82535D78;
	//	_0x826352A8 = 0x826352A8;
	//	_0x825D88E8 = 0x825D88E8;
	//	_0x5519EFFE = 0x5519EFFE;
	//	_0x419A0044 = 0x419A0044;
	//	_0x8268F5E8 = 0x8268F5E8;
	//	_0x8268F504 = 0x8268F504;
	//	_0x8268FED0 = 0x8268FED0;
	//	_0x4BFA8E89 = 0x4BFA8E89;
	//	_0x4BFAA33D = 0x4BFAA33D;
	//	_0x00000040 = 0x00000040;

	//	_0x00000066 = 0x00000066;
	//	_0x0000001F = 0x0000001F;
	//	_0x000004D6 = 0x000004D6;
	//	_0x3B800001 = 0x3B800001;


	//	_0x00000005 = 0x00000005;
	//	_0x83B309EC = 0x83B309EC;
	//	_0x82B0D2E8 = 0x82B0D2E8;
	//	_0x84652444 = 0x84652444;
	//	_0x00000008 = 0x00000008;
	//	_0x00000010 = 0x00000010;
	//	_0x00000014 = 0x00000014;
	//	_0x00000018 = 0x00000018;
	//	_0x00000020 = 0x00000020;
	//	_0x00000024 = 0x00000024;
	//	_0x00000028 = 0x00000028;
	//	_0x00000038 = 0x00000038;
	//	_0x0000003C = 0x0000003C;
	//	_0x822A0FC8 = 0x822A0FC8;
	//}

};



enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct GAME_ADDRESS_TRANSFER_AW
{
	aw_addr_s* addr;

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

GAME_ADDRESS_TRANSFER_AW* ExternalFunctions = 0;
aw_addr_s* addr = 0;



bool AW_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_AW;

	if (addr)
		free(addr);

	addr = (aw_addr_s*)malloc(sizeof(aw_addr_s));

	for (int i = 0; i < 167; i++)
		((int*)(addr))[i] = GetAddress(aw_addr_s_Data, aw_addr_s_PatchID, i);

	ExternalFunctions->addr = addr;
	
	ExternalFunctions->SL_ConvertToString = (void*)ReverseInt((unsigned int) AW_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (void*)ReverseInt((unsigned int) AW_SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (void*)ReverseInt((unsigned int) AW_SL_GetStringOfSize);

	ExternalFunctions->Dvar_FindVar = (void*)ReverseInt((unsigned int) AW_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void*)ReverseInt((unsigned int) AW_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void*)ReverseInt((unsigned int) AW_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (void*)ReverseInt((unsigned int) AW_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (void*)ReverseInt((unsigned int) AW_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (void*)ReverseInt((unsigned int) AW_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (void*)ReverseInt((unsigned int) AW_Dvar_GetInt);

	ExternalFunctions->ClampChar_r = (void*)ReverseInt((unsigned int) AW_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (void*)ReverseInt((unsigned int) AW_SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (void*)ReverseInt((unsigned int) AW_DEG2RAD);
	ExternalFunctions->getStructures = (void*)ReverseInt((unsigned int) AW_getStructures);
	ExternalFunctions->ApplyPatches = (void*)ReverseInt((unsigned int)AW_ApplyGamePatches);
	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((unsigned int) AW_GetAsyncKeyState);

	ExternalFunctions->TextHeight = (void*)ReverseInt((unsigned int) AW_TextHeight);
	ExternalFunctions->TextWidth = (void*)ReverseInt((unsigned int) AW_TextWidth);
	ExternalFunctions->R_RegisterFont = (void*)ReverseInt((unsigned int) AW_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (void*)ReverseInt((unsigned int) AW_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void*)ReverseInt((unsigned int) AW_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void*)ReverseInt((unsigned int) AW_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void*)ReverseInt((unsigned int) AW_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (void*)ReverseInt((unsigned int) AW_R_TextHeight);
	ExternalFunctions->R_TextWidth = (void*)ReverseInt((unsigned int) AW_R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void*)ReverseInt((unsigned int) AW_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void*)ReverseInt((unsigned int) AW_SetTextCentered);
	ExternalFunctions->SetTextRight = (void*)ReverseInt((unsigned int) AW_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (void*)ReverseInt((unsigned int) AW_Material_RegisterHandle);

	ExternalFunctions->RandomBulletDir = (void*)ReverseInt((unsigned int) AW_RandomBulletDir);
	ExternalFunctions->CG_GoodRandomFloat = (void*)ReverseInt((unsigned int) AW_CG_GoodRandomFloat);
	ExternalFunctions->TransformSeed = (void*)ReverseInt((unsigned int) AW_TransformSeed);

	ExternalFunctions->CL_DrawStretchPicRotatedST = (void*)ReverseInt((unsigned int)  AW_CL_DrawStretchPicRotatedST);
	ExternalFunctions->R_AddCmdDrawStretchPicRotateST = (void*)ReverseInt((unsigned int) AW_R_AddCmdDrawStretchPicRotateST);


	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((unsigned int)(int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((unsigned int)(int)sizeof(GAME_ADDRESS_TRANSFER_AW)));

	return true;
}


int* AW_Material_RegisterHandle(const char* name, int imageTrack)
{
	int(*DB_FindXAssetHeader)(int type, const char* name, int allowCreateDefault) = (int(*)(int, const char*, int))addr->DB_FindXAssetHeader;
	return (int*)DB_FindXAssetHeader(0x05, name, 1);
}

void AW_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	AW_R_AddCmdDrawText(text, 0x7FFFFFFF, AW_R_RegisterFont(font, 0), (x - ((AW_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void AW_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	AW_R_AddCmdDrawText(text, 0x7FFFFFFF, AW_R_RegisterFont(font, 0), (x - ((AW_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void AW_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	AW_CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, AW_Material_RegisterHandle(material, 0));
}

int AW_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

int AW_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

void AW_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void AW_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void AW_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* AW_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

int AW_R_RegisterFont(const char* name, int imageTrack)
{
	int(*DB_FindXAssetHeader)(int type, const char* name, int allowCreateDefault) = (int(*)(int, const char*, int))addr->DB_FindXAssetHeader;
	return DB_FindXAssetHeader(0x1C, AW_R_GetFontPathFromName(name), 1);
}

int AW_TextWidth(const char* text, const char* font)
{
	return AW_R_TextWidth(text, 0x7FFFFFFF, AW_R_RegisterFont(font, 0));
}

int AW_TextHeight(const char* font, float scale)
{
	return (AW_R_TextHeight(AW_R_RegisterFont(font, 0)) * scale);
}

bool AW_GetAsyncKeyState(DWORD KEY)
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


bool AW_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive)
{
	*clientUIActive = (int*)addr->clientUIActive;
	*cgs = *(int**)addr->cgs_t;
	*cg = *(int**)addr->cg_s;
	*Entity = *(int**)addr->centity_s;
	*ClientActive_t = *(int**)addr->clientactive_t;
	*ClientNetwork = (int*)addr->ClientNetwork_s;

	if (!*(int*)addr->cgs_t || !*(int*)addr->cg_s || !*(int*)addr->centity_s || !*(int*)addr->clientactive_t) return false;
	return true;
}

const char* AW_SEH_StringEd_GetString(const char* str)
{
	const char*(*SEH_StringEd_GetString)(const char* str) = (const char*(*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char AW_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float AW_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int AW_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char*))addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

float AW_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char*) = (float(*)(const char*))addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

const char* AW_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char*) = (const char*(*)(const char*))addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

bool AW_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char*))addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

void AW_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))addr->Dvar_SetBool;
	int pDvar = AW_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}


void AW_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))addr->Dvar_SetStringByName;
	int pDvar = AW_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

int AW_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

unsigned int AW_SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(*)(const char *, unsigned int, unsigned int, int))addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int AW_SL_GetString(const char* str, unsigned int user)
{
	return AW_SL_GetStringOfSize(str, user, strlen(str) + 1, 7);
}

const char* AW_SL_ConvertToString(unsigned int stringValue)
{
	if (stringValue)
		return (const char*)((*(int*)(addr->_0x83B309EC) + (stringValue << 4)) + 0x4);
	return 0;
}


void AW_ApplyGamePatches()
{
	*(int*)(*(int*)(addr->_0x82B0D2E8) + 0xC) = 100; //cl_maxpackets
	int snaps = AW_Dvar_FindVar("snaps");
	if (snaps != 0)
		*(int*)(snaps + 0xC) = 40; //snaps
	int rate = AW_Dvar_FindVar("rate");
	if (rate != 0)
		*(int*)(rate + 0xC) = 25000; //rate

									 //disable impacts
	*(int*)addr->_0x825D22F8 = addr->_0x4E800020; //CG_DrawImpacts
	*(int*)addr->_0x82535D78 = addr->_0x4E800020;

	//offensive clan tags
	//*(int*)(0x82309A30) = addr->_0x38600001;
	//*(int*)(0x82182C10) = addr->_0x38600001;
	//*(int*)(0x82182C14) = addr->_0x4E800020;
	//*(int*)(0x82309B84) = addr->_0x60000000;
	//*(int*)(0x82309B90) = addr->_0x60000000;
	//*(int*)(0x8217E8D8) = addr->_0x38600001;
	//*(int*)(0x8247C590) = addr->_0x38600001;
}

int AW_TransformSeed(int *pHoldrand)
{
	*pHoldrand = 214013 * (214013 * (214013 * (214013 * *pHoldrand + 2531011) + 2531011) + 2531011) + 2531011;

	return *pHoldrand;
}

double AW_CG_GoodRandomFloat(int *pHoldrand)
{
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11;
	return (double)(r11 >> 17) * 0.000030517578;
}

void AW_RandomBulletDir(int* randSeed, float *x, float *y)
{
	float f26 = (AW_CG_GoodRandomFloat(randSeed) * 360.0f) * (3.141592653589793f / 180.0f);
	float f28 = AW_CG_GoodRandomFloat(randSeed);
	*x = f28 * cosf(f26); // sin
	*y = f28 * sinf(f26); // cos
}

int R_GetCommandBuffer(int renderCmd, int bytes)
{
	int(*R_GetCommandBuffer)(int renderCmd, int bytes) = (int(*)(int renderCmd, int bytes))addr->_0x82293788;
	return R_GetCommandBuffer(renderCmd, bytes);
}

float AngleNormalize360(float angle) {
	if ((angle >= 360.0f) || (angle < 0.0f)) {
		angle -= floorf(angle * (1.0f / 360.0f)) * 360.0f;
	}
	return angle;
}

void AW_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, int* material)
{
	int r31 = R_GetCommandBuffer(0xD, addr->_0x00000040);
	if (r31)
	{
		int* materialPointer = material;
		if (!material)
			materialPointer = *(int**)addr->_0x84652444;
		*(int**)(r31 + 0x4) = materialPointer;

		*(float*)(r31 + addr->_0x00000008) = x;
		*(float*)(r31 + addr->_0x0000000C) = y;
		*(float*)(r31 + addr->_0x00000010) = w;
		*(float*)(r31 + addr->_0x00000014) = h;
		*(float*)(r31 + addr->_0x00000018) = centerS;
		*(float*)(r31 + addr->_0x0000001C) = centerT;
		*(float*)(r31 + addr->_0x00000020) = radiusST;
		*(float*)(r31 + addr->_0x00000024) = scaleFinalS;
		*(float*)(r31 + addr->_0x00000028) = s1;
		*(float*)(r31 + addr->_0x0000002C) = t1;
		*(float*)(r31 + addr->_0x00000030) = s2;
		*(float*)(r31 + addr->_0x00000034) = t2;

		DWORD* r4 = (DWORD *)(r31 + addr->_0x00000038);
		if (colour)
			((void(*)(...))addr->R_ConvertColorToBytes)(colour, r4); //R_ConvertColorToBytes
		else
			*r4 = -1;
		AngleNormalize360(Angle); //Normalize Angle
		*(float*)(r31 + addr->_0x0000003C) = Angle;
	}
}

void AW_CL_DrawStretchPicRotatedST(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float s1, float t1, float s2, float t2, float Angle, float* colour, int* material)
{
	((void(*)(...))addr->_0x822A0FC8)(material, &s1, &t1, &s2, &t2);
	AW_R_AddCmdDrawStretchPicRotateST(x, y, w, h, centerS, centerT, radiusST, scaleFinalS, s1, t1, s2, t2, Angle, colour, material);
}

void AW_SetupGameAddresses(ServerData_AW* Server)
{
	if (aw_addr_s_Data)
		delete aw_addr_s_Data;

	aw_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		aw_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	aw_addr_s_Data = new Security(t, g_Session);
	aw_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, aw_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}