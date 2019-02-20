#include "main.h"

unsigned char GlobalRunbuffer[0x1000] = { 0 };

char ServerOneIp[255] = { 0 };
char ServerTwoIp[255] = { 0 };

bool firstDvdChall = false;

#if defined(DEVKIT)
char Out_IP[0x20];

//New Ip & Port
char Out_IP_BK[0x20];

#else
char Out_IP[0x20];

//New Ip & Port
char Out_IP_BK[0x20];

#endif

bool GotAnewUpdate = false;

long long thickHck[2] = { 0 };

int _thingHck = 0;
int server_cod_aw = 0;
int server_cod_mw = 0;
int server_cod_waw = 0;
int server_cod_mw2 = 0;
int server_cod_bo1 = 0;
int server_cod_mw3 = 0;
int server_cod_bo2 = 0;
int server_cod_ghosts = 0;
int server_cod_bo3 = 0;
int server_csgo = 0;

Notification CNotify;

bool updateFinished = false;

PXEX_EXECUTION_ID xosc_Execution = (PXEX_EXECUTION_ID)malloc(0x18);

/*
mflr %r11
std %r11, -8(%r1)
std %r31, -0x10(%r1)
std %r30, -0x18(%r1)
std %r29, -0x20(%r1)
std %r28, -0x28(%r1)
std %r27, -0x30(%r1)
std %r26, -0x38(%r1)
std %r25, -0x40(%r1)
stdu %r1, -0xF0(%r1)

mr %r3, %r4
mr %r4, %r5
mr %r5, %r6
mr %r6, %r7
mr %r7, %r8

li %r6, 0
mr %r8, %r4
cmpwi cr6, %r4, 0
blelr cr6
mtctr %r4

loc_loop:
lbzx %r5, %r6, %r3
xor %r5, %r5, %r8
xori %r5, %r5, 0xE4
xori %r5, %r5, 0x61
xori %r5, %r5, 0x91
xori %r5, %r5, 0xD6
xori %r5, %r5, 0x1
xori %r5, %r5, 0xCF
xori %r5, %r5, 0xFF
stbx %r5, %r6, %r3
addi %r6, %r6, 1
bdnz loc_loop

addi %r1, %r1, 0xF0
ld %r11, -8(%r1)
mtlr %r11
ld %r25, -0x40(%r1)
ld %r26, -0x38(%r1)
ld %r27, -0x30(%r1)
ld %r28, -0x28(%r1)
ld %r29, -0x20(%r1)
ld %r30, -0x18(%r1)
ld %r31, -0x10(%r1)
li %r3, 0
blr
*/

unsigned char FirstPacketLoad[176] = {
	0x7D, 0x68, 0x02, 0xA6, 0xF9, 0x61, 0xFF, 0xF8, 0xFB, 0xE1, 0xFF, 0xF0,
	0xFB, 0xC1, 0xFF, 0xE8, 0xFB, 0xA1, 0xFF, 0xE0, 0xFB, 0x81, 0xFF, 0xD8,
	0xFB, 0x61, 0xFF, 0xD0, 0xFB, 0x41, 0xFF, 0xC8, 0xFB, 0x21, 0xFF, 0xC0,
	0xF8, 0x21, 0xFF, 0x11, 0x7C, 0x83, 0x23, 0x78, 0x7C, 0xA4, 0x2B, 0x78,
	0x7C, 0xC5, 0x33, 0x78, 0x7C, 0xE6, 0x3B, 0x78, 0x7D, 0x07, 0x43, 0x78,
	0x38, 0xC0, 0x00, 0x00, 0x7C, 0x88, 0x23, 0x78, 0x2F, 0x04, 0x00, 0x00,
	0x4C, 0x99, 0x00, 0x20, 0x7C, 0x89, 0x03, 0xA6, 0x7C, 0xA6, 0x18, 0xAE,
	0x7C, 0xA5, 0x42, 0x78, 0x68, 0xA5, 0x00, 0xE4, 0x68, 0xA5, 0x00, 0x61,
	0x68, 0xA5, 0x00, 0x91, 0x68, 0xA5, 0x00, 0xD6, 0x68, 0xA5, 0x00, 0x01,
	0x68, 0xA5, 0x00, 0xCF, 0x68, 0xA5, 0x00, 0xFF, 0x7C, 0xA6, 0x19, 0xAE,
	0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xD4, 0x38, 0x21, 0x00, 0xF0,
	0xE9, 0x61, 0xFF, 0xF8, 0x7D, 0x68, 0x03, 0xA6, 0xEB, 0x21, 0xFF, 0xC0,
	0xEB, 0x41, 0xFF, 0xC8, 0xEB, 0x61, 0xFF, 0xD0, 0xEB, 0x81, 0xFF, 0xD8,
	0xEB, 0xA1, 0xFF, 0xE0, 0xEB, 0xC1, 0xFF, 0xE8, 0xEB, 0xE1, 0xFF, 0xF0,
	0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20
};

