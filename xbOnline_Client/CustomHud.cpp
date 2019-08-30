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

HUDOffsets HUD_Addresses = { 0x913F02CC, 0x913E64B8, 0x14, 0x913E62E0 };

bool popup7Day = false;
HRESULT XamBuildResourceLocatorHook( HANDLE hModule, PWCHAR wModuleName, PWCHAR CONST cdModule, PWCHAR pBuffer, ULONG ddSize )
{
	LPCWSTR Edits[] = { L"notify.xur",
		L"edge.png",
		L"GamerCard.xur",
		L"loadingRing.png",
	};

	for ( int i = 0; i < 4; i++ )
	{
		if ( !wcscmp( cdModule, Edits[ i ] ) ) {

			hModule = ::g_hModule;
			wModuleName = L"UI";
		}
	}
	return XamBuildResourceLocator_Original( hModule, wModuleName, cdModule, pBuffer, ddSize );
}

long XuiElementGetId_( HXUIOBJ hObj, LPCWSTR *pszId )
{
	return ( ( long( *)( ... ) )ResolveFunction_0( dashHandle, 0x27C0 ) )( hObj, pszId );
}

long XuiFigureSetFillz( HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans )
{
	return ( ( long( *)( ... ) )ResolveFunction_0( dashHandle, 0x27E2 ) )( hObj, nFillType, dwFillColor, pStops, nNumStops, fGradientAngle, pvScale, pvTrans );
}
long XuiElementBeginRenderHookXam(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct) {
	LPCWSTR szId;
	XuiElementGetId(hObj, &szId);
	if (szId != 0) {
		if (lstrcmpW(szId, L"GreenHighlight") == 0 || lstrcmpW(szId, L"GreenHighlight1") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			::XuiFigureSetFill(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
	}
	return xuiz.xam.XuiElementBeginRenderOriginal(hObj, pRenderData, pRenderStruct);
}

// add the boolean in here to set the blades to the default color otherwise the blades will just be white/grey when its disabled | buttonColor = D3DCOLOR_ARGB(0xFF, 57, 152, 254);
long XuiElementEndRenderHook(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct) {
	HXUIOBJ hParent; LPCWSTR szId; DWORD dwProp;
	if (XuiElementGetParent(hObj, &hParent) == 0) {
		XuiElementGetId(hParent, &szId);
		if (szId != 0) {
			if (lstrcmpW(szId, L"HUD_Bladegrey") == 0) {

				if (XuiObjectGetPropertyId(hObj, L"ColorFactor", &dwProp) == 0) {
					XUIElementPropVal prop;
					if (!rainbowDash && !hudColourChange)
						XUIElementPropVal_SetColorFromUint(&prop, hudColourDefault);
					else if (hudColourChange)
						XUIElementPropVal_SetColorFromUint(&prop, buttonColor);
					else
						XUIElementPropVal_SetColorFromUint(&prop, hudColourDefault);

					XuiObjectSetProperty(hObj, dwProp, 0, &prop);
				}
			}
		}
	}
	return xuiz.xam.XuiElementEndRenderOriginal(hObj, pRenderData, pRenderStruct);
}
long XuiElementBeginRender_hook( HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct )
{
	
	LPCWSTR szId;

	XuiElementGetId_( hObj, &szId );

	//DbgPrint("Name Element: %ws\n", szId);

	if ( szId == 0 )
		return XuiElementBeginRender_Orig( hObj, pRenderData, pRenderStruct );

	if ( lstrcmpW( szId, L"Background" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );
		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans );
	}
	else if ( lstrcmpW( szId, L"background" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );
		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans );
	}
	else if ( lstrcmpW( szId, L"GreenHighlight" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );
		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans );
	}
	else if ( lstrcmpW( szId, L"GreenHighlight1" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );
		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans );
	}
	else if ( lstrcmpW( szId, L"_Background" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );
		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans );
	}
	else if (lstrcmpW(szId, L"background") == 0) {
		D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
		XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
	}
	if (rainbowBackground)
	{
		if (lstrcmpW(szId, L"slotDescription") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"TileIcon") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"imgCornerHighlight") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Vignette_Bottom") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Vignette_Top") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}

		else if (lstrcmpW(szId, L"ImgBG") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Full1") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Full2") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Full3") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Full4") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
		else if (lstrcmpW(szId, L"Full5") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}

		else if (lstrcmpW(szId, L"lightgrayBG") == 0) {
			D3DXVECTOR2 trans(0.0f, 0.0f), scale(1.0f, 1.0f);
			XuiFigureSetFillz(hObj, XUI_FILL_SOLID, buttonColor, 0, 0, 0, &scale, &trans);
		}
	}

	else if ( lstrcmpW( szId, L"floor" ) == 0 ) {
		D3DXVECTOR2 trans( 0.0f, 0.0f ), scale( 1.0f, 1.0f );

		XuiFigureSetFillz( hObj, XUI_FILL_SOLID, D3DCOLOR_ARGB( 0xFF, 45, 45, 45 ), 0, 0, 0, &scale, &trans );
	}
	return XuiElementBeginRender_Orig( hObj, pRenderData, pRenderStruct );
}

void RedeemThread( )
{
	unsigned char CPUKey[ 0x10 ] = { 0 };
	unsigned char Geneology[ 0x10 ] = { 0 };

	Tramps->CallFunction( GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false );

	Tramps->CallFunction( xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false );

	xbRedeem( g_Session, CPUKey, Geneology, XEX_Hash, 1 );

}

void CheckThread( )
{
	unsigned char CPUKey[ 0x10 ] = { 0 };
	unsigned char Geneology[ 0x10 ] = { 0 };

	Tramps->CallFunction( GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false );

	Tramps->CallFunction( xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false );

	xbRedeem( g_Session, CPUKey, Geneology, XEX_Hash, 0 );
}
void _7DayTrial()
{
	unsigned char CPUKey[0x10] = { 0 };
	unsigned char Geneology[0x10] = { 0 };

	Tramps->CallFunction(GetCPUKey_Function, (int)CPUKey, 0, 0, 0, false);

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Geneology, 0, 0, false);

	xbRedeem(g_Session, CPUKey, Geneology, XEX_Hash, 2);

}