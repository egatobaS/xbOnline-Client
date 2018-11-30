#include "main.h"

int VEngineClient013_tf2 = 0;
int VGUI_Surface031_tf2 = 0;

Security * tf2_addr_s_Data = 0;
unsigned int *tf2_addr_s_PatchID = 0;

struct tf2_addr_offhost_s
{
	unsigned int _0x8452BF60;
	unsigned int _0x8452BBA8;
	unsigned int _0x845285B0;
	unsigned int _0x84528C40;
	unsigned int _0x84528D80;
	unsigned int _0x84528C38;
	unsigned int _0x8452CF18;
	unsigned int _0x84528658;
	unsigned int _0x84528C10;
	unsigned int _0x84528BD0;
	unsigned int _0x8609A848;
	unsigned int _0x86162760;
	unsigned int _0x86164550;
	unsigned int _0x86164B30;
	unsigned int _0x872F5298;
	unsigned int _0x8639a894;
	unsigned int _0x845C5460;
	unsigned int _0x00001337;
	unsigned int _0x00001338;
	unsigned int _0x00000091;
	unsigned int _0x000000FF;
	unsigned int _0x00FF007D;
	unsigned int _0xFF00007D;
	unsigned int _0x84544280;
	unsigned int _0x8309EE58;
	unsigned int _0x87180080;
	unsigned int _0xF5B0DCFB;
	unsigned int _0x872CF1C0;
	unsigned int _0x000004F4;
	unsigned int _0x77BA7751;
	unsigned int _0x873134B0;
	unsigned int _0x0000074C;
	unsigned int _0x00000088;
	unsigned int _0x00000090;
	unsigned int _0x000002DC;
	unsigned int _0x00000698;
	unsigned int _0x8857E100;
	unsigned int _0x00000778;
	unsigned int _0x000000E9;
	unsigned int _0x000006AB;
	unsigned int _0x00000456;
	unsigned int _0x00000648;
	unsigned int _0x000016B0;
	unsigned int _0x00000087;
	unsigned int _0x000000E8;
	unsigned int _0x00001294;
	unsigned int _0x00001CB4;
	unsigned int _0x00001CBC;
	unsigned int _0x000001F4;
	unsigned int _0x0000148C;
	unsigned int _0x00001AEC;
	unsigned int _0x000000DC;
	unsigned int _0x00000030;
	unsigned int _0x00000160;
	unsigned int _0xFFFFFF80;
	unsigned int _0x000002D0;
	unsigned int _0x00FF00FF;
	unsigned int _0xFF0000FF;
	unsigned int _0x00000008;
	unsigned int _0x00000009;
};

tf2_addr_offhost_s* tf2_addr;

struct GAME_ADDRESS_TRANSFER_TF2
{
	tf2_addr_offhost_s* addr;

	void* DrawShader_f;
	void* DrawLine_f;
	void* DrawSetColor_f;
	void* DrawSetTextColor_f;
	void* DrawSetTextPos_f;
	void* DrawSetTextFont_f;
	void* DrawPrintText_f;
	void* DrawOutlinedRect_f;
	void* GetFontName_f;
	void* GetTextSize_f;
	void* Cbuf_AddText_f;
	void* GetLocalClientNumber_f;
	void* getPlayerInfo_f;
	void* GetScreenSize_f;
	void* IsInGame_f;
	void* SetVTables;
	void* createRGBA;
	void* createRGB;
	void* GetAsyncKeyState;
	void* DrawLineWithColor;
	void* GetScreenSize;
	void* GetLocalClientNumber;
	void* DrawText;
	void* DrawRect;
	void* DrawBox;
	void* PlayerBox;
	void* DrawRectWithBorder;
	void* drawCheckBox;
	void* DrawTextWithBG;
	void* GetWC;

};

GAME_ADDRESS_TRANSFER_TF2* ExternalFunctions;

