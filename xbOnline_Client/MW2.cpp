#include "main.h"

Security * MW2_addr_s_Data = 0;
Security * MW2_init_resp_s_Data = 0;

unsigned int *MW2_addr_s_PatchID = 0;
unsigned int *MW2_init_resp_s_PatchID = 0;

enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

struct mw2_addr_s
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

	//Game Threading
	unsigned int Sys_CreateThread;
	unsigned int Sys_ResumeThread;
	unsigned int ThreadStorage;
	unsigned int SetThreadProcessor;
	unsigned int CM_InitThreadData;
	unsigned int Com_InitThreadData;

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


	//void SetAddresses()
	//{
	//	Dvar_FindVar = 0x8229ED20;//
	//	Dvar_GetBool = 0x8229EEE8;//
	//	Dvar_SetBool = 0x822A0998;//
	//	Dvar_GetInt = 0x8229EF50;//
	//	Dvar_GetFloat = 0x8229EFB8;//
	//	Dvar_GetString = 0x8229F0A8;//
	//	Dvar_SetStringByName = 0x822A0F30;//
	//	SL_GetStringOfSize = 0x82241E90;//
	//	SL_ConvertToString = 0x82241898;//
	//	CG_GameMessage = 0x821071D0;//
	//	CG_BoldGameMessage = 0x821071F0;//
	//	Cbuf_AddText = 0x82224990;//
	//	CL_AddReliableCommand = 0x82142BB8;//
	//	CG_VisionSetStartLerp_To = 0x8212A380;//
	//	UI_GetMapName = 0x822729A0;//
	//	UI_GetGameTypeName = 0x82272BD0;//
	//	SEH_StringEd_GetString = 0x82261278;//
	//	Com_GetClientDObj = 0x8222FCC0;//
	//	CG_DObjGetWorldTagPos = 0x820FB9E8;//
	//	CG_GetPlayerVelocity = 0x0;
	//	CG_GetPlayerViewOrigin = 0x8212E670;//
	//	CG_LocationalTrace = 0x82136E88;//
	//	BG_GetSpreadForWeapon = 0x820E33F0;//
	//	TransformSeed = 0x820D94B8;//
	//	RandomBulletDir = 0x8212EF78;//
	//	Trace_GetEntityHitId = 0x8221DAD0;//
	//	SV_IsMigrating = 0x8225A0B8;//
	//	CL_IsServerRestarting = 0x82137D48;//
	//	CG_PlayRumbleOnClient = 0x82116398;//
	//	UI_PlaySound = 0x8232B660;//
	//	BG_GetAmmoInClip = 0x820DB108;//
	//	R_TextWidth = 0x8234DD20;//
	//	R_TextHeight = 0x8234DE10;//
	//	R_AddCmdDrawText = 0x82350278;//
	//	R_AddCmdDrawStretchPic = 0x8234F9B8;//
	//	CG_DrawRotatedPicPhysical = 0x820F7900;//
	//	Material_RegisterHandle = 0x8234E510;//
	//	R_RegisterFont = 0x8234DCB0;//
	//	ScreenPlacement = 0x82690F40;//
	//	R_TextLineWrapPosition = 0x8234DE58;//
	//	R_ConvertColorToBytes = 0x8238A490;//
	//	Sys_CreateThread = 0x8223CA28;//
	//	Sys_ResumeThread = 0x8223CC00;//
	//	ThreadStorage = 0x83372254;//
	//	SetThreadProcessor = 0x823311A8;//
	//	CM_InitThreadData = 0x82290A78;//
	//	Com_InitThreadData = 0x822A70E8;//
	//	WeaponDef = 0x8255A320;//
	//	WeaponVariantDef = 0x82557750;//
	//	cgs_t = 0x825B861C;//
	//	cg_s = 0x825B8638;
	//	centity_s = 0x825BE150;
	//	clientactive_t = 0x82682350;//
	//	ClientNetwork_s = 0x8268EEB0;//
	//	BulletTrace = 0x8212E760;//
	//	BG_AdvanceTrace = 0x820E2A78;//
	//	BG_GetSurfacePenetrationDepth = 0x820E2178;//
	//	CG_ClientHasPerk = 0x0;
	//	FireBulletPenetrate = 0x82134648;//
	//	BG_GetPerkIndexForName = 0x820D1700;//
	//	NameAddress = 0x838BA824;//
	//	ClantagAddress = 0x82687068;//
	//	XAM_191 = 0x823B64C4;//
	//	RB_SetTessTechnique = 0x82373B18;//
	//	R_EndFrame = 0x82351748;//
	//	SCR_DrawScreenField = 0x8214BEB8;//
	//	Menu_PaintAll = 0x82285E98;//
	//	CL_WritePacket = 0x821402E0;//
	//	CG_Obituary = 0x820FC908;//
	//	CL_Disconnect = 0x82143420;//
	//	Com_Error = 0x8222EAB8;//
	//	NetDll_XNetGetTitleXnAddr = 0x823B69B4;//
	//	Com_SafeClientDObjFree = 0x822300A0;//
	//}

};

