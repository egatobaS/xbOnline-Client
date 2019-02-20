#include "main.h"
//39 98 FE
#define COLOR D3DCOLOR_ARGB(0xFF,57,152,254)
//#define COLOR D3DCOLOR_ARGB(0xFF,255,137,34)
//#define COLOR_ D3DCOLOR_ARGB(0xFF,255,174,72)
XamBuildResourceLocator_t XamBuildResourceLocator_Original;
XuiElementBeginRender_t XuiElementBeginRender_Orig;
HMODULE dashHandle;


Detour XamBuildResourceLocatorDetour;
Detour XuiElementBeginRenderDetour;
Detour XuiSceneCreateDetour;
Detour XuiSceneCreateDetour_Dash;
Detour AllowRuntimeHostToRewriteLocatorDetour;
#if defined(DEVKIT)

HUDOffsets HUD_Addresses = { 0x913F12D4, 0x913E7498, 0x14, 0x913E72C0 };

#else

HUDOffsets HUD_Addresses = { 0x913F02CC, 0x913E64B8, 0x14, 0x913E62E0 };
//HUDOffsets HUD_Addresses = { 0x913F0314, 0x913E6468, 0x14, 0x913E6290 };

#endif

HRESULT XamBuildResourceLocatorHook(HANDLE hModule, PWCHAR wModuleName, PWCHAR CONST cdModule, PWCHAR pBuffer, ULONG ddSize)
{
	LPCWSTR Edits[] = { L"notify.xur",
		L"edge.png",
		L"GamerCard.xur",
		L"loadingRing.png",
	};

	for (int i = 0; i < 4; i++)
	{
		if (!wcscmp(cdModule, Edits[i])) {

			hModule = ::g_hModule;
			wModuleName = L"UI";
		}
	}
	return XamBuildResourceLocator_Original(hModule, wModuleName, cdModule, pBuffer, ddSize);
}

long XuiElementGetId(HXUIOBJ hObj, LPCWSTR *pszId) {
	return ((long(*)(...))ResolveFunction_0(dashHandle, 0x27C0))(hObj, pszId);
}
long XuiFigureSetFillz(HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans) {
	return ((long(*)(...))ResolveFunction_0(dashHandle, 0x27E2))(hObj, nFillType, dwFillColor, pStops, nNumStops, fGradientAngle, pvScale, pvTrans);
}
long XuiElementBeginRender_hook(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct) {
	LPCWSTR szId;
	XuiElementGetId(hObj, &szId);
	if (szId == 0)
		return XuiElementBeginRender_Orig(hObj, pRenderData, pRenderStruct);

	if (lstrcmpW(szId, L"Background") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, COLOR, 0, 0, 0, &scale, &trans);
	}
	else if (lstrcmpW(szId, L"background") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, COLOR, 0, 0, 0, &scale, &trans);
	}
	else if (lstrcmpW(szId, L"GreenHighlight") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, COLOR, 0, 0, 0, &scale, &trans);
	}
	else if (lstrcmpW(szId, L"GreenHighlight1") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, COLOR, 0, 0, 0, &scale, &trans);
	}
	else if (lstrcmpW(szId, L"_Background") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, COLOR, 0, 0, 0, &scale, &trans);
	}
	else if (lstrcmpW(szId, L"floor") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, D3DCOLOR_ARGB(0xFF, 45, 45, 45), 0, 0, 0, &scale, &trans);
	}
	return XuiElementBeginRender_Orig(hObj, pRenderData, pRenderStruct);
}

void RedeemThread()
{
	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	xbRedeem(g_Session, CPUKey, Geneology, XEX_Hash, 1);
	
}
void CheckThread()
{
	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	xbRedeem(g_Session, CPUKey, Geneology, XEX_Hash, 0);
}
