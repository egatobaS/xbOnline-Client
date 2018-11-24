
typedef DWORD(*XamBuildResourceLocator_t)(HANDLE hModule, PWCHAR wModuleName, PWCHAR CONST cdModule, PWCHAR pBuffer, ULONG ddSize);

typedef DWORD(*HUD_BOOTTODASHHELPER)(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData, DWORD* cstr, DWORD* r6, DWORD* r7);

typedef long(*XuiElementBeginRender_t)(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct);

typedef struct _HUDOffsets
{
	DWORD FamilySettings_LaunchStr;
	DWORD BootToDashHelper_Jump;
	DWORD LaunchData_FamilySettings;
	DWORD BootToDashHelper_Func;
} HUDOffsets;

extern Detour XuiSceneCreateDetour;
extern Detour XuiSceneCreateDetour_Dash;
extern Detour XamBuildResourceLocatorDetour;
extern Detour XuiElementBeginRenderDetour;
extern Detour AllowRuntimeHostToRewriteLocatorDetour;
extern HMODULE dashHandle;

extern XamBuildResourceLocator_t XamBuildResourceLocator_Original;
extern XuiElementBeginRender_t XuiElementBeginRender_Orig;


extern HUDOffsets HUD_Addresses;

DWORD HUD_BootToDashHelper_Hook(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData, DWORD* cstr, DWORD* r6, DWORD* r7);

HRESULT XuiSceneCreateHook(LPCWSTR BasePath, LPCWSTR ScenePath, PVOID InitData, HXUIOBJ *hScene);
long XuiElementBeginRender_hook(HXUIOBJ hObj, XUIMessageRender *pRenderData, XUIRenderStruct *pRenderStruct);
HRESULT XamBuildResourceLocatorHook(HANDLE hModule, PWCHAR wModuleName, PWCHAR CONST cdModule, PWCHAR pBuffer, ULONG ddSize);
VOID PathHuds();
void RedeemThread();
void CheckThread();
VOID setElementText(LPCWSTR szId, LPCWSTR Text);
VOID propSetString(HXUIOBJ obj, LPCWSTR ChildID, LPCWSTR Text);
