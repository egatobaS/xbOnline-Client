#include "main.h"

xuiz_s xuiz;
LPCWSTR xuiz_s::xam_s::szxbOnlineSkin;
HXUIOBJ obj = 0;
DWORD red = 128, green = 128, blue = 128;
DWORD hudColourDefault = D3DCOLOR_ARGB(0xFF, 0, 148, 241);
DWORD buttonColor = D3DCOLOR_ARGB(0xFF, 57, 152, 254);
bool rainbowDash = 0;
bool rainbowBackground = 0;
bool hudColourChange = 0;
int stage;

int(*Xam_XuiSceneCreate_)(LPCWSTR szBasePath, LPCWSTR szScenePath, PVOID pvInitData, HXUIOBJ* phScene) = (int(*)(LPCWSTR szBasePath, LPCWSTR szScenePath, PVOID pvInitData, HXUIOBJ* phScene))0x817C4420;
HRESULT(*Xam_XuiLoadVisualFromBinary_)(LPCWSTR szResourcePath, LPCWSTR szPrefix) = (HRESULT(*)(LPCWSTR szResourcePath, LPCWSTR szPrefix))0x817C5C88;
HRESULT(*Xam_XuiElementAddChild_)(HXUIOBJ hObj, HXUIOBJ hChild) = (HRESULT(*)(HXUIOBJ hObj, HXUIOBJ hChild))0x817BC678;
BOOL(*Xam_XuiHandleIsValid_)(HXUIOBJ hObj) = (BOOL(*)(HXUIOBJ hObj))0x817AE480;
HRESULT(*Xam_XuiLoadVisualFromBinary)(LPCWSTR szResourcePath, LPCWSTR szPrefix) = (HRESULT(*)(LPCWSTR szResourcePath, LPCWSTR szPrefix))0x817C5C88;
void(*Xam_XuiFreeVisuals)(LPCWSTR szPrefix) = (void(*)(LPCWSTR szPrefix))0x817C5B38;
HRESULT(*Xam_XuiTextElementSetText)(HXUIOBJ hObj, LPCWSTR szText) = (HRESULT(*)(HXUIOBJ hObj, LPCWSTR szText))0x817C0C60;
int(*Xam_XuiSceneCreate)(LPCWSTR szBasePath, LPCWSTR szScenePath, PVOID pvInitData, HXUIOBJ* phScene) = (int(*)(LPCWSTR szBasePath, LPCWSTR szScenePath, PVOID pvInitData, HXUIOBJ* phScene))0x817C4420;
HRESULT(*Xam_XuiElementGetChildById)(HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild) = (HRESULT(*)(HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild))0x817BD1F0;
void(*Xam_XUIElementPropVal_SetColorFromUint)(XUIElementPropVal* pThis, unsigned int val) = (void(*)(XUIElementPropVal* pThis, unsigned int val))0x817A8DC0;
HRESULT(*Xam_XuiObjectGetPropertyId)(HXUIOBJ hObj, LPCWSTR szPropName, DWORD *pdwId) = (HRESULT(*)(HXUIOBJ hObj, LPCWSTR szPropName, DWORD *pdwId))0x817AE560;
HRESULT(*Xam_XuiObjectSetProperty)(HXUIOBJ hObj, DWORD dwPropId, DWORD dwIndex, const XUIElementPropVal *pVal) = (HRESULT(*)(HXUIOBJ hObj, DWORD dwPropId, DWORD dwIndex, const XUIElementPropVal *pVal))0x817AE838;
void(*Xam_XUIElementPropVal_Construct)(XUIElementPropVal* pThis) = (void(*)(XUIElementPropVal* pThis))0x817A8BE8;
void(*Xam_XUIElementPropVal_Destruct)(XUIElementPropVal* pThis) = (void(*)(XUIElementPropVal* pThis))0x817A9358;
BOOL(*Xam_XuiHandleIsValid)(HXUIOBJ hObj) = (BOOL(*)(HXUIOBJ hObj))0x817AE480;
HRESULT(*Xam_XuiElementAddChild)(HXUIOBJ hObj, HXUIOBJ hChild) = (HRESULT(*)(HXUIOBJ hObj, HXUIOBJ hChild))0x817BC678;
HRESULT(*Xam_XUIElementPropVal_SetString)(XUIElementPropVal* pThis, LPCWSTR val) = (HRESULT(*)(XUIElementPropVal* pThis, LPCWSTR val))0x817A8E08;

HRESULT(*Dash_XuiSendMessage)(HXUIOBJ hObj, XUIMessage *pMessage) = (HRESULT(*)(HXUIOBJ, XUIMessage *))0x921D2FA8;
int(*XHttpConnectHook_Call)(int idk, PVOID hSession, const CHAR *pcszServerName, WORD nServerPort, DWORD dwFlags) = (int(*)(int idk, PVOID hSession, const CHAR *pcszServerName, WORD nServerPort, DWORD dwFlags))0x9293B384;
int(*XHttpSendRequest_Call)(int idk, PVOID hRequest, const CHAR *pcszHeaders, DWORD dwHeadersLength, const VOID *lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext) = (int(*)(int idk, PVOID hRequest, const CHAR *pcszHeaders, DWORD dwHeadersLength, const VOID *lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext))0x9293B3C4;
VOID(*AllowRuntimeHostToRewriteLocatorOrig)(PWCHAR resourcePath, INT Unk1, INT resourcePathLength) = (VOID(*)(PWCHAR resourcePath, INT Unk1, INT resourcePathLength))0x922005B8;

