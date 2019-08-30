#include "main.h"


const char* Cod4_SL_ConvertToString(unsigned int stringValue);
unsigned int Cod4_SL_GetString(const char* str, unsigned int user);
unsigned int Cod4_SL_GetStringOfSize(const char *str, int user, int length, int type);

int Cod4_Dvar_FindVar(const char* Dvar);
void Cod4_Dvar_SetStringByName(const char* Dvar, const char*  val);
void Cod4_Dvar_SetBool(const char* Dvar, bool val);
bool Cod4_Dvar_GetBool(const char* Dvar);
const char* Cod4_Dvar_GetString(const char* Dvar);
float Cod4_Dvar_GetFloat(const char* Dvar);
int Cod4_Dvar_GetInt(const char* Dvar);

char Cod4_ClampChar_r(const int i);
const char* Cod4_SEH_StringEd_GetString(const char* str);
float Cod4_DEG2RAD(float DEG);
bool Cod4_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive);
bool Cod4_GetAsyncKeyState(DWORD KEY);

int Cod4_TextHeight(const char* font, float scale);
int Cod4_TextWidth(const char* text, const char* font);
int Cod4_R_RegisterFont(const char* name, int imageTrack);
const char* Cod4_R_GetFontPathFromName(const char* name);
void Cod4_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material);
void Cod4_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material);
void Cod4_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
int Cod4_R_TextHeight(int font);
int Cod4_R_TextWidth(const char* text, int maxchars, int font);

int* Cod4_Material_RegisterHandle(const char* name, int imageTrack);
void Cod4_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void Cod4_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void Cod4_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);
void Cod4_RandomBulletDir(int randSeed, float *x, float *y);
void Cod4_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float *colour, int *material);
void Cod4_ApplyGamePatches();