struct mw2_init_addr_s
{
	unsigned int _0x822AE2E4;
	unsigned int _0x822AE2F8;
	unsigned int _0x822AE2FC;
	unsigned int _0x8226DB68;
	unsigned int _0x8226DB74;
	unsigned int _0x8226DB80;
	unsigned int _0x8226DB7C;
	unsigned int _0x82134510;
	unsigned int _0x821A4A58;
	unsigned int _0x822CBE80;
	unsigned int _0x820C588C;
	unsigned int _0x822AE400;
	unsigned int _0x82273B44;
	unsigned int _0x82273D10;
	unsigned int _0x82273D1C;
	unsigned int _0x8214D458;
	unsigned int _0x82273BB0;
	unsigned int _0x82273BC8;
	unsigned int _0x82273BE0;
	unsigned int _0x825CED7C;
	unsigned int _0x83759678;
	unsigned int _0x83759B84;
	unsigned int _0x83759B40;

	/*#if defined(DEVKIT)
	void SetAddresses()
	{
	_0x822AE2E4 = 0x822AE2E4;
	_0x822AE2F8 = 0x822AE2F8;
	_0x822AE2FC = 0x822AE2FC;
	_0x8226DB68 = 0x8226DB68;
	_0x8226DB74 = 0x8226DB74;
	_0x8226DB80 = 0x8226DB80;
	_0x8226DB7C = 0x8226DB7C;
	_0x82134510 = 0x82134510;
	_0x821A4A58 = 0x821A4A58;
	_0x822CBE80 = 0x822CBE80;
	_0x820C588C = 0x820C588C;
	_0x822AE400 = 0x822AE400;
	_0x82273B44 = 0x82273B44;
	_0x82273D10 = 0x82273D10;
	_0x82273D1C = 0x82273D1C;
	_0x8214D458 = 0x8214D458;
	_0x82273BB0 = 0x82273BB0;
	_0x82273BC8 = 0x82273BC8;
	_0x82273BE0 = 0x82273BE0;
	_0x825CED7C = 0x825CED7C;
	_0x83759678 = 0x83759678;
	_0x83759B84 = 0x83759B84;
	_0x83759B40 = 0x83759B40;
	}
	#endif*/

};

struct mw2_init_resp_s
{
	int _0000025000;
	int _0000000040;
	int _0000000100;
	int _0x3D608200;
	int _0x7C1F5800;
	int _0x4181002C;
	int _0x3D208202;
	int _0x38892F8C;
	int _0x7C9D2378;
	int _0x4E800020;
	int _0x2B030000;
	int _0x60000000;
	int _0x38600001;