long xuiz_s::xam_s::XuiElementGetId_(HXUIOBJ hObj, LPCWSTR *pszId) {
	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x32E))(hObj, pszId);
}

struct _XUIOBJ* xuiz_s::xam_s::XuiGetOuter(HXUIOBJ hObj) {
	return ((struct _XUIOBJ*(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x33F))(hObj);
}

long xuiz_s::xam_s::XuiSceneNavigateForward(HXUIOBJ hCur, BOOL bStayVisible, HXUIOBJ hFwd, BYTE UserIndex) {
	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x35A))(hCur, bStayVisible, hFwd, UserIndex);
}

long xuiz_s::xam_s::XuiElementGetParent(HXUIOBJ hObj, HXUIOBJ *phParent) {
	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x331))(hObj, phParent);
}

long xuiz_s::xam_s::XuiElementGetChildById(HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild) {
	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x32A))(hObj, szId, phChild);
}

void xuiz_s::xam_s::XNotifyQueueUI(XNOTIFYQUEUEUI_TYPE exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData) {
	return ((void(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x290))(exnq, dwUserIndex, qwAreas, displayText, contextData);
}

HRESULT XuiSetSourceText(HXUIOBJ hObj, INT iItem, BOOL bItemData, LPCWSTR szText) {
	XUIMessage msg;
	XUIMessageSetSourceText msgExt;
	XuiMessageSetSourceText(&msg, &msgExt, iItem, 0, bItemData, szText);
	return Dash_XuiSendMessage(hObj, &msg);
}

HRESULT XuiSetSourceImage(HXUIOBJ hObj, INT iItem, BOOL bItemData, LPCWSTR szText) {
	XUIMessage msg;
	XUIMessageSetSourceImage msgExt;
	XuiMessageSetSourceImage(&msg, &msgExt, iItem, 0, bItemData, szText, NULL, NULL);
	return XuiSendMessage(hObj, &msg);
}

HRESULT XuiGetSourceText(HXUIOBJ hObj, XUIMessage *Message, INT iItem, BOOL bItemData) {
	XUIMessageGetSourceText msgExt;
	XuiMessageGetSourceText(Message, &msgExt, iItem, 0, bItemData);
	return Dash_XuiSendMessage(hObj, Message);
}

VOID setElementText(LPCWSTR szId, LPCWSTR Text)
{
	HXUIOBJ TmpObj = 0;

	if (Xam_XuiElementGetChildById(obj, szId, &TmpObj) == 0)
		Xam_XuiTextElementSetText(TmpObj, Text);
}

VOID propSetString(HXUIOBJ obj, LPCWSTR ChildID, LPCWSTR Text)
{
	HXUIOBJ child = 0; DWORD id = 0;
	if (Xam_XuiElementGetChildById(obj, ChildID, &child) == 0)
	{
		XUIElementPropVal prop;
		Xam_XUIElementPropVal_Construct(&prop);
		Xam_XUIElementPropVal_SetString(&prop, Text);
		if (!Xam_XuiObjectGetPropertyId(child, L"Text", &id)) Xam_XuiObjectSetProperty(child, id, NULL, &prop);
		Xam_XUIElementPropVal_Destruct(&prop);

	}
}


long xuiz_s::xam_s::XuiControlSetText(HXUIOBJ hObj, LPCWSTR szText) {
	XUIMessage msg;
	XUIMessageSetSourceText msgExt;
	XuiMessageSetSourceText(&msg, &msgExt, 0, 0, FALSE, szText);

	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x35F))(xuiz.xam.XuiGetOuter(hObj), &msg);

}

long xuiz_s::xam_s::XuiCheckboxSetCheck(HXUIOBJ hObj, BOOL bCheck) {
	XUIMessage msg;
	XUIMessageSetCheckState msgData;
	XuiMessageSetCheckstate(&msg, &msgData, bCheck);

	return ((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x35F))(xuiz.xam.XuiGetOuter(hObj), &msg);
}

bool xuiz_s::xam_s::XuiCheckboxIsChecked(HXUIOBJ hObj) {
	XUIMessage msg;
	XUIMessageGetCheckState msgData;
	XuiMessageGetCheckstate(&msg, &msgData);

	((long(*)(...))xbscene.resolveFunction((HMODULE)xbscene.hXam, 0x35F))(xuiz.xam.XuiGetOuter(hObj), &msg);
	return msgData.bChecked;
}

long xuiz_s::xam_s::XuiLoadVisualFromBinary(LPCWSTR szResourcePath, LPCWSTR szPrefix) {
	return xuiz.xam.XuiLoadVisualFromBinaryOriginal(szResourcePath, szPrefix);
}