/*
mflr %r11
std %r11, -8(%r1)
std %r31, -0x10(%r1)
std %r30, -0x18(%r1)
std %r29, -0x20(%r1)
std %r28, -0x28(%r1)
std %r27, -0x30(%r1)
std %r26, -0x38(%r1)
std %r25, -0x40(%r1)
stdu %r1, -0xF0(%r1)

mr %r3, %r4
mr %r4, %r5
mr %r5, %r6
mr %r6, %r7
mr %r7, %r8

li %r6, 0
mr %r8, %r4
cmpwi cr6, %r4, 0
blelr cr6
mtctr %r4

loc_loop:
lbzx %r5, %r6, %r3
xori %r5, %r5, 0x30
xori %r5, %r5, 0x24
xori %r5, %r5, 0x44
xori %r5, %r5, 0x34
xori %r5, %r5, 0x25
xori %r5, %r5, 0xCE
xori %r5, %r5, 0xF1
stbx %r5, %r6, %r3
addi %r6, %r6, 1
bdnz loc_loop

addi %r1, %r1, 0xF0
ld %r11, -8(%r1)
mtlr %r11
ld %r25, -0x40(%r1)
ld %r26, -0x38(%r1)
ld %r27, -0x30(%r1)
ld %r28, -0x28(%r1)
ld %r29, -0x20(%r1)
ld %r30, -0x18(%r1)
ld %r31, -0x10(%r1)
li %r3, 0
blr
*/

int SecondPacketSize = 0;

unsigned char SecondPacketLoad[500] = { 0 };

Notification::Notification()
{
	isBanned = false;
	isFirstChallenge = false;
	isUnbanned = false;
	isFreeMode = false;
	isExpired = false;
	isIsNew = false;
	isNewRedeem = true;
}

void Notification::ShowNotification(CLIENT_AUTH_STATUS Status, unsigned char* Session, unsigned char* CPUkey, unsigned char* XEX_Hash, unsigned char* Geneology)
{
	switch (Status)
	{
	case BANNED:
		if (!isBanned) {

			XNotify(L"Please contact xbOnline support\nLooks like you are banned from xbOnline.");

			isNewRedeem = true;
			isBanned = true;
		}
		break;
	case EXPIRED:
		if (!isExpired) {

			//ShowMessageBoxUI(L"Time Expired!", L"Your time has expired on xbOnline. You can continue using the service by purchasing time from:\n\n\nhttps://xbonline.live\nOR\nhttps://livestore.sale\n\n\nWe hope you enjoyed your time with us!");
			XNotify(L"Your time has expired.\nPlease purchase some more from http://xbonline.live");

			isExpired = true;
			isFirstChallenge = false;
			isNewRedeem = true;
		}
		break;
	case NOT_INDB:
		if (!isIsNew) {

			XNotify(L"Welcome New User\nPlease purchase some time from http://xbonline.live");

			isExpired = false;
			isBanned = false;
			isIsNew = true;
			isFreeMode = false;
			isFirstChallenge = false;
			isNewRedeem = true;
		}
		break;
	case FREEMODE:

		if (!(*(long long*)(Session)))
		{
			if (isNewRedeem)
			{
				Client Connection(CPUkey, Geneology, XEX_Hash);

				if (Connection.GetSession(Session, &g_TimeleftInSeconds, &g_GlobalStatus) && !GotAnewUpdate) {
					g_Endtime = time(NULL) + g_TimeleftInSeconds;
				}
				isNewRedeem = false;
			}
		}

		if (isBanned) {
			XNotify(L"Looks like you have been unbanned.\nWelcome to xbOnline!");
			isBanned = false;
			isFreeMode = true;
		}
		if (!isFreeMode) {
			//ShowUpdateBlock(L"xbOnline Update r27", L"\n[+] Preparations for MW3 OnHost release\n.[-] Networking changes");
			XNotify(L"[Free Mode] Welcome To xbOnline - Enjoy the Free Time!");
			isFreeMode = true;
			isExpired = false;
			isFirstChallenge = false;
		}
		break;
	case TIMELEFT:
		if (!(*(long long*)(Session)))
		{
			if (isNewRedeem)
			{
				Client Connection(CPUkey, Geneology, XEX_Hash);

				if (Connection.GetSession(Session, &g_TimeleftInSeconds, &g_GlobalStatus) && !GotAnewUpdate) {
					g_Endtime = time(NULL) + g_TimeleftInSeconds;
				}
				isNewRedeem = false;
			}
		}
		if (isBanned) {
			XNotify(L"Looks like you have been unbanned.\nWelcome to xbOnline!");
			isBanned = false;
			isFirstChallenge = true;
		}

		if (!isFirstChallenge) {
			isFreeMode = false;
			//ShowUpdateBlock(L"xbOnline Update r27", L"\n[+] Preparations for MW3 On Host release.\n[-] Networking changes.");
			XNotify(L"Welcome To xbOnline!\nConnected to Service");
			isFirstChallenge = true;
			isExpired = false;
		}
		break;
	}

}

bool Client::isFirstCall = false;

void PacketAuthentication(INCOMING_PACKET_HEADER* Pk)
{
	unsigned short temp = 0;

	unsigned char SMCMessageID[1] = { 0x12 };

	for (int i = 0; i < 4; i++)
		Pk->SignInStates[i] = XamUserGetSigninState(i);

	NetDll_XNetGetTitleXnAddr(XNCALLER_SYSAPP, (XNADDR*)&Pk->Addr);
	NetDll_XNetXnAddrToMachineId(XNCALLER_SYSAPP, (XNADDR*)&Pk->Addr, &Pk->MachineID);
	XeKeysGetConsoleID(0, Pk->ConsoleID);

	Pk->XamHandle = (unsigned int)GetModuleHandleA("xam.xex");
	Pk->KernelHandle = (unsigned int)GetModuleHandleA("xboxkrnl.exe");

#if defined(DEVKIT)
#else
	Pk->Launch = (unsigned int)GetModuleHandleA("launch.xex");
	Pk->LaunchBaseAddress = (int)((PLDR_DATA_TABLE_ENTRY)(Pk->Launch))->ImageBase;
#endif

	Pk->XbdmHandle = (unsigned int)GetModuleHandleA("xbdm.xex");

	Pk->XamUserGetSigninStateptr = (int)XamUserGetSigninState;

	Pk->XamBaseAddress = (int)((PLDR_DATA_TABLE_ENTRY)(Pk->XamHandle))->ImageBase;
	Pk->KernelBaseAddress = (int)((PLDR_DATA_TABLE_ENTRY)(Pk->KernelHandle))->ImageBase;

	Pk->HV_Version = HVGetVersionsPeekDWORD(0);

	ExGetXConfigSetting(2, 1, (void*)Pk->MacAddress, 6, &temp);

	HalSendSMCMessage(SMCMessageID, Pk->SMCVersion);

	srand(time(NULL));

	int RandomeSize = rand() % 70 + 10;

	sha1(Pk, RandomeSize, Pk->ShaDigest);

	Pk->RandomDigestSize = RandomeSize;
}

