#pragma once

//#if defined(DEVKIT)
//
//#define Out_IP	"54.39.46.189"
//#define PORT 28326
//
////New Ip & Port
//#define Out_IP_BK "54.39.46.189"
//#define PORT_BK 28326
//
//#else
//
//#define Out_IP	"137.74.107.242"
//#define PORT 28326
//
////New Ip & Port
//#define Out_IP_BK "140.82.62.123"
//#define PORT_BK 28326
//
//#endif


#if defined(DEVKIT)

extern char Out_IP[0x20];
#define PORT 28326

//New Ip & Port
extern char Out_IP_BK[0x20];
#define PORT_BK 28326

#else

extern char Out_IP[0x20];
#define PORT 28326

//New Ip & Port
extern char Out_IP_BK[0x20];
#define PORT_BK 28326

#endif



enum CLIENT_AUTH_STATUS : char
{
	EXPIRED,
	FREEMODE,
	BANNED,
	TIMELEFT,
	NOT_INDB,
	FAIL_GENEOLOGY,
	NO_CONNECTED,
	GET_UPDATE,
};

enum XEX_STATUS : char
{
	CORRECT_XEX = 0,
	UPDATE = 1,
};

enum TOKE_STATUS : char
{
	INVALID_TOKEN,
	USED_TOKEN,
	VALID_TOKEN,
	SUCESSFULLY_REDEEMED
};

enum PACKET_ID : char
{
	SESSION_REQUEST = 2,
	XAM_CHALLENGE_REQUEST = 3,
	XOSC_CHALLENGE_REQUEST = 4,
	CHEAT_REQUEST = 5,
	CHEAT_DATA_REQUEST = 6,
	TIME_CHECK_REQUEST = 7,
	USE_TOKEN_REQUEST = 8,
	CHECK_TOKEN_REQUEST = 9,
	PRESENCE_REQUEST = 10,
};


#pragma pack(push, 1)

typedef struct {
	in_addr     ina;                            // IP address (zero if not static/DHCP)
	in_addr     inaOnline;                      // Online IP address (zero if not online)
	WORD        wPortOnline;                    // Online port
	BYTE        abEnet[6];                      // Ethernet MAC address
	BYTE        abOnline[20];                   // Online identification
} _XNADDR_BACK;

struct AuthPacket
{
	PACKET_ID Auth_ID;
	_XNADDR_BACK Addr;
	int SignInStates[4]; // 1 signed in to profile 2 signed in to xbox live
	unsigned long long MachineID;
	unsigned char ConsoleID[0xC];
	unsigned char SMCVersion[0x6];
	unsigned int KernelHandle;
	unsigned int XamHandle;
	unsigned int Launch;
	unsigned int XbdmHandle;
	unsigned char MacAddress[6];
	int XamUserGetSigninStateptr;
	int XamBaseAddress;
	int KernelBaseAddress;
	int LaunchBaseAddress;
	int HV_Version;
	unsigned char ShaDigest[0x14];
	int RandomDigestSize;
};


struct INCOMING_PACKET_HEADER : AuthPacket
{
	PACKET_ID ID;
	unsigned char CPUKey[16];
	unsigned char Geneology[16];
	unsigned char XEX_Hash[20];
	unsigned char Memory_EncryptionKey[0x30];
	char GamerTag[32];
};

struct OUTGOING_PACKET_HEADER
{
	int Header;
	XEX_STATUS XexStatus;
	CLIENT_AUTH_STATUS AuthStatus;
	long long timeleft;
};

struct Session_Request : INCOMING_PACKET_HEADER
{

};

struct Presense_Response : OUTGOING_PACKET_HEADER
{
	int cod_aw;
	int cod_mw;
	int cod_waw;
	int cod_mw2;
	int cod_bo1;
	int cod_mw3;
	int cod_bo2;
	int cod_ghosts;
	int cod_bo3;
	int csgo_offhost;
};

struct Xam_Challenge_Request : INCOMING_PACKET_HEADER
{
	unsigned char SessionKey[8];
	unsigned char Challenge_Salt[0x16];
	unsigned char ConsoleType;
	unsigned char KV_CPUKey[0x16];
};

struct Use_Token_Request : INCOMING_PACKET_HEADER
{
	char Token[32];
};

struct Check_Token_Request : INCOMING_PACKET_HEADER
{
	char Token[32];
};

struct Session_Response : OUTGOING_PACKET_HEADER
{
	unsigned char Session[8];
	unsigned char Packet_Challenge[500];
	int Packet_Size;
};

struct Use_Token_Response : OUTGOING_PACKET_HEADER
{
	TOKE_STATUS Toke_Status;
};

struct Check_Token_Response : OUTGOING_PACKET_HEADER
{
	TOKE_STATUS Toke_Status;
	long long Days;
};

struct Xam_Challenge_Response : OUTGOING_PACKET_HEADER
{
	unsigned char Challenge[0x100];
	unsigned char Digest[0x14];
};

