#include "main.h"

Security * MW3_OnHosts_addr_s_Data = 0;
unsigned int *MW3_OnHosts_addr_s_PatchID = 0;

void MW3_OnHosts_SetupGameAddresses(ServerData_MW3_OnHosts* Server)
{
	if (MW3_OnHosts_addr_s_Data)
		delete MW3_OnHosts_addr_s_Data;

	MW3_OnHosts_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		MW3_OnHosts_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	MW3_OnHosts_addr_s_Data = new Security(t, g_Session);
	MW3_OnHosts_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, MW3_OnHosts_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

struct gclient_t;
struct gentity_t;
enum DvarSetSource;

enum netsrc_t {
	NS_CLIENT1 = 0x0,
	NS_MAXCLIENTS = 0x1,
	NS_SERVER = 0x2,
	NS_PACKET = 0x3,
	NS_INVALID_NETSRC = 0x4,
};

enum netadrtype_t
{
	NA_BOT = 0x0,
	NA_BAD = 0x1,
	NA_LOOPBACK = 0x2,
	NA_BROADCAST = 0x3,
	NA_IP = 0x4,
};

struct netadr_s {
	netadrtype_t type;
	char ip[4];
	unsigned short port;
	netsrc_t localNetID;
	unsigned int addrHandleIndex;
};

struct msg_t {
	int overflowed;
	int readOnly;
	char* data;
	char* splitData;
	int maxsize;
	int cursize;
	int splitSize;
	int readcount;
	int bit;
	int lastEntityRef;
	netsrc_t targetLocalNetID;
	int useZlib;
};


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

struct Usercmd_t
{
	int time;     //0x0
	int buttons;    //0x4
	int viewAngles[3];   //0x8
	char padding00[0x8];  //0x14
	char fDir;
	char rDir;
	char uDir;
	char yDir;     //0x1C
	char padding[0xC];   //0x20
						 //Size: 0x2C
};

struct mw3_addr_onhost_s
{
	int gentity_s_a; //0x82DCCC80,
	int g_hudelems_a; //0x82D9FBD0,
	int levels_locals_t; //0x82FDA080,
	int client_s_a; //0x834C0480,
	int client_p_a; //0x836C6310, 
	int AngleVectors_a; //0x8231A980, 
	int BG_GetPerkIndexForName_a; //0x820E1710,
	int BG_TakePlayerWeapon_a; //0x820F90B8,
	int BG_GetWeaponDef_a; //0x820D5A10,
	int BG_GetWeaponName_a; //0x820F7818,

	int Cbuf_AddText_a; //0x82287EE0,
	int ClientThink_Real_a; //0x8222E278,
	int Cmd_RegisterNotification_a; //0x82288F68,

	int DB_FindXAssetHeader_a; //0x821EEB70,

	int Dvar_GetBool_a; //0x8232E200,
	int Dvar_GetString_a; //0x8232E3C0,
	int Dvar_GetInt_a; //0x8232E268,
	int Dvar_GetFloat_a; //0x8232E2D0,
	int Dvar_SetFromStringByNameFromSource_a; //0x82330478,

	int G_EntLinkTo_a; //0x82274630,
	int G_EntUnlink_a; //0x82273400,
	int G_SetModel_a; //0x8226EA20,
	int G_Spawn_a; //0x8226F2F8,
	int G_TempEntity_a; //0x82270618,
	int G_SetOrigin_a; //0x8226F860,
	int G_SetAngle_a; //0x8226F8B8,
	int G_SoundAliasIndex_a; //0x8226E758,
	int G_EffectIndex_a; //0x8226E5F0,
	int G_MaterialIndex_a; //0x8226E100,
	int G_LocalizedStringIndex_a; //0x8226E020,
	int G_InitializeAmmo_a; //0x822311D0,
	int G_FindConfigstringIndex_a; //0x8226DF28,
	int G_AddEvent_a; //0x8226F7C0,
	int G_GetWeaponIndexForName_a; //0x822722F0,
	int G_GivePlayerWeapon_a; //0x82272D88,
	int G_EntEnablePhysics_a; //0x82242008,
	int G_CallSpawnEntity_a; //0x8226AB30,
	int G_ModelIndex_a; //0x8226E1E8,
	int G_LocationalTrace_a; //0x82245650,
	int G_GetPlayerViewOrigin_a; //0x82230000,
	int G_SpawnHelicopter_a; //0x823AD480,
	int G_FreeEntity_a; //0x8226F5C8,
	int G_VehFreeEntity_a; //0x8239F838,
	int G_FireRocket_a; //0x8224CCB8,
	int G_SpawnTurret_a; //0x8227C2B0,

	int GScr_LoadMap_a; //0x82262F88,

	int Menu_PaintAll_a; //0x82309108,

	int Player_Die_a; //0x8223A4C0,

	int Scr_AddInt_a; //0x822BFA18,
	int Scr_AddBool_a; //0x822BF9E0,
	int Scr_AddFloat_a; //0x822BFA50,
	int Scr_AddString_a; //0x822BFBC8,
	int Scr_AddEntity_a; //0x8226ACF0,
	int Scr_AddVector_a; //0x822BFCD8,
	int Scr_AddConstString_a; //0x822BFC68,
	int Scr_GetSelf_a; //0x822B7768,
	int Scr_PlayerDamage_a; //0x82266608,
	int Scr_MagicBullet_a; //0x8225EA08,

	int scrVmPub_t_a; //0x83452C00,

	int SetClientViewAngle_a; //0x8222FC90,

	int SL_ConvertToString_a; //0x822B5080,
	int SL_GetString_a; //0x822B5C28,

	int SP_Script_Model_a; //0x822680B8,

	int SV_GameSendServerCommand_a; //0x822C9278,
	int SV_ExecuteClientCommand_a; //0x822C7800,
	int SV_SendServerCommandMsg_a; //0x822CD380,
	int SV_GetConfigstring_a; //0x822CA378,
	int SV_LinkEntity_a; //0x822D6DB0,
	int SV_SetBrushModel_a; //0x822C9500,
	int SV_UnlinkEntity_a; //0x822D6CC8,
	int SV_GetProtocol_a; //0x8232A258,
	int SV_GetChecksum_a; //0x820E0B50,
	int SV_Cmd_TokenizeString_a; //0x82288968,
	int SV_Cmd_EndTokenizedString_a; //0x82288988,
	int SV_DirectConnect_a; //0x822C89E8,
	int SV_SendClientGameState_a; //0x822C6D30,
	int SV_ClientEnterWorld_a; //0x822C6EB0,
	int SV_DelayDropClient_a; //0x822C6890,
	int SV_DropClient_a; //0x822C6608,
	int SV_CheckTimeout_a; //0x822CE5B0,
	int SV_SendServerMessage_a; //0x822CCD70,
	int SV_SetConfigString_a; //0x822CB3E8,

	int Turret_Shoot_a; //0x82278B08,

	int VectoAngles_a; //0x82315528,
	int VM_Notify_a; //0x822BDF38,

	int sub_8237CA90_a; //0x8237CA90,
	int sub_823798C0_a; //0x823798C0,

	int SuperJump_a; //0x82001D68,
	int FallDamage_a; //0x82000C04,
	int SuperSpeed_a; //0x8222E59E

	int sub_823C5EA8_a;
	int sub_823C61B0_a;

	int sub_82241320_a;
	int sub_82240C68_a;
	int sub_82240970_a;

	/*void SetAddresses()
	{
		gentity_s_a = 0x82DCCC80;
		g_hudelems_a = 0x82D9FBD0;
		levels_locals_t = 0x82FDA080;
		client_s_a = 0x834C0480;
		client_p_a = 0x836C6310;

		AngleVectors_a = 0x8231A980;

		BG_GetPerkIndexForName_a = 0x820E1710;
		BG_TakePlayerWeapon_a = 0x820F90B8;
		BG_GetWeaponDef_a = 0x820D5A10;
		BG_GetWeaponName_a = 0x820F7818;

		Cbuf_AddText_a = 0x82287EE0;
		ClientThink_Real_a = 0x8222E278;
		Cmd_RegisterNotification_a = 0x82288F68;

		DB_FindXAssetHeader_a = 0x821EEB70;

		Dvar_GetBool_a = 0x8232E200;
		Dvar_GetString_a = 0x8232E3C0;
		Dvar_GetInt_a = 0x8232E268;
		Dvar_GetFloat_a = 0x8232E2D0;
		Dvar_SetFromStringByNameFromSource_a = 0x82330478;

		G_EntLinkTo_a = 0x82274630;
		G_EntUnlink_a = 0x82273400;
		G_SetModel_a = 0x8226EA20;
		G_Spawn_a = 0x8226F2F8;
		G_TempEntity_a = 0x82270618;
		G_SetOrigin_a = 0x8226F860;
		G_SetAngle_a = 0x8226F8B8;
		G_SoundAliasIndex_a = 0x8226E758;
		G_EffectIndex_a = 0x8226E5F0;
		G_MaterialIndex_a = 0x8226E100;
		G_LocalizedStringIndex_a = 0x8226E020;
		G_InitializeAmmo_a = 0x822311D0;
		G_FindConfigstringIndex_a = 0x8226DF28;
		G_AddEvent_a = 0x8226F7C0;
		G_GetWeaponIndexForName_a = 0x822722F0;
		G_GivePlayerWeapon_a = 0x82272D88;
		G_EntEnablePhysics_a = 0x82242008;
		G_CallSpawnEntity_a = 0x8226AB30;
		G_ModelIndex_a = 0x8226E1E8;
		G_LocationalTrace_a = 0x82245650;
		G_GetPlayerViewOrigin_a = 0x82230000;
		G_SpawnHelicopter_a = 0x823AD480;
		G_FreeEntity_a = 0x8226F5C8;
		G_VehFreeEntity_a = 0x8239F838;
		G_FireRocket_a = 0x8224CCB8;
		G_SpawnTurret_a = 0x8227C2B0;

		GScr_LoadMap_a = 0x82262F88;

		Menu_PaintAll_a = 0x82309108;

		Player_Die_a = 0x8223A4C0;

		Scr_AddInt_a = 0x822BFA18;
		Scr_AddBool_a = 0x822BF9E0;
		Scr_AddFloat_a = 0x822BFA50;
		Scr_AddString_a = 0x822BFBC8;
		Scr_AddEntity_a = 0x8226ACF0;
		Scr_AddVector_a = 0x822BFCD8;
		Scr_AddConstString_a = 0x822BFC68;

		Scr_GetSelf_a = 0x822B7768;
		Scr_PlayerDamage_a = 0x82266608;
		Scr_MagicBullet_a = 0x8225EA08;

		scrVmPub_t_a = 0x83452C00;

		SetClientViewAngle_a = 0x8222FC90;

		SL_ConvertToString_a = 0x822B5080;
		SL_GetString_a = 0x822B5C28;

		SP_Script_Model_a = 0x822680B8;

		SV_GameSendServerCommand_a = 0x822C9278;
		SV_ExecuteClientCommand_a = 0x822C7800;
		SV_SendServerCommandMsg_a = 0x822CD380;
		SV_GetConfigstring_a = 0x822CA378;
		SV_LinkEntity_a = 0x822D6DB0;
		SV_SetBrushModel_a = 0x822C9500;
		SV_UnlinkEntity_a = 0x822D6CC8;
		SV_GetProtocol_a = 0x8232A258;
		SV_GetChecksum_a = 0x820E0B50;
		SV_Cmd_TokenizeString_a = 0x82288968;
		SV_Cmd_EndTokenizedString_a = 0x82288988;
		SV_DirectConnect_a = 0x822C89E8;
		SV_SendClientGameState_a = 0x822C6D30;
		SV_ClientEnterWorld_a = 0x822C6EB0;
		SV_DelayDropClient_a = 0x822C6890;
		SV_DropClient_a = 0x822C6608;
		SV_CheckTimeout_a = 0x822CE5B0;
		SV_SendServerMessage_a = 0x822CCD70;
		SV_SetConfigString_a = 0x822CB3E8;

		Turret_Shoot_a = 0x82278B08;

		VectoAngles_a = 0x82315528;
		VM_Notify_a = 0x822BDF38;

		sub_8237CA90_a = 0x8237CA90;
		sub_823798C0_a = 0x823798C0;

		sub_823C5EA8_a = 0x823C5EA8;
		sub_823C61B0_a = 0x823C61B0;

		sub_82241320_a = 0x82241320;
		sub_82240C68_a = 0x82240C68;
		sub_82240970_a = 0x82240970;

		SuperJump_a = 0x82001D68;
		FallDamage_a = 0x82000C04;
		SuperSpeed_a = 0x8222E59E;
	}*/

	//New stuff

	/*void SetAddresses()
	{
		gentity_s_a = 0x82DCCC80; //0x82DCCC80;
		g_hudelems_a = 0x82D9FBD0; //0x82D9FBD0;
		levels_locals_t = 0x82FDA080; //0x82FDA080;
		client_s_a = 0x834C0480; //0x834C0480;
		client_p_a = 0x836C6310; //0x836C6310;

		AngleVectors_a = 0x8231AA48; //0x8231A980;

		BG_GetPerkIndexForName_a = 0x820E1710; //0x820E1710;
		BG_TakePlayerWeapon_a = 0x820F90B8; //0x820F90B8;
		BG_GetWeaponDef_a = 0x820D5A10; //0x820D5A10;
		BG_GetWeaponName_a = 0x820F7818; //0x820F7818;

		Cbuf_AddText_a = 0x82287F68; //0x82287EE0;
		ClientThink_Real_a = 0x8222E2F8;//0x8222E278;
		Cmd_RegisterNotification_a = 0x82288FF0; //0x82288F68;

		DB_FindXAssetHeader_a = 0x821EEBF0; //0x821EEB70;

		Dvar_GetBool_a = 0x8232E2C8; //0x8232E200;
		Dvar_GetString_a = 0x8232E488; //0x8232E3C0;
		Dvar_GetInt_a = 0x8232E330; //0x8232E268;
		Dvar_GetFloat_a = 0x8232E398; //0x8232E2D0;
		Dvar_SetFromStringByNameFromSource_a = 0x82330540; //0x82330478;

		G_EntLinkTo_a = 0x822746B0; //0x82274630;
		G_EntUnlink_a = 0x82273480; //0x82273400;
		G_SetModel_a = 0x8226EAA0; //0x8226EA20;
		G_Spawn_a = 0x8226F378; //0x8226F2F8;
		G_TempEntity_a = 0x82270698; //0x82270618;
		G_SetOrigin_a = 0x8226F8E0; //0x8226F860;
		G_SetAngle_a = 0x8226F938; //0x8226F8B8;
		G_SoundAliasIndex_a = 0x8226E7D8; //0x8226E758;
		G_EffectIndex_a = 0x8226E670; //0x8226E5F0;
		G_MaterialIndex_a = 0x8226E180; //0x8226E100;
		G_LocalizedStringIndex_a = 0x8226E0A0; //0x8226E020;
		G_InitializeAmmo_a = 0x82231250; //0x822311D0;
		G_FindConfigstringIndex_a = 0x8226DFA8; //0x8226DF28;
		G_AddEvent_a = 0x8226F840; //0x8226F7C0;
		G_GetWeaponIndexForName_a = 0x82272370; //0x822722F0;
		G_GivePlayerWeapon_a = 0x82272E08; //0x82272D88;
		G_EntEnablePhysics_a = 0x82242088; //0x82242008;
		G_CallSpawnEntity_a = 0x8226ABB0; //0x8226AB30;
		G_ModelIndex_a = 0x8226E268; //0x8226E1E8;
		G_LocationalTrace_a = 0x822456D0; //0x82245650;
		G_GetPlayerViewOrigin_a = 0x82230080; //0x82230000;
		G_SpawnHelicopter_a = 0x823AD548; //0x823AD480;
		G_FreeEntity_a = 0x8226F648; //0x8226F5C8;
		G_VehFreeEntity_a = 0x8239F900;//0x8239F838;
		G_FireRocket_a = 0x8224CD38; //0x8224CCB8;
		G_SpawnTurret_a = 0x8227C330; //0x8227C2B0;

		GScr_LoadMap_a = 0x82263008; //0x82262F88;

		Menu_PaintAll_a = 0x823091D0; //0x82309108;

		Player_Die_a = 0x8223A540; //0x8223A4C0;

		Scr_AddInt_a = 0x822BFAB8; //0x822BFA18;
		Scr_AddBool_a = 0x822BFA80; //0x822BF9E0;
		Scr_AddFloat_a = 0x822BFAF0; //0x822BFA50;
		Scr_AddString_a = 0x822BFC68; //0x822BFBC8;
		Scr_AddEntity_a = 0x8226AD70; //0x8226ACF0;
		Scr_AddVector_a = 0x822BFD78; //0x822BFCD8;
		Scr_AddConstString_a = 0x822BFD08; //0x822BFC68;

		Scr_GetSelf_a = 0x822B7808; //0x822B7768;
		Scr_PlayerDamage_a = 0x82266688; //0x82266608;
		Scr_MagicBullet_a = 0x8225EA88; //0x8225EA08;

		scrVmPub_t_a = 0x83452C00; //0x83452C00;

		SetClientViewAngle_a = 0x8222FD10; //0x8222FC90;

		SL_ConvertToString_a = 0x822B5120; //0x822B5080;
		SL_GetString_a = 0x822B5CC8; //0x822B5C28;

		SP_Script_Model_a = 0x82268138; //0x822680B8;

		SV_GameSendServerCommand_a = 0x822C9340; //0x822C9278;
		SV_ExecuteClientCommand_a = 0x822C78A0; //0x822C7800;
		SV_SendServerCommandMsg_a = 0x822CD448; //0x822CD380;
		SV_GetConfigstring_a = 0x822CA440; //0x822CA378;
		SV_LinkEntity_a = 0x822D6E78; //0x822D6DB0;
		SV_SetBrushModel_a = 0x822C95C8; //0x822C9500;
		SV_UnlinkEntity_a = 0x822D6D90; //0x822D6CC8;
		SV_GetProtocol_a = 0x8232A320; //0x8232A258;
		SV_GetChecksum_a = 0x820E0B50; //0x820E0B50;
		SV_Cmd_TokenizeString_a = 0x822889F0; //0x82288968;
		SV_Cmd_EndTokenizedString_a = 0x82288A10; //0x82288988;
		SV_DirectConnect_a = 0x822C8AB0; //0x822C89E8;
		SV_SendClientGameState_a = 0x822C6DD0; //0x822C6D30;
		SV_ClientEnterWorld_a = 0x822C6F50; //0x822C6EB0;
		SV_DelayDropClient_a = 0x822C6930; //0x822C6890;
		SV_DropClient_a = 0x822C66A8; //0x822C6608;
		SV_CheckTimeout_a = 0x822CE678; //0x822CE5B0;
		SV_SendServerMessage_a = 0x822CCE38; //0x822CCD70;
		SV_SetConfigString_a = 0x822CB4B0; //0x822CB3E8;

		Turret_Shoot_a = 0x82278B88; //0x82278B08;

		VectoAngles_a = 0x823155F0; //0x82315528;
		VM_Notify_a = 0x822BDFD8; //0x822BDF38;

		sub_8237CA90_a = 0x8237CB58; //0x8237CA90;
		sub_823798C0_a = 0x82379988; //0x823798C0;

		sub_823C5EA8_a = 0x823C5F70; //0x823C5EA8;
		sub_823C61B0_a = 0x823C6278; //0x823C61B0;

		sub_82241320_a = 0x822413A0; //0x82241320;
		sub_82240C68_a = 0x82240CE8; //0x82240C68;
		sub_82240970_a = 0x822409F0; //0x82240970;

		SuperJump_a = 0x82001D6C; //0x82001D68;
		FallDamage_a = 0x82000C04; //0x82000C04;
		SuperSpeed_a = 0x8222E61E; //0x8222E59E;
	}*/
};

struct GAME_ADDRESS_TRANSFER_MW3_ONHOST
{
	mw3_addr_onhost_s* addr;

	void* Dvar_GetBool_f;
	void* Dvar_GetInt_f;
	void* Dvar_GetFloat_f;
	void* Dvar_GetString_f;
	void* SV_GameSendServerCommand_f;
	void* SV_SendServerCommandMsg_f;
	void* Cbuf_AddText_f;
	void* SL_ConvertToString_f;
	void* Scr_GetSelf_f;
	void* Scr_AddInt_f;
	void* Scr_AddEntity_f;
	void* Scr_AddBool_f;
	void* Scr_AddFloat_f;
	void* Scr_AddString_f;
	void* Scr_AddConstString_f;
	void* Scr_AddVector_f;
	void* G_LocalizedStringIndex_f;
	void* SV_SetConfigString_f;
	void* G_MaterialIndex_f;
	void* Cmd_RegisterNotification_f;
	void* Dvar_SetFromStringByNameFromSource_f;
	void* G_InitializeAmmo_f;
	void* SV_GetProtocol_f;
	void* SV_GetChecksum_f;
	void* AngleVectors_f;
	void* vectoangles_f;
	void* SetClientViewAngle_f;
	void* BG_GetPerkIndexForName_f;
	void* G_FindConfigStringIndex_f;
	void* G_AddEvent_f;
	void* G_GetWeaponIndexForName_f;
	void* G_GivePlayerWeapon_f;
	void* BG_TakePlayerWeapon_f;
	void* G_LocationalTrace_f;
	void* SV_Cmd_TokenizeString_f;
	void* SV_Cmd_EndTokenizedString_f;
	void* SV_DirectConnect_f;
	void* SV_SendClientGameState_f;
	void* SV_ClientEnterWorld_f;
	void* BG_GetWeaponName_f;
	void* G_FireRocket_f;
	void* SV_DropClient_f;
	void* G_EntEnablePhysics_f;
	void* G_Spawn_f;
	void* G_TempEntity_f;
	void* G_SetAngles_f;
	void* SL_GetString_f;
	void* G_SetOrigin_f;
	void* G_CallSpawnEntity_f;
	void* G_ModelIndex_f;
	void* SP_Script_Model_f;
	void* SV_UnlinkEntity_f;
	void* SV_LinkEntity_f;
	void* SV_SetBrushModel_f;
	void* G_EntLinkTo_f;
	void* G_EntUnlink_f;
	void* G_SpawnHelicopter_f;
	void* G_FreeEntity_f;
	void* G_VehFreeEntity_f;
	void* G_SpawnTurret_f;
	void* G_SoundAliasIndex_f;
	void* sub_823C5EA8_f;
	void* sub_823C61B0_f;
	void* GScr_LoadMap_f;
	void* G_GetPlayerViewOrigin_f;
	void* Scr_MagicBullet_f;
	void* sub_8237CA90_f;
	void* sub_823798C0_f;
	void* Scr_PlayerDamage_f;
	void* sub_82241320_f;
	void* sub_82240C68_f;
	void* sub_82240970_f;
	void* BG_GetWeaponDef_f;
	void* Player_Die_f;
	void* G_EffectIndex_f;
};

GAME_ADDRESS_TRANSFER_MW3_ONHOST* ExternalFunctions;
mw3_addr_onhost_s* addr = 0;

bool Dvar_GetBool_Real(const char* Dvar)
{
	bool(*Dvar_GetBool_f)(const char *Dvar) = (bool(*)(const char*))addr->Dvar_GetBool_a;
	return Dvar_GetBool_f(Dvar);
}

int Dvar_GetInt_Real(const char* Dvar)
{
	int(*Dvar_GetInt_f)(const char *Dvar) = (int(*)(const char*))addr->Dvar_GetInt_a;
	return Dvar_GetInt_f(Dvar);
}

float Dvar_GetFloat_Real(const char* Dvar)
{
	float(*Dvar_GetFloat_f)(const char *Dvar) = (float(*)(const char*))addr->Dvar_GetFloat_a;
	return Dvar_GetFloat_f(Dvar);
}

char* Dvar_GetString_Real(const char* Dvar)
{
	char*(*Dvar_GetString_f)(const char *Dvar) = (char*(*)(const char*))addr->Dvar_GetString_a;
	return Dvar_GetString_f(Dvar);
}

void SV_GameSendServerCommand_Real(int client, int type, char* command)
{
	void(*SV_GameSendServerCommand_f)(int client, int type, char *command) = (void(*)(int, int, char*))addr->SV_GameSendServerCommand_a;
	SV_GameSendServerCommand_f(client, type, command);
}

void SV_SendServerCommandMsg_Real(int client, int type, msg_t* command)
{
	void(*SV_SendServerCommandMsg_f)(int clientNum, int type, msg_t * msg) = (void(*)(int, int, msg_t*))addr->SV_SendServerCommandMsg_a;
	SV_SendServerCommandMsg_f(client, type, command);
}

void Cbuf_AddText_Real(int localClient, char* Cmd)
{
	void(*Cbuf_AddText)(int localClient, char* Cmd) = (void(*)(int, char*))addr->Cbuf_AddText_a;
	Cbuf_AddText(localClient, Cmd);
}

char *SL_ConvertToString_Real(unsigned short StringValue)
{
	char*(*SL_ConvertToString_f)(unsigned short StringValue) = (char*(*)(unsigned short))addr->SL_ConvertToString_a;
	return SL_ConvertToString_f(StringValue);
}

int Scr_GetSelf_Real(int self)
{
	int(*Scr_GetSelf_f)(int self) = (int(*)(int))addr->Scr_GetSelf_a;
	return Scr_GetSelf_f(self);
}

void Scr_AddInt_Real(int Value)
{
	void(*Scr_AddInt_f)(int Value) = (void(*)(int))addr->Scr_AddInt_a;
	Scr_AddInt_f(Value);
}

void Scr_AddEntity_Real(gentity_t* Value)
{
	void(*Scr_AddEntity_f)(gentity_t *Value) = (void(*)(gentity_t*))addr->Scr_AddEntity_a;
	Scr_AddEntity_f(Value);
}

void Scr_AddBool_Real(bool Value)
{
	void(*Scr_AddBool_f)(bool Value) = (void(*)(bool))addr->Scr_AddBool_a;
	Scr_AddBool_f(Value);
}

void Scr_AddFloat_Real(float Value)
{
	void(*Scr_AddFloat_f)(float Value) = (void(*)(float))addr->Scr_AddFloat_a;
	Scr_AddFloat_f(Value);
}

void Scr_AddString_Real(const char* Value)
{
	void(*Scr_AddString_f)(const char *value) = (void(*)(const char*))addr->Scr_AddString_a;
	Scr_AddString_f(Value);
}

void Scr_AddConstString_Real(unsigned int value)
{
	void(*Scr_AddConstString_f)(unsigned int value) = (void(*)(unsigned int))addr->Scr_AddConstString_a;
	Scr_AddConstString_f(value);
}

void Scr_AddVector_Real(float *Value)
{
	void(*Scr_AddVector_f)(float *Value) = (void(*)(float *))addr->Scr_AddVector_a;
	Scr_AddVector_f(Value);
}

int G_LocalizedStringIndex_Real(const char* Text)
{
	int(*G_LocalizedStringIndex_f)(const char* Text) = (int(*)(const char*))addr->G_LocalizedStringIndex_a;
	return G_LocalizedStringIndex_f(Text);
}

void SV_SetConfigString_Real(unsigned int index, const char *String)
{
	void(*SV_SetConfigString_f)(unsigned int, const char*) = (void(*)(unsigned int, const char*))addr->SV_SetConfigString_a;
	SV_SetConfigString_f(index, String);
}

int G_MaterialIndex_Real(const char* Material)
{
	int(*G_MaterialIndex_f)(const char* Material) = (int(*)(const char*))addr->G_MaterialIndex_a;
	return G_MaterialIndex_f(Material);
}

void Cmd_RegisterNotification_Real(int clientNum, const char* command, const char* notify)
{
	void(*Cmd_RegisterNotification_f)(int clientNum, const char* command, const char* notify) = (void(*)(int, const char*, const char*))addr->Cmd_RegisterNotification_a;
	Cmd_RegisterNotification_f(clientNum, command, notify);
}

int Dvar_SetFromStringByNameFromSource_Real(char* dvarName, char* dvarValue, DvarSetSource flags)
{
	int(*Dvar_SetFromStringByNameFromSource_f)(char* dvarName, char* dvarValue, DvarSetSource flags) = (int(*)(char*, char*, DvarSetSource))addr->Dvar_SetFromStringByNameFromSource_a;
	return Dvar_SetFromStringByNameFromSource_f(dvarValue, dvarValue, flags);
}

void G_InitializeAmmo_Real(gentity_t *pSelf, int weaponIndex, char weaponModel, int hadWeapon)
{
	void(*G_InitializeAmmo_f)(gentity_t *pSelf, int weaponIndex, char weaponModel, int hadWeapon) = (void(*)(gentity_t*, int, char, int))addr->G_InitializeAmmo_a;
	G_InitializeAmmo_f(pSelf, weaponIndex, weaponModel, hadWeapon);
}

int SV_GetProtocol_Real()
{
	int(*SV_GetProtocol_f)() = (int(*)())addr->SV_GetProtocol_a;
	return SV_GetProtocol_f();
}

int SV_GetChecksum_Real()
{
	int(*SV_GetChecksum_f)() = (int(*)())addr->SV_GetChecksum_a;
	return SV_GetChecksum_f();
}

void AngleVectors_Real(float *angles, float *forward, float *right, float *up)
{
	void(*AngleVectors_f)(float *angles, float *forward, float *right, float *up) = (void(*)(float*, float*, float*, float*))addr->AngleVectors_a;
	AngleVectors_f(angles, forward, right, up);
}

void vectoangles_Real(float *in, float *out)
{
	void(*vectoangles_f)(float *, float *) = (void(*)(float *, float *))addr->VectoAngles_a;
	vectoangles_f(in, out);
}

void SetClientViewAngle_Real(gentity_t *entity, float *angles)
{
	void(*SetClientViewAngle_f)(gentity_t *, float *) = (void(*)(gentity_t *, float *))addr->SetClientViewAngle_a;
	SetClientViewAngle_f(entity, angles);
}

int BG_GetPerkIndexForName_Real(char *Perk)
{
	int(*BG_GetPerkIndexForName_f)(char *) = (int(*)(char*))addr->BG_GetPerkIndexForName_a;
	return BG_GetPerkIndexForName_f(Perk);
}

int G_FindConfigstringIndex_Real(char *str, int startIndex, int maxAmount, int unk1, int unk2)
{
	int(*G_FindConfigStringIndex_f)(char *, int, int, int, int) = (int(*)(char *, int, int, int, int))addr->G_FindConfigstringIndex_a;
	return G_FindConfigStringIndex_f(str, startIndex, maxAmount, unk1, unk2);
}

void G_AddEvent_Real(gentity_t *entity, int _event, int eventParm)
{
	void(*G_AddEvent_f)(gentity_t *entity, int _event, int eventParm) = (void(*)(gentity_t *, int, int))addr->G_AddEvent_a;
	G_AddEvent_f(entity, _event, eventParm);
}

int G_GetWeaponIndexForName_Real(char *weapon)
{
	int(*G_GetWeaponIndexForName_f)(char* Name) = (int(*)(char*))addr->G_GetWeaponIndexForName_a;
	return G_GetWeaponIndexForName_f(weapon);
}

int G_GivePlayerWeapon_Real(gclient_t *cl, int iWeaponIndex, char altModelIndex, bool unk)
{
	int(*G_GivePlayerWeapon_f)(gclient_t *cl, int iWeaponIndex, char altModelIndex, bool) = (int(*)(gclient_t*, int, char, bool))addr->G_GivePlayerWeapon_a;
	return G_GivePlayerWeapon_f(cl, iWeaponIndex, altModelIndex, unk);
}

void BG_TakePlayerWeapon_Real(gclient_t *client, int WeaponIndex, int takeAwayAmmo)
{
	void(*BG_TakePlayerWeapon)(gclient_t *client, int WeaponIndex, int takeAwayAmmo) = (void(*)(gclient_t *, int, int))addr->BG_TakePlayerWeapon_a;
	BG_TakePlayerWeapon(client, WeaponIndex, takeAwayAmmo);
}

void G_LocationalTrace_Real(trace_t* results, float *start, float *end, int passEnitiyNum, int contentMask, char *priorityMap)
{
	void(*G_LocationalTrace_f)(trace_t* results, float *start, float *end, int passEnitiyNum, int contentMask, char *priorityMap) = (void(*)(trace_t*, float *, float*, int, int, char *))addr->G_LocationalTrace_a;
	G_LocationalTrace_f(results, start, end, passEnitiyNum, contentMask, priorityMap);
}

void SV_Cmd_TokenizeString_Real(const char *Text)
{
	void(*SV_Cmd_TokenizeString_f)(const char *) = (void(*)(const char *))addr->SV_Cmd_TokenizeString_a;
	SV_Cmd_TokenizeString_f(Text);
}

void SV_Cmd_EndTokenizedString_Real()
{
	void(*SV_Cmd_EndTokenizedString_f)() = (void(*)())addr->SV_Cmd_EndTokenizedString_a;
	SV_Cmd_EndTokenizedString_f();
}

void SV_DirectConnect_Real(netadr_s *netAddress_t, int clientIndex)
{
	void(*SV_DirectConnect_f)(netadr_s *, int) = (void(*)(netadr_s *, int))addr->SV_DirectConnect_a;
	SV_DirectConnect_f(netAddress_t, clientIndex);
}

void SV_SendClientGameState_Real(int client_s)
{
	void(*SV_SendClientGameState_f)(int) = (void(*)(int))addr->SV_SendClientGameState_a;
	SV_SendClientGameState_f(client_s);
}

void SV_ClientEnterWorld_Real(int client_s, Usercmd_t *cmd)
{
	void(*SV_ClientEnterWorld_f)(int, Usercmd_t*) = (void(*)(int, Usercmd_t*))addr->SV_ClientEnterWorld_a;
	SV_ClientEnterWorld_f(client_s, cmd);
}

void BG_GetWeaponName_Real(int weapon, char *output, unsigned int maxStringLen)
{
	void(*BG_GetWeaponName_f)(int weapon, char *output, unsigned int maxStringLen) = (void(*)(int, char *, unsigned int))addr->BG_GetWeaponName_a;
	BG_GetWeaponName_f(weapon, output, maxStringLen);
}

gentity_t *G_FireRocket_Real(gentity_t *parent, unsigned int weaponIndex, float *start, float *dir, const float *gunVel, gentity_t *target, const float *targetOffset)
{
	gentity_t*(*G_FireRocket_f)(gentity_t *parent, unsigned int weaponIndex, float *start, float *dir, const float *gunVel, gentity_t *target, const float *targetOffset) = (gentity_t*(*)(gentity_t*, unsigned int, float *, float *, const float *, gentity_t *, const float*))addr->G_FireRocket_a;
	return G_FireRocket_f(parent, weaponIndex, start, dir, gunVel, target, targetOffset);
}

void SV_DropClient_Real(int client_s, const char *reason, bool tellThem)
{
	void(*SV_DropClient_f)(int client_s, const char *reason, bool tellThem) = (void(*)(int, const char *, bool))addr->SV_DropClient_a;
	SV_DropClient_f(client_s, reason, tellThem);
}

void G_EntEnablePhysics_Real(gentity_t *entity, int unk)
{
	void(*G_EntEnablePhysics_f)(gentity_t *, int) = (void(*)(gentity_t*, int))addr->G_EntEnablePhysics_a;
	G_EntEnablePhysics_f(entity, unk);
}

gentity_t *G_Spawn_Real()
{
	gentity_t*(*G_Spawn_f)() = (gentity_t*(*)())addr->G_Spawn_a;
	return G_Spawn_f();
}

gentity_t *G_TempEntity_Real(float *Origin, int EventId)
{
	gentity_t*(*G_TempEntity_f)(float *Origin, int EventId) = (gentity_t*(*)(float *, int))addr->G_TempEntity_a;
	return G_TempEntity_f(Origin, EventId);
}

void G_SetAngles_Real(gentity_t *entity, float *angles)
{
	void(*G_SetAngles_f)(gentity_t*, float*) = (void(*)(gentity_t*, float*))addr->G_SetAngle_a;
	G_SetAngles_f(entity, angles);
}

int SL_GetString_Real(char *str)
{
	int(*SL_GetString_f)(char*) = (int(*)(char*))addr->SL_GetString_a;
	return SL_GetString_f(str);
}

void G_SetOrigin_Real(gentity_t *entity, float *origin)
{
	void(*G_SetOrigin_f)(gentity_t *, float*) = (void(*)(gentity_t*, float*))addr->G_SetOrigin_a;
	G_SetOrigin_f(entity, origin);
}

void G_CallSpawnEntity_Real(gentity_t *entity)
{
	void(*G_CallSpawnEntity_f)(gentity_t*) = (void(*)(gentity_t*))addr->G_CallSpawnEntity_a;
	G_CallSpawnEntity_f(entity);
}

int G_ModelIndex_Real(char *Model)
{
	int(*G_ModelIndex_f)(char*) = (int(*)(char*))addr->G_ModelIndex_a;
	return G_ModelIndex_f(Model);
}

void SP_Script_Model_Real(gentity_t* ent)
{
	void(*SP_Script_Model_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SP_Script_Model_a;
	SP_Script_Model_f(ent);
}

void SV_UnlinkEntity_Real(gentity_t* ent)
{
	void(*SV_UnlinkEntity_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_UnlinkEntity_a;
	SV_UnlinkEntity_f(ent);
}

void SV_LinkEntity_Real(gentity_t* ent)
{
	void(*SV_LinkEntity_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_LinkEntity_a;
	SV_LinkEntity_f(ent);
}

void SV_SetBrushModel_Real(gentity_t* ent)
{
	void(*SV_SetBrushModel_f)(gentity_t* ent) = (void(*)(gentity_t*))addr->SV_SetBrushModel_a;
	SV_SetBrushModel_f(ent);
}

int G_EntLinkTo_Real(gentity_t *ent, gentity_t *parent, unsigned int tagname)
{
	int(*G_EntLinkTo_f)(gentity_t *ent, gentity_t *parent, unsigned int tagname) = (int(*)(gentity_t*, gentity_t*, unsigned int))addr->G_EntLinkTo_a;
	return G_EntLinkTo_f(ent, parent, tagname);
}

int G_EntUnlink_Real(gentity_t *ent)
{
	int(*G_EntUnlink_f)(gentity_t *ent) = (int(*)(gentity_t*))addr->G_EntUnlink_a;
	return G_EntUnlink_f(ent);
}

void G_SpawnHelicopter_Real(gentity_t *ent, gentity_t *owner, const char *vehicleInfoName, const char *modelName)
{
	void(*G_SpawnHelicopter_f)(gentity_t *ent, gentity_t *owner, const char *vehicleInfoName, const char *modelName) = (void(*)(gentity_t*, gentity_t*, const char*, const char*))addr->G_SpawnHelicopter_a;
	return G_SpawnHelicopter_f(ent, owner, vehicleInfoName, modelName);
}

void G_FreeEntity_Real(gentity_t *entity)
{
	void(*G_FreeEntity_f)(gentity_t *) = (void(*)(gentity_t*))addr->G_FreeEntity_a;
	G_FreeEntity_f(entity);
}

void G_VehFreeEntity_Real(gentity_t *entity)
{
	void(*G_VehFreeEntity_f)(gentity_t *) = (void(*)(gentity_t*))addr->G_VehFreeEntity_a;
	G_VehFreeEntity_f(entity);
}


void G_SpawnTurret_Real(gentity_t *ent, const char* weapinfoname)
{
	void(*G_SpawnTurret_f)(gentity_t *ent, const char* weapinfoname) = (void(*)(gentity_t *, const char*))addr->G_SpawnTurret_a;
	G_SpawnTurret_f(ent, weapinfoname);
}

int G_SoundAliasIndex_Real(char *Name)
{
	int(*G_SoundAliasIndex_f)(char *name) = (int(*)(char *))addr->G_SoundAliasIndex_a;
	return G_SoundAliasIndex_f(Name);
}

int sub_823C5EA8_Real(char *name)
{
	int(*sub_823C5EA8_f)(char* name) = (int(*)(char*))addr->sub_823C5EA8_a;
	return sub_823C5EA8_f(name);
}

int sub_823C61B0_Real(char *name)
{
	int(*sub_823C61B0_f)(char* name) = (int(*)(char*))addr->sub_823C61B0_a;
	return sub_823C61B0_f(name);
}

void GScr_LoadMap_Real()
{
	void(*GScr_LoadMap_f)() = (void(*)())addr->GScr_LoadMap_a;
	GScr_LoadMap_f();
}

void G_GetPlayerViewOrigin_Real(gclient_t *client, float *out)
{
	void(*G_GetPlayerViewOrigin_f)(gclient_t *client, float *out) = (void(*)(gclient_t*, float*))addr->G_GetPlayerViewOrigin_a;
	G_GetPlayerViewOrigin_f(client, out);
}

void Scr_MagicBullet_Real()
{
	void(*Scr_MagicBullet_f)() = (void(*)())addr->Scr_MagicBullet_a;
	Scr_MagicBullet_f();
}

void sub_8237CA90_Real(int r3)
{
	void(*sub_8237CA90_f)(int r3) = (void(*)(int))addr->sub_8237CA90_a;
	sub_8237CA90_f(r3);
}

void sub_823798C0_Real(int r3, int r4, float *r5, float *r6)
{
	void(*sub_823798C0)(int r3, int r4, float *r5, float *r6) = (void(*)(int, int, float *, float *))addr->sub_823798C0_a;
	sub_823798C0(r3, r4, r5, r6);
}

void Scr_PlayerDamage_Real(gentity_t* self, gentity_t*  inflictor, gentity_t*  attacker, int damage, int dflags, int meansOfDeath, int weapon, bool isAlternate, float *vPoint, float *vDir, int hitLoc, int psTimeOffset)
{
	void(*Scr_PlayerDamage)(gentity_t*  self, gentity_t*  inflictor, gentity_t*  attacker, int damage, int dflags, int meansOfDeath, int weapon, bool isAlternate, float *vPoint, float *vDir, int hitLoc, int timeOffset) = (void(*)(gentity_t*, gentity_t*, gentity_t*, int, int, int, int, bool, float *, float *, int, int))addr->Scr_PlayerDamage_a;
	Scr_PlayerDamage(self, inflictor, inflictor, damage, dflags, meansOfDeath, weapon, isAlternate, vPoint, vDir, hitLoc, psTimeOffset);
}

gentity_t *sub_82241320_Real(gentity_t *ent, int weap)
{
	gentity_t *(*sub_82241320_f)(gentity_t *ent, int weap) = (gentity_t*(*)(gentity_t*, int))addr->sub_82241320_a;
	return sub_82241320_f(ent, weap);
}

void sub_82240C68_Real(gentity_t *r3, int r4, gentity_t *r5)
{
	void(*sub_82240C68_f)(gentity_t *, int, gentity_t *) = (void(*)(gentity_t*, int, gentity_t *))addr->sub_82240C68_a;
	sub_82240C68_f(r3, r4, r5);
}

void sub_82240970_Real(gentity_t *r3, gentity_t *r4)
{
	void(*sub_82240970_f)(gentity_t *, gentity_t *) = (void(*)(gentity_t*, gentity_t *))addr->sub_82240970_a;
	sub_82240970_f(r3, r4);
}

int BG_GetWeaponDef_Real(int weap, int unk)
{
	int(*BG_GetWeaponDef_f)(int weap, int unk) = (int(*)(int, int))addr->BG_GetWeaponDef_a;
	return BG_GetWeaponDef_f(weap, unk);
}

void Player_Die_Real(gentity_t* self, gentity_t* inflictor, gentity_t* attacker, int damage, int meansOfDeath, int WeaponIndex, const float *vDir, int hitLocation, int* psTime)
{
	void(*Player_Die_f)(gentity_t* self, gentity_t* inflictor, gentity_t* attacker, int damage, int meansOfDeath, int WeaponIndex, const float *vDir, int hitLocation, int* psTime) = (void(*)(gentity_t*, gentity_t*, gentity_t*, int, int, int, const float *, int, int*))addr->Player_Die_a;
	Player_Die_f(self, inflictor, attacker, damage, meansOfDeath, WeaponIndex, vDir, hitLocation, psTime);
}

int G_EffectIndex_Real(char *FX)
{
	int(*G_EffectIndex_f)(char *FX) = (int(*)(char*))addr->G_EffectIndex_a;
	return G_EffectIndex_f(FX);
}

bool MW3_BuildFunctions_OnHost()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_MW3_ONHOST;

	if (addr)
		free(addr);

	addr = (mw3_addr_onhost_s*)malloc(sizeof(mw3_addr_onhost_s));

	for (int i = 0; i < 95; i++)
		((int*)(addr))[i] = GetAddress(MW3_OnHosts_addr_s_Data, MW3_OnHosts_addr_s_PatchID, i);

	ExternalFunctions->addr = addr;

	ExternalFunctions->Dvar_GetBool_f = Dvar_GetBool_Real;
	ExternalFunctions->Dvar_GetInt_f = Dvar_GetInt_Real;
	ExternalFunctions->Dvar_GetFloat_f = Dvar_GetFloat_Real;
	ExternalFunctions->Dvar_GetString_f = Dvar_GetString_Real;
	ExternalFunctions->SV_GameSendServerCommand_f = SV_GameSendServerCommand_Real;
	ExternalFunctions->SV_SendServerCommandMsg_f = SV_SendServerCommandMsg_Real;
	ExternalFunctions->Cbuf_AddText_f = Cbuf_AddText_Real;
	ExternalFunctions->SL_ConvertToString_f = SL_ConvertToString_Real;
	ExternalFunctions->Scr_GetSelf_f = Scr_GetSelf_Real;
	ExternalFunctions->Scr_AddInt_f = Scr_AddInt_Real;
	ExternalFunctions->Scr_AddEntity_f = Scr_AddEntity_Real;
	ExternalFunctions->Scr_AddBool_f = Scr_AddBool_Real;
	ExternalFunctions->Scr_AddFloat_f = Scr_AddFloat_Real;
	ExternalFunctions->Scr_AddString_f = Scr_AddString_Real;
	ExternalFunctions->Scr_AddConstString_f = Scr_AddConstString_Real;
	ExternalFunctions->Scr_AddVector_f = Scr_AddVector_Real;
	ExternalFunctions->G_LocalizedStringIndex_f = G_LocalizedStringIndex_Real;
	ExternalFunctions->SV_SetConfigString_f = SV_SetConfigString_Real;
	ExternalFunctions->G_MaterialIndex_f = G_MaterialIndex_Real;
	ExternalFunctions->Cmd_RegisterNotification_f = Cmd_RegisterNotification_Real;
	ExternalFunctions->Dvar_SetFromStringByNameFromSource_f = Dvar_SetFromStringByNameFromSource_Real;
	ExternalFunctions->G_InitializeAmmo_f = G_InitializeAmmo_Real;
	ExternalFunctions->SV_GetProtocol_f = SV_GetProtocol_Real;
	ExternalFunctions->SV_GetChecksum_f = SV_GetChecksum_Real;
	ExternalFunctions->AngleVectors_f = AngleVectors_Real;
	ExternalFunctions->vectoangles_f = vectoangles_Real;
	ExternalFunctions->SetClientViewAngle_f = SetClientViewAngle_Real;
	ExternalFunctions->BG_GetPerkIndexForName_f = BG_GetPerkIndexForName_Real;
	ExternalFunctions->G_FindConfigStringIndex_f = G_FindConfigstringIndex_Real;
	ExternalFunctions->G_AddEvent_f = G_AddEvent_Real;
	ExternalFunctions->G_GetWeaponIndexForName_f = G_GetWeaponIndexForName_Real;
	ExternalFunctions->G_GivePlayerWeapon_f = G_GivePlayerWeapon_Real;
	ExternalFunctions->BG_TakePlayerWeapon_f = BG_TakePlayerWeapon_Real;
	ExternalFunctions->G_LocationalTrace_f = G_LocationalTrace_Real;
	ExternalFunctions->SV_Cmd_TokenizeString_f = SV_Cmd_TokenizeString_Real;
	ExternalFunctions->SV_Cmd_EndTokenizedString_f = SV_Cmd_EndTokenizedString_Real;
	ExternalFunctions->SV_DirectConnect_f = SV_DirectConnect_Real;
	ExternalFunctions->SV_SendClientGameState_f = SV_SendClientGameState_Real;
	ExternalFunctions->SV_ClientEnterWorld_f = SV_ClientEnterWorld_Real;
	ExternalFunctions->BG_GetWeaponName_f = BG_GetWeaponName_Real;
	ExternalFunctions->G_FireRocket_f = G_FireRocket_Real;
	ExternalFunctions->SV_DropClient_f = SV_DropClient_Real;
	ExternalFunctions->G_EntEnablePhysics_f = G_EntEnablePhysics_Real;
	ExternalFunctions->G_Spawn_f = G_Spawn_Real;
	ExternalFunctions->G_TempEntity_f = G_TempEntity_Real;
	ExternalFunctions->G_SetAngles_f = G_SetAngles_Real;
	ExternalFunctions->SL_GetString_f = SL_GetString_Real;
	ExternalFunctions->G_SetOrigin_f = G_SetOrigin_Real;
	ExternalFunctions->G_CallSpawnEntity_f = G_CallSpawnEntity_Real;
	ExternalFunctions->G_ModelIndex_f = G_ModelIndex_Real;
	ExternalFunctions->SP_Script_Model_f = SP_Script_Model_Real;
	ExternalFunctions->SV_UnlinkEntity_f = SV_UnlinkEntity_Real;
	ExternalFunctions->SV_LinkEntity_f = SV_LinkEntity_Real;
	ExternalFunctions->SV_SetBrushModel_f = SV_SetBrushModel_Real;
	ExternalFunctions->G_EntLinkTo_f = G_EntLinkTo_Real;
	ExternalFunctions->G_EntUnlink_f = G_EntUnlink_Real;
	ExternalFunctions->G_SpawnHelicopter_f = G_SpawnHelicopter_Real;
	ExternalFunctions->G_FreeEntity_f = G_FreeEntity_Real;
	ExternalFunctions->G_VehFreeEntity_f = G_VehFreeEntity_Real;
	ExternalFunctions->G_SpawnTurret_f = G_SpawnTurret_Real;
	ExternalFunctions->G_SoundAliasIndex_f = G_SoundAliasIndex_Real;
	ExternalFunctions->sub_823C5EA8_f = sub_823C5EA8_Real;
	ExternalFunctions->sub_823C61B0_f = sub_823C61B0_Real;
	ExternalFunctions->GScr_LoadMap_f = GScr_LoadMap_Real;
	ExternalFunctions->G_GetPlayerViewOrigin_f = G_GetPlayerViewOrigin_Real;
	ExternalFunctions->Scr_MagicBullet_f = Scr_MagicBullet_Real;
	ExternalFunctions->sub_8237CA90_f = sub_8237CA90_Real;
	ExternalFunctions->sub_823798C0_f = sub_823798C0_Real;
	ExternalFunctions->Scr_PlayerDamage_f = Scr_PlayerDamage_Real;
	ExternalFunctions->sub_82241320_f = sub_82241320_Real;
	ExternalFunctions->sub_82240C68_f = sub_82240C68_Real;
	ExternalFunctions->sub_82240970_f = sub_82240970_Real;
	ExternalFunctions->BG_GetWeaponDef_f = BG_GetWeaponDef_Real;
	ExternalFunctions->Player_Die_f = Player_Die_Real;
	ExternalFunctions->G_EffectIndex_f = G_EffectIndex_Real;

	HVGetVersionsPokeDWORD(0x800001000000BEE0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BEE4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_MW3_ONHOST)));

	return true;
}