struct hostent *gethostbyname(const char *name)
{
	WSAEVENT event;
	static struct hostent he;
	static struct in_addr addr;
	static char *addr_ptr = NULL;
	XNDNS *dns = NULL;

	he.h_addr_list = &addr_ptr;
	addr_ptr = (char*)&addr;

	if (!name)
		return NULL;

	event = NetDll_WSACreateEvent();
	NetDll_XNetDnsLookup(XNCALLER_SYSAPP, name, event, &dns);
	if (!dns)
		goto error;

	WaitForSingleObject((HANDLE)event, INFINITE);
	if (dns->iStatus)
		goto error;

	memcpy(&addr, dns->aina, sizeof(addr));

	NetDll_WSACloseEvent(event);
	NetDll_XNetDnsRelease(XNCALLER_SYSAPP, dns);

	return &he;

error:
	if (event)
		WSACloseEvent(event);
	return NULL;
}


int PopulateAddresses(Sockets* Connection)
{
	static bool isDoneOnce = false;
	if (!isDoneOnce)
	{
		int DNSResolveCount = 0;

		XNetStartupParams xnsp;
		WSADATA WsaData;

		ZeroMemory(&xnsp, sizeof(xnsp));

		xnsp.cfgSizeOfStruct = sizeof(XNetStartupParams);
		xnsp.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;

		if ((NetDll_XNetStartup(XNCALLER_SYSAPP, &xnsp)) != S_OK)
			return 0;

		if ((NetDll_WSAStartupEx(XNCALLER_SYSAPP, MAKEWORD(2, 2), &WsaData, 2)) != S_OK)
			return 0;

		bool DNSResolved[4] = { 0 };

		while (true)
		{


#if defined(DEVKIT)
			struct hostent *hp = gethostbyname("server1.xbonline.live");
#else
			struct hostent *hp = gethostbyname("server1.xbonline.live");
#endif
			if (hp && hp->h_addr_list && hp->h_addr_list[0])
			{
				unsigned char* ip = (unsigned char*)hp->h_addr_list[0];

				_snprintf(Out_IP, 0x20, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
				DNSResolved[0] = true;
			}

#if defined(DEVKIT)
			hp = gethostbyname("server1.xbonline.live");
#else
			hp = gethostbyname("server2.xbonline.live");
#endif
			if (hp && hp->h_addr_list && hp->h_addr_list[0])
			{
				unsigned char* ip = (unsigned char*)hp->h_addr_list[0];

				_snprintf(Out_IP_BK, 0x20, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
				DNSResolved[1] = true;
			}

			hp = gethostbyname("downloadone.xbonline.live");

			if (hp && hp->h_addr_list && hp->h_addr_list[0])
			{
				unsigned char* ip = (unsigned char*)hp->h_addr_list[0];

				_snprintf(ServerOneIp, 0x20, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);

				//DbgPrint("ServerOneIp: %s\n", ServerOneIp);

				DNSResolved[2] = true;
			}

			hp = gethostbyname("downloadtwo.xbonline.live");

			if (hp && hp->h_addr_list && hp->h_addr_list[0])
			{
				unsigned char* ip = (unsigned char*)hp->h_addr_list[0];

				_snprintf(ServerTwoIp, 0x20, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);

				//DbgPrint("ServerTwoIp: %s\n", ServerTwoIp);

				DNSResolved[3] = true;
			}

			if (DNSResolved[0] && DNSResolved[1] && DNSResolved[2] && DNSResolved[3])
			{
				Connection->ChangeIPnPort(Out_IP, PORT);
				isDoneOnce = true;
				break;
			}

			DNSResolveCount++;

			if (DNSResolveCount > 10)
				break;
		}
	}
	return 0;
}

Client::Client(unsigned char* CPUKey, unsigned char* Geneology, unsigned char* Hash)
{
	ConnectionAttempCount = 0;
	Connection = 0;

	this->CPUKey = new unsigned char[16];
	this->Geneology = new unsigned char[16];
	this->XEX_Hash = new unsigned char[20];
	this->Gamertag = new char[32];
	this->IP = new char[32];

	for (int i = 0; i < 16; i++)
		this->CPUKey[i] = CPUKey[i];

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)this->Geneology, 0, 0, false);

	for (int i = 0; i < 20; i++)
		this->XEX_Hash[i] = Hash[i];

	char XamUserName[32] = { 0 };
	XamUserGetName(0, XamUserName, 16);

	strcpy(this->Gamertag, XamUserName);
	strcpy(this->IP, "192.168.1.1");

	Connection = new Sockets(Out_IP, PORT);

	PopulateAddresses(Connection);
}

