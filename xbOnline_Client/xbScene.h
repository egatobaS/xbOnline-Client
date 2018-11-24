#pragma once


#define XAM_XEX			0x815F0000
#define LAUNCH_XEX		0x91F00000
#define XBOXKRNL_PE		0x80040000
#define XBDM_XEX		0x91000000
#define DASH_XEX		0x92000000
#define HUD_XEX			0x913E0000
#define TITLE_XEX		0x82000000

struct pluginLoadpath_s {
	unsigned int magic;
	const char* devicePath;
	const char* iniPath;
};

struct xbScene_s {
	bool init();
	bool GetHandle(void* pvAddress, PHANDLE hModule);
	int resolveFunction(HMODULE hHandle, unsigned int dwOrdinal);
	bool createSymboliclink(std::string &device, std::string &link);
	bool mountDrives();
	void print(const PCHAR fmt, ...);

	pluginLoadpath_s* dlaunchPluginPath;
	HANDLE hClient, hKernel, hXam, hDl;
};

extern xbScene_s xbscene;
