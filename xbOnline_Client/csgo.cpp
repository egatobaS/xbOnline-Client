#include "main.h"
int VEngineClient013;
int VGUI_Surface031;
int VClientEntityList003;
int CCInputAddr;
int ClientModeAddr;
int CModelRenderAddr;
int CVRenderViewAddr;
int KeyValuesAddr;


Security * CSGO_OnHosts_addr_s_Data = 0;
unsigned int *CSGO_OnHosts_addr_s_PatchID = 0;

void CSGO_OnHosts_SetupGameAddresses(ServerData_CSGO_OnHosts* Server)
{
	if (CSGO_OnHosts_addr_s_Data)
		delete CSGO_OnHosts_addr_s_Data;

	CSGO_OnHosts_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		CSGO_OnHosts_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	CSGO_OnHosts_addr_s_Data = new Security(t, g_Session);
	CSGO_OnHosts_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, CSGO_OnHosts_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

struct csgo_addr_offhost_s
{
	unsigned int _0x86C54178;
	unsigned int _0x85D05BBC;
	unsigned int _0x886FC164;
	unsigned int _0x887302D0;
	unsigned int _0x88729A10;
	unsigned int _0x86E196C8;
	unsigned int _0x86C574BC;
	unsigned int _0x886DA354;
	unsigned int _0x86939560;
	unsigned int _0x869399F0;
	unsigned int _0x8693C8A0;
	unsigned int _0x881DB410;
	unsigned int _0x8847d140;
	unsigned int _0x868C7C28;
	unsigned int _0x8693C200;
	unsigned int _0x85C4A340;
	unsigned int _0x85C49430;
	unsigned int _0x85C44A08;
	unsigned int _0x85C45C40;
	unsigned int _0x85C45D78;
	unsigned int _0x85C45C38;
	unsigned int _0x85c4c430;
	unsigned int _0x85C44C78;
	unsigned int _0x85C45BD8;
	unsigned int _0x8693BB40;
	unsigned int _0x8693BAF0;
	unsigned int _0x88268EB0;
	unsigned int _0x881477C0;
	unsigned int _0x85C45B50;
	unsigned int _0x86A1A330;
	unsigned int _0x8699C368;
	unsigned int _0x869D7170;
	unsigned int _0x86990738;
	unsigned int _0x8853E5A8;
	unsigned int _0x881A18C0;
	unsigned int _0x000000FC;
	unsigned int _0x000000F0;
	unsigned int _0x00000100;
	unsigned int _0x000000E9;
	unsigned int _0x000016B0;
	unsigned int _0x0000025B;
	unsigned int _0x00000110;
	unsigned int _0x00001294;
	unsigned int _0x00001CB4;
	unsigned int _0x00001CBC;
	unsigned int _0x000000AC;
	unsigned int _0x00001AEC;
	unsigned int _0x00000104;
	unsigned int _0x00000310;
	unsigned int _0x000000B8;
	unsigned int _0x000000B7;
	unsigned int _0x85C839C0;
	unsigned int _0x881E6CB8;
	unsigned int _0x82CF501C;

	/*void SetAddress()
	{
		_0x86C54178 = 0x86C54178;
		_0x85D05BBC = 0x85D05BBC;
		_0x886FC164 = 0x886FC164;
		_0x887302D0 = 0x887302D0;
		_0x88729A10 = 0x88729A10;
		_0x86E196C8 = 0x86E196C8;
		_0x86C574BC = 0x86C574BC;
		_0x886DA354 = 0x886DA354;
		_0x86939560 = 0x86939560;
		_0x869399F0 = 0x869399F0;
		_0x8693C8A0 = 0x8693C8A0;
		_0x881DB410 = 0x881DB410;
		_0x8847d140 = 0x8847d140;
		_0x868C7C28 = 0x868C7C28;
		_0x8693C200 = 0x8693C200;
		_0x85C4A340 = 0x85C4A340;
		_0x85C49430 = 0x85C49430;
		_0x85C44A08 = 0x85C44A08;
		_0x85C45C40 = 0x85C45C40;
		_0x85C45D78 = 0x85C45D78;
		_0x85C45C38 = 0x85C45C38;
		_0x85c4c430 = 0x85c4c430;
		_0x85C44C78 = 0x85C44C78;
		_0x85C45BD8 = 0x85C45BD8;
		_0x8693BB40 = 0x8693BB40;
		_0x8693BAF0 = 0x8693BAF0;
		_0x88268EB0 = 0x88268EB0;
		_0x881477C0 = 0x881477C0;
		_0x85C45B50 = 0x85C45B50;
		_0x86A1A330 = 0x86A1A330;
		_0x8699C368 = 0x8699C368;
		_0x869D7170 = 0x869D7170;
		_0x86990738 = 0x86990738;
		_0x8853E5A8 = 0x8853E5A8;
		_0x881A18C0 = 0x881A18C0;
		_0x000000FC = 0x000000FC;
		_0x000000F0 = 0x000000F0;
		_0x00000100 = 0x00000100;
		_0x000000E9 = 0x000000E9;
		_0x000016B0 = 0x000016B0;
		_0x0000025B = 0x0000025B;
		_0x00000110 = 0x00000110;
		_0x00001294 = 0x00001294;
		_0x000016B0 = 0x000016B0;
		_0x00001CB4 = 0x00001CB4;
		_0x00001CBC = 0x00001CBC;
		_0x000000AC = 0x000000AC;
		_0x00001AEC = 0x00001AEC;
		_0x00000104 = 0x00000104;
		_0x00000310 = 0x00000310;
		_0x000000B8 = 0x000000B8;
		_0x000000B7 = 0x000000B7;
		_0x85C839C0 = 0x85C839C0;
		_0x881E6CB8 = 0x881E6CB8;
		_0x82CF501C = 0x82CF501C;
	}*/
};



struct GAME_ADDRESS_TRANSFER_CSGO
{
	csgo_addr_offhost_s* addr;

	void* WorldToScreenMatrix_f;
	void* GetUserCmd_f;
	void* DrawModelExecute_f;
	void* GetViewAngles_f;
	void* SetViewAngles_f;
	void* GetScreenSize_f;
	void* GetLocalClientNumber_f;
	void* GetClientEntity_f;
	void* GetHighestEntityIndex_f;
	void* isInGame_f;
	void* getPlayerInfo_f;
	void* DrawShader_f;
	void* DrawLine_f;
	void* DrawSetColor_f;
	void* DrawSetTextColor_f;
	void* DrawSetTextPos_f;
	void* DrawSetTextFont_f;
	void* DrawPrintText_f;
	void* DrawOutlinedRect_f;
	void* setupBones_f;
	void* Cbuf_AddText_f;
	void* ForcedMaterialOverride_f;
	void* SetColorModulation_f;
	void* GetTextSize_f;
	void* DrawLineWithColor;
	void* DrawText;
	void* DrawRect;
	void* createRGBA;
	void* DrawBox;
	void* PlayerBox;
	void* GetAsyncKeyState;
	void* GetScreenSize;
	void* isInGame;
	void* GetLocalClientNumber;
	void* GetClientEntity;
	void* GetHighestEntityIndex;
	void* drawCheckBox;
	void* DrawRectWithBorder;
	void* DrawTextWithBG;
	void* PopulateVtables;
};

csgo_addr_offhost_s* addr;
GAME_ADDRESS_TRANSFER_CSGO * ExternalFunctions;


//int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height);
//int(*GetLocalClientNumber_f)(int SomeStructure);
//int(*GetClientEntity_f)(int SomeStructure, int clientID);
//int(*GetHighestEntityIndex_f)(int SomeStructure);
//int(*isInGame_f)(int pVEngineClient013);
//int(*getPlayerInfo_f)(int pVEngineClient013, int id, int* info);
//void(*DrawShader_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
//void(*DrawLine_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
//void(*DrawSetColor_f)(int pVGUI_Surface031, int RGBA);
//void(*DrawSetTextColor_f)(int pVGUI_Surface031, int r, int g, int b, int a);
//void(*DrawSetTextPos_f)(int pVGUI_Surface031, int x, int y);
//void(*DrawSetTextFont_f)(int pVGUI_Surface031, int font);
//void(*DrawPrintText_f)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType);
//void(*DrawOutlinedRect_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
//bool(*setupBones_f)(int hax, int* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
//void(*Cbuf_AddText_f)(int unk, char* cmd, int localClientNum);
//void(*ForcedMaterialOverride_f)(int pCModelRenderAddr, int* mat);
//void(*SetColorModulation_f)(int pCVRenderView, int blend);
//void(*GetTextSize_f)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall);

//void(*DrawLineWithColor)(int x0, int y0, int x1, int y1, int col);
//void(*DrawText)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered);
//void(*DrawRect)(int x, int y, int w, int h, int col);
//int(*createRGBA)(int r, int g, int b, int a);
//void(*DrawBox)(float x, float y, float width, float height, int RGBA);
//void(*PlayerBox)(float x, float y, float w, float h, int clr);
//bool(*GetAsyncKeyState)(int button);
//int(*GetScreenSize)(int* width, int* height);
//int(*isInGame)();
//int(*GetLocalClientNumber)();
//int(*GetClientEntity)(int id);
//int(*GetHighestEntityIndex)();
//void(*drawCheckBox)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked);
//void(*DrawRectWithBorder)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor);
//void(*DrawTextWithBG)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor);
//void(*PopulateVtables)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr);




int GetLocalClientNumber_f_Real(int SomeStructure)
{
	int(*GetLocalClientNumber_f)(int SomeStructure) = (int(*)(int SomeStructure))addr->_0x86939560;
	return GetLocalClientNumber_f(SomeStructure);
}

int GetScreenSize_f_Real(int pVEngineClient013, int* width, int* height)
{
	int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height) = (int(*)(int pVEngineClient013, int* width, int* height))addr->_0x8693C8A0;
	return GetScreenSize_f(pVEngineClient013, width, height);
}

