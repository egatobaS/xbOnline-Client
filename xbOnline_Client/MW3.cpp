#include "main.h"

Security * MW3_addr_s_Data = 0;

unsigned int *MW3_addr_s_PatchID = 0;

struct mw3_addr_s
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

	//AutoWall
	unsigned int BulletTrace;
	unsigned int BG_AdvanceTrace;
	unsigned int BG_GetSurfacePenetrationDepth;
	unsigned int CG_ClientHasPerk;
	unsigned int FireBulletPenetrate;
	unsigned int BG_GetPerkIndexForName;

	//Misc - 2
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
	unsigned int NetDll_XNetGetTitleXnAddr;
	unsigned int Com_SafeClientDObjFree;

	unsigned int _0x827135EC;
	unsigned int _0x837D6CF8;
	unsigned int _0x820301BC;
	unsigned int _0x822ECB84;
	unsigned int _0x8215F9C0;
	unsigned int _0x821FDF18;
	unsigned int _0x826547DC;
	unsigned int _0x8242B438;
	unsigned int _0x82524DD4;
	unsigned int _0x8252EEC0;
	unsigned int _0x82309A30;
	unsigned int _0x82182C10;
	unsigned int _0x82182C14;
	unsigned int _0x82309B84;
	unsigned int _0x82309B90;
	unsigned int _0x8217E8D8;
	unsigned int _0x8247C590;
	unsigned int _0x38600001;
	unsigned int _0x4E800020;
	unsigned int _0x60000000;
	unsigned int _0x390A018C;
	unsigned int _0x822C6608;
	unsigned int _0x822C6890;
	unsigned int _0x836E5AF8;
	unsigned int _0x83D113B0;
	unsigned int _0x83D113A4;
	unsigned int _0x82434B90;
	unsigned int AngleNormalize360;
	unsigned int _0x82414170;
	unsigned int YawVectors2D;
	unsigned int _0x82732100;
	unsigned int _0x82622C88;
	unsigned int CL_ClientIsInMyParty;
	unsigned int CalcCompassFriendlySize;
	unsigned int _0x83B48890;
	unsigned int _0x83B49918;
	unsigned int _0x8261E108;
	unsigned int _0x8261E488;
	unsigned int _0x8261EA08;
	unsigned int _0x8212EEA0;
	unsigned int clientUIActive;
	unsigned int _0x820D5A10;
	unsigned int _0x8233D808;
	unsigned int _0x82F0CC88;
	unsigned int _0x830D1DB0;
	unsigned int _0x830CFDA8;
	unsigned int _0x830D1DA8;
	unsigned int _0xAE000000;
	unsigned int _0x82000000;
	unsigned int _0x82109AD8;
	unsigned int _0x8241ED18;
	unsigned int _0x83D113B4;
	unsigned int _0x83D11380;
	unsigned int _0x83D009CC;
	unsigned int _0x83D009D0;
	unsigned int _0x822AEF48;
	unsigned int _0x83ED5280;
	unsigned int _0x82437E88;
	unsigned int _0x820DEC98;
	unsigned int _0x8210BB50;
	unsigned int _0x822A1770;
	unsigned int _0x83CFFFA8;
	unsigned int _0x82643EC4;
	unsigned int _0x82103CD8;
	unsigned int _0x8210468C;
	unsigned int _0x82104680;
	unsigned int _0x82104698;
	unsigned int _0x821046A4;
	unsigned int _0x821614D4;
	unsigned int _0x8210E58C;
	unsigned int _0x82124BD3;
	unsigned int _0x82132CF0;
	unsigned int _0x821331E0;
	unsigned int _0x82132D98;
	unsigned int _0x8210AF34;
	unsigned int _0x822FF05C;
	unsigned int _0x82132C58;
	unsigned int _0x82132C80;
	unsigned int _0x82132CA8;
	unsigned int _0x82132CD0;
	unsigned int _0x82132E48;
	unsigned int _0x82132E64;
	unsigned int _0x82132DB4;
	unsigned int _0x82132DD0;
	unsigned int _0x82132DEC;
	unsigned int _0x82132E10;
	unsigned int _0x82133340;
	unsigned int _0x82132D28;
	unsigned int _0x82132E2C;
	unsigned int _0x4BFDC379;
	unsigned int _0x4BFDC755;
	unsigned int _0x4BFDADB5;
	unsigned int _0x4BFDB611;
	unsigned int _0x4BFD8755;
	unsigned int _0x4BFDD001;
	unsigned int _0x4827A339;
	unsigned int _0x4BFD9601;
	unsigned int _0x4BFDBB7D;
	unsigned int _0x4BFD7FA9;
	unsigned int _0x4BFD6F49;
	unsigned int _0x4BFD9071;
	unsigned int _0x48004905;
	unsigned int _0x4BFED0A5;
	unsigned int _0x4BFD75B1;
	unsigned int _0x4BFD7849;
	unsigned int _0x4BFD7AC9;
	unsigned int _0x4BFD7D19;
	unsigned int _0x4BFFEA61;
	unsigned int _0x4BFFFB9D;
	unsigned int _0x4BFFF9C1;
	unsigned int _0x4BFFFD41;
	unsigned int _0x4BFFFECD;
	unsigned int _0x4BFA0395;
	unsigned int _0x557C87FE;
	unsigned int _0x7D8802A6;
	unsigned int _0x3B800001;
	unsigned int _0x826B81E8;

	//#ifdef DEVKIT
	//	void SetAddresses()
	//	{
	//		Dvar_FindVar = 0x8232E100;
	//		Dvar_GetBool = 0x8232E2C8;
	//		Dvar_SetBool = 0x8232FE50;
	//		Dvar_GetInt = 0x8232E330;
	//		Dvar_GetFloat = 0x8232E398;
	//		Dvar_GetString = 0x8232E488;
	//		Dvar_SetStringByName = 0x823303E8;
	//		SL_GetStringOfSize = 0x822B5CF8;
	//		SL_ConvertToString = 0x822B5120;
	//		CG_GameMessage = 0x82127BF8;
	//		CG_BoldGameMessage = 0x82127C18;
	//		Cbuf_AddText = 0x82287F68;
	//		CL_AddReliableCommand = 0x821708B0;
	//		CG_VisionSetStartLerp_To = 0x82153F88;
	//		UI_GetMapName = 0x822F2580;
	//		UI_GetGameTypeName = 0x822F27A8;
	//		SEH_StringEd_GetString = 0x822F1588;
	//		Com_GetClientDObj = 0x822A28D0;
	//		CG_DObjGetWorldTagPos = 0x8211BCB8;
	//		CG_GetPlayerVelocity = 0x0; //Not Used
	//		CG_GetPlayerViewOrigin = 0x82159240;
	//		CG_LocationalTrace = 0x821631B8;
	//		BG_GetSpreadForWeapon = 0x82101B08;
	//		TransformSeed = 0x820E9C28;
	//		RandomBulletDir = 0x82159BE8;
	//		Trace_GetEntityHitId = 0x82280720;
	//		SV_IsMigrating = 0x822D0708;
	//		CL_IsServerRestarting = 0x82164170;
	//		CG_PlayRumbleOnClient = 0x82139B40;
	//		UI_PlaySound = 0x824E19D0;
	//		BG_GetAmmoInClip = 0x820E1FA0;
	//		R_TextWidth = 0x82407B00;
	//		R_TextHeight = 0x82407C80;
	//		R_AddCmdDrawText = 0x8241F9E0;
	//		R_AddCmdDrawStretchPic = 0x8241F100;
	//		CG_DrawRotatedPicPhysical = 0x82117668;
	//		Material_RegisterHandle = 0x82413F48;
	//		R_RegisterFont = 0x82407A90;
	//		ScreenPlacement = 0x82732100;
	//		R_TextLineWrapPosition = 0x82407CC8;
	//		R_ConvertColorToBytes = 0x82434C58;
	//		WeaponDef = 0x825E06E0;
	//		WeaponVariantDef = 0x825E0318;
	//		cgs_t = 0x8263EE44;
	//		cg_s = 0x8263EE60;
	//		centity_s = 0x826436B8;
	//		clientUIActive = 0x82713610;
	//		clientactive_t = 0x82713DC4;
	//		ClientNetwork_s = 0x82720EB8;
	//		BulletTrace = 0x82159330;
	//		BG_AdvanceTrace = 0x820F7EB8;
	//		BG_GetSurfacePenetrationDepth = 0x820F6F60;
	//		CG_ClientHasPerk = 0x0; //not used
	//		FireBulletPenetrate = 0x8215FB08;
	//		BG_GetPerkIndexForName = 0x820E1710;
	//		NameAddress = 0x839691A8;
	//		ClantagAddress = 0x82718A32;
	//		XAM_191 = 0x8257FF4C;
	//		RB_SetTessTechnique = 0x8244B3A8;
	//		R_EndFrame = 0x82421048;
	//		SCR_DrawScreenField = 0x8217CF90;
	//		Menu_PaintAll = 0x823091D0;
	//		CL_WritePacket = 0x8216DAF0;
	//		CG_Obituary = 0x8211CB68;
	//		CL_Disconnect = 0x821716A8;
	//		Com_Error = 0x822A17F8;
	//		NetDll_XNetGetTitleXnAddr = 0x825809CC;
	//		Com_SafeClientDObjFree = 0x822A2CF8;
	//
	//		_0x827135EC = 0x827135EC;
	//		_0x837D6CF8 = 0x837D6CF8;
	//		_0x820301BC = 0x820301BC;
	//		_0x822ECB84 = 0x822ECB84;
	//		_0x8215F9C0 = 0x8215F9C0;
	//		_0x821FDF18 = 0x821FDF18;
	//		_0x826547DC = 0x826547DC;
	//		_0x8242B438 = 0x8242B438;
	//		_0x82524DD4 = 0x82524DD4;
	//		_0x8252EEC0 = 0x8252EEC0;
	//		_0x82309A30 = 0x82309A30;
	//		_0x82182C10 = 0x82182C10;
	//		_0x82182C14 = 0x82182C14;
	//		_0x82309B84 = 0x82309B84;
	//		_0x82309B90 = 0x82309B90;
	//		_0x8217E8D8 = 0x8217E8D8;
	//		_0x8247C590 = 0x8247C590;
	//		_0x38600001 = 0x38600001;
	//		_0x4E800020 = 0x4E800020;
	//		_0x60000000 = 0x60000000;
	//		_0x390A018C = 0x390A018C;
	//		_0x822C6608 = 0x822C6608;
	//		_0x822C6890 = 0x822C6890;
	//		_0x836E5AF8 = 0x836E5AF8;
	//		_0x83D113B0 = 0x83D113B0;
	//		_0x83D113A4 = 0x83D113A4;
	//		_0x82434B90 = 0x82434B90;
	//		AngleNormalize360 = 0x82317CB8;
	//		_0x82414170 = 0x82414170;
	//		YawVectors2D = 0x82315860;
	//		_0x82732100 = 0x82732100;
	//		_0x82622C88 = 0x82622C88;
	//		CL_ClientIsInMyParty = 0x82134580;
	//		CalcCompassFriendlySize = 0x8210C228;
	//		_0x83B48890 = 0x83B48890;
	//		_0x83B49918 = 0x83B49918;
	//		_0x8261E108 = 0x8261E108;
	//		_0x8261E488 = 0x8261E488;
	//		_0x8261EA08 = 0x8261EA08;
	//		_0x8212EEA0 = 0x8212EEA0;
	//		_0x820D5A10 = 0x820D5A10;
	//		_0x8233D808 = 0x8233D808;
	//		_0x82F0CC88 = 0x82F0CC88;
	//		_0x830D1DB0 = 0x830D1DB0;
	//		_0x830CFDA8 = 0x830CFDA8;
	//		_0x830D1DA8 = 0x830D1DA8;
	//		_0xAE000000 = 0xAE000000;
	//		_0x82000000 = 0x82000000;
	//		_0x82109AD8 = 0x82109AD8;
	//		_0x8241ED18 = 0x8241ED18;
	//		_0x83D113B4 = 0x83D113B4;
	//		_0x83D11380 = 0x83D11380;
	//		_0x83D009CC = 0x83D009CC;
	//		_0x83D009D0 = 0x83D009D0;
	//		_0x822AEF48 = 0x822AEF48;
	//		_0x83ED5280 = 0x83ED5280;
	//		_0x82437E88 = 0x82437E88;
	//		_0x820DEC98 = 0x820DEC98;
	//		_0x8210BB50 = 0x8210BB50;
	//		_0x822A1770 = 0x822A1770;
	//		_0x83CFFFA8 = 0x83CFFFA8;
	//		_0x82643EC4 = 0x82643EC4;
	//		_0x82103CD8 = 0x82103CD8;
	//		_0x8210468C = 0x8210468C;
	//		_0x82104680 = 0x82104680;
	//		_0x82104698 = 0x82104698;
	//		_0x821046A4 = 0x821046A4;
	//		_0x821614D4 = 0x821614D4;
	//		_0x8210E58C = 0x8210E58C;
	//		_0x82124BD3 = 0x82124BD3;
	//		_0x82132CF0 = 0x82132CF0;
	//		_0x821331E0 = 0x821331E0;
	//		_0x82132D98 = 0x82132D98;
	//		_0x8210AF34 = 0x8210AF34;
	//		_0x822FF05C = 0x822FF05C;
	//		_0x82132C58 = 0x82132C58;
	//		_0x82132C80 = 0x82132C80;
	//		_0x82132CA8 = 0x82132CA8;
	//		_0x82132CD0 = 0x82132CD0;
	//		_0x82132E48 = 0x82132E48;
	//		_0x82132E64 = 0x82132E64;
	//		_0x82132DB4 = 0x82132DB4;
	//		_0x82132DD0 = 0x82132DD0;
	//		_0x82132DEC = 0x82132DEC;
	//		_0x82132E10 = 0x82132E10;
	//		_0x82133340 = 0x82133340;
	//		_0x82132D28 = 0x82132D28;
	//		_0x82132E2C = 0x82132E2C;
	//		_0x4BFDC379 = 0x4BFDC379;
	//		_0x4BFDC755 = 0x4BFDC755;
	//		_0x4BFDADB5 = 0x4BFDADB5;
	//		_0x4BFDB611 = 0x4BFDB611;
	//		_0x4BFD8755 = 0x4BFD8755;
	//		_0x4BFDD001 = 0x4BFDD001;
	//		_0x4827A339 = 0x4827A339;
	//		_0x4BFD9601 = 0x4BFD9601;
	//		_0x4BFDBB7D = 0x4BFDBB7D;
	//		_0x4BFD7FA9 = 0x4BFD7FA9;
	//		_0x4BFD6F49 = 0x4BFD6F49;
	//		_0x4BFD9071 = 0x4BFD9071;
	//		_0x48004905 = 0x48004905;
	//		_0x4BFED0A5 = 0x4BFED0A5;
	//		_0x4BFD75B1 = 0x4BFD75B1;
	//		_0x4BFD7849 = 0x4BFD7849;
	//		_0x4BFD7AC9 = 0x4BFD7AC9;
	//		_0x4BFD7D19 = 0x4BFD7D19;
	//		_0x4BFFEA61 = 0x4BFFEA61;
	//		_0x4BFFFB9D = 0x4BFFFB9D;
	//		_0x4BFFF9C1 = 0x4BFFF9C1;
	//		_0x4BFFFD41 = 0x4BFFFD41;
	//		_0x4BFFFECD = 0x4BFFFECD;
	//		_0x4BFA0395 = 0x4BFA0395;
	//		_0x557C87FE = 0x557C87FE;
	//		_0x7D8802A6 = 0x7D8802A6;
	//		_0x3B800001 = 0x3B800001;
	//		_0x826B81E8 = 0x826B81E8;
	//	}
	//#endif
};


enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct GAME_ADDRESS_TRANSFER_MW3
{
	mw3_addr_s* addr;

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
};

GAME_ADDRESS_TRANSFER_MW3* ExternalFunctions = 0;
mw3_addr_s* addr = 0;

int* MW3_Material_RegisterHandle(const char* name, int imageTrack);
void MW3_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void MW3_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void MW3_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);
int MW3_R_TextWidth(const char* text, int maxchars, int font);
int MW3_R_TextHeight(int font);
void MW3_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
void MW3_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material);
void MW3_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material);
const char* MW3_R_GetFontPathFromName(const char* name);
int MW3_R_RegisterFont(const char* name, int imageTrack);
int MW3_TextWidth(const char* text, const char* font);
int MW3_TextHeight(const char* font, float scale);
bool MW3_GetAsyncKeyState(DWORD KEY);
bool MW3_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive);
const char* MW3_SEH_StringEd_GetString(const char* str);
char MW3_ClampChar_r(const int i);
float MW3_DEG2RAD(float DEG);
int MW3_Dvar_GetInt(const char* Dvar);
float MW3_Dvar_GetFloat(const char* Dvar);
const char* MW3_Dvar_GetString(const char* Dvar);
bool MW3_Dvar_GetBool(const char* Dvar);
void MW3_Dvar_SetBool(const char* Dvar, bool val);
void MW3_Dvar_SetStringByName(const char* Dvar, const char*  val);
int MW3_Dvar_FindVar(const char* Dvar);
unsigned int MW3_SL_GetStringOfSize(const char *str, int user, int length, int type);
unsigned int MW3_SL_GetString(const char* str, unsigned int user);
const char* MW3_SL_ConvertToString(unsigned int stringValue);
void MW3_ApplyGamePatches();

