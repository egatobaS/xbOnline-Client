#include "main.h"

Security * BO1_addr_s_Data = 0;
Security * BO1_init_addr_s_Data = 0;

unsigned int *BO1_addr_s_PatchID = 0;
unsigned int *BO1_init_addr_s_PatchID = 0;

struct BO1_addr_s
{
	unsigned int Dvar_FindVar;
	unsigned int Dvar_GetBool;
	unsigned int Dvar_SetBool;
	unsigned int Dvar_GetInt;
	unsigned int Dvar_GetFloat;
	unsigned int Dvar_GetString;
	unsigned int Dvar_SetStringByName;

	unsigned int SL_GetString;
	unsigned int StringTable;
	unsigned int StringTable_GetAsset;
	unsigned int StringTable_Lookup;
	unsigned int UI_SafeTranslateString;
	unsigned int SEH_StringEd_GetString;

	unsigned int CG_GameMessage;
	unsigned int CG_BoldGameMessage;
	unsigned int Cbuf_AddText;
	unsigned int CL_AddReliableCommand;
	unsigned int CG_VisionSetStartLerp_To;
	unsigned int Com_GetClientDObj;
	unsigned int CG_DObjGetWorldTagPos;
	unsigned int CG_GetPlayerViewOrigin;
	unsigned int CG_LocationalTrace;
	unsigned int BG_GetSpreadForWeapon;
	unsigned int G_GoodRandomFloat;
	unsigned int Trace_GetEntityHitId;
	unsigned int SV_IsMigrating;
	unsigned int CL_IsServerRestarting;

	unsigned int R_TextWidth;
	unsigned int R_TextHeight;
	unsigned int R_AddCmdDrawText;
	unsigned int R_AddCmdDrawStretchPic;
	unsigned int CG_DrawRotatedPicPhysical;
	unsigned int Material_RegisterHandle;
	unsigned int R_RegisterFont;
	unsigned int ScreenPlacement;
	unsigned int R_TextLineWrapPosition;
	unsigned int R_GetCommandBuffer;
	unsigned int R_ConvertColorToBytes;
	unsigned int AngleNormalize360;

	unsigned int BulletTrace;
	unsigned int BG_AdvanceTrace;
	unsigned int BG_GetSurfacePenetrationDepth;
	unsigned int FireBulletPenetrate;
	unsigned int BG_GetPerkIndexForName;

	unsigned int WeaponVariantDef;
	unsigned int cgs_t;
	unsigned int cg_s;
	unsigned int centity_s;
	unsigned int clientactive_t;
	unsigned int ClientNetwork_s;
	unsigned int clientUIActive;
	unsigned int UiContext;

	unsigned int NameAddress;
	unsigned int ClantagAddress;

	unsigned int XAM_191;
	unsigned int XamUserGetName;
	unsigned int R_EndFrame;
	unsigned int SCR_DrawScreenField;
	unsigned int Menu_PaintAll;
	unsigned int CL_WritePacket;
	unsigned int CG_Obituary;
	unsigned int R_AddDObjToScene;