void tf2_SetupGameAddresses(ServerData_tf2* Server)
{
	if (tf2_addr_s_Data)
		delete tf2_addr_s_Data;

	tf2_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		tf2_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	tf2_addr_s_Data = new Security(t, g_Session);
	tf2_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, tf2_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

wchar_t *GetWC_tf2_Real(const char *c);

void DrawShader_f_tf2_Real(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2)
{
	void(*DrawShader_f)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))tf2_addr->_0x8452BF60;
	DrawShader_f(pVGUI_Surface031_tf2, x1, y1, x2, y2);
}

void DrawLine_f_tf2_Real(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2)
{
	void(*DrawLine_f)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))tf2_addr->_0x8452BBA8;
	DrawLine_f(pVGUI_Surface031_tf2, x1, y1, x2, y2);
}

void DrawSetColor_f_tf2_Real(int pVGUI_Surface031_tf2, int RGBA)
{
	void(*DrawSetColor_f)(int pVGUI_Surface031_tf2, int RGBA) = (void(*)(int pVGUI_Surface031_tf2, int RGBA))tf2_addr->_0x845285B0;
	DrawSetColor_f(pVGUI_Surface031_tf2, RGBA);
}

void DrawSetTextColor_f_tf2_Real(int pVGUI_Surface031_tf2, int r, int g, int b, int a)
{
	void(*DrawSetTextColor_f)(int pVGUI_Surface031_tf2, int r, int g, int b, int a) = (void(*)(int pVGUI_Surface031_tf2, int r, int g, int b, int a))tf2_addr->_0x84528C40;
	DrawSetTextColor_f(pVGUI_Surface031_tf2, r, g, b, a);
}

void DrawSetTextPos_f_tf2_Real(int pVGUI_Surface031_tf2, int x, int y)
{
	void(*DrawSetTextPos_f)(int pVGUI_Surface031_tf2, int x, int y) = (void(*)(int pVGUI_Surface031_tf2, int x, int y))tf2_addr->_0x84528D80;
	DrawSetTextPos_f(pVGUI_Surface031_tf2, x, y);
}

void DrawSetTextFont_f_tf2_Real(int pVGUI_Surface031_tf2, int font)
{
	void(*DrawSetTextFont_f)(int pVGUI_Surface031_tf2, int font) = (void(*)(int pVGUI_Surface031_tf2, int font))tf2_addr->_0x84528C38;
	DrawSetTextFont_f(pVGUI_Surface031_tf2, font);
}

void DrawPrintText_f_tf2_Real(int pVGUI_Surface031_tf2, const wchar_t *text, int textLen, int drawType)
{
	void(*DrawPrintText_f)(int pVGUI_Surface031_tf2, const wchar_t *text, int textLen, int drawType) = (void(*)(int pVGUI_Surface031_tf2, const wchar_t *text, int textLen, int drawType))tf2_addr->_0x8452CF18;
	DrawPrintText_f(pVGUI_Surface031_tf2, text, textLen, drawType);
}

void DrawOutlinedRect_f_tf2_Real(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2)
{
	void(*DrawOutlinedRect_f)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))tf2_addr->_0x84528658;
	DrawOutlinedRect_f(pVGUI_Surface031_tf2, x1, y1, x2, y2);
}

int GetFontName_f_tf2_Real(int pVGUI_Surface031_tf2, unsigned int font)
{
	int(*GetFontName_f)(int pVGUI_Surface031_tf2, unsigned int font) = (int(*)(int, unsigned int))tf2_addr->_0x84528C10;
	return GetFontName_f(pVGUI_Surface031_tf2, font);
}

void GetTextSize_f_tf2_Real(int pVGUI_Surface031_tf2, int font, const wchar_t *text, int* wide, int* tall)
{
	void(*GetTextSize_f)(int pVGUI_Surface031_tf2, int font, const wchar_t *text, int* wide, int* tall) = (void(*)(int, int, const wchar_t*, int*, int*))tf2_addr->_0x84528BD0;
	GetTextSize_f(pVGUI_Surface031_tf2, font, text, wide, tall);
}