int xuiz_s::xam_s::SendNotifyPressHook(HXUIOBJ r3, WORD r4, WORD r5) {
	XUIMessage msg;
	XuiGetSourceText(r3, &msg, 0, FALSE);

	XUIMessageGetSourceText* pSrcText = (XUIMessageGetSourceText*)msg.pvData;

	if (pSrcText->szText > 0)
	{
		if (lstrcmpiW(pSrcText->szText, L"Check Time") == 0) {


			CreateXboxThread(CheckThread, NULL);
		}
		else if (lstrcmpiW(pSrcText->szText, L"Redeem Token") == 0) {
			CreateXboxThread(RedeemThread, NULL);
		}

		else if (lstrcmpiW(pSrcText->szText, L"Check Keyvault Life") == 0) {
			if (!WantKvLess)
				CreateXboxThread(getKeyvaultLife, NULL);
			else
				XNotify(L"You currently have no keyvault!");
		}
		else if (lstrcmpiW(pSrcText->szText, L"Reset xbOnline") == 0) {
			CreateXboxThread(resetxbOnline, NULL);
		}
		else if (lstrcmpiW(pSrcText->szText, L"Test Xbox Live Connection") == 0) {
			if (g_GlobalStatus == EXPIRED)
			{
				XNotify(L"Your time has expired, you won't be able to connect to LIVE.\nRedeem a token, and try again!");
				return 0;
			}
			else if (g_GlobalStatus == FAIL_GENEOLOGY)
			{
				XNotify(L"We have detected a problem, you won't be able to connect to LIVE.\nPlease contact us!");
				return 0;
			}
			else if (g_GlobalStatus == NO_CONNECTED)
			{
				XNotify(L"You must be connected to xbOnline before performing a connection test!");
				return 0;
			}
			//Modern Warfare 3 Host Menu - OUT NOW!
		}
		else if (lstrcmpiW(pSrcText->szText, L"Modern Warfare 3 Host Menu - OUT NOW!") == 0) {
			XNotify(L"Try out our Modern Warfare 3 Menu now! - Simply load the game");
		}

	}
	return xuiz.xam.SendNotifyOriginal(r3, r4, r5);
}


size_t xuiz_s::xam_s::wcslenHook_DashHook(CONST PWCHAR _Str)
{
	if (DoesContainText(_Str, L"/dashhome.xml"))
		wcscpy(_Str, L"http://51.38.75.105/output_02.xml");

	return wcslen(_Str);
}



int xuiz_s::xam_s::XHttpConnectHook_Detour(PVOID hSession, const CHAR *pcszServerName, WORD nServerPort, DWORD dwFlags) {

	if (strcmp(pcszServerName, "51.38.75.105") == 0) {
		nServerPort = 80;
		dwFlags = 0;
	}

	int Result = XHttpConnectHook_Call(1, hSession, pcszServerName, nServerPort, dwFlags);
	return Result;
}


bool xuiz_s::xam_s::XHttpSendRequestHook(PVOID hRequest, const CHAR *pcszHeaders, DWORD dwHeadersLength, const VOID *lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext) {

	if (dwHeadersLength > 0x00002000)
		dwHeadersLength = 0;

	return XHttpSendRequest_Call(1, hRequest, pcszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
}

long xuiz_s::xam_s::XuiSceneCreate(LPCWSTR szBasePath, LPCWSTR szScenePath, void* pvInitData, HXUIOBJ* phScene) {

	WCHAR szGuideMain[0x100];

	if (lstrcmpW(szScenePath, L"GuideMain.xur") == 0)
	{
		swprintf_s(szGuideMain, L"section://@0,hud#GuideMain.xur", ::g_hModule);
		Xam_XuiSceneCreate_(nullptr, szGuideMain, nullptr, &xuiz.xam.xuiGuideMain);
		*phScene = xuiz.xam.xuiGuideMain;

		Xam_XuiSceneCreate_(NULL, charToWChar("section://%4X,UI#xbOnlineScene.xur", ::g_hModule), NULL, &obj);
		Xam_XuiElementAddChild_(*phScene, obj);

		if (Xam_XuiHandleIsValid_(obj))
		{
			HANDLE hThread = 0; DWORD threadId = 0;
			ExCreateThread(&hThread, 0x10000, &threadId, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)xuiz_s::xam_s::HudDisplay, NULL, 2 | CREATE_SUSPENDED);
			XSetThreadProcessor(hThread, 4);
			SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
			ResumeThread(hThread);
			CloseHandle(hThread);
		}
		return(FALSE);
	}

	else if (lstrcmpW(szBasePath, szGuideMain) == 0) {
		return Xam_XuiSceneCreate_(L"section://@0,hud#", szScenePath, pvInitData, phScene);
	}

	return Xam_XuiSceneCreate_(szBasePath, szScenePath, pvInitData, phScene);
}

long xuiz_s::xam_s::XuiSendMessage(HXUIOBJ hObj, XUIMessage *pMessage) {

	if (hObj != 0 && pMessage != 0)
	{
		LPCWSTR szID;

		if (xuiz.xam.XuiElementGetId_(hObj, &szID) != 0)
			goto end;

		if (szID == 0)
			goto end;

		if (pMessage->dwMessage == XM_PRESS) {

			// The button doesn't have to be the custom one I made but
			// can be the family settings button, turn off console button OR
			// any button that is available to use within the HUD.
			if (lstrcmpW(szID, L"btnFamilySettings") == 0)
			{

				WCHAR szSettings[64], szSkin[64];
				swprintf_s(szSettings, L"section://%4X,UI#xbOnline_settings.xur", ::g_hModule);
				swprintf_s(szSkin, L"section://%4X,UI#xbOnline_skin.xur", ::g_hModule);
				xuiz.xam.XuiLoadVisualFromBinary(szSkin, 0);
				Xam_XuiSceneCreate_(nullptr, szSettings, nullptr, &xuiz.xam.xuiSettings);
				xuiz.xam.XuiSceneNavigateForward(xuiz.xam.xuiGuideMain, false, xuiz.xam.xuiSettings, (BYTE)nullptr);
				return(FALSE);
			}
			else if (pressedElements(hObj, szID))
			{
				return(FALSE);
			}
		}
		else if (pMessage->dwMessage == XM_INIT)
		{
			if (lstrcmpW(szID, L"btnFamilySettings") == 0) {
				xuiz.xam.XuiControlSetText(hObj, L"xbOnline Menu"); // Family Settings -> xbOnline
			}
			else if (initElements(hObj, szID)) {
				goto end;
			}
		}
	}

end:
	return xuiz.xam.XuiSendMessageOriginal(hObj, pMessage);
}