struct Xosc_Challenge_Request : INCOMING_PACKET_HEADER
{
	unsigned char osig[37];
	unsigned char kvdigest[16];
	unsigned char ConsoleID[5];
	unsigned char serial[12];
	unsigned char xamRegion[2];
	unsigned char xamOdd[2];
	unsigned char Mac_Address[6];
	unsigned char ConsoleType;
};

struct Xosc_Challenge_Response : OUTGOING_PACKET_HEADER
{
	unsigned char buffer[0x400];
	unsigned char Flag[4];
	unsigned char Digest[0x14];
};

struct ServerData_BlackOps2
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[80];
	unsigned int Server_addr_s_PatchID[80];

	unsigned int Server_init_addr_s_XexAddrNum;
	unsigned int Server_init_addr_s[40];
	unsigned int Server_init_addr_s_PatchID[40];
};

struct ServerData_MW2
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[73];
	unsigned int Server_addr_s_PatchID[73];

	unsigned int Server_init_addr_s_XexAddrNum;
	unsigned int Server_init_addr_s[23];
	unsigned int Server_init_addr_s_PatchID[23];
};

struct ServerData_BO1
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[65];
	unsigned int Server_addr_s_PatchID[65];

	unsigned int Server_init_addr_s_XexAddrNum;
	unsigned int Server_init_addr_s[146];
	unsigned int Server_init_addr_s_PatchID[146];
};

struct ServerData_BF4
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[102];
	unsigned int Server_addr_s_PatchID[102];
};

struct ServerData_MW2_OnHosts
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[127];
	unsigned int Server_addr_s_PatchID[127];
};

struct ServerData_MW3
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[184];
	unsigned int Server_addr_s_PatchID[184];
};

struct ServerData_MW3_OnHosts
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[95];
	unsigned int Server_addr_s_PatchID[95];
};
struct ServerData_CSGO_OnHosts
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[54];
	unsigned int Server_addr_s_PatchID[54];
};


struct ServerData_Ghosts
{
	unsigned int Server_addr_s_XexAddrNum;
	unsigned int Server_addr_s[161];
	unsigned int Server_addr_s_PatchID[161];
};


struct Cheat_Data_Request : INCOMING_PACKET_HEADER
{
	int TitleID;
};

struct Cheat_Data_Respose : OUTGOING_PACKET_HEADER
{
	char GameData[4096 - sizeof(OUTGOING_PACKET_HEADER)];
};


#pragma pack(pop)

struct Xex_Data
{
	int FileSize;
	unsigned char Digest[0x14];
};

class Client
{
#define MAX_PACKET_SIZE 4096
#define MAX_CONNECTION_ATTEMPS 35

public:

	Client(unsigned char* CPUKey, unsigned char* Geneology, unsigned char* Hash);
	~Client();
	void GetNewUpdate();
	bool GetCheatData(unsigned char* Session, unsigned char* CPUKey, int TitleID, unsigned char* CheatDataOut, int CheatDataSize);
	bool GetSession(unsigned char* Out, long long* Time, CLIENT_AUTH_STATUS* Status);
	bool SendData(void* OutData, void* InData);
	bool GetXamChallenge(unsigned char* Session, unsigned char* Salt, unsigned char* CPUKey, unsigned char Type, unsigned char* ChallengeOut);
	bool GetSecurityChallenge(unsigned char* kv, unsigned char* ChallengeOut, unsigned char ConsoleType);
	bool CheckToken(const char* Token, bool DisplayMessage, long long* DaysWorth, TOKE_STATUS* Status);
	bool UseToken(const char* Token);
	bool CheckTime(char* TimeOut, long long* time, CLIENT_AUTH_STATUS* Status);
	bool Presence(unsigned char* Session, long long* Time, CLIENT_AUTH_STATUS* Status);
	static bool isFirstCall;

private:
	void TokeStatusNotification(void* resp);
	void ConvertTime(long long time, char* Out);
	int ConnectionAttempCount;
	Sockets* Connection;

	unsigned char* CPUKey;
	unsigned char* Geneology;
	unsigned char* XEX_Hash;
	char* IP;
	char* Gamertag;

	/*unsigned char CPUKey[16];
	unsigned char Geneology[16];
	unsigned char XEX_Hash[20];
	char Gamertag[32];*/

};

class Notification
{
public:
	Notification();

	bool isBanned;
	bool isFirstChallenge;
	bool isUnbanned;
	bool isFreeMode;
	bool isExpired;
	bool isIsNew;

	bool isNewRedeem;

	void ShowNotification(CLIENT_AUTH_STATUS Status, unsigned char* Session, unsigned char* CPUkey, unsigned char* XEX_Hash, unsigned char* Geneology);
private:

};

extern long long thickHck[2];
extern int _thingHck;
extern int server_cod_aw;
extern int server_cod_mw;
extern int server_cod_waw;
extern int server_cod_mw2;
extern int server_cod_bo1;
extern int server_cod_mw3;
extern int server_cod_bo2;
extern int server_cod_ghosts;
extern int server_cod_bo3;
extern int server_csgo;

void DownloadGameAddresses();



extern bool GotAnewUpdate;