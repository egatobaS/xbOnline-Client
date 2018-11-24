#include "main.h"

Security * MW2_OnHosts_addr_s_Data = 0;
unsigned int *MW2_OnHosts_addr_s_PatchID = 0;

void MW2_OnHosts_SetupGameAddresses(ServerData_MW2_OnHosts* Server)
{
	if (MW2_OnHosts_addr_s_Data)
		delete MW2_OnHosts_addr_s_Data;

	MW2_OnHosts_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		MW2_OnHosts_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	MW2_OnHosts_addr_s_Data = new Security(t, g_Session);
	MW2_OnHosts_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, MW2_OnHosts_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

typedef struct gclient_t;
typedef struct gentity_t;

enum TraceHitType {
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};

struct trace_t
{
	float fraction;
	float Normal[3];
	int SurfaceFlags;
	int Contents;
	char* Material;
	TraceHitType HitType;
	unsigned short HitId;
	unsigned short ModelIndex;
	unsigned short PartName;
	unsigned short PartGroup;
	bool AllSolid;
	bool StartSolid;
	bool Walkable;
};

struct scr_entref_t
{
	short entNum;
	short classNum;
};

enum hitLocation_t {
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_LWR = 0x5,
	HITLOC_R_ARM_UPR = 0x6,
	HITLOC_L_ARM_UPR = 0x7,
	HITLOC_R_ARM_LWR = 0x8,
	HITLOC_L_ARM_LWR = 0x9,
	HITLOC_R_HAND = 0xA,
	HITLOC_L_HAND = 0xB,
	HITLOC_R_LEG_UPR = 0xC,
	HITLOC_L_LEG_UPR = 0xD,
	HITLOC_R_LEG_LWR = 0xE,
	HITLOC_L_LEG_LWR = 0xF,
	HITLOC_R_FOOT = 0x10,
	HITLOC_L_FOOT = 0x11,
	HITLOC_GUN = 0x12,
	HITLOC_SHIELD = 0x13,
	HITLOC_ARMOR = 0x14,
	HITLOC_SOFT = 0x15,
	HITLOC_NUM = 0x16,
};

struct mw2_addr_onhost_s
{
	int _0x8360922C;//0x8360922C
	int _0x97F80;//0x97F80   
	int _0x83620380;//0x83620380
	int _0x3818;//0x3818	   
	int _0x186A0;//0x186A0   
	int _0x206426;//0x206426  
	int _0x8200183C;//0x8200183C
	int _0x394002FF;//0x394002FF
	int _0x394000BE;//0x394000BE
	int _0x83623B98;//0x83623B98
	int _0x806831;//0x806831  
	int _0x825E2200;//0x825E2200
	int _0x415E0;//0x415E0   
	int _0x82255A68;//0x82255A68
	int _0x8310A12C;//0x8310A12C
	int _0x838BA824;//0x838BA824
	int _0x825B8638;//0x825B8638
	int _0x33A8;//0x33A8
	int level_locals_t_a; //0x83109D80,
	int cgArray_a; //0x825B8638,
	int client_t; //0x83620380,
	int g_hudelem_s_a; //0x82ED6560,
	int g_hudelem_s_size; //0xB4,
	int gentity_s_a; //0x82F03600,
	int gentity_s_size; //0x280,
	int GetObjectType_a; //0x00202560,
	int Scr_NotifyNum_a; //0x8224AF98,
	int Scr_AddEntityNum_a; //0x8224C648,
	int Scr_AddObject_a; //0x0020C480,
	int Scr_AddHudElem_a; //0x822096F8,
	int Scr_GetSelf_a; //0x822437E0,
	int scrVarGlob_t_a; //0x83373B80,
	int GetVariableValueAddress_a; //0x82243E18,
	int Scr_AddInt_a; //0x8224C3D0,
	int Scr_AddBool_a; //0x8224C350,
	int Scr_AddFloat_a; //0x8224C450,
	int Scr_AddString_a; //0x8224C6A8,
	int Scr_AddEntity_a; //0x82209580,
	int Scr_AddVector_a; //0x8224C850,
	int Scr_AddUndefined_a; //0x8224C550,
	int Scr_AddConstString_a; //0x8224C7C8,
	int Scr_ClearOutParams_a; //0x82249E78,
	int AngleVectors_a; //0x8228EDC0,
	int vectoangles_a; //0x822899A0,
	int SV_ExecuteClientCommand_a; //0x822531C8,
	int G_Spawn_a; //0x8220DBE8,
	int G_SpawnHelicopter_a; //0x82315E48,
	int G_SetOrigin_a; //0x8220E170,
	int G_SetAngles_a; //0x8220E1C8,
	int G_EntLinkTo_a; //0x822122C0,
	int GSC_Earthquake_a; //0x821F5230,
	int scrVmPub_t_a; //0x835C49D8,
	int FindVariable_a; //0x82243BE8,
	int GetValueType_a; //0x82244318,
	int FindEntityId_a; //0x822444C0,
	int Scr_GetEntityIdRef_a; //0x822448F8,
	int GetArraySize_a; //0x82243F78,
	int G_LocationalTrace_a; //0x821E7790,
	int G_SetModel_a; //0x8220D310,
	int G_LocalizedStringIndex_a; //0x8220C838,
	int G_MaterialIndex_a; //0x8220C9F8,
	int G_GivePlayerWeapon_a; //0x82210BC8,
	int G_GetWeaponIndexForName_a; //0x82210640,
	int G_InitializeAmmo_a; //0x821D4A00,
	int G_GetPlayerViewOrigin_a; //0x821D3960,
	int Menu_PaintAll_a; //0x82285F08,
	int va_a; //0x822A7008,
	int Dvar_FindMalleableVar_a; //0x8229ED90,
	int Dvar_GetBool_a; //0x8229EF58,
	int Dvar_GetString_a; //0x8229F118,
	int Scr_Notify_a; //0x822097A8,
	int SL_GetString_a; //0x822422D8,
	int SL_ConvertToString_a; //0x82241920,
	int SV_SendServerCommand_a; //0x822579B0,
	int Scr_GetEntityId_a; //0x0,
	int GetArrayVariable_a; //0x82245C58,
	int GetVariable_a; //0x82245D48,
	int Scr_GetObjectField_a; //0x0,
	int VM_Notify_a; //0x8224AA28,
	int Cmd_RegisterNotification_a; //0x822258F0,
	int irand_a; //0x8220E470,
	int BG_TakePlayerWeapon_a; //0x82210A28,
	int BG_GetWeaponName_a; //0x820E22F0,
	int Cbuf_AddText_a; //0x82224A28,
	int G_ModelIndex_a; //0x8220CAD8,
	int GScr_Earthquake_a; //0x821F5230,
	int GScr_MagicBullet_a; //0x821FDA78,
	int ClientThink_Real_a; //0x821D1B28,
	int player_die_a; //0x821DCE60,
	int ScrCmd_Attach_a; //0x821F5668,
	int SP_Script_Model_a; //0x82206E20,
	int SV_UnlinkEntity_a; //0x8225F4A0,
	int SV_LinkEntity_a; //0x8225F588,
	int SV_SetBrushModel_a; //0x82254BB8,
	int G_EffectIndex_a; //0x8220CEE0,
	int Scr_PlayFX_a; //0x821FB858,
	int ScrCmd_LinkTo_a; //0x821F63D0,
	int ScriptEntCmd_RotateTo_a; //0x82207600,
	int GScr_Spawn_a; //0x821F54D0,
	int G_CallSpawnEntity_a; //0x822093E0,
	int Scr_SetString_a; //0x82242AD0,
	int ScriptEntCmd_CloneBrushModelToScriptModel_a; //0x822081D8,
	int ScriptEntCmd_rotateyaw_a; //0x82207AC0,
	int SV_DObjGetBoneIndex_a; //0x822552E0,
	int G_FindConfigstringIndex_a; //0x8220C740,
	int G_AddEvent_a; //0x8220E0D0,
	int PlayerCmd_cloneplayer_a; //0x821DAB88,
	int G_SpawnPlayerClone_a; //0x8220EDD8,
	int G_SoundAliasIndex_a; //0x8220D048,
	int Dvar_GetInt_a; //0x8229EFC0,
	int Dvar_GetFloat_a; //0x8229F028,
	int SV_AddTestClient_a; //0x822546F8,
	int SetClientViewAngle_a; //0x821D35E8,
	int G_Damage_a; //0x821DD470,
	int HudElem_DestroyAll_a; //0x821DFAF0,
	int G_SpawnTurret_a; //0x82219990,
	int GScr_PlayerLinkTo_a; //0x821F6938,
	int ScrCmd_Unlink_a; //0x821F63E0,
	int ScriptEntCmd_MoveTo_a; //0x82207058,
	int GScr_LoadMap_a; //0x822015B0,
	int G_RadiusDamage_a; //0x821DE4B0,
	int G_EntUnlink_a; //0x82211208,
	int SV_KickClient_a; //0x82251698,
	int SV_SetConfigString_a; //0x822568A8,
	int SuperJump_a; //0x8200183C,
	int SuperSpeed_a; //0x821D1E78,
	int FallDamage_a; //0x82000858

	/*void SetAddresses()
	{
		_0x8360922C = 0x8360922C;
		_0x83623B98 = 0x83623B98;
		_0x97F80 = 0x00097F80;
		_0x83620380 = 0x83620380;
		_0x3818 = 0x00003818;
		_0x186A0 = 0x000186A0;
		_0x206426 = 0x00206426;
		_0x8200183C = 0x8200183C;
		_0x394002FF = 0x394002FF;
		_0x394000BE = 0x394000BE;
		_0x806831 = 0x00806831;
		_0x825E2200 = 0x825E2200;
		_0x415E0 = 0x000415E0;
		_0x82255A68 = 0x82255A68;
		_0x8310A12C = 0x8310A12C;
		_0x838BA824 = 0x838BA824;
		_0x825B8638 = 0x825B8638;
		_0x33A8 = 0x000033A8;
		level_locals_t_a = 0x83109D80;
		cgArray_a = 0x825B8638;
		client_t = 0x83620380;
		g_hudelem_s_a = 0x82ED6560;
		g_hudelem_s_size = 0x000000B4;
		gentity_s_a = 0x82F03600;
		gentity_s_size = 0x00000280;
		GetObjectType_a = 0x00202560;
		Scr_NotifyNum_a = 0x8224AF98;
		Scr_AddEntityNum_a = 0x8224C648;
		Scr_AddObject_a = 0x0020C480;
		Scr_AddHudElem_a = 0x822096F8;
		Scr_GetSelf_a = 0x822437E0;
		scrVarGlob_t_a = 0x83373B80;
		GetVariableValueAddress_a = 0x82243E18;
		Scr_AddInt_a = 0x8224C3D0;
		Scr_AddBool_a = 0x8224C350;
		Scr_AddFloat_a = 0x8224C450;
		Scr_AddString_a = 0x8224C6A8;
		Scr_AddEntity_a = 0x82209580;
		Scr_AddVector_a = 0x8224C850;
		Scr_AddUndefined_a = 0x8224C550;
		Scr_AddConstString_a = 0x8224C7C8;
		Scr_ClearOutParams_a = 0x82249E78;
		AngleVectors_a = 0x8228EDC0;
		vectoangles_a = 0x822899A0;
		SV_ExecuteClientCommand_a = 0x822531C8;
		G_Spawn_a = 0x8220DBE8;
		G_SpawnHelicopter_a = 0x82315E48;
		G_SetOrigin_a = 0x8220E170;
		G_SetAngles_a = 0x8220E1C8;
		G_EntLinkTo_a = 0x822122C0;
		GSC_Earthquake_a = 0x821F5230;
		scrVmPub_t_a = 0x835C49D8;
		FindVariable_a = 0x82243BE8;
		GetValueType_a = 0x82244318;
		FindEntityId_a = 0x822444C0;
		Scr_GetEntityIdRef_a = 0x822448F8;
		GetArraySize_a = 0x82243F78;
		G_LocationalTrace_a = 0x821E7790;
		G_SetModel_a = 0x8220D310;
		G_LocalizedStringIndex_a = 0x8220C838;
		G_MaterialIndex_a = 0x8220C9F8;
		G_GivePlayerWeapon_a = 0x82210BC8;
		G_GetWeaponIndexForName_a = 0x82210640;
		G_InitializeAmmo_a = 0x821D4A00;
		G_GetPlayerViewOrigin_a = 0x821D3960;
		Menu_PaintAll_a = 0x82285F08;
		va_a = 0x822A7008;
		Dvar_FindMalleableVar_a = 0x8229ED90;
		Dvar_GetBool_a = 0x8229EF58;
		Dvar_GetString_a = 0x8229F118;
		Scr_Notify_a = 0x822097A8;
		SL_GetString_a = 0x822422D8;
		SL_ConvertToString_a = 0x82241920;
		SV_SendServerCommand_a = 0x822579B0;
		Scr_GetEntityId_a = 0x00000000;
		GetArrayVariable_a = 0x82245C58;
		GetVariable_a = 0x82245D48;
		Scr_GetObjectField_a = 0x00000000;
		VM_Notify_a = 0x8224AA28;
		Cmd_RegisterNotification_a = 0x822258F0;
		irand_a = 0x8220E470;
		BG_TakePlayerWeapon_a = 0x82210A28;
		BG_GetWeaponName_a = 0x820E22F0;
		Cbuf_AddText_a = 0x82224A28;
		G_ModelIndex_a = 0x8220CAD8;
		GScr_Earthquake_a = 0x821F5230;
		GScr_MagicBullet_a = 0x821FDA78;
		ClientThink_Real_a = 0x821D1B28;
		player_die_a = 0x821DCE60;
		ScrCmd_Attach_a = 0x821F5668;
		SP_Script_Model_a = 0x82206E20;
		SV_UnlinkEntity_a = 0x8225F4A0;
		SV_LinkEntity_a = 0x8225F588;
		SV_SetBrushModel_a = 0x82254BB8;
		G_EffectIndex_a = 0x8220CEE0;
		Scr_PlayFX_a = 0x821FB858;
		ScrCmd_LinkTo_a = 0x821F63D0;
		ScriptEntCmd_RotateTo_a = 0x82207600;
		GScr_Spawn_a = 0x821F54D0;
		G_CallSpawnEntity_a = 0x822093E0;
		Scr_SetString_a = 0x82242AD0;
		ScriptEntCmd_CloneBrushModelToScriptModel_a = 0x822081D8;
		ScriptEntCmd_rotateyaw_a = 0x82207AC0;
		SV_DObjGetBoneIndex_a = 0x822552E0;
		G_FindConfigstringIndex_a = 0x8220C740;
		G_AddEvent_a = 0x8220E0D0;
		PlayerCmd_cloneplayer_a = 0x821DAB88;
		G_SpawnPlayerClone_a = 0x8220EDD8;
		G_SoundAliasIndex_a = 0x8220D048;
		Dvar_GetInt_a = 0x8229EFC0;
		Dvar_GetFloat_a = 0x8229F028;
		SV_AddTestClient_a = 0x822546F8;
		SetClientViewAngle_a = 0x821D35E8;
		G_Damage_a = 0x821DD470;
		HudElem_DestroyAll_a = 0x821DFAF0;
		G_SpawnTurret_a = 0x82219990;
		GScr_PlayerLinkTo_a = 0x821F6938;
		ScrCmd_Unlink_a = 0x821F63E0;
		ScriptEntCmd_MoveTo_a = 0x82207058;
		GScr_LoadMap_a = 0x822015B0;
		G_RadiusDamage_a = 0x821DE4B0;
		G_EntUnlink_a = 0x82211208;
		SV_KickClient_a = 0x82251698;
		SV_SetConfigString_a = 0x822568A8;
		SuperJump_a = 0x8200183C;
		SuperSpeed_a = 0x821D1E78;
		FallDamage_a = 0x82000858;
	}*/
};

struct GAME_ADDRESS_TRANSFER_MW2_ONHOST
{
	mw2_addr_onhost_s* addr;

	void* G_Spawn;
	void* G_SetOrigin;
	void* G_SetAngles;
	void* G_CallSpawnEntity;
	void* ScrCmd_LinkTo;
	void* rotateto;
	void* G_SpawnTurret;
	void* rotateyaw;
	void* Dvar_GetBool;
	void* Dvar_GetInt;
	void* Dvar_GetFloat;
	void* Dvar_GetString;
	void* SV_SendServerCommand;
	void* Cbuf_AddText;
	void* G_SoundAliasIndex;
	void* Cmd_RegisterNotification;
	void* G_ModelIndex;
	void* G_LocationalTrace;
	void* SL_ConvertToString;
	void* Scr_GetSelf;
	void* Scr_AddInt;
	void* Scr_AddEntity;
	void* Scr_AddBool;
	void* Scr_AddFloat;
	void* Scr_AddString;
	void* Scr_AddConstString;
	void* Scr_AddEntity_i;
	void* Scr_AddVector;
	void* Scr_AddUndefined;
	void* Scr_ClearOutParams;
	void* SV_SetConfigString;
	void* GScr_Earthquake;
	void* AngleVectors;
	void* G_GetPlayerViewOrigin;
	void* GSC_magicbullet;
	void* Player_Die;
	void* G_GetWeaponIndexForName;
	void* G_GivePlayerWeapon;
	void* G_InitializeAmmo;
	void* SetClientViewAngle;
	void* SP_Script_Model;
	void* SV_UnlinkEntity;
	void* SV_LinkEntity;
	void* SV_SetBrushModel;
	void* BG_GetWeaponName;
	void* G_EffectIndex;
	void* Scr_PlayFX;
	void* SL_GetString;
	void* Scr_SetString;
	void* SV_DObjGetBoneIndex;
	void* G_FindConfigStringIndex;
	void* G_AddEvent;
	void* vectoangles;
	void* SV_AddTestClient;
	void* SV_ExecuteClientCommand;
	void* G_Damage;
	void* HudElem_DestroyAll;
	void* G_SpawnHelicopter;
	void* G_EntLinkTo;
	void* G_EntUnlink;
	void* ScriptEntCmd_MoveTo;
	void* GScr_LoadMap;
	void* SV_KickClient;
	void* LocalizedStringIndex;
	void* GetMaterialIndex;
	void* G_RadiusDamage;
};

GAME_ADDRESS_TRANSFER_MW2_ONHOST* ExternalFunctions;
mw2_addr_onhost_s* addr = 0;

gentity_t* G_Spawn()
{
	gentity_t*(*G_Spawn_f)() = (gentity_t*(*)())addr->G_Spawn_a;
	return G_Spawn_f();
}

void G_SetOrigin(gentity_t* p1, float* p2)
{
	void(*G_SetOrigin_f)(gentity_t*, float*) = (void(*)(gentity_t*, float*))addr->G_SetOrigin_a;
	G_SetOrigin_f(p1, p2);
}

void G_SetAngles(gentity_t* p1, float* p2)
{
	void(*G_SetAngles_f)(gentity_t*, float*) = (void(*)(gentity_t*, float*))addr->G_SetAngles_a;
	G_SetAngles_f(p1, p2);
}

int G_CallSpawnEntity(gentity_t* p1)
{
	int(*G_CallSpawnEntity_f)(gentity_t*) = (int(*)(gentity_t*))addr->G_CallSpawnEntity_a;
	return G_CallSpawnEntity_f(p1);
}

void ScrCmd_LinkTo(scr_entref_t entref)
{
	void(*ScrCmd_LinkTo_f)(scr_entref_t entref) = (void(*)(scr_entref_t))addr->ScrCmd_LinkTo_a;
	ScrCmd_LinkTo_f(entref);
}

void rotateto(scr_entref_t entref)
{
	void(*rotateto_f)(scr_entref_t entref) = (void(*)(scr_entref_t))addr->ScriptEntCmd_RotateTo_a;
	rotateto_f(entref);
}

void G_SpawnTurret(gentity_t *ent, const char* weapinfoname)
{
	void(*G_SpawnTurret_f)(gentity_t *ent, const char* weapinfoname) = (void(*)(gentity_t *, const char*))addr->G_SpawnTurret_a;
	G_SpawnTurret_f(ent, weapinfoname);
}

void rotateyaw(scr_entref_t entref)
{
	void(*rotateyaw_f)(scr_entref_t entref) = (void(*)(scr_entref_t))addr->ScriptEntCmd_rotateyaw_a;
	rotateyaw_f(entref);
}

bool Dvar_GetBool_mw2(const char* Dvar)
{
	bool(*Dvar_GetBool_f)(const char *Dvar) = (bool(*)(const char*))addr->Dvar_GetBool_a;
	return Dvar_GetBool_f(Dvar);
}

int Dvar_GetInt_mw2(const char* Dvar)
{
	int(*Dvar_GetInt_f)(const char *Dvar) = (int(*)(const char*))addr->Dvar_GetInt_a;
	return Dvar_GetInt_f(Dvar);
}

float Dvar_GetFloat_mw2(const char* Dvar)
{
	float(*Dvar_GetFloat_f)(const char *Dvar) = (float(*)(const char*))addr->Dvar_GetFloat_a;
	return Dvar_GetFloat_f(Dvar);
}

char* Dvar_GetString(const char* Dvar)
{
	char*(*Dvar_GetString_f)(const char *Dvar) = (char*(*)(const char*))addr->Dvar_GetString_a;
	return Dvar_GetString_f(Dvar);
}

void SV_SendServerCommand(int client_s, int type, const char *fmt)
{
	void(*SV_SendServerCommand_f)(int client_s, int type, const char *fmt) = (void(*)(int, int, const char*))addr->SV_SendServerCommand_a;
	SV_SendServerCommand_f(client_s, type, fmt);
}

void Cbuf_AddText(int localClient, char* Cmd)
{
	void(*Cbuf_AddText)(int localClient, char* Cmd) = (void(*)(int, char*))addr->Cbuf_AddText_a;
	Cbuf_AddText(localClient, Cmd);
}

int G_SoundAliasIndex(char* name)
{
	int(*G_SoundAliasIndex_f)(char *name) = (int(*)(char *))addr->G_SoundAliasIndex_a;
	return G_SoundAliasIndex_f(name);
}

void Cmd_RegisterNotification(int clientNum, const char* command, const char* notify)
{
	void(*Cmd_RegisterNotification_f)(int clientNum, const char* command, const char* notify) = (void(*)(int clientNum, const char* command, const char* notify))addr->Cmd_RegisterNotification_a;
	Cmd_RegisterNotification_f(clientNum, command, notify);
}

int G_ModelIndex(char* Model)
{
	int(*G_ModelIndex_f)(char* Model) = (int(*)(char* Model))addr->G_ModelIndex_a;
	return G_ModelIndex_f(Model);
}

void G_LocationalTrace(trace_t* results, float *start, float *end, int passEnitiyNum, int contentMask, char *priorityMap)
{
	void(*G_LocationalTrace_f)(trace_t* results, float *start, float *end, int passEnitiyNum, int contentMask, char *priorityMap) = (void(*)(trace_t* results, float *start, float *end, int passEnitiyNum, int contentMask, char *priorityMap))addr->G_LocationalTrace_a;
	G_LocationalTrace_f(results, start, end, passEnitiyNum, contentMask, priorityMap);
}

char* SL_ConvertToString(unsigned short StringValue)
{
	char*(*SL_ConvertToString_f)(unsigned short StringValue) = (char*(*)(unsigned short StringValue))addr->SL_ConvertToString_a;
	return SL_ConvertToString_f(StringValue);
}

int Scr_GetSelf(int r3)
{
	int(*Scr_GetSelf_f)(int r3) = (int(*)(int r3))addr->Scr_GetSelf_a;
	return Scr_GetSelf_f(r3);
}

void Scr_AddInt(int r3)
{
	void(*Scr_AddInt_f)(int r3) = (void(*)(int r3))addr->Scr_AddInt_a;
	Scr_AddInt_f(r3);
}

void Scr_AddEntity(gentity_t* r3)
{
	void(*Scr_AddEntity_f)(gentity_t* r3) = (void(*)(gentity_t* r3))addr->Scr_AddEntity_a;
	Scr_AddEntity_f(r3);
}

void Scr_AddBool(bool r3)
{
	void(*Scr_AddBool_f)(bool r3) = (void(*)(bool r3))addr->Scr_AddBool_a;
	Scr_AddBool_f(r3);
}

void Scr_AddFloat(float r3)
{
	void(*Scr_AddFloat_f)(float r3) = (void(*)(float r3))addr->Scr_AddFloat_a;
	Scr_AddFloat_f(r3);
}

void Scr_AddString(const char* r3)
{
	void(*Scr_AddString_f)(const char* r3) = (void(*)(const char* r3))addr->Scr_AddString_a;
	Scr_AddString_f(r3);
}

void Scr_AddConstString(unsigned int r3)
{
	void(*Scr_AddConstString_f)(unsigned int r3) = (void(*)(unsigned int r3))addr->Scr_AddConstString_a;
	Scr_AddConstString_f(r3);
}

void Scr_AddEntity_i(int r3)
{
	void(*Scr_AddEntity_f_i)(int r3) = (void(*)(int r3))addr->Scr_AddEntity_a;
	Scr_AddEntity_f_i(r3);
}

void Scr_AddVector(float* r3)
{
	void(*Scr_AddVector_f)(float* r3) = (void(*)(float* r3))addr->Scr_AddVector_a;
	Scr_AddVector_f(r3);
}

void Scr_AddUndefined()
{
	void(*Scr_AddUndefined_f)() = (void(*)())addr->Scr_AddUndefined_a;
	Scr_AddUndefined_f();
}

void Scr_ClearOutParams()
{
	void(*Scr_ClearOutParams_f)() = (void(*)())addr->Scr_ClearOutParams_a;
	Scr_ClearOutParams_f();
}

void SV_SetConfigString(unsigned int r3, const char* r4)
{
	void(*SV_SetConfigString_f)(unsigned int r3, const char* r4) = (void(*)(unsigned int r3, const char* r4))addr->SV_SetConfigString_a;
	SV_SetConfigString_f(r3, r4);
}

void GScr_Earthquake()
{
	void(*GScr_Earthquake_f)() = (void(*)())addr->GScr_Earthquake_a;
	GScr_Earthquake_f();
}

void AngleVectors(const float* p1, float* p2, float* p3, float* p4)
{
	void(*AngleVectors_f)(const float*, float*, float*, float*) = (void(*)(const float*, float*, float*, float*))addr->AngleVectors_a;
	AngleVectors_f(p1, p2, p3, p4);
}

void G_GetPlayerViewOrigin(gclient_t *client, float *out)
{
	void(*G_GetPlayerViewOrigin_f)(gclient_t *client, float *out) = (void(*)(gclient_t*, float*))addr->G_GetPlayerViewOrigin_a;
	G_GetPlayerViewOrigin_f(client, out);
}

void GSC_magicbullet()
{
	void(*GSC_magicbullet_f)() = (void(*)())addr->GScr_MagicBullet_a;
	GSC_magicbullet_f();
}

void Player_Die(gentity_t* self, gentity_t* inflictor, gentity_t* attacker, int damage, int meansOfDeath, int WeaponIndex, const float *vDir, int hitLocation, int* psTime)
{
	void(*Player_Die_f)(gentity_t* self, gentity_t* inflictor, gentity_t* attacker, int damage, int meansOfDeath, int WeaponIndex, const float *vDir, int hitLocation, int* psTime) = (void(*)(gentity_t*, gentity_t*, gentity_t*, int, int, int, const float *, int, int*))addr->player_die_a;
	Player_Die_f(self, inflictor, attacker, damage, meansOfDeath, WeaponIndex, vDir, hitLocation, psTime);
}

int G_GetWeaponIndexForName(const char* Name)
{
	int(*G_GetWeaponIndexForName_f)(const char* Name) = (int(*)(const char*))addr->G_GetWeaponIndexForName_a;
	return G_GetWeaponIndexForName_f(Name);
}

int G_GivePlayerWeapon(gclient_t *cl, int iWeaponIndex, char altModelIndex, bool p4)
{
	int(*G_GivePlayerWeapon_f)(gclient_t *cl, int iWeaponIndex, char altModelIndex, bool) = (int(*)(gclient_t*, int, char, bool))addr->G_GivePlayerWeapon_a;
	return G_GivePlayerWeapon_f(cl, iWeaponIndex, altModelIndex, p4);
}

void G_InitializeAmmo(gentity_t *pSelf, int weaponIndex, char weaponModel, int hadWeapon)
{
	void(*G_InitializeAmmo_f)(gentity_t *pSelf, int weaponIndex, char weaponModel, int hadWeapon) = (void(*)(gentity_t*, int, char, int))addr->G_InitializeAmmo_a;
	G_InitializeAmmo_f(pSelf, weaponIndex, weaponModel, hadWeapon);
}

void SetClientViewAngle(gentity_t *ent, float *p2)
{
	void(*SetClientViewAngle_f)(gentity_t *, float *) = (void(*)(gentity_t *, float *))addr->SetClientViewAngle_a;
	SetClientViewAngle_f(ent, p2);
}

void SP_Script_Model(gentity_t* ent)
{
	void(*SP_Script_Model_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SP_Script_Model_a;
	SP_Script_Model_f(ent);
}

void SV_UnlinkEntity(gentity_t* ent)
{
	void(*SV_UnlinkEntity_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_UnlinkEntity_a;
	SV_UnlinkEntity_f(ent);
}

void SV_LinkEntity(gentity_t* ent)
{
	void(*SV_LinkEntity_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_LinkEntity_a;
	SV_LinkEntity_f(ent);
}

void SV_SetBrushModel(gentity_t* ent)
{
	void(*SV_SetBrushModel_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_SetBrushModel_a;
	SV_SetBrushModel_f(ent);
}

char *BG_GetWeaponName(int p1)
{
	char *(*BG_GetWeaponName_f)(int) = (char *(*)(int))addr->BG_GetWeaponName_a;
	return BG_GetWeaponName_f(p1);
}

int G_EffectIndex(char *FX)
{
	int(*G_EffectIndex_f)(char *FX) = (int(*)(char*))addr->G_EffectIndex_a;
	return G_EffectIndex_f(FX);
}

void Scr_PlayFX()
{
	void(*Scr_PlayFX)() = (void(*)())addr->Scr_PlayFX_a;
	Scr_PlayFX();
}

short SL_GetString(const char *p1, int p2)
{
	short(*SL_GetString_f)(const char*, int) = (short(*)(const char*, int))addr->SL_GetString_a;
	return SL_GetString_f(p1, p2);
}

void Scr_SetString(unsigned __int16 *to, unsigned int from)
{
	void(*Scr_SetString_f)(unsigned __int16 *to, unsigned int from) = (void(*)(unsigned __int16 *, unsigned int))addr->Scr_SetString_a;
	Scr_SetString_f(to, from);
}

int SV_DObjGetBoneIndex(gentity_t* p1, int p2)
{
	int(*SV_DObjGetBoneIndex_f)(gentity_t*, int) = (int(*)(gentity_t*, int))addr->SV_DObjGetBoneIndex_a;
	return SV_DObjGetBoneIndex_f(p1, p2);
}

int G_FindConfigStringIndex(char * p1, int p2, int p3, int p4, int p5)
{
	int(*G_FindConfigStringIndex_f)(char *, int, int, int, int) = (int(*)(char *, int, int, int, int))addr->G_FindConfigstringIndex_a;

	return G_FindConfigStringIndex_f(p1, p2, p3, p4, p5);
}

void G_AddEvent(gentity_t *entity, int _event, int eventParm)
{
	void(*G_AddEvent_f)(gentity_t *entity, int _event, int eventParm) = (void(*)(gentity_t *, int, int))addr->G_AddEvent_a;
	G_AddEvent_f(entity, _event, eventParm);
}

void vectoangles(float * f1, float * f2)
{
	void(*vectoangles_f)(float *, float *) = (void(*)(float *, float *))addr->vectoangles_a;
	return vectoangles_f(f1, f2);
}

gentity_t* SV_AddTestClient()
{
	gentity_t *(*SV_AddTestClient_f)() = (gentity_t*(*)())addr->SV_AddTestClient_a;
	return SV_AddTestClient_f();
}

void SV_ExecuteClientCommand(void *cl, const char *s, int clientOK, int p1)
{
	void(*SV_ExecuteClientCommand_f)(void *cl, const char *s, int clientOK, int) = (void(*)(void*, const char*, int, int))addr->SV_ExecuteClientCommand_a;

	SV_ExecuteClientCommand_f(cl, s, clientOK, p1);
}

void G_Damage(gentity_t *targ, gentity_t *inflictor, gentity_t *attacker, const float *dir, const float *point, int damage, int dFlags, int mod, int weapon, hitLocation_t hitLoc, unsigned int modelIndex, unsigned int partName, int timeOffset)
{
	void(*G_Damage_f)(gentity_t *targ, gentity_t *inflictor, gentity_t *attacker, const float *dir, const float *point, int damage, int dFlags, int mod, int weapon, hitLocation_t hitLoc, unsigned int modelIndex, unsigned int partName, int timeOffset) = (void(*)(gentity_t *, gentity_t *, gentity_t *, const float *, const float *, int, int, int, int, hitLocation_t, unsigned int, unsigned int, int))addr->G_Damage_a;
	G_Damage_f(targ, inflictor, attacker, dir, point, damage, dFlags, mod, weapon, hitLoc, modelIndex, partName, timeOffset);
}

void HudElem_DestroyAll()
{
	void(*HudElem_DestroyAll_f)() = (void(*)())addr->HudElem_DestroyAll_a;
	HudElem_DestroyAll_f();
}

void G_SpawnHelicopter(gentity_t *ent, gentity_t *owner, const char *vehicleInfoName, const char *modelName)
{
	void(*G_SpawnHelicopter_f)(gentity_t *ent, gentity_t *owner, const char *vehicleInfoName, const char *modelName) = (void(*)(gentity_t*, gentity_t*, const char*, const char*))addr->G_SpawnHelicopter_a;
	G_SpawnHelicopter_f(ent, owner, vehicleInfoName, modelName);
}

int G_EntLinkTo(gentity_t *ent, gentity_t *parent, unsigned int tagname)
{
	int(*G_EntLinkTo_f)(gentity_t *ent, gentity_t *parent, unsigned int tagname) = (int(*)(gentity_t*, gentity_t*, unsigned int))addr->G_EntLinkTo_a;
	return G_EntLinkTo_f(ent, parent, tagname);
}

int G_EntUnlink(gentity_t *ent)
{
	int(*G_EntUnlink_f)(gentity_t *ent) = (int(*)(gentity_t*))addr->G_EntUnlink_a;
	return G_EntUnlink_f(ent);
}

void ScriptEntCmd_MoveTo(scr_entref_t entref)
{
	void(*ScriptEntCmd_MoveTo_f)(scr_entref_t entref) = (void(*)(scr_entref_t))addr->ScriptEntCmd_MoveTo_a;
	ScriptEntCmd_MoveTo_f(entref);
}

void GScr_LoadMap()
{
	void(*GScr_LoadMap_f)() = (void(*)())addr->GScr_LoadMap_a;
	GScr_LoadMap_f();
}

void SV_KickClient(void* cl, int p1, int p2, int p3, char * reasonText)
{
	void(*SV_KickClient)(void* cl, int, int, int, char * reasonText) = (void(*)(void*, int, int, int, char *))addr->SV_KickClient_a;
	SV_KickClient(cl, p1, p2, p3, reasonText);
}

int LocalizedStringIndex(const char* Text)
{
	int(*LocalizedStringIndex)(const char* Text) = (int(*)(const char*))addr->G_LocalizedStringIndex_a;
	return LocalizedStringIndex(Text);
}

int GetMaterialIndex(const char* Material)
{
	int(*GetMaterialIndex)(const char* Material) = (int(*)(const char*))addr->G_MaterialIndex_a;
	return GetMaterialIndex(Material);
}

void G_RadiusDamage(const float *origin, gentity_t *inflictor, gentity_t *attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float *coneDirection, gentity_t *ignore, int mod, int weapon)
{
	void(*G_RadiusDamage_f)(const float *origin, gentity_t *inflictor, gentity_t *attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float *coneDirection, gentity_t *ignore, int mod, int weapon) = (void(*)(const float*, gentity_t*, gentity_t*, float, float, float, float, float *, gentity_t*, int, int))addr->G_RadiusDamage_a;
	return G_RadiusDamage_f(origin, inflictor, attacker, fInnerDamage, fOuterDamage, radius, coneAngleCos, coneDirection, ignore, mod, weapon);
}

bool MW2_BuildFunctions_OnHost()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_MW2_ONHOST;

	if (addr)
		free(addr);

	addr = (mw2_addr_onhost_s*)malloc(sizeof(mw2_addr_onhost_s));

	for (int i = 0; i < 127; i++)
		((int*)(addr))[i] = GetAddress(MW2_OnHosts_addr_s_Data, MW2_OnHosts_addr_s_PatchID, i);

	/*CWriteFile("xbOnline:\\DownloadedOnhost.bin", addr, sizeof(mw2_addr_onhost_s));

	addr->SetAddresses();

	CWriteFile("xbOnline:\\LocalOnhost.bin", addr, sizeof(mw2_addr_onhost_s));*/

	ExternalFunctions->addr = addr;

	ExternalFunctions->G_Spawn = G_Spawn;
	ExternalFunctions->G_SetOrigin = G_SetOrigin;
	ExternalFunctions->G_SetAngles = G_SetAngles;
	ExternalFunctions->G_CallSpawnEntity = G_CallSpawnEntity;
	ExternalFunctions->ScrCmd_LinkTo = ScrCmd_LinkTo;
	ExternalFunctions->rotateto = rotateto;
	ExternalFunctions->G_SpawnTurret = G_SpawnTurret;
	ExternalFunctions->rotateyaw = rotateyaw;
	ExternalFunctions->Dvar_GetBool = Dvar_GetBool_mw2;
	ExternalFunctions->Dvar_GetInt = Dvar_GetInt_mw2;
	ExternalFunctions->Dvar_GetFloat = Dvar_GetFloat_mw2;
	ExternalFunctions->Dvar_GetString = Dvar_GetString;
	ExternalFunctions->SV_SendServerCommand = SV_SendServerCommand;
	ExternalFunctions->Cbuf_AddText = Cbuf_AddText;
	ExternalFunctions->G_SoundAliasIndex = G_SoundAliasIndex;
	ExternalFunctions->Cmd_RegisterNotification = Cmd_RegisterNotification;
	ExternalFunctions->G_ModelIndex = G_ModelIndex;
	ExternalFunctions->G_LocationalTrace = G_LocationalTrace;
	ExternalFunctions->SL_ConvertToString = SL_ConvertToString;
	ExternalFunctions->Scr_GetSelf = Scr_GetSelf;
	ExternalFunctions->Scr_AddInt = Scr_AddInt;
	ExternalFunctions->Scr_AddEntity = Scr_AddEntity;
	ExternalFunctions->Scr_AddBool = Scr_AddBool;
	ExternalFunctions->Scr_AddFloat = Scr_AddFloat;
	ExternalFunctions->Scr_AddString = Scr_AddString;
	ExternalFunctions->Scr_AddConstString = Scr_AddConstString;
	ExternalFunctions->Scr_AddEntity_i = Scr_AddEntity_i;
	ExternalFunctions->Scr_AddVector = Scr_AddVector;
	ExternalFunctions->Scr_AddUndefined = Scr_AddUndefined;
	ExternalFunctions->Scr_ClearOutParams = Scr_ClearOutParams;
	ExternalFunctions->SV_SetConfigString = SV_SetConfigString;
	ExternalFunctions->GScr_Earthquake = GScr_Earthquake;
	ExternalFunctions->AngleVectors = AngleVectors;
	ExternalFunctions->G_GetPlayerViewOrigin = G_GetPlayerViewOrigin;
	ExternalFunctions->GSC_magicbullet = GSC_magicbullet;
	ExternalFunctions->Player_Die = Player_Die;
	ExternalFunctions->G_GetWeaponIndexForName = G_GetWeaponIndexForName;
	ExternalFunctions->G_GivePlayerWeapon = G_GivePlayerWeapon;
	ExternalFunctions->G_InitializeAmmo = G_InitializeAmmo;
	ExternalFunctions->SetClientViewAngle = SetClientViewAngle;
	ExternalFunctions->SP_Script_Model = SP_Script_Model;
	ExternalFunctions->SV_UnlinkEntity = SV_UnlinkEntity;
	ExternalFunctions->SV_LinkEntity = SV_LinkEntity;
	ExternalFunctions->SV_SetBrushModel = SV_SetBrushModel;
	ExternalFunctions->BG_GetWeaponName = BG_GetWeaponName;
	ExternalFunctions->G_EffectIndex = G_EffectIndex;
	ExternalFunctions->Scr_PlayFX = Scr_PlayFX;
	ExternalFunctions->SL_GetString = SL_GetString;
	ExternalFunctions->Scr_SetString = Scr_SetString;
	ExternalFunctions->SV_DObjGetBoneIndex = SV_DObjGetBoneIndex;
	ExternalFunctions->G_FindConfigStringIndex = G_FindConfigStringIndex;
	ExternalFunctions->G_AddEvent = G_AddEvent;
	ExternalFunctions->vectoangles = vectoangles;
	ExternalFunctions->SV_AddTestClient = SV_AddTestClient;
	ExternalFunctions->SV_ExecuteClientCommand = SV_ExecuteClientCommand;
	ExternalFunctions->G_Damage = G_Damage;
	ExternalFunctions->HudElem_DestroyAll = HudElem_DestroyAll;
	ExternalFunctions->G_SpawnHelicopter = G_SpawnHelicopter;
	ExternalFunctions->G_EntLinkTo = G_EntLinkTo;
	ExternalFunctions->G_EntUnlink = G_EntUnlink;
	ExternalFunctions->ScriptEntCmd_MoveTo = ScriptEntCmd_MoveTo;
	ExternalFunctions->GScr_LoadMap = GScr_LoadMap;
	ExternalFunctions->SV_KickClient = SV_KickClient;
	ExternalFunctions->LocalizedStringIndex = LocalizedStringIndex;
	ExternalFunctions->GetMaterialIndex = GetMaterialIndex;
	ExternalFunctions->G_RadiusDamage = G_RadiusDamage;

	HVGetVersionsPokeDWORD(0x800001000000BEE0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BEE4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_MW2_ONHOST)));

	return true;
}