	unsigned int CL_Disconnect;
	unsigned int NetDll_XNetGetTitleXnAddr;
	unsigned int Com_SafeClientDObjFree;

//#ifdef DEVKIT
//	void SetAddresses()
//	{
//		//Dvars
//		Dvar_FindVar = 0x823E2818;
//		Dvar_GetBool = 0x823E28F8;
//		Dvar_SetBool = 0x823E4AF0;
//		Dvar_GetInt = 0x823E2980;
//		Dvar_GetFloat = 0x823E2CC0;
//		Dvar_GetString = 0x823E2E18;
//		Dvar_SetStringByName = 0x823E5118;
//
//		//string tables
//		SL_GetString = 0x822E1B58;
//		StringTable_GetAsset = 0x823DE138;
//		StringTable_Lookup = 0x823DDDE0;
//		UI_SafeTranslateString = 0x8238F0A8;
//		SEH_StringEd_GetString = 0x82373978;
//
//		//Misc
//		CG_GameMessage = 0x821CD128;
//		CG_BoldGameMessage = 0x821CD148;
//		Cbuf_AddText = 0x8233E8D8;
//		CL_AddReliableCommand = 0x822408E8;
//		CG_VisionSetStartLerp_To = 0x82218590;
//		Com_GetClientDObj = 0x82346710;
//		CG_DObjGetWorldTagPos = 0x821BDB10;
//		CG_GetPlayerViewOrigin = 0x82223E48;
//		CG_LocationalTrace = 0x822296E0;
//		BG_GetSpreadForWeapon = 0x82186940;
//		G_GoodRandomFloat = 0x822AC660;
//		Trace_GetEntityHitId = 0x82334E58;
//		SV_IsMigrating = 0x8236AD70;
//		CL_IsServerRestarting = 0x8222C8A8;
//
//		//Drawing
//		R_TextWidth = 0x8263D378;
//		R_TextHeight = 0x823F6998;
//		R_AddCmdDrawText = 0x8263EF00;
//		R_AddCmdDrawStretchPic = 0x8263EA68;
//		CG_DrawRotatedPicPhysical = 0x821B86A8;
//		Material_RegisterHandle = 0x82624B78;
//		R_RegisterFont = 0x8263D330;
//		ScreenPlacement = 0x82A06718;
//		R_TextLineWrapPosition = 0x8263D4D0;
//		R_GetCommandBuffer = 0x8263E058;
//		R_ConvertColorToBytes = 0x82647D78;
//		AngleNormalize360 = 0x823D9FB8;
//
//		//AutoWall
//		BulletTrace = 0x8221EF90;
//		BG_AdvanceTrace = 0x82186438;
//		BG_GetSurfacePenetrationDepth = 0x82186568;
//		FireBulletPenetrate = 0x822252F8;
//		BG_GetPerkIndexForName = 0x8216ED80;
//
//		//Structs
//		WeaponVariantDef = 0x828750D8;
//		cgs_t = 0x82964E64;
//		cg_s = 0x82964EA0;
//		centity_s = 0x8296808C;
//		clientactive_t = 0x829D9728;
//		ClientNetwork_s = 0x829F0350;
//		clientUIActive = 0x829D5580;
//		UiContext = 0x83911158;
//
//		//Misc - 2
//		NameAddress = 0x841987D5;
//		ClantagAddress = 0x0;
//
//		//Hooks
//		XAM_191 = 0x826CF558;
//		XamUserGetName = 0x824F7340;
//		R_EndFrame = 0x82640350;
//		SCR_DrawScreenField = 0x8224EAC0;
//		Menu_PaintAll = 0x823AFA98;
//		CL_WritePacket = 0x8223B3C8;
//		CG_Obituary = 0x821BF9B0;
//		R_AddDObjToScene = 0x8262CDE0;
//
//		CL_Disconnect = 0x82240ED8;
//		NetDll_XNetGetTitleXnAddr = 0x826D00B8;
//		Com_SafeClientDObjFree = 0x82346590;
//
//	}
//#endif
};

struct BO1_init_addr_s
{
	unsigned int _0x842E7BBC;
	unsigned int _0x00000004;
	unsigned int _0x00000008;
	unsigned int _0x0000000C;
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
	unsigned int _0x823D8678;
	unsigned int _0x828B9458;
	unsigned int _0x00000558;
	unsigned int _0x0000004C;
	unsigned int _0x828B8958;
	unsigned int _0x000001C0;
	unsigned int _0x830A9FE0;
	unsigned int _0x00001DD8;
	unsigned int _0x828BBAB8;
	unsigned int _0x000001F8;
	unsigned int _0x828BA9B8;
	unsigned int _0x000000E0;
	unsigned int _0x828B7758;
	unsigned int _0x821D4A40;
	unsigned int _0x821A54F8;
	unsigned int _0x82223DA8;
	unsigned int _0x82292230;
	unsigned int _0x4E800020;
	unsigned int _0x7D8802A6;
	unsigned int _0x823F2D10;
	unsigned int _0x8216C3E0;
	unsigned int _0x00803003;
	unsigned int _0x83225CF8;
	unsigned int _0x831C8CF8;
	unsigned int _0x00000C00;
	unsigned int _0x0000007C;
	unsigned int _0x821E4DB8;
	unsigned int _0x824B19D0;
	unsigned int _0x824B1C88;
	unsigned int _0x82167B08;
	unsigned int _0x00000604;
	unsigned int _0x829D5554;
	unsigned int _0x8218D960;
	unsigned int _0x60000000;
	unsigned int _0x84198950;
	unsigned int _0x8204C580;
	unsigned int _0x82287D3C;
	unsigned int _0x82225594;
	unsigned int _0x82225598;
	unsigned int _0x823F4B28;
	unsigned int _0x8238F980;
	unsigned int _0x823B0C20;
	unsigned int _0x823B0C24;
	unsigned int _0x82392D6C;
	unsigned int _0x82392EE0;
	unsigned int _0x82392EEC;
	unsigned int _0x82250FA0;
	unsigned int _0x8238C52C;
	unsigned int _0x38600001;
	unsigned int _0x2F030001;
	unsigned int _0x38600000;
	unsigned int _0x82392CE0;
	unsigned int _0x82392CC8;
	unsigned int _0x82392CB0;
	unsigned int _0x83C88900;

