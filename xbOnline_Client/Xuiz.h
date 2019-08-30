#ifndef __XUIZ_H__
#define __XUIZ_H__
#pragma once



// Bypasses Tab
#define COD4_BYPASS_CHECKBOX	L"btnCOD4Bypass"
#define WAW_BYPASS_CHECKBOX		L"btnWAWBypass"
#define MW2_BYPASS_CHECKBOX		L"btnMW2Bypass"
#define BO1_BYPASS_CHECKBOX		L"btnBO1Bypass"
#define MW3_BYPASS_CHECKBOX		L"btnMW3Bypass"
#define BO2_BYPASS_CHECKBOX		L"btnBO2Bypass"
#define GHOST_BYPASS_CHECKBOX	L"btnGhostBypass"
#define AW_BYPASS_CHECKBOX		L"btnAWBypass"

// Cheats Tab
#define COD4_CHEATS_CHECKBOX	L"btnCOD4Cheats"
#define WAW_CHEATS_CHECKBOX		L"btnWAWCheats"
#define MW2_CHEATS_CHECKBOX		L"btnMW2Cheats"
#define BO1_CHEATS_CHECKBOX		L"btnBO1Cheats"
#define MW3_CHEATS_CHECKBOX		L"btnMW3Cheats"
#define BO2_CHEATS_CHECKBOX		L"btnBO2Cheats"
#define GHOST_CHEATS_CHECKBOX	L"btnGhostsCheats"
#define AW_CHEATS_CHECKBOX		L"btnAWCheats"
#define BF4_CHEATS_CHECKBOX		L"btnBF4Cheats"
#define MW2_ONHOST_CHECKBOX		L"btnMW2Onhost"
#define BF3_CHEATS_CHECKBOX		L"btnBF3Cheats"
#define CSGO_CHEATS_CHECKBOX	L"btnCSGOCheats"
#define TF2_CHEATS_CHECKBOX		L"btnTF2Cheats"
#define MW3_ONHOST_CHECKBOX		L"btnMW3OnHost"

// HUD Tab
#define REDEEM_HOOK_CHECKBOX	L"btnRedeemHook"
#define CUSTOM_TIME_CHECKBOX	L"btnCustomTime"
#define CUSTOM_NOTIFY_CHECKBOX	L"btnCustomNotify"
#define CUSTOM_XUI_CHECKBOX		L"btnCustomXui"

//KV Data
#define KV_SERIAL_LABEL			L"labelKVSerial_value"
#define KV_TYPE_LABEL			L"labelKVType_value"
#define KV_LIFE_LABEL			L"labelKVLife_value"
#define KV_PROTECTION_CHECKBOX	L"btnKVProtection"

#define KV_TAB					L"Tab6"
#define BYPASSES_TAB			L"Tab5"
#define CHEATS_TAB				L"Tab4"
#define HUD_TAB					L"Tab3"
#define CHANGES_TAB				L"Tab2"
#define XBONLINE_TAB			L"Tab1"
#define APPLY_BUTTON			L"btnApply"
#define CLAIM_TOKEN_BUTTON		L"btnClaimToken"
#define CHECK_TIME_BUTTON		L"btnCheckTime"
#define CHANGES_ELEMENT			L"labelChanges"

//Custom Colour
#define APPLY_RGB				L"btnApplyChanges"
#define SLIDER_R				L"XuiSliderR"
#define SLIDER_G				L"XuiSliderG"
#define SLIDER_B				L"XuiSliderB"
#define RAINBOW_DASH				L"btnRainbow"
#define RESTORE_UI				L"btnRestoreRGB"
#define RAINBOW_BACKGROUND		L"btnRainbowFloor"


extern DWORD buttonColor;
extern DWORD hudColourDefault;
extern bool rainbowDash;
extern bool rainbowBackground;
extern bool hudColourChange;
void SetUIColourToFile(int r, int g, int b);
struct xuiz_s {
	struct xam_s {
		static LPCWSTR szxbOnlineSkin;
		HXUIOBJ xuiGuideMain, xuiSettings, hlstSettings;


		Detour _XuiSceneCreateDetour;
		Detour XuiSendMessageDetour;
		Detour XuiLoadVisualFromBinaryDetour;
		Detour XuiElementEndRenderDetour;
		Detour XuiElementBeginRenderHookXamDetour;

		Detour SendNotifyHook;
		//Detour XHttpConnectHookDetour;
		//Detour XHttpSendRequestDetour;
		//Detour wcslen_Detour;
		typedef bool( *XuiSceneCreate_t )( LPCWSTR szBasePath, LPCWSTR szScenePath, void* pvInitData, HXUIOBJ* phScene );
		XuiSceneCreate_t XuiSceneCreateOriginal;


		typedef bool( *XuiSendMessage_t )( HXUIOBJ hObj, XUIMessage *pMessage );
		XuiSendMessage_t XuiSendMessageOriginal;

		typedef bool( *XuiLoadVisualFromBinary_t )( LPCWSTR szResourcePath, LPCWSTR szPrefix );
		XuiLoadVisualFromBinary_t XuiLoadVisualFromBinaryOriginal;

		typedef int( *XHttpConnectHook_t )( SOCKET hSession, const CHAR *pcszServerName, WORD nServerPort, DWORD dwFlags );
		XHttpConnectHook_t XHttpConnectHookOriginal;