Client::~Client()
{

	delete Connection;
	delete[] this->CPUKey;
	delete[] this->Geneology;
	delete[] this->XEX_Hash;
	delete[] this->Gamertag;
}

void Client::TokeStatusNotification(void* resp)
{

	Use_Token_Response * Resp = (Use_Token_Response *)resp;

	switch (Resp->Toke_Status)
	{
	case INVALID_TOKEN:
		XNotify(L"This token is in an incorrect format.");
		break;
	case USED_TOKEN:
		XNotify(L"This token has been previously used.");
		break;
	case VALID_TOKEN:
		XNotify(L"This is a valid token!");
		break;
	case SUCESSFULLY_REDEEMED:
		XNotify(L"Token sucessfully redeemed!");
		break;
	default:
		break;
	}
}

void Client::ConvertTime(long long time, char* Out)
{
	long long days = time / 60 / 60 / 24;
	long long hours = (time / 60 / 60) % 24;
	long long minutes = (time / 60) % 60;
	long long seconds = time % 60;

	if (days > 6000) {
		_snprintf(Out, 1024, "Lifetime!");
		return;
	}


	if (days < 1000)
		_snprintf(Out, 1024, "%lli Days %lli Hours %lli Minutes", days, hours, minutes);
	else
		_snprintf(Out, 1024, "Nigel Time!");
}

bool Client::SendData(void* OutData, void* InData)
{
	printf("Attempting to send Data\n");

	bool RotateIP = false;

	while (ConnectionAttempCount <= MAX_CONNECTION_ATTEMPS)
	{
		if (Connection->InitConnection())
		{
			unsigned char* outBuffer = (unsigned char*)InData;
			sha1(InData, MAX_PACKET_SIZE - 0x14, &outBuffer[MAX_PACKET_SIZE - 0x14]);

			if (Connection->Send((const char*)OutData, MAX_PACKET_SIZE))
			{
				if (Connection->Receive((char*)InData, MAX_PACKET_SIZE))
				{
					unsigned char OutSha1[0x14] = { 0 };

					unsigned char* outBuffer = (unsigned char*)InData;
					sha1(InData, MAX_PACKET_SIZE - 0x14, OutSha1);

					if (!memcmp(&outBuffer[MAX_PACKET_SIZE - 0x14], OutSha1, 0x14)) {

						Connection->Close();

						printf("Data Sent Sucessfully\n");

						return true;
					}
					else
						printf("Digest Didn't Match, Trying Connection\n");
				}
				else printf("Recieve failed\n");
			}
			else printf("Send Failed\n");
		}
		else printf("Connection Failed\n");

		Connection->ChangeIPnPort(RotateIP ? Out_IP : Out_IP_BK, RotateIP ? PORT : PORT_BK);

		RotateIP = !RotateIP;

		ConnectionAttempCount++;
		Connection->Close();
	}
	return false;
}


bool Client::GetSession(unsigned char* Out, long long* Time, CLIENT_AUTH_STATUS* Status)
{
	if (GotAnewUpdate)
	{
		g_GlobalStatus = GET_UPDATE;
		SetLiveBlock(true);
		return true;
	}

	printf("Attempting to get session\n");

	SetLiveBlock(true);

	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	Session_Request Request;
	Request.ID = SESSION_REQUEST;
	Request.Auth_ID = SESSION_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, ipAddress);

	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);

	TitleID[0] = XamGetCurrentTitleId();

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	DoXEXHash(Request.XEX_Hash, (void*)&Request);

	strcpy(Request.GamerTag, this->Gamertag);

	memcpy(RespBuffer, &Request, sizeof(Session_Request));

#if defined(DEVKIT)
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif	

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif	

		Session_Response* Resp = (Session_Response*)RespBuffer;

		SecondPacketSize = Resp->Packet_Size;

		Tramps->CallFunction(memcpy_Function, (int)SecondPacketLoad, (int)Resp->Packet_Challenge, (int)Resp->Packet_Size, (int)0, false);

#if defined(DEVKIT)
#else

		_thingHck = _byteswap_ulong(*(int*)(Resp->Packet_Challenge + 172));

		thickHck[0] = _byteswap_uint64(*(long long*)(Resp->Packet_Challenge + 172 + 0x8));
		thickHck[1] = _byteswap_uint64(*(long long*)(Resp->Packet_Challenge + 172 + 0x10));

		*(unsigned long long*)((_thingHck ^ 0x272719) + 0x0) = (thickHck[0] ^ 0x22872802327128);
		*(unsigned long long*)((_thingHck ^ 0x272719) + 0x8) = (thickHck[1] ^ 0x32712822872802);

		int FunctionRet = 0;

		while (FunctionRet != 0xDEADBEEF) {

			FunctionRet = RunCode((int*)Resp->SabCodebuffer, Resp->SabCode_Size);
		}

#endif


		if (Time)
			*Time = _byteswap_uint64(Resp->timeleft);

		if (Status)
			*Status = Resp->AuthStatus;

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			break;
		}

		memcpy(Out, Resp->Session, 8);

		return true;
	}
	SetLiveBlock(true);
	return false;
}

bool Client::GetXamChallenge(unsigned char* Session, unsigned char* Salt, unsigned char* CPUKey, unsigned char Type, unsigned char* ChallengeOut)
{
	printf("Attempting to get Get Challenge\n");

	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	Xam_Challenge_Request Request;
	Request.ID = XAM_CHALLENGE_REQUEST;
	Request.Auth_ID = XAM_CHALLENGE_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, ipAddress);
	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	TitleID[0] = XamGetCurrentTitleId();


	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	DoXEXHash(Request.XEX_Hash, (void*)&Request);

	strcpy(Request.GamerTag, this->Gamertag);

	memcpy(Request.KV_CPUKey, CPUKey, 20);
	memcpy(Request.Challenge_Salt, Salt, 16);
	Request.ConsoleType = Type;
	memcpy(Request.SessionKey, Session, 8);

	memcpy(RespBuffer, &Request, sizeof(Xam_Challenge_Request));