	unsigned int _0x82195200;
	unsigned int _0x82195D1C;
	unsigned int _0x82968374;
	unsigned int _0x82195D04;
	unsigned int _0x82217190;
	unsigned int _0x82227624;
	unsigned int _0x821A819C;
	unsigned int _0x82255E1C;
	unsigned int _0x828D7118;
	unsigned int _0x4BFFEB09;
	unsigned int _0x4BFFFA85;
	unsigned int _0x4BFFF95D;
	unsigned int _0x4BFF8531;
	unsigned int _0x4BF67EC5;
	unsigned int _0x2B0B0000;
	unsigned int _0x2B0B0001;
	unsigned int _0x2B110010;

	unsigned int _0x82d40578;
	unsigned int _0x82341CA8;
	unsigned int _0x0005DA70;
	unsigned int _0x829BE624;
	unsigned int _0x821DAC1C;
	unsigned int _0x821DAC4C;
	unsigned int _0x821DAC78;
	unsigned int _0x821DACA0;
	unsigned int _0x821DACCC;
	unsigned int _0x821DACE4;
	unsigned int _0x821DAD0C;
	unsigned int _0x821DAD38;
	unsigned int _0x821DAD64;
	unsigned int _0x821DAD9C;
	unsigned int _0x821DADC8;
	unsigned int _0x821DADF4;
	unsigned int _0x821DAE20;
	unsigned int _0x821DAE4C;
	unsigned int _0x821DB310;
	unsigned int _0x821DB340;
	unsigned int _0x821DB368;
	unsigned int _0x821DB390;
	unsigned int _0x821DB560;
	unsigned int _0x821DB5C0;
	unsigned int _0x821DB670;
	unsigned int _0x821DC6E8;
	unsigned int _0x821DC1D0;
	unsigned int _0x821DC164;
	unsigned int _0x821DC0F4;
	unsigned int _0x821DC07C;
	unsigned int _0x4BFC8C85;
	unsigned int _0x4BFCBC75;
	unsigned int _0x4BFCC959;
	unsigned int _0x4BFCF959;
	unsigned int _0x4BFD029D;
	unsigned int _0x4BFD046D;
	unsigned int _0x4BFD062D;
	unsigned int _0x4BFCBFD1;
	unsigned int _0x4BFD180D;
	unsigned int _0x4BFD206D;
	unsigned int _0x4BFD2499;
	unsigned int _0x4BFD2A15;
	unsigned int _0x4BFD2E89;
	unsigned int _0x4BFD1725;
	unsigned int _0x4BFCB5B1;
	unsigned int _0x4BFCB341;
	unsigned int _0x4BFD2DD1;
	unsigned int _0x4BFD08D9;
	unsigned int _0x4BFCAEE1;
	unsigned int _0x4BFD0A49;
	unsigned int _0x4BFD0E21;
	unsigned int _0x4BFCA9D9;
	unsigned int _0x4BFC8661;
	unsigned int _0x4BFC81AD;
	unsigned int _0x4BFC96A5;
	unsigned int _0x4BFC971D;
	unsigned int _0x82374298;
	unsigned int _0x82660D38;
	unsigned int _0x82349D48;
	unsigned int _0x8256EF58;
//#if defined(DEVKIT)
//	void SetAddresses()
//	{
//		_0x842E7BBC = 0x842E7BBC;
//		_0x00000004 = 0x00000004;
//		_0x00000008 = 0x00000008;
//		_0x0000000C = 0x0000000C;
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
//		_0x823D8678 = 0x823D8678;
//		_0x828B9458 = 0x828B9458;
//		_0x00000558 = 0x00000558;
//		_0x0000004C = 0x0000004C;
//		_0x828B8958 = 0x828B8958;
//		_0x000001C0 = 0x000001C0;
//		_0x830A9FE0 = 0x830A9FE0;
//		_0x00001DD8 = 0x00001DD8;
//		_0x828BBAB8 = 0x828BBAB8;
//		_0x000001F8 = 0x000001F8;
//		_0x828BA9B8 = 0x828BA9B8;
//		_0x000000E0 = 0x000000E0;
//		_0x828B7758 = 0x828B7758;
//		_0x821D4A40 = 0x821D4A40;
//		_0x821A54F8 = 0x821A54F8;
//		_0x82223DA8 = 0x82223DA8;
//		_0x82292230 = 0x82292230;
//		_0x4E800020 = 0x4E800020;
//		_0x7D8802A6 = 0x7D8802A6;
//		_0x823F2D10 = 0x823F2D10;
//		_0x8216C3E0 = 0x8216C3E0;
//		_0x00803003 = 0x00803003;
//		_0x83225CF8 = 0x83225CF8;
//		_0x831C8CF8 = 0x831C8CF8;
//		_0x00000C00 = 0x00000C00;
//		_0x0000007C = 0x0000007C;
//		_0x821E4DB8 = 0x821E4DB8;
//		_0x824B19D0 = 0x824B19D0;
//		_0x824B1C88 = 0x824B1C88;
//		_0x82167B08 = 0x82167B08;
//		_0x00000604 = 0x00000604;
//		_0x829D5554 = 0x829D5554;
//		_0x8218D960 = 0x8218D960;
//		_0x60000000 = 0x60000000;
//		_0x84198950 = 0x84198950;
//		_0x8204C580 = 0x8204C580;
//		_0x82287D3C = 0x82287D3C;
//		_0x82225594 = 0x82225594;
//		_0x82225598 = 0x82225598;
//		_0x823F4B28 = 0x823F4B28;
//		_0x8238F980 = 0x8238F980;
//		_0x823B0C20 = 0x823B0C20;
//		_0x823B0C24 = 0x823B0C24;
//		_0x82392D6C = 0x82392D6C;
//		_0x82392EE0 = 0x82392EE0;
//		_0x82392EEC = 0x82392EEC;
//		_0x82250FA0 = 0x82250FA0;
//		_0x8238C52C = 0x8238C52C;
//		_0x38600001 = 0x38600001;
//		_0x2F030001 = 0x2F030001;
//		_0x38600000 = 0x38600000;
//		_0x82392CE0 = 0x82392CE0;
//		_0x82392CC8 = 0x82392CC8;
//		_0x82392CB0 = 0x82392CB0;
//		_0x83C88900 = 0x83C88900;
//		_0x82195200 = 0x82195200;
//		_0x82195D1C = 0x82195D1C;
//		_0x82968374 = 0x82968374;
//		_0x82195D04 = 0x82195D04;
//		_0x82217190 = 0x82217190;
//		_0x82227624 = 0x82227624;
//		_0x821A819C = 0x821A819C;
//		_0x82255E1C = 0x82255E1C;
//		_0x828D7118 = 0x828D7118;
//		_0x4BFFEB09 = 0x4BFFEB09;
//		_0x4BFFFA85 = 0x4BFFFA85;
//		_0x4BFFF95D = 0x4BFFF95D;
//		_0x4BFF8531 = 0x4BFF8531;
//		_0x4BF67EC5 = 0x4BF67EC5;
//		_0x2B0B0000 = 0x2B0B0000;
//		_0x2B0B0001 = 0x2B0B0001;
//		_0x2B110010 = 0x2B110010;
//
//		_0x82d40578 = 0x82d40578;
//		_0x82341CA8 = 0x82341CA8;
//		_0x0005DA70 = 0x0005DA70;
//		_0x829BE624 = 0x829BE624;
//		_0x821DAC1C = 0x821DAC1C;
//		_0x821DAC4C = 0x821DAC4C;
//		_0x821DAC78 = 0x821DAC78;
//		_0x821DACA0 = 0x821DACA0;
//		_0x821DACCC = 0x821DACCC;
//		_0x821DACE4 = 0x821DACE4;
//		_0x821DAD0C = 0x821DAD0C;
//		_0x821DAD38 = 0x821DAD38;
//		_0x821DAD64 = 0x821DAD64;
//		_0x821DAD9C = 0x821DAD9C;
//		_0x821DADC8 = 0x821DADC8;
//		_0x821DADF4 = 0x821DADF4;
//		_0x821DAE20 = 0x821DAE20;
//		_0x821DAE4C = 0x821DAE4C;
//		_0x821DB310 = 0x821DB310;
//		_0x821DB340 = 0x821DB340;
//		_0x821DB368 = 0x821DB368;
//		_0x821DB390 = 0x821DB390;
//		_0x821DB560 = 0x821DB560;
//		_0x821DB5C0 = 0x821DB5C0;
//		_0x821DB670 = 0x821DB670;
//		_0x821DC6E8 = 0x821DC6E8;
//		_0x821DC1D0 = 0x821DC1D0;
//		_0x821DC164 = 0x821DC164;
//		_0x821DC0F4 = 0x821DC0F4;
//		_0x821DC07C = 0x821DC07C;
//		_0x4BFC8C85 = 0x4BFC8C85;
//		_0x4BFCBC75 = 0x4BFCBC75;
//		_0x4BFCC959 = 0x4BFCC959;
//		_0x4BFCF959 = 0x4BFCF959;
//		_0x4BFD029D = 0x4BFD029D;
//		_0x4BFD046D = 0x4BFD046D;
//		_0x4BFD062D = 0x4BFD062D;
//		_0x4BFCBFD1 = 0x4BFCBFD1;
//		_0x4BFD180D = 0x4BFD180D;
//		_0x4BFD206D = 0x4BFD206D;
//		_0x4BFD2499 = 0x4BFD2499;
//		_0x4BFD2A15 = 0x4BFD2A15;
//		_0x4BFD2E89 = 0x4BFD2E89;
//		_0x4BFD1725 = 0x4BFD1725;
//		_0x4BFCB5B1 = 0x4BFCB5B1;
//		_0x4BFCB341 = 0x4BFCB341;
//		_0x4BFD2DD1 = 0x4BFD2DD1;
//		_0x4BFD08D9 = 0x4BFD08D9;
//		_0x4BFCAEE1 = 0x4BFCAEE1;
//		_0x4BFD0A49 = 0x4BFD0A49;
//		_0x4BFD0E21 = 0x4BFD0E21;
//		_0x4BFCA9D9 = 0x4BFCA9D9;
//		_0x4BFC8661 = 0x4BFC8661;
//		_0x4BFC81AD = 0x4BFC81AD;
//		_0x4BFC96A5 = 0x4BFC96A5;
//		_0x4BFC971D = 0x4BFC971D;
//
//		_0x82374298 = 0x82374298;
//		_0x82660D38 = 0x82660D38;
//		_0x82349D48 = 0x82349D48;
//		_0x8256EF58 = 0x8256EF58;
//	}
//#endif
};


enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct GAME_ADDRESS_TRANSFER_BO1
{
	BO1_addr_s* addr;
	BO1_init_addr_s* init_addr;

	void* getStructures;
	void* ApplyPatches;
	void* GetAsyncKeyState;
	void* DEG2RAD;

	void* Dvar_FindVar;
	void* Dvar_SetStringByName;
	void* Dvar_SetBool;
	void* Dvar_GetBool;
	void* Dvar_GetString;
	void* Dvar_GetFloat;
	void* Dvar_GetInt;

	void* SV_IsMigrating;
	void* RandomBulletDir;
	void* CL_IsServerRestarting;
	void* BG_GetPerkIndexForName;
	void* BG_HasPerk;
	void* BG_GetSurfacePenetrationDepth;

	void* SL_ConvertToString;
	void* SL_GetString;

	void* ClampChar_r;
	void* SEH_StringEd_GetString;
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
};


int BO1_Dvar_FindVar(const char* Dvar);
void BO1_Dvar_SetStringByName(const char* Dvar, const char*  val);
void BO1_Dvar_SetBool(const char* Dvar, bool val);
bool BO1_Dvar_GetBool(const char* Dvar);
const char* BO1_Dvar_GetString(const char* Dvar);
float BO1_Dvar_GetFloat(const char* Dvar);
int BO1_Dvar_GetInt(const char* Dvar);