int GetClientEntity_f_Real(int SomeStructure, int clientID)
{
	int(*GetClientEntity_f)(int SomeStructure, int clientID) = (int(*)(int SomeStructure, int clientID))addr->_0x881DB410;
	return GetClientEntity_f(SomeStructure, clientID);
}

int GetHighestEntityIndex_f_Real(int  SomeStructure)
{
	int(*GetHighestEntityIndex_f)(int SomeStructure) = (int(*)(int SomeStructure))addr->_0x8847d140;
	return GetHighestEntityIndex_f(SomeStructure);
}

int isInGame_f_Real(int pVEngineClient013)
{
	int(*isInGame_f)(int pVEngineClient013) = (int(*)(int pVEngineClient013))addr->_0x868C7C28;
	return isInGame_f(pVEngineClient013);
}

int getPlayerInfo_f_Real(int pVEngineClient013, int id, int* info)
{
	int(*getPlayerInfo)(int pVEngineClient013, int id, int* info) = (int(*)(int pVEngineClient013, int id, int* info))addr->_0x8693C200;

	return getPlayerInfo(pVEngineClient013, id, info);
}

void DrawShader_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawShader)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C4A340;

	return DrawShader(pVGUI_Surface031, x1, y1, x2, y2);
}

void DrawLine_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawLine)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C49430;

	return DrawLine(pVGUI_Surface031, x1, y1, x2, y2);
}