int* MW3_Material_RegisterHandle(const char* name, int imageTrack)
{
	int*(*Material_RegisterHandle)(const char *name, int imageTrack) = (int*(*)(const char*, int))addr->Material_RegisterHandle;
	return Material_RegisterHandle(name, imageTrack);
}

void MW3_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	MW3_R_AddCmdDrawText(text, 0x7FFFFFFF, MW3_R_RegisterFont(font, 0), (x - ((MW3_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void MW3_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	MW3_R_AddCmdDrawText(text, 0x7FFFFFFF, MW3_R_RegisterFont(font, 0), (x - ((MW3_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void MW3_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	MW3_CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, MW3_Material_RegisterHandle(material, 0));
}

int MW3_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

int MW3_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

void MW3_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void MW3_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void MW3_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* MW3_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

int MW3_R_RegisterFont(const char* name, int imageTrack)
{
	static int(*R_RegisterFont)(const char * name, int imageTrack) = (int(*)(const char*, int))addr->R_RegisterFont;
	return R_RegisterFont(MW3_R_GetFontPathFromName(name), 0);
}

int MW3_TextWidth(const char* text, const char* font)
{
	return MW3_R_TextWidth(text, 0x7FFFFFFF, MW3_R_RegisterFont(font, 0));
}

int MW3_TextHeight(const char* font, float scale)
{
	return (MW3_R_TextHeight(MW3_R_RegisterFont(font, 0)) * scale);
}

bool MW3_GetAsyncKeyState(DWORD KEY)
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

bool MW3_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork, int** clientUIActive)
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

const char* MW3_SEH_StringEd_GetString(const char* str)
{
	const char*(*SEH_StringEd_GetString)(const char* str) = (const char*(*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char MW3_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float MW3_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int MW3_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char*))addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

float MW3_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char*) = (float(*)(const char*))addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

const char* MW3_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char*) = (const char*(*)(const char*))addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

bool MW3_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char*))addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

void MW3_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))addr->Dvar_SetBool;
	int pDvar = MW3_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}