bool BO1_SV_IsMigrating();
void BO1_RandomBulletDir(int *randSeed, float *x, float *y);
bool BO1_CL_IsServerRestarting();
int BO1_BG_GetPerkIndexForName(const char *perkName);
float BO1_BG_GetSurfacePenetrationDepth(int* weapDef, int surfaceFlags);

const char* BO1_SL_ConvertToString(unsigned int stringValue);
unsigned int BO1_SL_GetString(const char* str, unsigned int user);

char BO1_ClampChar_r(const int i);
const char* BO1_SEH_StringEd_GetString(const char* str);
const char* BO1_UI_SafeTranslateString(const char* str);

int BO1_TextHeight(const char* font, float scale);
int BO1_TextWidth(const char* text, const char* font);
int BO1_R_RegisterFont(const char* name, int imageTrack);
const char* BO1_R_GetFontPathFromName(const char* name);
void BO1_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material);
void BO1_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material);
void BO1_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
int BO1_R_TextHeight(int font);
int BO1_R_TextWidth(const char* text, int maxchars, int font);

int* BO1_Material_RegisterHandle(const char* name, int imageTrack);
void BO1_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void BO1_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void BO1_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);

GAME_ADDRESS_TRANSFER_BO1* ExternalFunctions = 0;
BO1_addr_s* addr = 0;
BO1_init_addr_s* init_addr = 0;