void DrawSetColor_f_Real(int pVGUI_Surface031, int RGBA)
{
	void(*DrawSetColor)(int pVGUI_Surface031, int RGBA) = (void(*)(int pVGUI_Surface031, int RGBA))addr->_0x85C44A08;

	return DrawSetColor(pVGUI_Surface031, RGBA);
}

void DrawSetTextColor_f_Real(int pVGUI_Surface031, int r, int g, int b, int a)
{
	void(*DrawSetTextColor)(int pVGUI_Surface031, int r, int g, int b, int a) = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))addr->_0x85C45C40;
	return DrawSetTextColor(pVGUI_Surface031, r, g, b, a);
}

void DrawSetTextPos_f_Real(int pVGUI_Surface031, int x, int y)
{
	void(*DrawSetTextPos)(int pVGUI_Surface031, int x, int y) = (void(*)(int pVGUI_Surface031, int x, int y))addr->_0x85C45D78;
	return DrawSetTextPos(pVGUI_Surface031, x, y);;
}

void DrawSetTextFont_f_Real(int pVGUI_Surface031, int font)
{
	void(*DrawSetTextFont)(int pVGUI_Surface031, int font) = (void(*)(int pVGUI_Surface031, int font))addr->_0x85C45C38;
	return DrawSetTextFont(pVGUI_Surface031, font);
}