void Cbuf_AddText_f_tf2_Real(char* cmd, int unk)
{
	void(*Cbuf_AddText_f)(char* cmd, int unk) = (void(*)(char*, int))tf2_addr->_0x8609A848;
	Cbuf_AddText_f(cmd, unk);
}

int GetLocalClientNumber_f_tf2_Real(int SomeStructure)
{
	int(*GetLocalClientNumber_f)(int SomeStructure) = (int(*)(int SomeStructure))tf2_addr->_0x86162760;
	return GetLocalClientNumber_f(SomeStructure);
}

int getPlayerInfo_f_tf2_Real(int pVEngineClient013_tf2, int id, int* info)
{
	int(*getPlayerInfo_f)(int pVEngineClient013_tf2, int id, int* info) = (int(*)(int pVEngineClient013_tf2, int id, int* info))tf2_addr->_0x86164550;

	return getPlayerInfo_f(pVEngineClient013_tf2, id, info);
}

int GetScreenSize_f_tf2_Real(int pVEngineClient013_tf2, int* width, int* height)
{
	int(*GetScreenSize_f)(int pVEngineClient013_tf2, int* width, int* height) = (int(*)(int pVEngineClient013_tf2, int* width, int* height))tf2_addr->_0x86164B30;

	return GetScreenSize_f(pVEngineClient013_tf2, width, height);
}

bool IsInGame_f_tf2_Real()
{
	bool(*IsInGame_f)() = (bool(*)())tf2_addr->_0x872F5298;
	return IsInGame_f();
}

void SetVTables_tf2_Real() {
	VEngineClient013_tf2 = tf2_addr->_0x8639a894;
	VGUI_Surface031_tf2 = tf2_addr->_0x845C5460;
}

int createRGBA_tf2_Real(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + ((a & 0xff));
}