bool xuiz_s::xam_s::pressedElements(HXUIOBJ hObj, LPCWSTR szID) {
	LPCWSTR szParent;
	HXUIOBJ hParent;


	if (lstrcmpW(szID, CLAIM_TOKEN_BUTTON) == 0)
	{
		// NOTE: Just make sure your XShowKeyboardUI or whatever you're using
		// is within a thread. This hook doesn't really like it when it isn't.
		// may cause some freezing issues.

		if (xb_redeemhook)
		{
			if (g_GlobalStatus == NO_CONNECTED)
				XNotify(L"You must be connected to xbOnline before trying to redeem time!");
			else if (g_GlobalStatus == BANNED)
				XNotify(L"You cannot redeem time on xbOnline, this console has been banned from the xbOnline Service!");
			else
			{
				HANDLE hThread = 0; DWORD threadId = 0;
				ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)RedeemThread, NULL, 0x2);
				XSetThreadProcessor(hThread, 4);
				ResumeThread(hThread);
				CloseHandle(hThread);
			}
		}
	}
	else if (lstrcmpW(szID, CHECK_TIME_BUTTON) == 0)
	{
		if (g_GlobalStatus == NO_CONNECTED)
			XNotify(L"You must be connected to xbOnline before checking your time!");
		else
		{
			HANDLE hThread = 0; DWORD threadId = 0;
			ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, (LPTHREAD_START_ROUTINE)CheckThread, NULL, 0x2);
			XSetThreadProcessor(hThread, 4);
			ResumeThread(hThread);
			CloseHandle(hThread);
		}
	}
	else if (lstrcmpW(szID, APPLY_BUTTON) == 0)
	{

		INI Parser("xbOnline:\\xbOnline.ini", true);

		if (xuiz.xam.XuiElementGetParent(hObj, &hParent) != 0)
			goto end;

		if (xuiz.xam.XuiElementGetId_(hParent, &szParent) != 0)
			goto end;

		if (szParent == 0)
			goto end;

		if (lstrcmpW(szParent, HUD_TAB) == 0) {
			HXUIOBJ hCustomXui(0), hCustomNotify(0), hTimeRemaining(0), hRedeemHook(0);
			bool bCustomXui(false), bCustomNotify(false), bTimeRemaining(false), bRedeemHook(false);

			if (xuiz.xam.XuiElementGetChildById(hParent, CUSTOM_XUI_CHECKBOX, &hCustomXui) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hCustomXui)) ? Parser.SetOption("Hud", "xb_custom_xui", "true") : Parser.SetOption("Hud", "xb_custom_xui", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, CUSTOM_NOTIFY_CHECKBOX, &hCustomNotify) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hCustomNotify)) ? Parser.SetOption("Hud", "xb_custom_notify", "true") : Parser.SetOption("Hud", "xb_custom_notify", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, CUSTOM_TIME_CHECKBOX, &hTimeRemaining) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hTimeRemaining)) ? Parser.SetOption("Hud", "xb_custom_time", "true") : Parser.SetOption("Hud", "xb_custom_time", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, REDEEM_HOOK_CHECKBOX, &hRedeemHook) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hRedeemHook)) ? Parser.SetOption("Hud", "xb_redeemhook", "true") : Parser.SetOption("Hud", "xb_redeemhook", "false");


			Parser.SaveFile();
			Sleep(500);
			LoadINI();
			xuiz.xam.XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, 0, 2, L"xbOnline: Settings Updated and Loaded!", 0);
		}
		else if (lstrcmpW(szParent, CHEATS_TAB) == 0) {
			HXUIOBJ hCOD4Cheats, hWAWCheats, hMW2Cheats, hBO1Cheats, hMW3Cheats,
				hBO2Cheats, hGhostCheats, hAWCheats, hBF4Cheats, hMW2Onhost, hMW3Onhost, hCSGOCheats, hTF2Cheats, hBF3Cheats;

			bool bCOD4Cheats, bWAWCheats, bMW2Cheats, bBO1Cheats, bMW3Cheats,
				bBO2Cheats, bGhostCheats, bAWCheats, bBF4Cheats, bMW2Onhost, bMW3Onhost, bBF3Cheats, bCSGOCheats, bTF2Cheats;

			if (xuiz.xam.XuiElementGetChildById(hParent, COD4_CHEATS_CHECKBOX, &hCOD4Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hCOD4Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_cod4", "true") : Parser.SetOption("Cheats", "xb_cheats_cod4", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, WAW_CHEATS_CHECKBOX, &hWAWCheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hWAWCheats)) ? Parser.SetOption("Cheats", "xb_cheats_waw", "true") : Parser.SetOption("Cheats", "xb_cheats_waw", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW2_CHEATS_CHECKBOX, &hMW2Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW2Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_mw2", "true") : Parser.SetOption("Cheats", "xb_cheats_mw2", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BO1_CHEATS_CHECKBOX, &hBO1Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBO1Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_bo1", "true") : Parser.SetOption("Cheats", "xb_cheats_bo1", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW3_CHEATS_CHECKBOX, &hMW3Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW3Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_mw3", "true") : Parser.SetOption("Cheats", "xb_cheats_mw3", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BO2_CHEATS_CHECKBOX, &hBO2Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBO2Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_bo2", "true") : Parser.SetOption("Cheats", "xb_cheats_bo2", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, GHOST_CHEATS_CHECKBOX, &hGhostCheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hGhostCheats)) ? Parser.SetOption("Cheats", "xb_cheats_ghosts", "true") : Parser.SetOption("Cheats", "xb_cheats_ghosts", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, AW_CHEATS_CHECKBOX, &hAWCheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hAWCheats)) ? Parser.SetOption("Cheats", "xb_cheats_aw", "true") : Parser.SetOption("Cheats", "xb_cheats_aw", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BF4_CHEATS_CHECKBOX, &hBF4Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBF4Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_bf4", "true") : Parser.SetOption("Cheats", "xb_cheats_bf4", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW2_ONHOST_CHECKBOX, &hMW2Onhost) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW2Onhost)) ? Parser.SetOption("Cheats", "xb_cheats_mw2_onhost", "true") : Parser.SetOption("Cheats", "xb_cheats_mw2_onhost", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW3_ONHOST_CHECKBOX, &hMW3Onhost) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW3Onhost)) ? Parser.SetOption("Cheats", "xb_cheats_mw3_onhost", "true") : Parser.SetOption("Cheats", "xb_cheats_mw3_onhost", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, CSGO_CHEATS_CHECKBOX, &hCSGOCheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hCSGOCheats)) ? Parser.SetOption("Cheats", "xb_cheats_csgo", "true") : Parser.SetOption("Cheats", "xb_cheats_csgo", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, TF2_CHEATS_CHECKBOX, &hTF2Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hTF2Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_tf2", "true") : Parser.SetOption("Cheats", "xb_cheats_tf2", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BF3_CHEATS_CHECKBOX, &hBF3Cheats) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBF3Cheats)) ? Parser.SetOption("Cheats", "xb_cheats_bf3", "true") : Parser.SetOption("Cheats", "xb_cheats_bf3", "false");

			Parser.SaveFile();
			Sleep(500);
			LoadINI();
			xuiz.xam.XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, 0, 2, L"xbOnline: Settings Updated and Loaded!", 0);
		}
		else if (lstrcmpW(szParent, BYPASSES_TAB) == 0) {
			HXUIOBJ hCOD4Bypass, hWAWBypass, hMW2Bypass, hBO1Bypass, hMW3Bypass,
				hBO2Bypass, hGhostBypass, hAWBypass;

			bool bCOD4Bypass, bWAWBypass, bMW2Bypass, bBO1Bypass, bMW3Bypass,
				bBO2Bypass, bGhostBypass, bAWBypass;

			if (xuiz.xam.XuiElementGetChildById(hParent, COD4_BYPASS_CHECKBOX, &hCOD4Bypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hCOD4Bypass)) ? Parser.SetOption("Bypasses", "xb_bypass_cod4", "true") : Parser.SetOption("Cheats", "xb_bypass_cod4", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, WAW_BYPASS_CHECKBOX, &hWAWBypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hWAWBypass)) ? Parser.SetOption("Bypasses", "xb_bypass_waw", "true") : Parser.SetOption("Cheats", "xb_bypass_waw", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW2_BYPASS_CHECKBOX, &hMW2Bypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW2Bypass)) ? Parser.SetOption("Bypasses", "xb_bypass_mw2", "true") : Parser.SetOption("Cheats", "xb_bypass_mw2", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BO1_BYPASS_CHECKBOX, &hBO1Bypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBO1Bypass)) ? Parser.SetOption("Bypasses", "xb_bypass_bo1", "true") : Parser.SetOption("Cheats", "xb_bypass_bo1", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, MW3_BYPASS_CHECKBOX, &hMW3Bypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hMW3Bypass)) ? Parser.SetOption("Bypasses", "xb_bypass_mw3", "true") : Parser.SetOption("Cheats", "xb_bypass_mw3", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, BO2_BYPASS_CHECKBOX, &hBO2Bypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hBO2Bypass)) ? Parser.SetOption("Bypasses", "xb_bypass_bo2", "true") : Parser.SetOption("Cheats", "xb_bypass_bo2", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, GHOST_BYPASS_CHECKBOX, &hGhostBypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hGhostBypass)) ? Parser.SetOption("Bypasses", "xb_bypass_ghosts", "true") : Parser.SetOption("Cheats", "xb_bypass_ghosts", "false");

			if (xuiz.xam.XuiElementGetChildById(hParent, AW_BYPASS_CHECKBOX, &hAWBypass) == 0)
				bool(xuiz.xam.XuiCheckboxIsChecked(hAWBypass)) ? Parser.SetOption("Bypasses", "xb_bypass_aw", "true") : Parser.SetOption("Cheats", "xb_bypass_aw", "false");


			Parser.SaveFile();
			Sleep(500);
			LoadINI();
			xuiz.xam.XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, 0, 2, L"xbOnline: Settings Updated and Loaded!", 0);
		}
		return(TRUE);
	}
	else if (lstrcmpW(szID, APPLY_RGB) == 0)
	{
		if (xuiz.xam.XuiElementGetParent(hObj, &hParent) != 0)
			goto end;

		HXUIOBJ sliderR(0), sliderG(0), sliderB(0);
		int r, g, b;
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_R, &sliderR) == 0)
			XuiSliderGetValue(sliderR, &r);
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_G, &sliderG) == 0)
			XuiSliderGetValue(sliderG, &g);
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_B, &sliderB) == 0)
			XuiSliderGetValue(sliderB, &b);

		buttonColor = D3DCOLOR_ARGB(0xFF, r, g, b);
		SetUIColourToFile(r, g, b);

	}
	else if (lstrcmpW(szID, RESTORE_UI) == 0)
	{
		buttonColor = D3DCOLOR_ARGB(0xFF, 57, 152, 254);
		SetUIColourToFile(57, 152, 254);
	}
	else if (lstrcmpW(szID, RAINBOW_DASH) == 0) {
		hudColourChange ^= 1;
		rainbowDash ^= 1;
		if (!rainbowDash) {
			buttonColor = D3DCOLOR_ARGB(0xFF, 57, 152, 254);
		}

	}
	else if (lstrcmpW(szID, RAINBOW_BACKGROUND) == 0) {
		rainbowBackground ^= 1;
	}