void BO1_ApplyGamePatches()
{
	if (*(int*)(init_addr->_0x829D5554))
		*(int*)(*(int*)(init_addr->_0x829D5554) + 0x18) = 100; //cl_maxpackets 


	*(int*)(init_addr->_0x8218D960) = init_addr->_0x60000000; //switch weapons if out of bullets


	//GT patch
	*(int*)(init_addr->_0x82287D3C) = init_addr->_0x60000000;

	//360 degree patch
	*(int*)init_addr->_0x82225594 = init_addr->_0x60000000;
	*(int*)init_addr->_0x82225598 = init_addr->_0x60000000;

	//Disable Impacts
	*(int*)init_addr->_0x82223DA8 = init_addr->_0x4E800020;
	*(int*)init_addr->_0x82292230 = init_addr->_0x4E800020;

	//Thread Fix
	*(int*)(init_addr->_0x823F4B28) = init_addr->_0x60000000;

	//3arc bypass
	*(int*)(init_addr->_0x8238F980) = init_addr->_0x2F030001;

	//offensive clan tags
	*(int*)(init_addr->_0x823B0C20) = init_addr->_0x38600001;
	*(int*)(init_addr->_0x823B0C24) = init_addr->_0x4E800020;
	*(int*)(init_addr->_0x82392D6C) = init_addr->_0x38600000;
	*(int*)(init_addr->_0x82392EE0) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x82392EEC) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x82250FA0) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x8238C52C) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x8238C52C) = init_addr->_0x60000000;

	//IW bypass
	*(int*)(init_addr->_0x82392CE0) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x82392CC8) = init_addr->_0x60000000;
	*(int*)(init_addr->_0x82392CB0) = init_addr->_0x60000000;
}

bool BO1_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive)
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

bool BO1_GetAsyncKeyState(DWORD KEY)
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

float BO1_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int BO1_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

void BO1_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetStringByName)(const char* Dvar, const char*  val) = (bool(*)(const char*, const char*))addr->Dvar_SetStringByName;
	Dvar_SetStringByName(Dvar, val);
}

void BO1_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int Dvar, bool val) = (bool(*)(int Dvar, bool))addr->Dvar_SetBool;
	int pDvar = BO1_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}

bool BO1_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char* Dvar))addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

const char* BO1_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char* Dvar) = (const char*(*)(const char* Dvar))addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

float BO1_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char* Dvar) = (float(*)(const char* Dvar))addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

int BO1_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char* Dvar))addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

bool BO1_SV_IsMigrating()
{
	bool(*SV_IsMigrating)() = (bool(*)())addr->SV_IsMigrating;
	return SV_IsMigrating();
}