	//#if defined(DEVKIT)
	void SetAddresses()
	{
		_0000025000 = 0000025000;
		_0000000040 = 0000000040;
		_0000000100 = 0000000100;
		_0x3D608200 = 0x3D608200;
		_0x7C1F5800 = 0x7C1F5800;
		_0x4181002C = 0x4181002C;
		_0x3D208202 = 0x3D208202;
		_0x38892F8C = 0x38892F8C;
		_0x7C9D2378 = 0x7C9D2378;
		_0x4E800020 = 0x4E800020;
		_0x2B030000 = 0x2B030000;
		_0x60000000 = 0x60000000;
		_0x38600001 = 0x38600001;
	}
	//#endif

};

struct GAME_ADDRESS_TRANSFER_MW2
{
	mw2_addr_s* addr;
	mw2_init_resp_s * init_resp;
	mw2_init_addr_s* init_addr;

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

GAME_ADDRESS_TRANSFER_MW2* ExternalFunctions;

mw2_addr_s* addr = 0;
mw2_init_resp_s * init_resp = 0;
mw2_init_addr_s* init_addr = 0;

void MW2_ApplyGamePatches();
const char* MW2_SL_ConvertToString(unsigned int stringValue);
unsigned int MW2_SL_GetString(const char* str, unsigned int user);
unsigned int MW2_SL_GetStringOfSize(const char *str, int user, int length, int type);
int MW2_Dvar_FindVar(const char* Dvar);
void MW2_Dvar_SetStringByName(const char* Dvar, const char*  val);
void MW2_Dvar_SetBool(const char* Dvar, bool val);
bool MW2_Dvar_GetBool(const char* Dvar);
const char* MW2_Dvar_GetString(const char* Dvar);
float MW2_Dvar_GetFloat(const char* Dvar);
int MW2_Dvar_GetInt(const char* Dvar);
float MW2_DEG2RAD(float DEG);
char MW2_ClampChar_r(const int i);
const char* MW2_SEH_StringEd_GetString(const char* str);
bool MW2_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork);
bool MW2_GetAsyncKeyState(DWORD KEY);
int MW2_TextHeight(const char* font, float scale);
int MW2_TextWidth(const char* text, const char* font);
int MW2_R_RegisterFont(const char* name, int imageTrack);
const char* MW2_R_GetFontPathFromName(const char* name);
void MW2_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material);
void MW2_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material);
void MW2_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style);
int MW2_R_TextHeight(int font);
int MW2_R_TextWidth(const char* text, int maxchars, int font);
void MW2_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material);
void MW2_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
void MW2_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A);
int* MW2_Material_RegisterHandle(const char* name, int imageTrack);

int* MW2_Material_RegisterHandle(const char* name, int imageTrack)
{
	int*(*Material_RegisterHandle)(const char *name, int imageTrack) = (int*(*)(const char*, int))addr->Material_RegisterHandle;

	return Material_RegisterHandle(name, imageTrack);
}