end:
	return(FALSE);
}

bool xuiz_s::xam_s::initElements(HXUIOBJ hObj, LPCWSTR szID) {

	LPCWSTR szParent;
	HXUIOBJ hParent;

	//setElementText(KV_LIFE_LABEL, L"WHY ARE U RUNNING");

	if (lstrcmpW(szID, CHANGES_ELEMENT) == 0) {
		std::wstring changes(L"xbOnline Update Notes | r52\n\n");

		// To add new lines is pretty self explanatory.
		// Just append the wstring.

		// added lorem just to showcase the scroller.
		changes += L" [+] Added RGB Guide\n [+] Added RGB Scroller\n [+] Improvement to RGB Mode\n [+] 7 Days won't be activated until you confirm\n\n\n\n";
		changes += L"\n\n\nxbOnline #1 Leading Stealth Service - Check and Purchase new time on https://xbonline.live\n\n\n";

		// apply the string to element
		xuiz.xam.XuiControlSetText(hObj, (LPCWSTR)changes.c_str());
	}
	else if (lstrcmpW(szID, RAINBOW_DASH) == 0) {
		xuiz.xam.XuiCheckboxSetCheck(hObj, rainbowDash);

		if (xuiz.xam.XuiElementGetParent(hObj, &hParent) != 0)
			goto end;

		// Save our values and read them directly from the stack when scene is re-opened.
		BYTE *color = (BYTE*)&buttonColor;
		int r = (int)color[1], g = (int)color[2], b = (int)color[3];
		HXUIOBJ sliderR(0), sliderG(0), sliderB(0);
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_R, &sliderR) == 0)
			XuiSliderSetValue(sliderR, r);
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_G, &sliderG) == 0)
			XuiSliderSetValue(sliderG, g);
		if (xuiz.xam.XuiElementGetChildById(hParent, SLIDER_B, &sliderB) == 0)
			XuiSliderSetValue(sliderB, b);
	}
	else {
		if (xuiz.xam.XuiElementGetParent(hObj, &hParent) != 0)
			goto end;

		if (xuiz.xam.XuiElementGetId_(hParent, &szParent) != 0)
			goto end;

		if (szParent == 0)
			goto end;


		// PLEASE NOTE !!!
		// change "false" to the value of your parsed ini.
		// this is so when the client goes to the certain tab
		// the checkbox's are set to the same values that are within their ini.

		if (lstrcmpW(szParent, HUD_TAB) == 0) {
			HXUIOBJ hCustomXui(0), hCustomNotify(0), hTimeRemaining(0), hRedeemHook(0);
			if (XuiElementGetChildById(hParent, CUSTOM_XUI_CHECKBOX, &hCustomXui) == 0)
				if (xb_custom_xui ? xuiz.xam.XuiCheckboxSetCheck(hCustomXui, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hCustomXui, FALSE));

			if (XuiElementGetChildById(hParent, CUSTOM_NOTIFY_CHECKBOX, &hCustomNotify) == 0)
				if (xb_custom_notify ? xuiz.xam.XuiCheckboxSetCheck(hCustomNotify, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hCustomNotify, FALSE));

			if (XuiElementGetChildById(hParent, CUSTOM_TIME_CHECKBOX, &hTimeRemaining) == 0)
				if (xb_custom_time ? xuiz.xam.XuiCheckboxSetCheck(hTimeRemaining, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hTimeRemaining, FALSE));

			if (XuiElementGetChildById(hParent, REDEEM_HOOK_CHECKBOX, &hRedeemHook) == 0)
				if (xb_redeemhook ? xuiz.xam.XuiCheckboxSetCheck(hRedeemHook, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hRedeemHook, FALSE));
		}
		else if (lstrcmpW(szParent, CHEATS_TAB) == 0) {

			HXUIOBJ hCOD4Cheats, hWAWCheats, hMW2Cheats, hBO1Cheats, hMW3Cheats,
				hBO2Cheats, hGhostCheats, hAWCheats, hBF4Cheats, hMW2Onhost, hMW3Onhost, hCSGOCheats, hTF2Cheats, hBF3Cheats;

			if (XuiElementGetChildById(hParent, COD4_CHEATS_CHECKBOX, &hCOD4Cheats) == 0)
				if (xb_cheats_cod4 ? xuiz.xam.XuiCheckboxSetCheck(hCOD4Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hCOD4Cheats, FALSE));

			if (XuiElementGetChildById(hParent, WAW_CHEATS_CHECKBOX, &hWAWCheats) == 0)
				if (xb_cheats_waw ? xuiz.xam.XuiCheckboxSetCheck(hWAWCheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hWAWCheats, FALSE));

			if (XuiElementGetChildById(hParent, MW2_CHEATS_CHECKBOX, &hMW2Cheats) == 0)
				if (xb_cheats_mw2 ? xuiz.xam.XuiCheckboxSetCheck(hMW2Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW2Cheats, FALSE));

			if (XuiElementGetChildById(hParent, BO1_CHEATS_CHECKBOX, &hBO1Cheats) == 0)
				if (xb_cheats_bo1 ? xuiz.xam.XuiCheckboxSetCheck(hBO1Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBO1Cheats, FALSE));

			if (XuiElementGetChildById(hParent, MW3_CHEATS_CHECKBOX, &hMW3Cheats) == 0)
				if (xb_cheats_mw3 ? xuiz.xam.XuiCheckboxSetCheck(hMW3Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW3Cheats, FALSE));

			if (XuiElementGetChildById(hParent, BO2_CHEATS_CHECKBOX, &hBO2Cheats) == 0)
				if (xb_cheats_bo2 ? xuiz.xam.XuiCheckboxSetCheck(hBO2Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBO2Cheats, FALSE));

			if (XuiElementGetChildById(hParent, GHOST_CHEATS_CHECKBOX, &hGhostCheats) == 0)
				if (xb_cheats_ghosts ? xuiz.xam.XuiCheckboxSetCheck(hGhostCheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hGhostCheats, FALSE));

			if (XuiElementGetChildById(hParent, AW_CHEATS_CHECKBOX, &hAWCheats) == 0)
				if (xb_cheats_aw ? xuiz.xam.XuiCheckboxSetCheck(hAWCheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hAWCheats, FALSE));

			if (XuiElementGetChildById(hParent, BF4_CHEATS_CHECKBOX, &hBF4Cheats) == 0)
				if (xb_cheats_bf4 ? xuiz.xam.XuiCheckboxSetCheck(hBF4Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBF4Cheats, FALSE));

			if (XuiElementGetChildById(hParent, BF3_CHEATS_CHECKBOX, &hBF3Cheats) == 0)
				if (xb_cheats_bf3 ? xuiz.xam.XuiCheckboxSetCheck(hBF3Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBF3Cheats, FALSE));

			if (XuiElementGetChildById(hParent, MW3_ONHOST_CHECKBOX, &hMW3Onhost) == 0)
				if (xb_cheats_mw3_onhost ? xuiz.xam.XuiCheckboxSetCheck(hMW3Onhost, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW3Onhost, FALSE));

			if (XuiElementGetChildById(hParent, CSGO_CHEATS_CHECKBOX, &hCSGOCheats) == 0)
				if (xb_cheats_csgo ? xuiz.xam.XuiCheckboxSetCheck(hCSGOCheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hCSGOCheats, FALSE));

			if (XuiElementGetChildById(hParent, MW2_ONHOST_CHECKBOX, &hMW2Onhost) == 0)
				if (xb_cheats_mw2_onhost ? xuiz.xam.XuiCheckboxSetCheck(hMW2Onhost, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW2Onhost, FALSE));

			if (XuiElementGetChildById(hParent, TF2_CHEATS_CHECKBOX, &hTF2Cheats) == 0)
				if (xb_cheats_tf2 ? xuiz.xam.XuiCheckboxSetCheck(hTF2Cheats, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hTF2Cheats, FALSE));

		}
		else if (lstrcmpW(szParent, BYPASSES_TAB) == 0) {
			HXUIOBJ hCOD4Bypass, hWAWBypass, hMW2Bypass, hBO1Bypass, hMW3Bypass,
				hBO2Bypass, hGhostBypass, hAWBypass;

			if (XuiElementGetChildById(hParent, COD4_BYPASS_CHECKBOX, &hCOD4Bypass) == 0)
				if (xb_bypass_cod4 ? xuiz.xam.XuiCheckboxSetCheck(hCOD4Bypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hCOD4Bypass, FALSE));

			if (XuiElementGetChildById(hParent, WAW_BYPASS_CHECKBOX, &hWAWBypass) == 0)
				if (xb_bypass_waw ? xuiz.xam.XuiCheckboxSetCheck(hWAWBypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hWAWBypass, FALSE));

			if (XuiElementGetChildById(hParent, MW2_BYPASS_CHECKBOX, &hMW2Bypass) == 0)
				if (xb_bypass_mw2 ? xuiz.xam.XuiCheckboxSetCheck(hMW2Bypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW2Bypass, FALSE));

			if (XuiElementGetChildById(hParent, BO1_BYPASS_CHECKBOX, &hBO1Bypass) == 0)
				if (xb_bypass_bo1 ? xuiz.xam.XuiCheckboxSetCheck(hBO1Bypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBO1Bypass, FALSE));

			if (XuiElementGetChildById(hParent, MW3_BYPASS_CHECKBOX, &hMW3Bypass) == 0)
				if (xb_bypass_mw3 ? xuiz.xam.XuiCheckboxSetCheck(hMW3Bypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hMW3Bypass, FALSE));

			if (XuiElementGetChildById(hParent, BO2_BYPASS_CHECKBOX, &hBO2Bypass) == 0)
				if (xb_bypass_bo2 ? xuiz.xam.XuiCheckboxSetCheck(hBO2Bypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hBO2Bypass, FALSE));

			if (XuiElementGetChildById(hParent, GHOST_BYPASS_CHECKBOX, &hGhostBypass) == 0)
				if (xb_bypass_ghosts ? xuiz.xam.XuiCheckboxSetCheck(hGhostBypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hGhostBypass, FALSE));

			if (XuiElementGetChildById(hParent, AW_BYPASS_CHECKBOX, &hAWBypass) == 0)
				if (xb_bypass_aw ? xuiz.xam.XuiCheckboxSetCheck(hAWBypass, TRUE) : xuiz.xam.XuiCheckboxSetCheck(hAWBypass, FALSE));
		}

	}
	return(TRUE);