		typedef int( *XHttpSendRequest_t )(SOCKET hRequest, const CHAR *pcszHeaders, DWORD dwHeadersLength, const VOID *lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext );
		XHttpSendRequest_t XHttpSendRequestOriginal;

		typedef int( *SendNotify_t )( HXUIOBJ r3, WORD r4, WORD r5 );
		SendNotify_t SendNotifyOriginal;

		typedef int(*XuiElementEndRenderHook_t)(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct);
		XuiElementEndRenderHook_t XuiElementEndRenderOriginal;

		typedef int(*XuiElementBeginRenderHook_t)(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct);
		XuiElementBeginRenderHook_t XuiElementBeginRenderOriginal;


		static struct _XUIOBJ* XuiGetOuter( HXUIOBJ hObj );
		static long XuiControlSetText( HXUIOBJ hObj, LPCWSTR szText );
		static long XuiElementGetId_( HXUIOBJ hObj, LPCWSTR *pszId );
		static long XuiSceneNavigateForward( HXUIOBJ hCur, BOOL bStayVisible, HXUIOBJ hFwd, BYTE UserIndex );
		static long XuiSceneCreate( LPCWSTR szBasePath, LPCWSTR szScenePath, void* pvInitData, HXUIOBJ* phScene );
		static long XuiSendMessage( HXUIOBJ hObj, XUIMessage *pMessage );
		static long XuiLoadVisualFromBinary( LPCWSTR szResourcePath, LPCWSTR szPrefix );
		static long XuiElementGetParent( HXUIOBJ hObj, HXUIOBJ *phParent );
		static long XuiElementGetChildById( HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild );
		static void XNotifyQueueUI( XNOTIFYQUEUEUI_TYPE exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData );
		static long XuiCheckboxSetCheck( HXUIOBJ hObj, BOOL bCheck );
		static bool XuiCheckboxIsChecked( HXUIOBJ hObj );
		static bool pressedElements( HXUIOBJ hObj, LPCWSTR szID );
		static bool initElements( HXUIOBJ hObj, LPCWSTR szID );
		static void HudDisplay( );
		static void RGBFlux( );
		static int SendNotifyPressHook( HXUIOBJ r3, WORD r4, WORD r5 );
		static size_t wcslenHook_DashHook( CONST PWCHAR _Str );
		static int XHttpConnectHook_Detour( PVOID hSession, const CHAR *pcszServerName, WORD nServerPort, DWORD dwFlags );
		static bool XHttpSendRequestHook( PVOID hRequest, const CHAR *pcszHeaders, DWORD dwHeadersLength, const VOID *lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext );
		//static HINTERNET XHttpConnectHook_Call(HINTERNET hSession, const CHAR *pcszServerName, INTERNET_PORT nServerPort, DWORD dwFlags);

		//Detour<long> *XuiSceneCreateDetour, *XuiSendMessageDetour, *XuiLoadVisualFromBinaryDetour;
		

		void HookRuntimeDashFunctions( )
		{

			SendNotifyOriginal = (SendNotify_t)SendNotifyHook.HookFunction( 0x921F0370, (unsigned int)xam_s::SendNotifyPressHook );
			PatchInJump_2( 0x921997F8, (DWORD*)xam_s::wcslenHook_DashHook, FALSE );
			PatchInJump_2( 0x92247D90, (DWORD*)xam_s::XHttpConnectHook_Detour, FALSE );
			PatchInJump_2( 0x92247E40, (DWORD*)xam_s::XHttpSendRequestHook, FALSE );

			//wcslen_Detour.HookFunction(0x92199808, (unsigned int)xam_s::wcslenHook_DashHook);
			//XHttpConnectHookDetour.HookFunction(0x92247D68, (unsigned int)xam_s::XHttpConnectHook_Detour);
			//XHttpSendRequestDetour.HookFunction(0x92247E18, (unsigned int)xam_s::XHttpSendRequestHook);
		}

		bool setupDetours( )
		{

			//XuiSceneCreateOriginal = (XuiSceneCreate_t)_XuiSceneCreateDetour.HookFunction((DWORD)ResolveFunction(MODULE_XAM, 0x357), (unsigned int )xam_s::XuiSceneCreate);
			XuiSendMessageOriginal = (XuiSendMessage_t)XuiSendMessageDetour.HookFunction( (DWORD)ResolveFunction( MODULE_XAM, 0x35F ), (unsigned int)xam_s::XuiSendMessage );
			XuiLoadVisualFromBinaryOriginal = (XuiLoadVisualFromBinary_t)XuiLoadVisualFromBinaryDetour.HookFunction( (DWORD)ResolveFunction( MODULE_XAM, 0x80A ), (unsigned int)xam_s::XuiLoadVisualFromBinary );
			XuiElementEndRenderOriginal = (XuiElementEndRenderHook_t)XuiElementEndRenderDetour.HookFunction((DWORD)ResolveFunction(MODULE_XAM, 937), (unsigned int)XuiElementEndRenderHook);
			XuiElementBeginRenderOriginal = (XuiElementBeginRenderHook_t)XuiElementBeginRenderDetour.HookFunction((DWORD)ResolveFunction(MODULE_XAM, 936), (unsigned int)XuiElementBeginRenderHookXam);
			CreateXboxThread(RGBFlux, NULL);
			
			return true;
		}

	};

	xam_s xam;
};

extern xuiz_s xuiz;

#endif // __XUIZ_H__