double G_GoodRandomFloat(int *idum)
{
	int iv[32];

	*idum = -*idum;
	for (int j = 39; j >= 0; --j)
	{
		*idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
		if (*idum < 0)
			*idum += 0x7FFFFFFF;
		if (j < 32)
			iv[j] = *idum;
	}

	*idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);

	if (*idum < 0)
		*idum += 0x7FFFFFFF;

	if (0.99999988 - (double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10 < 0.0)
		return (float)0.99999988;
	else
		return  (float)((double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10);
}

void BO1_RandomBulletDir(int *randSeed, float *x, float *y)
{
	float theta = G_GoodRandomFloat(randSeed) * 360.0;
	float r = G_GoodRandomFloat(randSeed);
	*x = r * cos(theta * 0.017453292);
	*y = r * sin(theta * 0.017453292);
}

bool BO1_CL_IsServerRestarting()
{
	bool(*CL_IsServerRestarting)() = (bool(*)())addr->CL_IsServerRestarting;
	return CL_IsServerRestarting();
}

int BO1_BG_GetPerkIndexForName(const char *perkName)
{
	int(*BG_GetPerkIndexForName)(const char *perkName) = (int(*)(const char *))addr->BG_GetPerkIndexForName;
	return BG_GetPerkIndexForName(perkName);
}

float BO1_BG_GetSurfacePenetrationDepth(int* weapDef, int surfaceFlags)
{
	float(*BG_GetSurfacePenetrationDepth)(int* weapDef, int surfaceFlags) = (float(*)(int*, int))addr->BG_GetSurfacePenetrationDepth;
	return BG_GetSurfacePenetrationDepth(weapDef, surfaceFlags);
}

const char* BO1_SL_ConvertToString(unsigned int stringValue)
{
	int r4 = 0; //scriptInstance
	if (stringValue)
		return (const char*)((*(int*)((r4 << 2) + init_addr->_0x83C88900) + (stringValue << 4)) + 4);
	else
		return 0;
}

unsigned int BO1_SL_GetString(const char* str, unsigned int user)
{
	unsigned int(*SL_GetString) (const char* str) = (unsigned int(*)(const char*))addr->SL_GetString;
	return SL_GetString(str);
}

char BO1_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

const char* BO1_SEH_StringEd_GetString(const char* str)
{
	const char*(*SEH_StringEd_GetString)(const char* str) = (const char*(*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

const char* BO1_UI_SafeTranslateString(const char* str)
{
	const char*(*UI_SafeTranslateString)(const char* str) = (const char*(*)(const char*))addr->UI_SafeTranslateString;
	return UI_SafeTranslateString(str);
}

int BO1_TextHeight(const char* font, float scale)
{
	return (BO1_R_TextHeight(BO1_R_RegisterFont(font, 0)) * scale);
}

int BO1_TextWidth(const char* text, const char* font)
{
	return BO1_R_TextWidth(text, 0x7FFFFFFF, BO1_R_RegisterFont(font, 0));
}

int BO1_R_RegisterFont(const char* name, int imageTrack)
{
	static int(*R_RegisterFont)(const char * name, int imageTrack) = (int(*)(const char*, int))addr->R_RegisterFont;
	return R_RegisterFont(BO1_R_GetFontPathFromName(name), 0);
}

const char* BO1_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

void BO1_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

void BO1_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void BO1_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

int BO1_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

int BO1_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

void BO1_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	BO1_CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, BO1_Material_RegisterHandle(material, 0));
}

void BO1_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	BO1_R_AddCmdDrawText(text, 0x7FFFFFFF, BO1_R_RegisterFont(font, 0), (x - ((BO1_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void BO1_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	BO1_R_AddCmdDrawText(text, 0x7FFFFFFF, BO1_R_RegisterFont(font, 0), (x - ((BO1_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

int* BO1_Material_RegisterHandle(const char* name, int imageTrack)
{
	static int*(*Material_RegisterHandle)(const char *name, int imageTrack) = (int*(*)(const char*, int))addr->Material_RegisterHandle;
	return Material_RegisterHandle(name, imageTrack);
}


void BO1_SetupGameAddresses(ServerData_BO1* Server) 
{
	if (BO1_addr_s_Data)
		delete BO1_addr_s_Data;

	if (BO1_init_addr_s_Data)
		delete BO1_init_addr_s_Data;

	BO1_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];
	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {
		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		BO1_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	BO1_init_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];
	unsigned int *init_addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum); i++) {
		init_addr_s_PatchFile[i] = Server->Server_init_addr_s[i];
		BO1_init_addr_s_PatchID[i] = Server->Server_init_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	BO1_addr_s_Data = new Security(t, g_Session);
	BO1_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, BO1_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	time(&t);

	Sleep(100);

	BO1_init_addr_s_Data = new Security(t, g_Session);
	BO1_init_addr_s_Data->ProcessAddressFile(init_addr_s_PatchFile, BO1_init_addr_s_PatchID, _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
	delete[] init_addr_s_PatchFile;
}


bool BO1_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_BO1;

	if (addr)
		free(addr);

	if (init_addr)
		free(init_addr);

	init_addr = (BO1_init_addr_s*)malloc(sizeof(BO1_init_addr_s));
	addr = (BO1_addr_s*)malloc(sizeof(BO1_addr_s));

	for (int i = 0; i < 65; i++)
		((int*)(addr))[i] = GetAddress(BO1_addr_s_Data, BO1_addr_s_PatchID, i);

	for (int i = 0; i < 146; i++)
		((int*)(init_addr))[i] = GetAddress(BO1_init_addr_s_Data, BO1_init_addr_s_PatchID, i);

	ExternalFunctions->addr = addr;
	ExternalFunctions->init_addr = init_addr;

	ExternalFunctions->ApplyPatches = (void*)ReverseInt((unsigned int)BO1_ApplyGamePatches);

	ExternalFunctions->getStructures = (void*)ReverseInt((unsigned int)BO1_getStructures);
	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((unsigned int)BO1_GetAsyncKeyState);

	ExternalFunctions->DEG2RAD = (void*)ReverseInt((unsigned int)BO1_DEG2RAD);

	ExternalFunctions->Dvar_FindVar = (void*)ReverseInt((unsigned int)BO1_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void*)ReverseInt((unsigned int)BO1_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void*)ReverseInt((unsigned int)BO1_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (void*)ReverseInt((unsigned int)BO1_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (void*)ReverseInt((unsigned int)BO1_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (void*)ReverseInt((unsigned int)BO1_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (void*)ReverseInt((unsigned int)BO1_Dvar_GetInt);

	ExternalFunctions->SV_IsMigrating = (void*)ReverseInt((unsigned int)BO1_SV_IsMigrating);
	ExternalFunctions->RandomBulletDir = (void*)ReverseInt((unsigned int)BO1_RandomBulletDir);
	ExternalFunctions->CL_IsServerRestarting = (void*)ReverseInt((unsigned int)BO1_CL_IsServerRestarting);
	ExternalFunctions->BG_GetPerkIndexForName = (void*)ReverseInt((unsigned int)BO1_BG_GetPerkIndexForName);
	ExternalFunctions->BG_GetSurfacePenetrationDepth = (void*)ReverseInt((unsigned int)BO1_BG_GetSurfacePenetrationDepth);

	ExternalFunctions->ClampChar_r = (void*)ReverseInt((unsigned int)BO1_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (void*)ReverseInt((unsigned int)BO1_SEH_StringEd_GetString);
	ExternalFunctions->UI_SafeTranslateString = (void*)ReverseInt((unsigned int)BO1_UI_SafeTranslateString);

	ExternalFunctions->SL_ConvertToString = (void*)ReverseInt((unsigned int)BO1_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (void*)ReverseInt((unsigned int)BO1_SL_GetString);

	ExternalFunctions->TextHeight = (void*)ReverseInt((unsigned int)BO1_TextHeight);
	ExternalFunctions->TextWidth = (void*)ReverseInt((unsigned int)BO1_TextWidth);
	ExternalFunctions->R_RegisterFont = (void*)ReverseInt((unsigned int)BO1_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (void*)ReverseInt((unsigned int)BO1_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void*)ReverseInt((unsigned int)BO1_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void*)ReverseInt((unsigned int)BO1_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void*)ReverseInt((unsigned int)BO1_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (void*)ReverseInt((unsigned int)BO1_R_TextHeight);
	ExternalFunctions->R_TextWidth = (void*)ReverseInt((unsigned int)BO1_R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void*)ReverseInt((unsigned int)BO1_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void*)ReverseInt((unsigned int)BO1_SetTextCentered);
	ExternalFunctions->SetTextRight = (void*)ReverseInt((unsigned int)BO1_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (void*)ReverseInt((unsigned int)BO1_Material_RegisterHandle);
	

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_BO1)));


	return true;
}