end:
	return(FALSE);
}

void xuiz_s::xam_s::HudDisplay()
{
	while (!g_isThreadRunning)
	{
		WCHAR* TimeWChar = new WCHAR[256];
		WCHAR* SharedInfoCounter = new WCHAR[30];

		if (!Xam_XuiHandleIsValid_(obj))
		{
			delete[] TimeWChar;
			delete[] SharedInfoCounter;

			break;
		}

		switch (g_GlobalStatus)
		{
		case EXPIRED:
			swprintf(TimeWChar, L"Time Expired");
			break;
		case FREEMODE:
			swprintf(TimeWChar, L"Free Mode");
			break;
		case BANNED:
			swprintf(TimeWChar, L"Banned");
			break;
		case TIMELEFT:
		{
			long long timeleft = (g_Endtime - time(NULL));

			if (timeleft < 0) {

				swprintf(TimeWChar, L"Time Expired");
				break;
			}

			long long days = timeleft / 60 / 60 / 24;
			long long hours = (timeleft / 60 / 60) % 24;
			long long minutes = (timeleft / 60) % 60;
			long long seconds = timeleft % 60;

			if (days > 6000) {
				swprintf(TimeWChar, L"Lifetime!");
				break;
			}

			if (days < 1000)
				swprintf(TimeWChar, L"%lliD %lliH %lliM %lliS", days, hours, minutes, seconds);
			else
				swprintf(TimeWChar, L"Nigel Time!");
			break;
		}

		case NOT_INDB:
			swprintf(TimeWChar, L"New Client");
			break;
		case FAIL_GENEOLOGY:
			swprintf(TimeWChar, L"Contact Support");
			break;
		case NO_CONNECTED:
			swprintf(TimeWChar, L"Not Connected");
			break;
		case GET_UPDATE:
			swprintf(TimeWChar, L"Getting Update!");
			break;
		default:
			break;
		}

		setElementText(L"Time", TimeWChar);

		delete[] TimeWChar;
		delete[] SharedInfoCounter;

		Sleep(750);
	}
	ExitThread(0);
}