#if defined(DEVKIT)
	EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif	

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif	

		unsigned char Digest[20] = { 0 };

		Xam_Challenge_Response* Resp = (Xam_Challenge_Response*)RespBuffer;

		sha1(Resp->Challenge, 0x100, Digest);

		memcpy(ChallengeOut, Resp->Challenge, 0x100);

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}

		if (memcmp(Digest, Resp->Digest, 20) != 0) {

			//XNotify(L"Is Something Wrong Sir?");
			printf("Xam Challenge Failed, we will get them next time\n");

			return false;
		}

		//CWriteFile("xbOnline:\\ChallengeDump.bin", Resp->Challenge, 0x100);

		CNotify.ShowNotification(Resp->AuthStatus, Session, this->CPUKey, this->XEX_Hash, this->Geneology);

		return true;
	}
	return false;
}

bool Client::CheckToken(const char* Token, bool DisplayMessage, long long* DaysWorth, TOKE_STATUS* Status)
{
	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	Check_Token_Request Request;
	Request.ID = CHECK_TOKEN_REQUEST;
	Request.Auth_ID = CHECK_TOKEN_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];


	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, ipAddress);

	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	TitleID[0] = XamGetCurrentTitleId();

	DoXEXHash(Request.XEX_Hash, (void*)&Request);

	strcpy(Request.GamerTag, this->Gamertag);
	strcpy(Request.Token, Token);
	memcpy(RespBuffer, &Request, sizeof(Check_Token_Request));

#if defined(DEVKIT)
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

		Check_Token_Response* Resp = (Check_Token_Response*)RespBuffer;

		if (DisplayMessage)
			TokeStatusNotification(Resp);

		if (Status)
			*Status = Resp->Toke_Status;

		if (DaysWorth)
			*DaysWorth = _byteswap_uint64(Resp->Days);

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}

		return true;
	}
	return false;
}

bool Client::UseToken(const char* Token)
{
	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	Use_Token_Request Request;
	Request.ID = USE_TOKEN_REQUEST;
	Request.Auth_ID = USE_TOKEN_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, ipAddress);

	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	TitleID[0] = XamGetCurrentTitleId();

	DoXEXHash(Request.XEX_Hash, (void*)&Request);

	strcpy(Request.GamerTag, this->Gamertag);
	strcpy(Request.Token, Token);
	memcpy(RespBuffer, &Request, sizeof(Use_Token_Request));

#if defined(DEVKIT)
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

	if (SendData(RespBuffer, RespBuffer))
	{

#if defined(DEVKIT)
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

		Use_Token_Response* Resp = (Use_Token_Response*)RespBuffer;

		TokeStatusNotification(Resp);

		g_GlobalStatus = Resp->AuthStatus;


		g_Endtime = time(NULL) + _byteswap_uint64(Resp->timeleft);;

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}

		return true;
	}
	return false;
}

bool Client::CheckTime(char* TimeOut, long long* time, CLIENT_AUTH_STATUS* Status)
{
	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	INCOMING_PACKET_HEADER Challenge;
	Challenge.ID = TIME_CHECK_REQUEST;
	Challenge.Auth_ID = TIME_CHECK_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Challenge);

	for (int i = 0; i < 16; i++)
		Challenge.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Challenge.CPUKey[i] = this->CPUKey[i];

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Challenge.Geneology, 0, 0, false);

	HvPeekBytes(0x8000010200010100, Challenge.Memory_EncryptionKey, 0x30);

	XeCryptRandom(Challenge.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Challenge.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Challenge.Memory_EncryptionKey, ipAddress);

	Challenge.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Challenge.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	TitleID[0] = XamGetCurrentTitleId();

	DoXEXHash(Challenge.XEX_Hash, (void*)&Challenge);
	strcpy(Challenge.GamerTag, this->Gamertag);
	memcpy(RespBuffer, &Challenge, sizeof(INCOMING_PACKET_HEADER));

#if defined(DEVKIT)
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

		OUTGOING_PACKET_HEADER* Resp = (OUTGOING_PACKET_HEADER*)RespBuffer;

		if (time)
			*time = _byteswap_uint64(Resp->timeleft);

		if (Status)
			*Status = Resp->AuthStatus;


		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);

			CNotify.isExpired = true;
			CNotify.isFirstChallenge = false;
			CNotify.isNewRedeem = true;

			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}

		if (Resp->timeleft == -1 && Resp->AuthStatus == EXPIRED) {
			strcpy(TimeOut, "You currently have no time.");
		}
		else if (Resp->AuthStatus == FREEMODE) {
			strcpy(TimeOut, "Currently in Freemode.");
		}
		else ConvertTime(_byteswap_uint64(Resp->timeleft), TimeOut);

		return true;
	}
	return false;
}


