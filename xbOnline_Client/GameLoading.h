#pragma once

struct ThreadPastGameData
{
	int ID;
	int TitleID;
	char titleName[255];
	char titleIp[255];
	void* AnotherGame;
	char Name[255];
	bool istoLoadAnotherGame;
	bool isCheatEnabled;
};

class CheatManager
{

public:
	CheatManager();
	void UnloadCheats();
	void LoadCheat(int ID, int TitleID, const char* titleName, const char* titleIp, const char* Name);
	bool isModuleLoaded[30];
	HANDLE Modulehandle[30];
	int LoadedForTitleID[30];
	int LastTitleIDPlayed;
	char lastCheatLoadedPath[30][255];
	int GetValidID();
private:
};

extern CheatManager GameManager;

extern byte b1BLKey[16];
extern byte bHvRomMagic[16];
extern byte GameKey[6];

void DownloadGameAddress(int TitleID, void* GameData, int Size);
void LoadCheat(int TitleID);