void xuiz_s::xam_s::RGBFlux() {
	while (true) {
		Sleep(1);
		if (rainbowDash) {
			if (stage == 0) {
				blue++;
				if (blue == 210)
					stage = 1;
			}
			else if (stage == 1) {
				red--;
				if (red == 0)
					stage = 2;
			}
			else if (stage == 2) {
				green++;
				if (green == 210)
					stage = 3;
			}
			else if (stage == 3) {
				blue--;
				if (blue == 0)
					stage = 4;
			}
			else if (stage == 4) {
				red++;
				if (red == 210)
					stage = 5;
			}
			else if (stage == 5) {
				green--;
				if (green == 0)
					stage = 0;
			}
			buttonColor = D3DCOLOR_ARGB(0xFF, red, green, blue);
		}
	}
}

void SetUIColourFromFile()
{
	MemoryBuffer fileBuffer;
	CReadFile("xbOnline:\\xbOnline\\RGB.clr", fileBuffer);
	int redClr = *(byte*)&fileBuffer.GetData()[0];
	int BlueClr = *(byte*)&fileBuffer.GetData()[1];
	int GreenClr = *(byte*)&fileBuffer.GetData()[2];
	if (fileBuffer.GetDataLength() == 3)
	{
		hudColourChange = true;
		buttonColor = D3DCOLOR_ARGB(0xFF, redClr, BlueClr, GreenClr);
	}

}
void SetUIColourToFile(int r, int g, int b)
{
	unsigned char clrArrayRGB[3] = { r,g,b };
	CWriteFile("xbOnline:\\xbOnline\\RGB.clr", clrArrayRGB, 3);
}
VOID PathHuds()
{
	CreateDirectoryA("xbOnline:\\xbOnline\\", NULL);
	if (FileExists("xbOnline:\\xbOnline\\RGB.clr"))
		SetUIColourFromFile();

	xbscene.init();
	HANDLE hHudSkin;
	XexLoadImage("\\SystemRoot\\huduiskin.xex", 8, 0, &hHudSkin);

	PVOID pSectionData; DWORD dwSectionSize;
	if (XGetModuleSection(hHudSkin, "skin", &pSectionData, &dwSectionSize)) {


		memcpy(((PBYTE)(pSectionData)+0x72DD), ((unsigned char*)(&(buttonColor))) + 1, 3); //XuiButton
		memcpy(((PBYTE)(pSectionData)+0x730D), ((unsigned char*)(&(buttonColor))) + 1, 3); //XuiButton Press

		XuiFreeVisuals(NULL);
		XuiLoadVisualFromBinary(charToWChar("section://%X,skin#skin.xur", hHudSkin), NULL);

		*(WORD*)((INT)(hHudSkin)+0x40) = 1;
		XexUnloadImage(hHudSkin);
	}

	Xam_XuiLoadVisualFromBinary_(charToWChar("section://%4X,UI#xbOnline.xur", ::g_hModule), NULL);
	XamBuildResourceLocator_Original = (XamBuildResourceLocator_t)XamBuildResourceLocatorDetour.HookFunction((DWORD)ResolveFunction(MODULE_XAM, 795), (DWORD)XamBuildResourceLocatorHook);
}