long createRGB_tf2_Real(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

XINPUT_STATE InputState_tf2;

bool GetAsyncKeyState_tf2_Real(int button)
{
	XInputGetState(0, &InputState_tf2);

	if (button == 0) return true;

	else if (button == tf2_addr->_0x00001337) return (InputState_tf2.Gamepad.bLeftTrigger / 30) > 0;
	else if (button == tf2_addr->_0x00001338) return (InputState_tf2.Gamepad.bRightTrigger / 30) > 0;

	return (InputState_tf2.Gamepad.wButtons & button);
}


void DrawLineWithColor_tf2_Real(int x0, int y0, int x1, int y1, int col)
{
	DrawSetColor_f_tf2_Real(VGUI_Surface031_tf2, col);
	DrawLine_f_tf2_Real(VGUI_Surface031_tf2, x0, y0, x1, y1);
}

int GetScreenSize_tf2_Real(int* width, int* height)
{
	return GetScreenSize_f_tf2_Real(VEngineClient013_tf2, width, height);
}

int GetLocalClientNumber_tf2_Real()
{
	return GetLocalClientNumber_f_tf2_Real(VEngineClient013_tf2);
}

void DrawText_tf2_Real(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered)
{
	DrawSetTextFont_f_tf2_Real(VGUI_Surface031_tf2, font);
	int width = 0, height = 0;
	GetTextSize_f_tf2_Real(VGUI_Surface031_tf2, font, msg, &width, &height);
	DrawSetTextColor_f_tf2_Real(VGUI_Surface031_tf2, r, g, b, a);
	DrawSetTextPos_f_tf2_Real(VGUI_Surface031_tf2, centered ? x - width / 2 : x, y);
	DrawPrintText_f_tf2_Real(VGUI_Surface031_tf2, msg, wcslen(msg), 0);
}

void DrawRect_tf2_Real(int x, int y, int w, int h, int col)
{
	DrawSetColor_f_tf2_Real(VGUI_Surface031_tf2, col);
	DrawShader_f_tf2_Real(VGUI_Surface031_tf2, x, y, x + w, y + h);
}

void DrawBox_tf2_Real(float x, float y, float width, float height, int RGBA)
{
	DrawSetColor_f_tf2_Real(VGUI_Surface031_tf2, RGBA);

	DrawOutlinedRect_f_tf2_Real(VGUI_Surface031_tf2, x, y, x + width, y + height);
}

void PlayerBox_tf2_Real(float x, float y, float w, float h, int clr)
{
	DrawSetColor_f_tf2_Real(VGUI_Surface031_tf2, clr);
	DrawOutlinedRect_f_tf2_Real(VGUI_Surface031_tf2, x, y, x + w, y + h);

	DrawSetColor_f_tf2_Real(VGUI_Surface031_tf2, tf2_addr->_0x000000FF);
	DrawOutlinedRect_f_tf2_Real(VGUI_Surface031_tf2, x - 1, y - 1, x + w + 1, y + h + 1);
	DrawOutlinedRect_f_tf2_Real(VGUI_Surface031_tf2, x + 1, y + 1, x + w - 1, y + h - 1);
}

void DrawRectWithBorder_tf2_Real(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor)
{
	DrawRect_tf2_Real(x, y, width, height, rectColor);

	DrawRect_tf2_Real(x, y, lineWidth, height, borderColor);
	DrawRect_tf2_Real(x + lineWidth, y, width - lineWidth, lineWidth, borderColor);
	DrawRect_tf2_Real(x + lineWidth, y + height - lineWidth, width - lineWidth, lineWidth, borderColor);
	DrawRect_tf2_Real(x + (width - lineWidth), y + lineWidth, lineWidth, height - (lineWidth * 2), borderColor);
}

void drawCheckBox_tf2_Real(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked) {
	DrawRect_tf2_Real(centerX, centerY, 12, 1, outlineBoxColor);
	DrawRect_tf2_Real(centerX, centerY + 12, 12, 1, outlineBoxColor);
	DrawRect_tf2_Real(centerX, centerY, 1, 12, outlineBoxColor);
	DrawRect_tf2_Real(centerX + 12, centerY, 1, 13, outlineBoxColor);

	DrawRect_tf2_Real(centerX + 1, centerY + 1, 11, 11, ticked ? tf2_addr->_0x00FF007D : tf2_addr->_0xFF00007D);
}

void DrawTextWithBG_tf2_Real(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor)
{
	int TextWidth = 0, TextHeight = 0, lineWidth = 3;
	GetTextSize_f_tf2_Real(VGUI_Surface031_tf2, fontName, GetWC_tf2_Real(text), &TextWidth, &TextHeight);

	DrawRectWithBorder_tf2_Real(x - 5, y - 4, TextWidth + 10, TextHeight + 8, lineWidth, tf2_addr->_0x00000091, menuColor);

	DrawText_tf2_Real(GetWC_tf2_Real(text), fontName, x, y, r, g, b, a, centered);
}

wchar_t NoneLeakedData[0x10000];

wchar_t *GetWC_tf2_Real(const char *c)
{
	const size_t cSize = strlen(c) + 1;

	mbstowcs(NoneLeakedData, c, cSize);
	return NoneLeakedData;
}



bool TF2_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_TF2;

	if (tf2_addr)
		free(tf2_addr);

	tf2_addr = (tf2_addr_offhost_s*)malloc(sizeof(tf2_addr_offhost_s));

	for (int i = 0; i < 60; i++)
		((int*)(tf2_addr))[i] = GetAddress(tf2_addr_s_Data, tf2_addr_s_PatchID, i);


	SetVTables_tf2_Real();
	ExternalFunctions->addr = tf2_addr;
	ExternalFunctions->DrawShader_f = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))DrawShader_f_tf2_Real;
	ExternalFunctions->DrawLine_f = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))DrawLine_f_tf2_Real;
	ExternalFunctions->DrawSetColor_f = (void(*)(int pVGUI_Surface031_tf2, int RGBA))DrawSetColor_f_tf2_Real;
	ExternalFunctions->DrawSetTextColor_f = (void(*)(int pVGUI_Surface031_tf2, int r, int g, int b, int a))DrawSetTextColor_f_tf2_Real;
	ExternalFunctions->DrawSetTextPos_f = (void(*)(int pVGUI_Surface031_tf2, int x, int y))DrawSetTextPos_f_tf2_Real;
	ExternalFunctions->DrawSetTextFont_f = (void(*)(int pVGUI_Surface031_tf2, int font))DrawSetTextFont_f_tf2_Real;
	ExternalFunctions->DrawPrintText_f = (void(*)(int pVGUI_Surface031_tf2, const wchar_t *text, int textLen, int drawType))DrawPrintText_f_tf2_Real;
	ExternalFunctions->DrawOutlinedRect_f = (void(*)(int pVGUI_Surface031_tf2, int x1, int y1, int x2, int y2))DrawOutlinedRect_f_tf2_Real;
	ExternalFunctions->GetFontName_f = (int(*)(int pVGUI_Surface031_tf2, unsigned int font))GetFontName_f_tf2_Real;
	ExternalFunctions->GetTextSize_f = (void(*)(int pVGUI_Surface031_tf2, int font, const wchar_t *text, int* wide, int* tall))GetTextSize_f_tf2_Real;
	ExternalFunctions->Cbuf_AddText_f = (void(*)(char* cmd, int unk))Cbuf_AddText_f_tf2_Real;
	ExternalFunctions->GetLocalClientNumber_f = (int(*)(int SomeStructure))GetLocalClientNumber_f_tf2_Real;
	ExternalFunctions->getPlayerInfo_f = (int(*)(int pVEngineClient013_tf2, int id, int* info))getPlayerInfo_f_tf2_Real;
	ExternalFunctions->GetScreenSize_f = (int(*)(int pVEngineClient013_tf2, int* width, int* height))GetScreenSize_f_tf2_Real;
	ExternalFunctions->IsInGame_f = (bool(*)())IsInGame_f_tf2_Real;

	ExternalFunctions->SetVTables = (void(*)())SetVTables_tf2_Real;
	ExternalFunctions->createRGBA = (int(*)(int r, int g, int b, int a))createRGBA_tf2_Real;
	ExternalFunctions->createRGB = (long(*)(int r, int g, int b))createRGB_tf2_Real;
	ExternalFunctions->GetAsyncKeyState = (bool(*)(int button))GetAsyncKeyState_tf2_Real;
	ExternalFunctions->DrawLineWithColor = (void(*)(int x0, int y0, int x1, int y1, int col))DrawLineWithColor_tf2_Real;
	ExternalFunctions->GetScreenSize = (int(*)(int* width, int* height))GetScreenSize_tf2_Real;
	ExternalFunctions->GetLocalClientNumber = (int(*)())GetLocalClientNumber_tf2_Real;
	ExternalFunctions->DrawText = (void(*)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered))DrawText_tf2_Real;
	ExternalFunctions->DrawRect = (void(*)(int x, int y, int w, int h, int col))DrawRect_tf2_Real;
	ExternalFunctions->DrawBox = (void(*)(float x, float y, float width, float height, int RGBA))DrawBox_tf2_Real;
	ExternalFunctions->PlayerBox = (void(*)(float x, float y, float w, float h, int clr))PlayerBox_tf2_Real;
	ExternalFunctions->DrawRectWithBorder = (void(*)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor))DrawRectWithBorder_tf2_Real;
	ExternalFunctions->drawCheckBox = (void(*)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked))drawCheckBox_tf2_Real;
	ExternalFunctions->DrawTextWithBG = (void(*)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor))DrawTextWithBG_tf2_Real;
	ExternalFunctions->GetWC = (wchar_t *(*)(const char *c))GetWC_tf2_Real;

	HVGetVersionsPokeDWORD(0x800001000000BEE0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BEE4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_TF2)));

	return true;

}

