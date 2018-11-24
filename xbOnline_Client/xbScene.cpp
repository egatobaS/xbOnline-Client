#include "main.h"

xbScene_s xbscene;

bool xbScene_s::init() {

	if (!GetHandle((void*)XAM_XEX, &xbscene.hXam))
		return false;

	if (!xuiz.xam.setupDetours())
		return false;

	return true;
}

void xbScene_s::print(const PCHAR fmt, ...) {
	/*char buffer[1000];
	va_list pArgList;
	va_start(pArgList, fmt);
	vsprintf_s(buffer, 1000, fmt, pArgList);
	va_end(pArgList);

	FILE * fp = fopen("xbScene:\\xbScene.log", "a+");
	fprintf(fp, "%s", buffer);
	fclose(fp);
	printf("%s", buffer);*/
}

bool xbScene_s::mountDrives() {
	/*dlaunchPluginPath = (pluginLoadpath_s*)resolveFunction((HMODULE)hDl, 0xE);
	if (dlaunchPluginPath->magic == int(0x504C5041) && dlaunchPluginPath->devicePath != NULL && dlaunchPluginPath->iniPath != NULL) {
		std::string device, file, drive, link, directory;
		device.assign(dlaunchPluginPath->devicePath);
		file.assign(dlaunchPluginPath->iniPath);

		drive = std::string("\\System??\\xbScene:");
		link.assign(drive.begin(), drive.end());
		directory.assign(device);
		directory.append(file.substr(1, file.find_last_of('\\')));

		if (createSymboliclink(directory, link)) {*/
			return true;
	/*	}
	}
	return false;*/
}

int xbScene_s::resolveFunction(HMODULE hHandle, unsigned int dwOrdinal) {
	int ptr = 0;
	if (hHandle == 0)
		return 0;

	// pointer may change per dash. ct: 17526
	((NTSTATUS(*)(...))XexGetProcAddressPointer)((HANDLE)hHandle, dwOrdinal, &ptr);

	return int(ptr);
}

bool xbScene_s::GetHandle(void* pvAddress, PHANDLE hModule) {
	CRITICAL_SECTION section;
	InitializeCriticalSection(&section);

	PLDR_DATA_TABLE_ENTRY entry;

	if (pvAddress <= 0)
		return false;

	if (*hModule != 0) // don't bother re-applying it.
		return true;

	((PVOID(*)(...))XexPcToFileHeaderPointer)(pvAddress, &entry);

	*hModule = (PHANDLE)entry;

	LeaveCriticalSection(&section);
	return true;
}

bool xbScene_s::createSymboliclink(std::string &device, std::string &link) {
	STRING szDevice, szLink;
	NTSTATUS ntStatus;

	int rtlInitAnsiStringPointer = resolveFunction((HMODULE)hKernel, 300),
		obDeleteSymbolicLinkPointer = resolveFunction((HMODULE)hKernel, 260),
		obCreateSymbolicLinkPointer = resolveFunction((HMODULE)hKernel, 259);

	if (rtlInitAnsiStringPointer == 0 || obDeleteSymbolicLinkPointer == 0 || obCreateSymbolicLinkPointer == 0)
		return false;

	((void(*)(...))rtlInitAnsiStringPointer)(&szDevice, device.c_str());
	((void(*)(...))rtlInitAnsiStringPointer)(&szLink, link.c_str());

	((HRESULT(*)(...))obDeleteSymbolicLinkPointer)(&szLink);

	ntStatus = ((HRESULT(*)(...))obCreateSymbolicLinkPointer)(&szLink, &szDevice);

	return (ntStatus >= 0) ? true : false;
}