void MW3_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))addr->Dvar_SetStringByName;
	int pDvar = MW3_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

int MW3_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

unsigned int MW3_SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(*)(const char *, unsigned int, unsigned int, int))addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int MW3_SL_GetString(const char* str, unsigned int user)
{
	return MW3_SL_GetStringOfSize(str, user, strlen(str) + 1, 7);
}

const char* MW3_SL_ConvertToString(unsigned int stringValue)
{
	const char*(*SL_ConvertToString)(unsigned int stringValue) = (const char*(*)(unsigned int stringValue))addr->SL_ConvertToString;
	return SL_ConvertToString(stringValue);
}

void MW3_ApplyGamePatches()
{
	*(int*)(*(int*)(addr->_0x827135EC) + 0x8) = 100; //cl_maxpackets
													 //*(int*)(*(int*)(0x827135EC) + 0x8) = 40; //snaps
													 //*(int*)(addr->_0x837D6CF8 + 0x8) = 25000; //rate

	*(int*)(addr->_0x822ECB84) = addr->_0x390A018C; //0x390A0194

													//disable impacts
	*(int*)addr->_0x8215F9C0 = addr->_0x4E800020;
	*(int*)addr->_0x821FDF18 = addr->_0x4E800020;

	//Misc
	*(char*)(*(int*)(addr->_0x826547DC) + 0x08) = 0x01; //cg_scoreboardPingText
	*(int*)addr->_0x8242B438 = addr->_0x60000000;//Fix Leader boards Credits to >el Nigel el loot lorde

#ifdef DEVKIT
	*(int*)addr->_0x82524DD4 = addr->_0x60000000;//XamUserWriteProfileSettings patch for el dev
	*(int*)addr->_0x8252EEC0 = addr->_0x60000000;
#endif

	//offensive clan tags
	*(int*)(addr->_0x82309A30) = addr->_0x38600001;
	*(int*)(addr->_0x82182C10) = addr->_0x38600001;
	*(int*)(addr->_0x82182C14) = addr->_0x4E800020;
	*(int*)(addr->_0x82309B84) = addr->_0x60000000;
	*(int*)(addr->_0x82309B90) = addr->_0x60000000;
	*(int*)(addr->_0x8217E8D8) = addr->_0x38600001;
	*(int*)(addr->_0x8247C590) = addr->_0x38600001;
}