void MW2_SetTextRight(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	MW2_R_AddCmdDrawText(text, 0x7FFFFFFF, MW2_R_RegisterFont(font, 0), (x - ((MW2_TextWidth(text, font)) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void MW2_SetTextCentered(const char *text, const char* font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)
{
	float Color[4] = { R, G, B, A };
	MW2_R_AddCmdDrawText(text, 0x7FFFFFFF, MW2_R_RegisterFont(font, 0), (x - ((MW2_TextWidth(text, font) / 2) * xScale)), y, xScale, yScale, 0, Color, 0);
}

void MW2_R_AddCmdDrawStretchPicRotateXY(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float Angle, float *color, const char* material)
{
	MW2_CG_DrawRotatedPicPhysical(addr->ScreenPlacement, x, y, w, h, Angle, color, MW2_Material_RegisterHandle(material, 0));
}

int MW2_R_TextWidth(const char* text, int maxchars, int font)
{
	int(*R_TextWidth)(const char* text, int maxchars, int font) = (int(*)(const char*, int, int))addr->R_TextWidth;
	return R_TextWidth(text, maxchars, font);
}

int MW2_R_TextHeight(int font)
{
	int(*R_TextHeight)(int font) = (int(__cdecl*)(int))addr->R_TextHeight;
	return R_TextHeight(font);
}

void MW2_R_AddCmdDrawText(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style)
{
	void(*R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(*)(const char*, int, int, float, float, float, float, float, float*, int))addr->R_AddCmdDrawText;
	R_AddCmdDrawText(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
}

void MW2_R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material)
{
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int* material) = (void(*)(float, float, float, float, float, float, float, float, float*, int*))addr->R_AddCmdDrawStretchPic;
	R_AddCmdDrawStretchPic(x, y, w, h, s0, t0, s1, t1, color, material);
}

void MW2_CG_DrawRotatedPicPhysical(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material)
{
	void(*CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int* material) = (void(*)(int, float, float, float, float, float, float*, int*))addr->CG_DrawRotatedPicPhysical;
	CG_DrawRotatedPicPhysical(ScreenPlacement, x, y, width, height, angle, color, material);
}

const char* MW2_R_GetFontPathFromName(const char* name)
{
	static char Buffer[0x200];
	ZeroMemory(Buffer, sizeof(Buffer));
	_snprintf(Buffer, sizeof(Buffer), "fonts/%s", name);
	return Buffer;
}

int MW2_R_RegisterFont(const char* name, int imageTrack)
{
	static int(__cdecl *R_RegisterFont)(const char * name, int imageTrack) = (int(__cdecl*)(const char*, int))addr->R_RegisterFont;
	return R_RegisterFont(MW2_R_GetFontPathFromName(name), 0);
}

int MW2_TextWidth(const char* text, const char* font)
{
	return MW2_R_TextWidth(text, 0x7FFFFFFF, MW2_R_RegisterFont(font, 0));
}

int MW2_TextHeight(const char* font, float scale)
{
	return (MW2_R_TextHeight(MW2_R_RegisterFont(font, 0)) * scale);
}

bool MW2_GetAsyncKeyState(DWORD KEY)
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

bool MW2_getStructures(int** cgs, int** cg, int** Entity, int** ClientActive_t, int** ClientNetwork)
{
	*cgs = *(int**)addr->cgs_t;
	*cg = *(int**)addr->cg_s;
	*Entity = *(int**)addr->centity_s;
	*ClientActive_t = *(int**)addr->clientactive_t;
	*ClientNetwork = (int*)addr->ClientNetwork_s;

	if (!*(int*)addr->cgs_t || !*(int*)addr->cg_s || !*(int*)addr->centity_s || !*(int*)addr->clientactive_t) return false;
	return true;
}

const char* MW2_SEH_StringEd_GetString(const char* str)
{
	const char*(__cdecl *SEH_StringEd_GetString)(const char* str) = (const char*(__cdecl*)(const char*))addr->SEH_StringEd_GetString;
	return SEH_StringEd_GetString(str);
}

char MW2_ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float MW2_DEG2RAD(float DEG)
{
	return ((DEG * 3.14159265358979323846f) / 180.0f);
}

int MW2_Dvar_GetInt(const char* Dvar)
{
	int(*Dvar_GetInt)(const char* Dvar) = (int(*)(const char*))addr->Dvar_GetInt;
	return Dvar_GetInt(Dvar);
}

float MW2_Dvar_GetFloat(const char* Dvar)
{
	float(*Dvar_GetFloat)(const char*) = (float(*)(const char*))addr->Dvar_GetFloat;
	return Dvar_GetFloat(Dvar);
}

const char* MW2_Dvar_GetString(const char* Dvar)
{
	const char*(*Dvar_GetString)(const char*) = (const char*(*)(const char*))addr->Dvar_GetString;
	return Dvar_GetString(Dvar);
}

bool MW2_Dvar_GetBool(const char* Dvar)
{
	bool(*Dvar_GetBool)(const char* Dvar) = (bool(*)(const char*))addr->Dvar_GetBool;
	return Dvar_GetBool(Dvar);
}

void MW2_Dvar_SetBool(const char* Dvar, bool val)
{
	bool(*Dvar_SetBool)(int dvar, bool val) = (bool(*)(int, bool))addr->Dvar_SetBool;
	int pDvar = MW2_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetBool(pDvar, val);
}

void MW2_Dvar_SetStringByName(const char* Dvar, const char*  val)
{
	bool(*Dvar_SetString)(int dvar, const char*  val) = (bool(*)(int, const char*))addr->Dvar_SetStringByName;
	int pDvar = MW2_Dvar_FindVar(Dvar);
	if (pDvar)
		Dvar_SetString(pDvar, val);
}

int MW2_Dvar_FindVar(const char* Dvar)
{
	int(*Dvar_FindVar)(const char* Dvar) = (int(*)(const char*))addr->Dvar_FindVar;
	return Dvar_FindVar(Dvar);
}

unsigned int MW2_SL_GetStringOfSize(const char *str, int user, int length, int type)
{
	unsigned int(__cdecl*SL_GetStringOfSize)(const char *str, unsigned int user, unsigned int length, int type) = (unsigned int(__cdecl*)(const char *, unsigned int, unsigned int, int))addr->SL_GetStringOfSize;
	return SL_GetStringOfSize(str, user, length, type);
}

unsigned int MW2_SL_GetString(const char* str, unsigned int user)
{
	return MW2_SL_GetStringOfSize(str, user, strlen(str) + 1, 7);
}

const char* MW2_SL_ConvertToString(unsigned int stringValue)
{
	const char*(*SL_ConvertToString)(unsigned int stringValue) = (const char*(*)(unsigned int stringValue))addr->SL_ConvertToString;
	return SL_ConvertToString(stringValue);
}

void MW2_ApplyGamePatches()
{
	*(int*)0x822AE304 = 0x3D608200;
	*(int*)0x822AE318 = 0x7C1F5800;
	*(int*)0x822AE31C = 0x4181002C;

	//version number 
	*(int*)(0x8226DAF8) = 0x3D208202;
	*(int*)(0x8226DB04) = 0x3889315C;
	*(int*)(0x8226DB10) = 0x7C9D2378;
	*(int*)(0x8226DB0C) = 0x60000000;

	//disable impacts
	*(int*)0x82134510 = 0x4E800020;
	*(int*)0x821A4A50 = 0x4E800020;

	//Misc
	*(int*)0x822CBEA0 = 0x60000000;
	*(char*)(*(int*)(0x825CED7C) + 0x08) = 0x01; //cg_scoreboardPingText
	*(int*)0x820C588C = 0x60000000; //Com_Error Tagpos
	*(int*)0x822AE420 = 0x2B030000; //AimTarget_GetTagPos

									//offensive clan tags 
	*(int*)(0x82273AD4) = 0x38600001;
	*(int*)(0x82273CA0) = 0x60000000;
	*(int*)(0x82273CAC) = 0x60000000;
	*(int*)(0x8214D448) = 0x38600001;

	//IW bypass
	*(int*)(0x82273B40) = 0x60000000;
	*(int*)(0x82273B58) = 0x60000000;
	*(int*)(0x82273B70) = 0x60000000;


	////Dobj fix
	//*(int*)init_addr->_0x822AE2E4 = init_resp->_0x3D608200;
	//*(int*)init_addr->_0x822AE2F8 = init_resp->_0x7C1F5800;
	//*(int*)init_addr->_0x822AE2FC = init_resp->_0x4181002C;

	////Dvars for no spread
	//*(int*)(init_addr->_0x83759678 + 0x8) = init_resp->_0000000100;
	//*(int*)(init_addr->_0x83759B84 + 0x8) = init_resp->_0000000040;
	//*(int*)(init_addr->_0x83759B40 + 0x8) = init_resp->_0000025000;

	////version number 
	//*(int*)(init_addr->_0x8226DB68) = init_resp->_0x3D208202;
	//*(int*)(init_addr->_0x8226DB74) = init_resp->_0x38892F8C;
	//*(int*)(init_addr->_0x8226DB80) = init_resp->_0x7C9D2378;
	//*(int*)(init_addr->_0x8226DB7C) = init_resp->_0x60000000;

	////disable impacts
	//*(int*)init_addr->_0x82134510 = init_resp->_0x4E800020;
	//*(int*)init_addr->_0x821A4A58 = init_resp->_0x4E800020;

	////Misc
	//*(int*)init_addr->_0x822CBE80 = init_resp->_0x60000000;
	//*(char*)(*(int*)(init_addr->_0x825CED7C) + 0x08) = 0x01; //cg_scoreboardPingText
	//*(int*)init_addr->_0x820C588C = init_resp->_0x60000000; //Com_Error Tagpos
	//*(int*)init_addr->_0x822AE400 = init_resp->_0x2B030000; //AimTarget_GetTagPos

	//								//offensive clan tags 
	//*(int*)(init_addr->_0x82273B44) = init_resp->_0x38600001;
	//*(int*)(init_addr->_0x82273D10) = init_resp->_0x60000000;
	//*(int*)(init_addr->_0x82273D1C) = init_resp->_0x60000000;
	//*(int*)(init_addr->_0x8214D458) = init_resp->_0x38600001;

	////IW bypass
	//*(int*)(init_addr->_0x82273BB0) = init_resp->_0x60000000;
	//*(int*)(init_addr->_0x82273BC8) = init_resp->_0x60000000;
	//*(int*)(init_addr->_0x82273BE0) = init_resp->_0x60000000;

	//DObj Fix TODO: Update
	//*(int*)(0x821AD8A0) = 0x48000090;
}


void MW2_SetupGameAddresses(ServerData_MW2* Server) {

	if (MW2_addr_s_Data)
		delete MW2_addr_s_Data;

	if (MW2_init_resp_s_Data)
		delete MW2_init_resp_s_Data;

	MW2_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];
	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {
		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		MW2_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	MW2_init_resp_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];
	unsigned int *init_resp_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_init_addr_s_XexAddrNum)];

	for (int i = 0; i < _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum); i++) {
		init_resp_s_PatchFile[i] = Server->Server_init_addr_s[i];
		MW2_init_resp_s_PatchID[i] = Server->Server_init_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	MW2_addr_s_Data = new Security(t, g_Session);
	MW2_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, MW2_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	time(&t);

	Sleep(100);

	MW2_init_resp_s_Data = new Security(t, g_Session);
	MW2_init_resp_s_Data->ProcessAddressFile(init_resp_s_PatchFile, MW2_init_resp_s_PatchID, _byteswap_ulong(Server->Server_init_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
	delete[] init_resp_s_PatchFile;
}


bool MW2_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_MW2;

	if (init_resp)
		free(init_resp);

	if (init_addr)
		free(init_addr);

	if (addr)
		free(addr);

	init_resp = (mw2_init_resp_s*)malloc(sizeof(mw2_init_resp_s));
	init_addr = (mw2_init_addr_s*)malloc(sizeof(mw2_init_addr_s));
	addr = (mw2_addr_s*)malloc(sizeof(mw2_addr_s));

	for (int i = 0; i < 73; i++)
		((int*)(addr))[i] = GetAddress(MW2_addr_s_Data, MW2_addr_s_PatchID, i);

	for (int i = 0; i < 23; i++)
		((int*)(init_addr))[i] = GetAddress(MW2_init_resp_s_Data, MW2_init_resp_s_PatchID, i);

	init_resp->SetAddresses();
	//addr->SetAddresses();

	//CWriteFile("xbOnline:\\addr.bin", addr, sizeof(mw2_addr_s));

	//init_addr->SetAddresses();
	//addr->SetAddresses();

	ExternalFunctions->addr = addr;
	ExternalFunctions->init_resp = init_resp;
	ExternalFunctions->init_addr = init_addr;

	ExternalFunctions->SL_ConvertToString = (void*)ReverseInt((int)MW2_SL_ConvertToString);
	ExternalFunctions->SL_GetString = (void*)ReverseInt((int)MW2_SL_GetString);
	ExternalFunctions->SL_GetStringOfSize = (void*)ReverseInt((int)MW2_SL_GetStringOfSize);
	ExternalFunctions->Dvar_FindVar = (void*)ReverseInt((int)MW2_Dvar_FindVar);
	ExternalFunctions->Dvar_SetStringByName = (void*)ReverseInt((int)MW2_Dvar_SetStringByName);
	ExternalFunctions->Dvar_SetBool = (void*)ReverseInt((int)MW2_Dvar_SetBool);
	ExternalFunctions->Dvar_GetBool = (void*)ReverseInt((int)MW2_Dvar_GetBool);
	ExternalFunctions->Dvar_GetString = (void*)ReverseInt((int)MW2_Dvar_GetString);
	ExternalFunctions->Dvar_GetFloat = (void*)ReverseInt((int)MW2_Dvar_GetFloat);
	ExternalFunctions->Dvar_GetInt = (void*)ReverseInt((int)MW2_Dvar_GetInt);
	ExternalFunctions->ClampChar_r = (void*)ReverseInt((int)MW2_ClampChar_r);
	ExternalFunctions->SEH_StringEd_GetString = (void*)ReverseInt((int)MW2_SEH_StringEd_GetString);
	ExternalFunctions->DEG2RAD = (void*)ReverseInt((int)MW2_DEG2RAD);
	ExternalFunctions->getStructures = (void*)ReverseInt((int)MW2_getStructures);
	ExternalFunctions->ApplyPatches = (void*)ReverseInt((int)MW2_ApplyGamePatches);
	ExternalFunctions->GetAsyncKeyState = (void*)ReverseInt((int)MW2_GetAsyncKeyState);
	ExternalFunctions->TextHeight = (void*)ReverseInt((int)MW2_TextHeight);
	ExternalFunctions->TextWidth = (void*)ReverseInt((int)MW2_TextWidth);
	ExternalFunctions->R_RegisterFont = (void*)ReverseInt((int)MW2_R_RegisterFont);
	ExternalFunctions->R_GetFontPathFromName = (void*)ReverseInt((int)MW2_R_GetFontPathFromName);
	ExternalFunctions->CG_DrawRotatedPicPhysical = (void*)ReverseInt((int)MW2_CG_DrawRotatedPicPhysical);
	ExternalFunctions->R_AddCmdDrawStretchPic = (void*)ReverseInt((int)MW2_R_AddCmdDrawStretchPic);
	ExternalFunctions->R_AddCmdDrawText = (void*)ReverseInt((int)MW2_R_AddCmdDrawText);
	ExternalFunctions->R_TextHeight = (void*)ReverseInt((int)MW2_R_TextHeight);
	ExternalFunctions->R_TextWidth = (void*)ReverseInt((int)MW2_R_TextWidth);
	ExternalFunctions->R_AddCmdDrawStretchPicRotateXY = (void*)ReverseInt((int)MW2_R_AddCmdDrawStretchPicRotateXY);
	ExternalFunctions->SetTextCentered = (void*)ReverseInt((int)MW2_SetTextCentered);
	ExternalFunctions->SetTextRight = (void*)ReverseInt((int)MW2_SetTextRight);
	ExternalFunctions->Material_RegisterHandle = (void*)ReverseInt((int)MW2_Material_RegisterHandle);

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_MW2)));


	return true;
}