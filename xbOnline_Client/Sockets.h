#pragma once

class Sockets
{
public:
	char IP[16];
	void Close();
	Sockets(unsigned short Port);
	Sockets(SOCKET s);
	Sockets(const char* ConnectReceiveionAddr, unsigned short Port);
	bool Receive(char* Data, int Size);
	bool Send(const char* Data, int Length);
	int SetSocketOption(int Level, int OptionName, void * OptionValue, int OptionLenght);
	bool StartListener(int MaxConnections);
	unsigned long long Accept(sockaddr * address, int* length);
	void ChangeIPnPort(const char* ConnectionAddr, unsigned short Port);
	bool InitConnection();
	SOCKET Socket;
	~Sockets();

private:
	bool InitSockets();
	bool isSocketConnected();
	bool hasConnectionBeenClosed;
	unsigned short port;

};

#define SOCKET_TIME_OUT 		10000