void DrawPrintText_f_Real(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType)
{
	void(*DrawPrintText)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType) = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))addr->_0x85c4c430;
	return DrawPrintText(pVGUI_Surface031, text, textLen, drawType);
}

void DrawOutlinedRect_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawOutlinedRect)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C44C78;
	return DrawOutlinedRect(pVGUI_Surface031, x1, y1, x2, y2);
}

int GetFontName_f_Real(int pVGUI_Surface031, unsigned int font)
{
	int(*GetFontName)(int pVGUI_Surface031, unsigned int font) = (int(*)(int, unsigned int))addr->_0x85C45BD8;
	return GetFontName(pVGUI_Surface031, font);
}


bool setupBones_f_Real(int hax, int* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	bool(*setupBones)(int hax, int* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = (bool(*)(int, int*, int, int, float))addr->_0x881477C0;

	return setupBones(hax, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}

void GetTextSize_f_Real(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall)
{
	void(*GetTextSize)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall) = (void(*)(int, int, const wchar_t*, int*, int*))addr->_0x85C45B50;
	return GetTextSize(pVGUI_Surface031, font, text, wide, tall);
}

void Cbuf_AddText_f_Real(int unk, char* cmd, int localClientNum)
{
	void(*Cbuf_AddText)(int unk, char* cmd, int localClientNum) = (void(*)(int, char*, int))addr->_0x86A1A330;
	return Cbuf_AddText(unk, cmd, localClientNum);

}

void SetColorModulation_f_Real(int pCVRenderView, int blend)
{
	void(*SetColorModulation)(int pCVRenderView, int blend) = (void(*)(int, int))addr->_0x869D7170;
	return SetColorModulation(pCVRenderView, blend);
}

void ForcedMaterialOverride_f_Real(int pCModelRenderAddr, int* mat)
{
	void(*ForcedMaterialOverride)(int pCModelRenderAddr, int* mat) = (void(*)(int, int*))addr->_0x86990738;
	return ForcedMaterialOverride(pCModelRenderAddr, mat);

}

void PopulateVtables_Real(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr)
{
	*VEngineClient013 = addr->_0x86C54178;
	*VGUI_Surface031 = addr->_0x85D05BBC;
	*VClientEntityList003 = addr->_0x886FC164;
	*CCInputAddr = addr->_0x887302D0;
	*ClientModeAddr = addr->_0x88729A10;
	*CModelRenderAddr = addr->_0x86E196C8;
	*CVRenderViewAddr = addr->_0x86C574BC;
	*KeyValuesAddr = addr->_0x886DA354;
}

void DrawLineWithColor_Real(int x0, int y0, int x1, int y1, int col)
{
	DrawSetColor_f_Real(VGUI_Surface031, col);
	DrawLine_f_Real(VGUI_Surface031, x0, y0, x1, y1);
}

void DrawText_Real(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered)
{
	DrawSetTextFont_f_Real(VGUI_Surface031, font);
	int width = 0, height = 0;
	GetTextSize_f_Real(VGUI_Surface031, font, msg, &width, &height);
	DrawSetTextColor_f_Real(VGUI_Surface031, r, g, b, a);
	DrawSetTextPos_f_Real(VGUI_Surface031, centered ? x - width / 2 : x, y);
	DrawPrintText_f_Real(VGUI_Surface031, msg, wcslen(msg), 0);
}

void DrawRect_Real(int x, int y, int w, int h, int col)
{
	DrawSetColor_f_Real(VGUI_Surface031, col);
	DrawShader_f_Real(VGUI_Surface031, x, y, x + w, y + h);
}

int createRGBA_Real(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + ((a & 0xff));
}

void DrawBox_Real(float x, float y, float width, float height, int RGBA)
{
	DrawSetColor_f_Real(VGUI_Surface031, RGBA);

	DrawOutlinedRect_f_Real(VGUI_Surface031, x, y, x + width, y + height);
}

void PlayerBox_Real(float x, float y, float w, float h, int clr)
{
	DrawSetColor_f_Real(VGUI_Surface031, clr);
	DrawOutlinedRect_f_Real(VGUI_Surface031, x - w, y, x + w, y + h);

	DrawSetColor_f_Real(VGUI_Surface031, 0x000000FF);
	DrawOutlinedRect_f_Real(VGUI_Surface031, x - w - 1, y - 1, x + w + 1, y + h + 1);
	DrawOutlinedRect_f_Real(VGUI_Surface031, x - w + 1, y + 1, x + w - 1, y + h - 1);
}

XINPUT_STATE InputState;

bool GetAsyncKeyState_Real(int button)
{
	XInputGetState(0, &InputState);

	if (button == 0) return true;

	else if (button == 0x1337) return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	else if (button == 0x1338) return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return (InputState.Gamepad.wButtons & button);
}

void DrawRectWithBorder_Real(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor)
{
	DrawRect_Real(x, y, width, height, rectColor);

	DrawRect_Real(x, y, lineWidth, height, borderColor);
	DrawRect_Real(x + lineWidth, y, width - lineWidth, lineWidth, borderColor);
	DrawRect_Real(x + lineWidth, y + height - lineWidth, width - lineWidth, lineWidth, borderColor);
	DrawRect_Real(x + (width - lineWidth), y + lineWidth, lineWidth, height - (lineWidth * 2), borderColor);
}

void drawCheckBox_Real(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked) {
	DrawRect_Real(centerX, centerY, 12, 1, outlineBoxColor);
	DrawRect_Real(centerX, centerY + 12, 12, 1, outlineBoxColor);
	DrawRect_Real(centerX, centerY, 1, 12, outlineBoxColor);
	DrawRect_Real(centerX + 12, centerY, 1, 13, outlineBoxColor);

	DrawRect_Real(centerX + 1, centerY + 1, 11, 11, ticked ? 0x00FF007D : 0xFF00007D);
}

wchar_t wc[0x2000];

const wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	//wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}


void DrawTextWithBG_Real(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor)
{
	int TextWidth = 0, TextHeight = 0, lineWidth = 3;
	GetTextSize_f_Real(VGUI_Surface031, fontName, GetWC(text), &TextWidth, &TextHeight);

	DrawRectWithBorder_Real(x - 5, y - 3, TextWidth + 10, TextHeight + 2, lineWidth, 0x00000091, menuColor);

	DrawText_Real(GetWC(text), fontName, x, y, r, g, b, a, centered);
}

int GetScreenSize_Real(int* width, int* height)
{
	return GetScreenSize_f_Real(VEngineClient013, width, height);
}

int isInGame_Real()
{
	return isInGame_f_Real(VEngineClient013);
}

int GetLocalClientNumber_Real()
{
	return GetLocalClientNumber_f_Real(VEngineClient013);
}

int GetClientEntity_Real(int id)
{
	return GetClientEntity_f_Real(VClientEntityList003, id);
}

int GetHighestEntityIndex_Real()
{
	return GetHighestEntityIndex_f_Real(VClientEntityList003);
}


void SetAddressesForGame()
{
	VEngineClient013 = addr->_0x86C54178;
	VGUI_Surface031 = addr->_0x85D05BBC;
	VClientEntityList003 = addr->_0x886FC164;
	CCInputAddr = addr->_0x887302D0;
	ClientModeAddr = addr->_0x88729A10;
	CModelRenderAddr = addr->_0x86E196C8;
	CVRenderViewAddr = addr->_0x86C574BC;
	KeyValuesAddr = addr->_0x886DA354;
}

bool CSGO_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_CSGO;

	if (addr)
		free(addr);

	addr = (csgo_addr_offhost_s*)malloc(sizeof(csgo_addr_offhost_s));

	for (int i = 0; i < 54; i++)
		((int*)(addr))[i] = GetAddress(CSGO_OnHosts_addr_s_Data, CSGO_OnHosts_addr_s_PatchID, i);

	SetAddressesForGame();

	ExternalFunctions->addr = addr;

	ExternalFunctions->GetScreenSize_f = (int(*)(int pVEngineClient013, int* width, int* height))ReverseInt((int)GetScreenSize_f_Real);
	ExternalFunctions->GetLocalClientNumber_f = (int(*)(int SomeStructure))ReverseInt((int)GetLocalClientNumber_f_Real);
	ExternalFunctions->GetClientEntity_f = (int(*)(int SomeStructure, int clientID))ReverseInt((int)GetClientEntity_f_Real);
	ExternalFunctions->GetHighestEntityIndex_f = (int(*)(int SomeStructure))ReverseInt((int)GetHighestEntityIndex_f_Real);
	ExternalFunctions->isInGame_f = (int(*)(int pVEngineClient013))ReverseInt((int)isInGame_f_Real);
	ExternalFunctions->getPlayerInfo_f = (int(*)(int pVEngineClient013, int id, int* info))ReverseInt((int)getPlayerInfo_f_Real);
	ExternalFunctions->DrawShader_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)DrawShader_f_Real);
	ExternalFunctions->DrawLine_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)DrawLine_f_Real);
	ExternalFunctions->DrawSetColor_f = (void(*)(int pVGUI_Surface031, int RGBA))ReverseInt((int)DrawSetColor_f_Real);
	ExternalFunctions->DrawSetTextColor_f = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))ReverseInt((int)DrawSetTextColor_f_Real);
	ExternalFunctions->DrawSetTextPos_f = (void(*)(int pVGUI_Surface031, int x, int y))ReverseInt((int)DrawSetTextPos_f_Real);
	ExternalFunctions->DrawSetTextFont_f = (void(*)(int pVGUI_Surface031, int font))ReverseInt((int)DrawSetTextFont_f_Real);
	ExternalFunctions->DrawPrintText_f = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))ReverseInt((int)DrawPrintText_f_Real);
	ExternalFunctions->DrawOutlinedRect_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)DrawOutlinedRect_f_Real);
	ExternalFunctions->setupBones_f = (bool(*)(int hax, int* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime))ReverseInt((int)setupBones_f_Real);
	ExternalFunctions->Cbuf_AddText_f = (void(*)(int unk, char* cmd, int localClientNum))ReverseInt((int)Cbuf_AddText_f_Real);
	ExternalFunctions->ForcedMaterialOverride_f = (void(*)(int pCModelRenderAddr, int* mat))ReverseInt((int)ForcedMaterialOverride_f_Real);
	ExternalFunctions->SetColorModulation_f = (void(*)(int pCVRenderView, int blend))ReverseInt((int)SetColorModulation_f_Real);
	ExternalFunctions->GetTextSize_f = (void(*)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall))ReverseInt((int)GetTextSize_f_Real);
	ExternalFunctions->DrawLineWithColor = (void(*)(int x0, int y0, int x1, int y1, int col))ReverseInt((int)DrawLineWithColor_Real);
	ExternalFunctions->DrawText = (void(*)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered))ReverseInt((int)DrawText_Real);
	ExternalFunctions->DrawRect = (void(*)(int x, int y, int w, int h, int col))ReverseInt((int)DrawRect_Real);
	ExternalFunctions->createRGBA = (int(*)(int r, int g, int b, int a))ReverseInt((int)createRGBA_Real);
	ExternalFunctions->DrawBox = (void(*)(float x, float y, float width, float height, int RGBA))ReverseInt((int)DrawBox_Real);
	ExternalFunctions->PlayerBox = (void(*)(float x, float y, float w, float h, int clr))ReverseInt((int)PlayerBox_Real);
	ExternalFunctions->GetAsyncKeyState = (bool(*)(int button))ReverseInt((int)GetAsyncKeyState_Real);
	ExternalFunctions->GetScreenSize = (int(*)(int* width, int* height))ReverseInt((int)GetScreenSize_Real);
	ExternalFunctions->isInGame = (int(*)())ReverseInt((int)isInGame_Real);
	ExternalFunctions->GetLocalClientNumber = (int(*)())ReverseInt((int)GetLocalClientNumber_Real);
	ExternalFunctions->GetClientEntity = (int(*)(int id))ReverseInt((int)GetClientEntity_Real);
	ExternalFunctions->GetHighestEntityIndex = (int(*)())ReverseInt((int)GetHighestEntityIndex_Real);
	ExternalFunctions->drawCheckBox = (void(*)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked))ReverseInt((int)drawCheckBox_Real);
	ExternalFunctions->DrawRectWithBorder = (void(*)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor))ReverseInt((int)DrawRectWithBorder_Real);
	ExternalFunctions->DrawTextWithBG = (void(*)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor))ReverseInt((int)DrawTextWithBG_Real);
	ExternalFunctions->PopulateVtables = (void(*)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr))ReverseInt((int)PopulateVtables_Real);

	HVGetVersionsPokeDWORD(0x800001000000BEE0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BEE4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_CSGO)));

	return true;
}