wchar_t *GetWC_Test(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

bool Client::Presence(unsigned char* Session, long long* Time, CLIENT_AUTH_STATUS* Status)
{
	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	INCOMING_PACKET_HEADER Challenge;
	Challenge.ID = PRESENCE_REQUEST;
	Challenge.Auth_ID = PRESENCE_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Challenge);

	for (int i = 0; i < 16; i++)
		Challenge.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Challenge.CPUKey[i] = this->CPUKey[i];

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Challenge.Geneology, 0, 0, false);

	HvPeekBytes(0x8000010200010100, Challenge.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Challenge.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Challenge.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Challenge.Memory_EncryptionKey, ipAddress);

	Challenge.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* TitleID = (int*)(&Challenge.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	TitleID[0] = XamGetCurrentTitleId();

	DoXEXHash(Challenge.XEX_Hash, (void*)&Challenge);

	strcpy(Challenge.GamerTag, this->Gamertag);
	memcpy(RespBuffer, &Challenge, sizeof(INCOMING_PACKET_HEADER));

#if defined(DEVKIT)
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (int)(MAX_PACKET_SIZE - 1), false);
#endif
		Presense_Response* Resp = (Presense_Response*)RespBuffer;

		server_cod_aw = Resp->cod_aw;
		server_cod_mw = Resp->cod_mw;
		server_cod_waw = Resp->cod_waw;
		server_cod_mw2 = Resp->cod_mw2;
		server_cod_bo1 = Resp->cod_bo1;
		server_cod_mw3 = Resp->cod_mw3;
		server_cod_bo2 = Resp->cod_bo2;
		server_cod_ghosts = Resp->cod_ghosts;
		server_cod_bo3 = Resp->cod_bo3;
		server_csgo = Resp->csgo_offhost;

		if (Resp->DisplayBox == 0x1337)
		{
			if (!strcmp(Resp->Data, "restart"))
			{
				HalReturnToFirmware(HalRebootRoutine);

			}
			else
			{
				wchar_t* data = GetWC_Test(Resp->Data);

				if (strlen(Resp->Data) > 5)
					ShowMessageBoxUI(L"xbOnline Message!", data);

				delete data;
			}
		}


		if (Time)
			*Time = _byteswap_uint64(Resp->timeleft);

		if (Status)
			*Status = Resp->AuthStatus;

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}


		CNotify.ShowNotification(Resp->AuthStatus, Session, this->CPUKey, this->XEX_Hash, this->Geneology);

		return true;
	}
	return false;
}

bool Client::GetCheatData(unsigned char* Session, unsigned char* CPUKey, int TitleID, unsigned char* CheatDataOut, int CheatDataSize)
{
	printf("Attempting to Get Cheat Data\n");

	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	Cheat_Data_Request Request;
	Request.ID = CHEAT_DATA_REQUEST;
	Request.Auth_ID = CHEAT_DATA_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, ipAddress);

	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* clTitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	clTitleID[0] = XamGetCurrentTitleId();

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	DoXEXHash(Request.XEX_Hash, (void*)&Request);

	strcpy(Request.GamerTag, this->Gamertag);

	Request.TitleID = TitleID;

	memcpy(RespBuffer, &Request, sizeof(Cheat_Data_Request));

#if defined(DEVKIT)
	EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif	

	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif	

		unsigned char Digest[20] = { 0 };

		Cheat_Data_Respose* Resp = (Cheat_Data_Respose*)RespBuffer;

		memcpy(CheatDataOut, Resp->GameData, CheatDataSize);

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}
		return true;
	}
	SetLiveBlock(true);
	return false;
}

int FinalizeBuffer(Xosc_Challenge_Response* Rev, BYTE* ChallReps)
{
	DWORD baseAddress = (DWORD)ResolveFunction("xosc9v2.xex", 1);

	if ((baseAddress != 0) && MmIsAddressValid((void*)baseAddress))
	{
		sha1_context context;
		sha1_starts(&context);
		sha1_update(&context, (BYTE*)(0x90010000 | *(WORD*)(baseAddress - 0x62)), 0x8E59);
		sha1_update(&context, (&Rev->buffer[0x60]), 0x14);
		sha1_finish(&context, (&Rev->buffer[0x60]));
	}

	(&Rev->buffer[0x60])[0] = 0x07;

	memcpy(ChallReps + 0x60, (&Rev->buffer[0x60]), 0x10);

	return 0;
}

