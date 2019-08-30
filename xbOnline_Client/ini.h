#pragma once

enum INI_ERRORS
{
	FILE_WRITE,
	FILE_READ,
	SUCCESS,
	NO_OPTION_FOUND,
	NO_FILE_READ,
	NO_FILE_WRITE,
	NO_POPULATION,
	NO_SECTION_FOUND,
	UNK_ERROR
};

class INI
{
public:
	INI(const char* Path, bool IgnoreFileExist = false);
	~INI();
	INI_ERRORS LastError;
	char* IniPointer;
	bool DoesSectionExist(const char* Section);
	int GetSectionItemCount(const char* Section);
	bool GetBool(const char* Section, const char* Option);
	void SetOption(const char* Section, const char* Option, const char* Value);
	bool DidFileExist();
	void SaveFile(const char* Path = NULL);
private:
	bool FoundFile;
	std::vector<std::string> LinesInFile;
	SIZE_T IniLength;
	bool isPopulated;
	char INIPath[1024];
};