enum cod4_miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct cod4_addr_s
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

	unsigned int _0x7FFFFFFF;
	unsigned int _0x00000020;
	unsigned int _0x823E0420;
	unsigned int _0x82AADAB0;
	unsigned int _0x00001130;
	unsigned int _0x00000064;
	unsigned int _0x823E0478;
	unsigned int _0x000000E0;
	unsigned int _0x0000001C;
	unsigned int _0x82306350;
	unsigned int _0x82323A90;
	unsigned int _0x82557750;
	unsigned int _0x00000030;
	unsigned int _0x8229C418;
	unsigned int _0x8229C6B0;
	unsigned int _0x822EC2F8;
	unsigned int _0x4E800020;
	unsigned int _0x7D8802A6;
	unsigned int _0x821ECA78;
	unsigned int _0x823B9F60;
	unsigned int _0x000000FF;
	unsigned int _0x82AF3908;
	unsigned int _0x82AC1900;
	unsigned int _0x84BC13A0;
	unsigned int _0x82031810;
	unsigned int _0x00803003;
	unsigned int _0x82346880;
	unsigned int _0x8228F868;
	unsigned int _0x0004E550;
	unsigned int _0x00000024;
	unsigned int _0x82B85408;
	unsigned int _0x823004A0;
	unsigned int _0x8230A078;
	unsigned int _0x00000330;
	unsigned int _0x000112A9;
	unsigned int _0x823F28A0;
	unsigned int _0x000005FC;
	unsigned int _0x0000001F;
	unsigned int _0x8216AD58;
	unsigned int _0x84CD597C;
	unsigned int _0x000B6020;
	unsigned int _0x84CD7B60;
	unsigned int _0x000002E8;
	unsigned int _0x0000026C;
	unsigned int _0x84CD7E9C;
	unsigned int _0x821028C8;
	unsigned int _0x82B854C8;
	unsigned int _0x82148C88;
	unsigned int _0x822CA3CC;
	unsigned int _0x825E2200;
	unsigned int _0x000415E0;
	unsigned int _0x8233048C;
	unsigned int _0x8233169C;
	unsigned int _0x823316B4;
	unsigned int _0x82330488;
	unsigned int _0x822EDAA0;
	unsigned int _0x4BFFC3B5;
	unsigned int _0x4BFFB3DD;
	unsigned int _0x4BFFCD05;
	unsigned int _0x4BFFDCA9;
	unsigned int _0x4803DD41;
	unsigned int _0x823F568C;
	unsigned int _0x82308040;
	unsigned int _0x82308070;
	unsigned int _0x823080A0;
	unsigned int _0x823080D0;
	unsigned int _0x82308100;
	unsigned int _0x82308128;
	unsigned int _0x82308150;
	unsigned int _0x8230818C;
	unsigned int _0x823081C8;
	unsigned int _0x823081EC;
	unsigned int _0x82308210;
	unsigned int _0x82308238;
	unsigned int _0x82308270;
	unsigned int _0x823082A8;
	unsigned int _0x4801DE39;
	unsigned int _0x4801DB51;
	unsigned int _0x4801D881;
	unsigned int _0x4801D5B1;
	unsigned int _0x4801D2C1;
	unsigned int _0x4801CF91;
	unsigned int _0x4801BED1;
	unsigned int _0x4801C29D;
	unsigned int _0x4801C261;
	unsigned int _0x4801A67D;
	unsigned int _0x4801A1D9;
	unsigned int _0x4801C9D1;
	unsigned int _0x48019B69;
	unsigned int _0x48019B31;
	unsigned int _0x82B8576C;
	unsigned int _0x822E9758;
	unsigned int _0x8216A640;
	unsigned int _0x84CD5980;
	unsigned int _0x00002024;
	unsigned int _0x8234DE10;
	unsigned int _0x821D9DA8;
	unsigned int _0x821D1504;
	unsigned int _0x823F5784;
	unsigned int _0x60000000;


	/*void SetAddresses()
	{
		Dvar_FindVar = 0x821D4C10;
		Dvar_GetBool = 0x821D15D8;
		Dvar_SetBool = 0x821D4500;
		Dvar_GetInt = 0x821D1570;
		Dvar_GetFloat = 0x821D14F8;
		Dvar_GetString = 0x821D1478;
		Dvar_SetStringByName = 0x821D4780;
		SL_GetStringOfSize = 0x8221F268;
		SL_ConvertToString = 0x0; //inline
		CG_GameMessage = 0x8230AAF0;
		CG_BoldGameMessage = 0x8230AA60;
		Cbuf_AddText = 0x82239FD0;
		CL_AddReliableCommand = 0x822CF268;
		CG_VisionSetStartLerp_To = 0x822F0370;
		UI_GetMapName = 0x821ED5A8;
		UI_GetGameTypeName = 0x821EAA08;
		SEH_StringEd_GetString = 0x821FA8A8;
		Com_GetClientDObj = 0x82308E20;
		CG_DObjGetWorldTagPos = 0x82316088;
		CG_GetPlayerVelocity = 0x0; //not present ?
		CG_GetPlayerViewOrigin = 0x822EB5E8;
		CG_LocationalTrace = 0x8235D7D0;
		BG_GetSpreadForWeapon = 0x8232C478;
		TransformSeed = 0x0; //not used
		RandomBulletDir = 0x822E9758;
		Trace_GetEntityHitId = 0x0; //inline
		SV_IsMigrating = 0x0; //not present
		CL_IsServerRestarting = 0x0; //not present
		PlayRumbleInternal = 0x823004A0;
		UI_PlaySound = 0x8230A078;
		BG_GetAmmoInClip = 0x0; //differnt ** will have to check
		R_TextWidth = 0x8216EB00;
		R_TextHeight = 0x822DEEA8; //gay boy
		R_AddCmdDrawText = 0x8216C0B8;
		R_AddCmdDrawStretchPic = 0x8216BAE8;
		CG_DrawRotatedPicPhysical = 0x82318A88;
		Material_RegisterHandle = 0x0; //inline	
		R_RegisterFont = 0x0; //inline
		DB_FindXAssetHeader = 0x822A0298;
		R_AddCmdDrawQuadPic = 0x8216B420;
		ScreenPlacement = 0x8246F308;
		R_TextLineWrapPosition = 0x8216E8F8;
		R_ConvertColorToBytes = 0x8234DE10;
		WeaponDef = 0x823B9F60;
		WeaponVariantDef = 0x0; //not present
		cgs_t = 0x823F2890;
		cg_s = 0x823F28A0;
		centity_s = 0x823F5054;
		clientUIActive = 0x82435A10;
		clientactive_t = 0x82435AB8;
		ClientNetwork_s = 0x8243D6F8;
		BulletTrace = 0x822EAB98;
		BG_AdvanceTrace = 0x8232C608;
		BG_GetSurfacePenetrationDepth = 0x0; //inline
		CG_ClientHasPerk = 0x0; //nope
		FireBulletPenetrate = 0x822EC4D0;
		BG_GetPerkIndexForName = 0x82363800;
		NameAddress = 0x84C24BBC;
		ClantagAddress = 0x0; //need to find
		XAM_191 = 0x8236E0C4;
		RB_SetTessTechnique = 0x0; //need to find
		R_EndFrame = 0x8216CAA0;
		SCR_DrawScreenField = 0x822C9D50;
		Menu_PaintAll = 0x821E7558;
		CL_WritePacket = 0x822DA6C8;
		CL_CreateNewCommand = 0x82301A28;
		CG_Obituary = 0x82312878;
		CL_Disconnect = 0x822CFF00;
		Com_Error = 0x82236640;

		YawVectors2D = 0x821DADF8;
		CL_ClientIsInMyParty = 0x0;
		CalcCompassFriendlySize = 0x823239A8;
		SERVER_ID = 0x0; //dvar get int this
		BG_EvaluateTrajectory = 0x8233D0E0;
		CG_GetVelocity = 0x0; //not present
		Sys_EnterCriticalSection = 0x0;
		Sys_LeaveCriticalSection = 0x0;
		xboxkrnl_125 = 0x8236E164;
		xboxkrnl_130 = 0x8236E174;
		CG_IsSelectingLocation = 0x0;
		VehicleCl_IsClientValid = 0x0;
		VehicleCl_GetClientDef = 0x0;
		uicontext = 0x849F2DF0;

		_0x7FFFFFFF = 0x7FFFFFFF;
		_0x00000020 = 0x00000020;
		_0x823E0420 = 0x823E0420;
		_0x82AADAB0 = 0x82AADAB0;
		_0x00001130 = 0x00001130;
		_0x00000064 = 0x00000064;
		_0x823E0478 = 0x823E0478;
		_0x000000E0 = 0x000000E0;
		_0x0000001C = 0x0000001C;
		_0x82306350 = 0x82306350;
		_0x82323A90 = 0x82323A90;
		_0x82557750 = 0x82557750;
		_0x00000030 = 0x00000030;
		_0x8229C418 = 0x8229C418;
		_0x8229C6B0 = 0x8229C6B0;
		_0x822EC2F8 = 0x822EC2F8;
		_0x4E800020 = 0x4E800020;
		_0x7D8802A6 = 0x7D8802A6;
		_0x821ECA78 = 0x821ECA78;
		_0x823B9F60 = 0x823B9F60;
		_0x000000FF = 0x000000FF;
		_0x82AF3908 = 0x82AF3908;
		_0x82AC1900 = 0x82AC1900;
		_0x84BC13A0 = 0x84BC13A0;
		_0x82031810 = 0x82031810;
		_0x00803003 = 0x00803003;
		_0x82346880 = 0x82346880;
		_0x8228F868 = 0x8228F868;
		_0x0004E550 = 0x0004E550;
		_0x00000024 = 0x00000024;
		_0x82B85408 = 0x82B85408;
		_0x823004A0 = 0x823004A0;
		_0x8230A078 = 0x8230A078;
		_0x00000330 = 0x00000330;
		_0x000112A9 = 0x000112A9;
		_0x823F28A0 = 0x823F28A0;
		_0x000005FC = 0x000005FC;
		_0x0000001F = 0x0000001F;
		_0x8216AD58 = 0x8216AD58;
		_0x84CD597C = 0x84CD597C;
		_0x000B6020 = 0x000B6020;
		_0x84CD7B60 = 0x84CD7B60;
		_0x000002E8 = 0x000002E8;
		_0x0000026C = 0x0000026C;
		_0x84CD7E9C = 0x84CD7E9C;
		_0x821028C8 = 0x821028C8;
		_0x82B854C8 = 0x82B854C8;
		_0x82148C88 = 0x82148C88;
		_0x822CA3CC = 0x822CA3CC;
		_0x825E2200 = 0x825E2200;
		_0x000415E0 = 0x000415E0;
		_0x8233048C = 0x8233048C;
		_0x8233169C = 0x8233169C;
		_0x823316B4 = 0x823316B4;
		_0x82330488 = 0x82330488;
		_0x822EDAA0 = 0x822EDAA0;
		_0x4BFFC3B5 = 0x4BFFC3B5;
		_0x4BFFB3DD = 0x4BFFB3DD;
		_0x4BFFCD05 = 0x4BFFCD05;
		_0x4BFFDCA9 = 0x4BFFDCA9;
		_0x4803DD41 = 0x4803DD41;
		_0x823F568C = 0x823F568C;
		_0x82308040 = 0x82308040;
		_0x82308070 = 0x82308070;
		_0x823080A0 = 0x823080A0;
		_0x823080D0 = 0x823080D0;
		_0x82308100 = 0x82308100;
		_0x82308128 = 0x82308128;
		_0x82308150 = 0x82308150;
		_0x8230818C = 0x8230818C;
		_0x823081C8 = 0x823081C8;
		_0x823081EC = 0x823081EC;
		_0x82308210 = 0x82308210;
		_0x82308238 = 0x82308238;
		_0x82308270 = 0x82308270;
		_0x823082A8 = 0x823082A8;
		_0x4801DE39 = 0x4801DE39;
		_0x4801DB51 = 0x4801DB51;
		_0x4801D881 = 0x4801D881;
		_0x4801D5B1 = 0x4801D5B1;
		_0x4801D2C1 = 0x4801D2C1;
		_0x4801CF91 = 0x4801CF91;
		_0x4801BED1 = 0x4801BED1;
		_0x4801C29D = 0x4801C29D;
		_0x4801C261 = 0x4801C261;
		_0x4801A67D = 0x4801A67D;
		_0x4801A1D9 = 0x4801A1D9;
		_0x4801C9D1 = 0x4801C9D1;
		_0x48019B69 = 0x48019B69;
		_0x48019B31 = 0x48019B31;
		_0x82B8576C = 0x82B8576C;
		_0x822E9758 = 0x822E9758;
		_0x8216A640 = 0x8216A640;
		_0x84CD5980 = 0x84CD5980;
		_0x00002024 = 0x00002024;
		_0x8234DE10 = 0x8234DE10;
		_0x821D9DA8 = 0x821D9DA8;
		_0x821D1504 = 0x821D1504;
		_0x823F5784 = 0x823F5784;
		_0x60000000 = 0x60000000;

	}*/
};