bool Client::GetSecurityChallenge(unsigned char* kv, unsigned char* ChallengeOut, unsigned char ConsoleType)
{
	printf("Attempting to get Get XOSC Challenge\n");

	unsigned short temp = 0;

	unsigned char SMCMessageID[1] = { 0x12 };

	unsigned char RespBuffer[MAX_PACKET_SIZE] = { 0 };

	XamGetExecutionId(&xosc_Execution);

	Xosc_Challenge_Request Request;
	Request.ID = XOSC_CHALLENGE_REQUEST;
	Request.Auth_ID = XOSC_CHALLENGE_REQUEST;

	PacketAuthentication((INCOMING_PACKET_HEADER*)&Request);

	for (int i = 0; i < 16; i++)
		Request.Geneology[i] = this->Geneology[i];

	for (int i = 0; i < 16; i++)
		Request.CPUKey[i] = this->CPUKey[i];

	Tramps->CallFunction(xbCreateBoxKey_Function, (long long)xbOnline_BoxKey1, (int)Request.Geneology, 0, 0, false);

	HvPeekBytes(0x8000010200010100, Request.Memory_EncryptionKey, 0x30);
	XeCryptRandom(Request.Memory_EncryptionKey, 0x30);

	char ipAddress[0x40] = { 0 };
	unsigned char* IP = (unsigned char*)&Request.Addr.inaOnline;
	_snprintf(ipAddress, 0x40, "%u.%u.%u.%u", IP[0], IP[1], IP[2], IP[3], IP[4], IP[5]);

	strcpy((char*)Request.Memory_EncryptionKey, this->IP);

	Request.Memory_EncryptionKey[strlen(ipAddress) + 1] = 0;

	int* clTitleID = (int*)(&Request.Memory_EncryptionKey[(strlen(ipAddress) + 1) + 4]);
	clTitleID[0] = XamGetCurrentTitleId();

	DoXEXHash(Request.XEX_Hash, (void*)&Request);
	strcpy(Request.GamerTag, this->Gamertag);

	Request.ConsoleType = ConsoleType;

	memcpy(Request.osig, (void*)((int)(&kv[0]) + 0xC89), 0x25);
	memcpy(Request.kvdigest, (PVOID)0x8E03AA40, 0x10);
	memcpy(Request.ConsoleID, (void*)((int)(&kv[0]) + 0x9CA), 0x5);
	memcpy(Request.serial, (void*)((int)(&kv[0]) + 0xB0), 0xC);
	memcpy(Request.xamRegion, (void*)((int)(&kv[0]) + 0xC8), 0x2);
	memcpy(Request.xamOdd, (void*)((int)(&kv[0]) + 0x1C), 0x2);
	ExGetXConfigSetting(2, 1, Request.Mac_Address, 6, &temp);

	memcpy(RespBuffer, &Request, sizeof(Xosc_Challenge_Request));

#if defined(DEVKIT)
	EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
	EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
	Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
	Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif	
	if (SendData(RespBuffer, RespBuffer))
	{
#if defined(DEVKIT)
		EncryptedDecryptPacket_Second(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
		EncryptedDecryptPacket(&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1));
#else
		Tramps->CallFunction(ExecuteCode_Function, (int)SecondPacketLoad, SecondPacketSize, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
		Tramps->CallFunction(ExecuteCode_Function, (int)FirstPacketLoad, 176, (int)&((unsigned char*)RespBuffer)[1], (MAX_PACKET_SIZE - 1), false);
#endif
		Xosc_Challenge_Response* Resp = (Xosc_Challenge_Response*)RespBuffer;

		unsigned char Digest[20] = { 0 };

		sha1(Resp->buffer, 0x400, Digest);

		switch (Resp->AuthStatus)
		{
		case BANNED:
			SetLiveBlock(true);
			break;
		case EXPIRED:
			SetLiveBlock(true);
			break;
		case NOT_INDB:
			SetLiveBlock(true);
			break;
		case FREEMODE:
			SetLiveBlock(false);
			break;
		case TIMELEFT:
			SetLiveBlock(false);
			break;
		default:
			SetLiveBlock(true);
			break;
		}

		switch (Resp->XexStatus)
		{
		case CORRECT_XEX:
			break;
		case UPDATE:
			g_GlobalStatus = GET_UPDATE;
			SetLiveBlock(true);
			GetNewUpdate();
			break;
		}


		memcpy(ChallengeOut, Resp->buffer, 0x400);

		//Perform Final 0x60 Digest
		FinalizeBuffer(Resp, ChallengeOut);


		*(int*)(ChallengeOut + 0x80) = *(char*)((int)(&KeyVault) + 0xC89);

		//CWriteFile("xbOnline:\\XOSC_CHALLENGE.bin", ChallengeOut, 0x400);

		if (memcmp(Digest, Resp->Digest, 20) != 0) {

			//XNotify(L"XOSC IS ANYONE THERE?!?");

			//printf("XOSC Failed, we will get them next time\n");

			return false;
		}
		return true;
	}
	return false;
}

void Client::GetNewUpdate()
{
	//Lets delete our update info
	//DeleteFile("xbOnline:\\UDInfo.txt");

	char TempIpBuffer[255] = { 0 };
	strcpy(TempIpBuffer, ServerTwoIp);

	if (!updateFinished)
	{
		int Attempts = 0;

		if (!g_GettingUpdate)
		{
			XNotify(L"Update Found!\nDownloading please wait");

			g_GettingUpdate = true;

			int XEX_SIZE = 0;

			unsigned char* XBO_XEX = 0;

			while (Attempts < 50)
			{
				if (XBO_XEX)
					free(XBO_XEX);

#if defined(DEVKIT)
				if (DownloadFile("149.56.195.127", "/DEVKIT_xbOnline.xex", &XBO_XEX, &XEX_SIZE))
#else
				if (DownloadFile(TempIpBuffer, "/xbOnline.xex", &XBO_XEX, &XEX_SIZE))
#endif	
				{
					if (XEX_SIZE && XBO_XEX && *(int*)(XBO_XEX) == 0x58455832)
					{
						unsigned char xbSha[0x14] = { 0 };

						sha1(XBO_XEX, (XEX_SIZE - 0x14), xbSha);

						if (!memcmp(xbSha, &XBO_XEX[XEX_SIZE - 0x14], 0x14))
						{
							printf("Path: %s\n", CurrentPath);

							if (CWriteFile((char*)CurrentPath, XBO_XEX, (XEX_SIZE - 0x14)))
							{
								GotAnewUpdate = true;

								g_GotSessionKey = true;

								updateFinished = true;

								XNotify(L"xbOnline Downloaded!");

								free(XBO_XEX);

								MESSAGEBOX_RESULT g_mb_result;
								XOVERLAPPED g_xol;

								LPCWSTR Buttons[2] = { L"Restart Me Now", L"Not right now" };

								while (XShowMessageBoxUI(XUSER_INDEX_ANY, L"xbOnline Update!", L"An update for xbOnline has been downloaded, Would you like to restart your console right now or do it later?\nIf you have any problems while updating please go to\nhttp://xbonline.live/xbOnline.zip", 2, Buttons, 0, XMB_ALERTICON, &g_mb_result, &g_xol) == ERROR_ACCESS_DENIED)
									Sleep(501);
								while (!XHasOverlappedIoCompleted(&g_xol))
									Sleep(501);

								if (g_mb_result.dwButtonPressed == 0)
									RebootConsole();

								break;
							}
						}
						else printf("File Digest Didn't Match\n");
					}
				}

				if (Attempts % 2)
					strcpy((char*)TempIpBuffer, ServerOneIp);
				else
					strcpy((char*)TempIpBuffer, ServerTwoIp);

				Attempts++;
				Sleep(50);
			}
			g_GettingUpdate = false;
		}
	}

}

void DownloadGameAddresses()
{

	ServerData_BlackOps2 GameData = { 0 };

	printf("Getting BO2 Addresses\n");

	DownloadGameAddress(0x415608C3, &GameData, sizeof(ServerData_BlackOps2));

	if (GameData.Server_addr_s_XexAddrNum && GameData.Server_init_addr_s_XexAddrNum) {

		printf("Setting Up BO2 Addresses\n");

		BO2_SetupGameAddresses(&GameData);
	}

	Sleep(400);

	ServerData_MW2 MW2_GameData = { 0 };

	printf("Getting MW2 Addresses\n");

	DownloadGameAddress(0x41560817, &MW2_GameData, sizeof(ServerData_MW2));

	if (MW2_GameData.Server_addr_s_XexAddrNum && MW2_GameData.Server_init_addr_s_XexAddrNum) {

		printf("Setting Up MW2 Addresses\n");

		MW2_SetupGameAddresses(&MW2_GameData);
	}

	Sleep(400);

	ServerData_BF4 BF4_GameData = { 0 };

	printf("Getting BF4 Addresses\n");

	DownloadGameAddress(0x454109BA, &BF4_GameData, sizeof(ServerData_BF4));

	if (BF4_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up BF4 Addresses\n");

		BF4_SetupGameAddresses(&BF4_GameData);
	}

	Sleep(400);

	ServerData_MW2_OnHosts MW2_GameData_OnHosts = { 0 };

	printf("Getting MW2 OnHosts Addresses\n");

	DownloadGameAddress(0x41560818, &MW2_GameData_OnHosts, sizeof(ServerData_MW2_OnHosts));

	if (MW2_GameData_OnHosts.Server_addr_s_XexAddrNum) {

		printf("Setting Up MW2 OnHosts Addresses\n");

		MW2_OnHosts_SetupGameAddresses(&MW2_GameData_OnHosts);
	}

	Sleep(400);

	ServerData_MW3 MW3_GameData = { 0 };

	printf("Getting MW3 Addresses\n");

	DownloadGameAddress(0x415608CB, &MW3_GameData, sizeof(ServerData_MW3));

	if (MW3_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up MW3 OnHosts Addresses\n");

		MW3_SetupGameAddresses(&MW3_GameData);
	}

	Sleep(400);

	ServerData_BO1 BO1_GameData = { 0 };

	printf("Getting BO1 Addresses\n");

	DownloadGameAddress(0x41560855, &BO1_GameData, sizeof(ServerData_BO1));

	if (BO1_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up BO1 OnHosts Addresses\n");

		BO1_SetupGameAddresses(&BO1_GameData);
	}

	Sleep(400);

	ServerData_MW3_OnHosts MW3_GameData_OnHosts = { 0 };

	printf("Getting MW3 OnHosts Addresses\n");

	DownloadGameAddress(0x4156C918, &MW3_GameData_OnHosts, sizeof(ServerData_MW3_OnHosts));

	if (MW3_GameData_OnHosts.Server_addr_s_XexAddrNum) {

		printf("Setting Up MW3 OnHosts Addresses\n");

		MW3_OnHosts_SetupGameAddresses(&MW3_GameData_OnHosts);
	}

	Sleep(400);

	ServerData_CSGO_OnHosts CSGO_GameData_OnHosts = { 0 };

	printf("Getting CSGO OnHosts Addresses\n");

	DownloadGameAddress(0x5841125A, &CSGO_GameData_OnHosts, sizeof(ServerData_CSGO_OnHosts));

	if (CSGO_GameData_OnHosts.Server_addr_s_XexAddrNum) {

		printf("Setting Up CSGO OnHosts Addresses\n");

		CSGO_OnHosts_SetupGameAddresses(&CSGO_GameData_OnHosts);
	}

	Sleep(400);

	ServerData_Ghosts Ghosts_GameData = { 0 };

	printf("Getting Ghosts Addresses\n");

	DownloadGameAddress(0x415608FC, &Ghosts_GameData, sizeof(ServerData_Ghosts));

	if (Ghosts_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up Ghosts Addresses\n");

		Ghosts_SetupGameAddresses(&Ghosts_GameData);
	}

	Sleep(400);

	ServerData_tf2 tfs_GameData = { 0 };

	printf("Getting tf2 Addresses\n");

	DownloadGameAddress(0x4541080F, &tfs_GameData, sizeof(ServerData_tf2));

	if (tfs_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up Ghosts Addresses\n");

		tf2_SetupGameAddresses(&tfs_GameData);
	}


	Sleep(400);

	ServerData_BF3 BF3_GameData = { 0 };

	printf("Getting BF3 Addresses\n");

	DownloadGameAddress(0x45410950, &BF3_GameData, sizeof(ServerData_BF3));

	if (BF3_GameData.Server_addr_s_XexAddrNum) {

		printf("Setting Up Ghosts Addresses\n");

		BF3_SetupGameAddresses(&BF3_GameData);
	}

}
