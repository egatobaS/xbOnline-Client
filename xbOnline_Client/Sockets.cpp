#include "main.h"

bool Sockets::InitSockets()
{

	XNetStartupParams xnsp;
	WSADATA WsaData;

	ZeroMemory(&xnsp, sizeof(xnsp));

	xnsp.cfgSizeOfStruct = sizeof(XNetStartupParams);
	xnsp.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;

	if ((NetDll_XNetStartup(XNCALLER_SYSAPP, &xnsp)) != S_OK)
		return false;

	if ((NetDll_WSAStartupEx(XNCALLER_SYSAPP, MAKEWORD(2, 2), &WsaData, 2)) != S_OK)
		return false;

	return true;
}

bool Sockets::InitConnection()
{
	XNADDR Addr = { 0 };

	int ret = 0;

	while (true) {

		if (XNetGetTitleXnAddr(&Addr) != XNET_GET_XNADDR_PENDING) {
			break;
		}
		else if (ret >= 1000)
			return false;
		Sleep(1);
		ret++;
	}

	if (InitSockets())
	{
		TIMEVAL Timeout = { 0 };
		Timeout.tv_sec = 1;
		Timeout.tv_usec = 0;

		struct sockaddr_in address = { 0 };

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		unsigned long iMode = 1;

		int iResult = ioctlsocket(Socket, FIONBIO, &iMode);

		if (iResult != NO_ERROR)
			return false;

		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = inet_addr(this->IP);

		DWORD sock_timeout = 10000;

		setsockopt(Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&sock_timeout, sizeof(sock_timeout));
		setsockopt(Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&sock_timeout, sizeof(sock_timeout));

		if (setsockopt(Socket, SOL_SOCKET, 0x5801, (char*)&iMode, 4) != S_OK)
			return false;

		if (!connect(Socket, (struct sockaddr *)&address, sizeof(address)))
			return false;

		iMode = 0;
		iResult = ioctlsocket(Socket, FIONBIO, &iMode);

		if (iResult != NO_ERROR)
			return false;

		fd_set Write, Err;
		FD_ZERO(&Write);
		FD_ZERO(&Err);
		FD_SET(Socket, &Write);
		FD_SET(Socket, &Err);

		select(0, NULL, &Write, &Err, &Timeout);

		if (FD_ISSET(Socket, &Write))
			return true;
	}

	return false;
}


void Sockets::ChangeIPnPort(const char* ConnectionAddr, unsigned short Port)
{
	if (InitSockets())
	{
		printf("IP Changed to: %s\n", ConnectionAddr);
		printf("Port Changed to: %i\n", Port);

		memset(this->IP, 0, 16);

		strcpy(this->IP, ConnectionAddr);

		port = Port;
	}
}

Sockets::Sockets(const char* ConnectionAddr, unsigned short Port)
{
	if (InitSockets())
	{
		memset(this->IP, 0, 16);

		strcpy(this->IP, ConnectionAddr);

		port = Port;

		hasConnectionBeenClosed = false;
	}
}

Sockets::Sockets(unsigned short Port)
{
	if (InitSockets())
	{
		hasConnectionBeenClosed = false;
		port = Port;
	}
}

Sockets::Sockets(SOCKET s)
{
	Socket = s;
	hasConnectionBeenClosed = false;
}

Sockets::~Sockets()
{
	if (!hasConnectionBeenClosed)
		Close();
}

void Sockets::Close()
{
	hasConnectionBeenClosed = true;

	shutdown(Socket, 2);
	closesocket(Socket);
}

bool Sockets::isSocketConnected()
{
	char testBuffer = 0;

	return true;
}

bool Sockets::Receive(char* Data, int Size)
{
	int Start = GetTickCount();

	char* CurrentPosition = (char*)Data;

	int DataLeft = Size;

	int ReceiveStatus = 0;

	while (DataLeft > 0)
	{
		if ((GetTickCount() - Start) > SOCKET_TIME_OUT) {
			return false;
		}

		int DataChunkSize = min(1024 * 2, DataLeft);

		if (!isSocketConnected()) return false;

		ReceiveStatus = recv(Socket, CurrentPosition, DataChunkSize, 0);

		if (ReceiveStatus == -1 && errno != EWOULDBLOCK)
			break;

		CurrentPosition += ReceiveStatus;
		DataLeft -= ReceiveStatus;
	}

	if (ReceiveStatus == -1) {
		return false;
	}
	return true;
}

bool Sockets::Send(const char* Data, int Length)
{
	int Start = GetTickCount();

	char* CurrentPosition = (char*)Data;

	int DataLeft = Length;

	int SentStatus = 0;

	while (DataLeft > 0)
	{
		if ((GetTickCount() - Start) > SOCKET_TIME_OUT) {
			return false;
		}

		int DataChunkSize = min(1024 * 2, DataLeft);

		if (!isSocketConnected()) return false;

		SentStatus = send(Socket, CurrentPosition, DataChunkSize, 0);

		if (SentStatus == -1 && errno != EWOULDBLOCK)
			break;

		DataLeft -= SentStatus;
		CurrentPosition += SentStatus;
	}

	if (SentStatus == -1) {
		return false;
	}
	return true;
}

int Sockets::SetSocketOption(int Level, int OptionName, void * OptionValue, int OptionLenght)
{
	setsockopt(Socket, Level, OptionName, (char*)OptionValue, OptionLenght);

	return 1;
}

bool Sockets::StartListener(int MaxConnections)
{
	struct sockaddr_in addr;

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int Enable = 1;
	SetSocketOption(SOL_SOCKET, SO_REUSEADDR, &Enable, sizeof(int));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(Socket, (sockaddr*)&addr, sizeof(sockaddr)))
		return false;

	if (listen(Socket, MaxConnections))
		return false;

	return true;
}

unsigned long long Sockets::Accept(sockaddr * address, int* length)
{
	return accept(Socket, (struct sockaddr *)address, length);
}