struct GAME_ADDRESS_TRANSFER_IW3MP
{
	cod4_addr_s* addr;

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
	void* R_AddCmdDrawStretchPicRotateST;
};

GAME_ADDRESS_TRANSFER_IW3MP* ExternalFunctions = 0;
cod4_addr_s* addr = 0;
Security * cod4_addr_s_Data = 0;

unsigned int *cod4_addr_s_PatchID = 0;

bool Cod4_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_IW3MP;

	if (addr)
		free(addr);

	addr = (cod4_addr_s*)malloc(sizeof(cod4_addr_s));

	for (int i = 0; i < 183; i++)
		((int*)(addr))[i] = GetAddress(cod4_addr_s_Data, cod4_addr_s_PatchID, i);

	//addr->SetAddresses();

	ExternalFunctions->addr = addr;

	ExternalFunctions->SL_ConvertToString = (void*)ReverseInt((int)Cod4_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (void*)ReverseInt((int)Cod4_SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (void*)ReverseInt((int)Cod4_SL_GetStringOfSize);

	ExternalFunctions->Dvar_FindVar = (void*)ReverseInt((int)Cod4_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void*)ReverseInt((int)Cod4_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void*)ReverseInt((int)Cod4_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (void*)ReverseInt((int)Cod4_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (void*)ReverseInt((int)Cod4_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (void*)ReverseInt((int)Cod4_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (void*)ReverseInt((int)Cod4_Dvar_GetInt);

	ExternalFunctions->ClampChar_r = (void*)ReverseInt((int)Cod4_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (void*)ReverseInt((int)Cod4_SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (void*)ReverseInt((int)Cod4_DEG2RAD);
	ExternalFunctions->getStructures = (void*)ReverseInt((int)Cod4_getStructures);
	ExternalFunctions->ApplyPatches = (void*)ReverseInt((int)Cod4_ApplyGamePatches);
	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((int)Cod4_GetAsyncKeyState);

	ExternalFunctions->TextHeight = (void*)ReverseInt((int)Cod4_TextHeight);
	ExternalFunctions->TextWidth = (void*)ReverseInt((int)Cod4_TextWidth);
	ExternalFunctions->R_RegisterFont = (void*)ReverseInt((int)Cod4_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (void*)ReverseInt((int)Cod4_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void*)ReverseInt((int)Cod4_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void*)ReverseInt((int)Cod4_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void*)ReverseInt((int)Cod4_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (void*)ReverseInt((int)Cod4_R_TextHeight);
	ExternalFunctions->R_TextWidth = (void*)ReverseInt((int)Cod4_R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void*)ReverseInt((int)Cod4_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void*)ReverseInt((int)Cod4_SetTextCentered);
	ExternalFunctions->SetTextRight = (void*)ReverseInt((int)Cod4_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (void*)ReverseInt((int)Cod4_Material_RegisterHandle);

	ExternalFunctions->RandomBulletDir = (void*)ReverseInt((int)Cod4_RandomBulletDir);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateST = (void*)ReverseInt((int)Cod4_R_AddCmdDrawStretchPicRotateST);


	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((unsigned int)(int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((unsigned int)(int)sizeof(GAME_ADDRESS_TRANSFER_IW3MP)));

	return true;
}



int* Cod4_Material_RegisterHandle(const char* name, int imageTrack)
{
	int(*DB_FindXAssetHeader)(int type, const char* name) = (int(*)(int, const char*))addr->DB_FindXAssetHeader;
	return (int*)DB_FindXAssetHeader(0x4, name);
}

void Cod4_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	Cod4_R_AddCmdDrawText(text, addr->_0x7FFFFFFF, Cod4_R_RegisterFont(font, 0), (x - ((Cod4_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void Cod4_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	Cod4_R_AddCmdDrawText(text, addr->_0x7FFFFFFF, Cod4_R_RegisterFont(font, 0), (x - ((Cod4_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void Cod4_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	Cod4_CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, Cod4_Material_RegisterHandle(material, 0));
}

int Cod4_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

int Cod4_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

void Cod4_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void Cod4_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void Cod4_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* Cod4_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

int Cod4_R_RegisterFont(const char* name, int imageTrack)
{
	int(*DB_FindXAssetHeader)(int type, const char* nam) = (int(*)(int, const char*))addr->DB_FindXAssetHeader;
	return DB_FindXAssetHeader(0x14, Cod4_R_GetFontPathFromName(name));
}

int Cod4_TextWidth(const char* text, const char* font)
{
	return Cod4_R_TextWidth(text, addr->_0x7FFFFFFF, Cod4_R_RegisterFont(font, 0));
}

int Cod4_TextHeight(const char* font, float scale)
{
	return (Cod4_R_TextHeight(Cod4_R_RegisterFont(font, 0)) * scale);
}

bool Cod4_GetAsyncKeyState(DWORD KEY)
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


bool Cod4_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive)
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

const char* Cod4_SEH_StringEd_GetString(const char* str)
{
	const char*(*SEH_StringEd_GetString)(const char* str) = (const char*(*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char Cod4_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float Cod4_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int Cod4_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char*))addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

float Cod4_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char*) = (float(*)(const char*))addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

const char* Cod4_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char*) = (const char*(*)(const char*))addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

bool Cod4_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char*))addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

void Cod4_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))addr->Dvar_SetBool;
	int pDvar = Cod4_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}


void Cod4_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))addr->Dvar_SetStringByName;
	int pDvar = Cod4_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

int Cod4_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

unsigned int Cod4_SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(*)(const char *, unsigned int, unsigned int, int))addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int Cod4_SL_GetString(const char* str, unsigned int user)
{
	return Cod4_SL_GetStringOfSize(str, user, strlen(str) + 1, 6);
}

const char* Cod4_SL_ConvertToString(unsigned int stringValue)
{
	if (stringValue)
		return (const char*)((*(int*)(addr->_0x82B8576C) + ((stringValue + (stringValue << 1)) << 2)) + 4);
	else
		return 0;
}

VOID Cod4_XNotify(CONST PWCHAR NotifyText)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)XNotifyThread, NotifyText, 0);
}

int * Cod4_GetDetours()
{
	return (int*)new Detour();
}

void* Cod4_HookFunction(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (unsigned int)c);
}

void Cod4_RandomBulletDir(int randSeed, float *x, float *y)
{
	void(*RandomBulletDir)(int randSeed, float *x, float *y) = (void(*)(int randSeed, float *x, float *y))addr->_0x822E9758;
	RandomBulletDir(randSeed, x, y);
}

void Cod4_R_AddCmdDrawStretchPicRotateST(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float *colour, int *material)
{
	int r31 = ((int(*)(...))addr->_0x8216A640)(9, 0x34);
	if (r31)
	{
		int* materialPointer = material;
		if (!material)
			materialPointer = *(int**)(addr->_0x84CD5980 + addr->_0x00002024);

		int* r4 = (int*)(r31 + 0x2C);
		*(float*)(r31 + 0x8) = x;
		*(int**)(r31 + 0x4) = materialPointer;
		*(float*)(r31 + 0xC) = y;
		*(float*)(r31 + 0x10) = w;
		*(float*)(r31 + 0x14) = h;
		*(float*)(r31 + 0x18) = centerS;
		*(float*)(r31 + 0x1C) = centerT;
		*(float*)(r31 + 0x20) = radiusST;
		*(float*)(r31 + 0x24) = scaleFinalS;
		*(float*)(r31 + 0x28) = scaleFinalT;
		if (colour)
			((void(*)(...))addr->_0x8234DE10)(colour, r4); //R_ConvertColorToBytes
		else
			*r4 = -1;
		*(float*)(r31 + 0x30) = ((float(*)(...))addr->_0x821D9DA8)(angle); //Normalize Angle
	}
}

void Cod4_ApplyGamePatches()
{
	int cl_maxpackets = Cod4_Dvar_FindVar("cl_maxpackets");
	if (cl_maxpackets != 0)
		*(int*)(cl_maxpackets + 0xC) = 100;

	int snaps = Cod4_Dvar_FindVar("snaps");
	if (snaps != 0)
		*(int*)(snaps + 0xC) = 40;

	int rate = Cod4_Dvar_FindVar("rate");
	if (rate != 0)
		*(int*)(rate + 0xC) = 25000;

	//inline float r3 lol
	*(QWORD*)(addr->_0x821D1504) = 0x6000000060000000;

	//disable impacts
	*(int*)addr->_0x8229C418 = addr->_0x4E800020;
	*(int*)addr->_0x8229C6B0 = addr->_0x4E800020;
	*(int*)addr->_0x822EC2F8 = addr->_0x4E800020;

	//offensive clan tags
	//*(int*)(0x82309A30) = addr->_0x38600001;
	//*(int*)(0x82182C10) = addr->_0x38600001;
	//*(int*)(0x82182C14) = addr->_0x4E800020;
	//*(int*)(0x82309B84) = addr->_0x60000000;
	//*(int*)(0x82309B90) = addr->_0x60000000;
	//*(int*)(0x8217E8D8) = addr->_0x38600001;
	//*(int*)(0x8247C590) = addr->_0x38600001;
}


void Cod4_SetupGameAddresses(ServerData_COD4* Server)
{
	if (cod4_addr_s_Data)
		delete cod4_addr_s_Data;

	cod4_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		cod4_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	cod4_addr_s_Data = new Security(t, g_Session);
	cod4_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, cod4_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}