void MW3_SetupGameAddresses(ServerData_MW3* Server)
{
	if (MW3_addr_s_Data)
		delete MW3_addr_s_Data;

	MW3_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		MW3_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	MW3_addr_s_Data = new Security(t, g_Session);
	MW3_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, MW3_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

bool MW3_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_MW3;

	if (addr)
		free(addr);

	addr = (mw3_addr_s*)malloc(sizeof(mw3_addr_s));

	for (int i = 0; i < 184; i++)
		((int*)(addr))[i] = GetAddress(MW3_addr_s_Data, MW3_addr_s_PatchID, i);

	ExternalFunctions->addr = addr;
	ExternalFunctions->SL_ConvertToString = (const char*(*)(unsigned int))(void*)ReverseInt((int)MW3_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (unsigned int(*)(const char*, unsigned int))(void*)ReverseInt((int)MW3_SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (unsigned int(*)(const char *, int, int, int))(void*)ReverseInt((int)MW3_SL_GetStringOfSize);

	ExternalFunctions->Dvar_FindVar = (int(*)(const char* Dvar))(void*)ReverseInt((int)MW3_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void(*)(const char* Dvar, const char*  val))(void*)ReverseInt((int)MW3_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void(*)(const char* Dvar, bool val))(void*)ReverseInt((int)MW3_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (bool(*)(const char* Dvar))(void*)ReverseInt((int)MW3_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (const char*(*)(const char* Dvar))(void*)ReverseInt((int)MW3_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (float(*)(const char* Dvar))(void*)ReverseInt((int)MW3_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (int(*)(const char* Dvar))(void*)ReverseInt((int)MW3_Dvar_GetInt);

	ExternalFunctions->ClampChar_r = (char(*)(const int i))(void*)ReverseInt((int)MW3_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (const char* (*)(const char* str))(void*)ReverseInt((int)MW3_SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (float(*)(float DEG))(void*)ReverseInt((int)MW3_DEG2RAD);
	ExternalFunctions->getStructures = (bool(*)(int**, int**, int**, int**, int**, int**))(void*)ReverseInt((int)MW3_getStructures);
	ExternalFunctions->ApplyPatches = (int(*)())(void*)ReverseInt((int)MW3_ApplyGamePatches);
	ExternalFunctions->GetAsyncKeyState = (bool(*)(DWORD KEY))(void*)ReverseInt((int)MW3_GetAsyncKeyState);

	ExternalFunctions->TextHeight = (int(*)(const char* font, float scale))(void*)ReverseInt((int)MW3_TextHeight);
	ExternalFunctions->TextWidth = (int(*)(const char* text, const char* font))(void*)ReverseInt((int)MW3_TextWidth);
	ExternalFunctions->R_RegisterFont = (int(*)(const char* name, int imageTrack))(void*)ReverseInt((int)MW3_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (const char* (*)(const char* name))(void*)ReverseInt((int)MW3_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void(*)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material))(void*)ReverseInt((int)MW3_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void(*)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material))(void*)ReverseInt((int)MW3_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void(*)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style))(void*)ReverseInt((int)MW3_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (int(*)(int font))(void*)ReverseInt((int)MW3_R_TextHeight);
	ExternalFunctions->R_TextWidth = (int(*)(const char* text, int maxchars, int font))(void*)ReverseInt((int)MW3_R_TextWidth);

	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void(*)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material))(void*)ReverseInt((int)MW3_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void(*)(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A))(void*)ReverseInt((int)MW3_SetTextCentered);
	ExternalFunctions->SetTextRight = (void(*)(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A))(void*)ReverseInt((int)MW3_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (int* (*)(const char* name, int imageTrack))(void*)ReverseInt((int)MW3_Material_RegisterHandle);

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_MW3)));

	return true;
}