#include "main.h"

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string number;
	while (std::getline(ss, number, delim)) {
		elems.push_back(number);
	}
	return elems;
}

std::string removeSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}
bool INI::DidFileExist()
{
	return FoundFile;
}
void INI::SaveFile(const char* Path)
{
	if (!isPopulated) {

		LastError = NO_POPULATION;
		return;
	}

	SIZE_T FileCount = 0, FileOffset = 0;

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{
		LinesInFile[i].append("\n");

		FileCount += strlen(LinesInFile[i].c_str());
	}

	char* FinalIni = (char*)malloc(FileCount);

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{

		SIZE_T CurrentStringSize = strlen(LinesInFile[i].c_str());

		memcpy(FinalIni + FileOffset, LinesInFile[i].c_str(), CurrentStringSize);

		FileOffset += CurrentStringSize;
	}

	CWriteFile(Path == NULL ? INIPath : Path, FinalIni, FileOffset);
	free(FinalIni);
}

bool INI::DoesSectionExist(const char* Section)
{
	if (!Section)
		return false;

	if (!isPopulated) {

		LastError = NO_POPULATION;
		return false;
	}

	bool isFound = false;

	SIZE_T SectionLength = strlen(Section) + 3;

	if (SectionLength < 3)
		return false;

	char* Data = (char*)malloc(SectionLength);
	memset(Data, 0, SectionLength);

	_snprintf(Data, (size_t)SectionLength, (const char*)"[%s]", Section);

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{
		if (LinesInFile[i].find(std::string(Data)) != -1)
		{
			isFound = true;
			LastError = SUCCESS;

			break;
		}
	}

	if (!isFound)
		LastError = NO_SECTION_FOUND;

	free(Data);

	return isFound;
}

int INI::GetSectionItemCount(const char* Section)
{
	if (!Section)
		return false;

	if (!isPopulated) {

		LastError = NO_POPULATION;
		return false;
	}

	int SectionCount = 0;

	SIZE_T SectionLength = strlen(Section) + 3;

	if (SectionLength < 3)
		return false;

	char* Data = (char*)malloc(SectionLength);
	memset(Data, 0, SectionLength);

	_snprintf(Data, (size_t)SectionLength, (const char*)"[%s]", Section);

	LastError = NO_OPTION_FOUND;

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{
		if (LinesInFile[i].find(std::string(Data)) != -1)
		{
			for (size_t e = i + 1; e < LinesInFile.size(); e++)
			{
				if (LinesInFile[e].find('[') != -1)
					break;

				LastError = SUCCESS;

				SectionCount++;
			}
			break;
		}
	}


	free(Data);

	return SectionCount;
}

bool INI::GetBool(const char* Section, const char* Option)
{
	if (!Section)
		return false;

	if (!isPopulated) {

		LastError = NO_POPULATION;
		return false;
	}

	int SectionID = -1;
	int OptionID = -1;

	bool ShouldEndSearch = false;

	bool BoolReturnType = false;

	SIZE_T SectionLength = strlen(Section) + 3;

	if (SectionLength < 3)
		return false;

	char* Data = (char*)malloc(SectionLength);
	memset(Data, 0, SectionLength);

	_snprintf(Data, (size_t)SectionLength, (const char*)"[%s]", Section);

	LastError = NO_OPTION_FOUND;

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{
		if (LinesInFile[i].find(std::string(Data)) != -1)
		{
			SectionID = i;

			for (size_t e = i + 1; e < LinesInFile.size(); e++)
			{
				if (LinesInFile[e].find('[') != -1)
					break;

				std::string SpacelessOption = removeSpaces(LinesInFile[e]);
				size_t EqualOccurance = std::count(SpacelessOption.begin(), SpacelessOption.end(), '=');

				if (EqualOccurance > 1 || EqualOccurance <= 0)
				{
					LastError = UNK_ERROR;
					ShouldEndSearch = true;
					break;
				}

				std::vector<std::string> Options = split(SpacelessOption, '=');

				if (Options.size() == 2 && (Options[1].length() >= 4 && Options[1].length() <= 6))
				{
					if (Options[0] == std::string(Option))
					{

						if (Options[1].find("true") != -1)
							BoolReturnType = true;
						else
							BoolReturnType = false;

						LastError = SUCCESS;

						ShouldEndSearch = true;
						break;
					}
				}
				else
				{
					LastError = UNK_ERROR;
					ShouldEndSearch = true;
					break;
				}
			}

			break;
		}

		if (ShouldEndSearch)
			break;
	}

	if (LastError == NO_OPTION_FOUND && SectionID == -1)
		LastError = NO_SECTION_FOUND;

	free(Data);

	return BoolReturnType;

}

void INI::SetOption(const char* Section, const char* Option, const char* Value)
{
	if (!Section)
		return;

	if (!Option)
		return;

	if (!Value)
		return;

	if (!isPopulated) {

		LastError = NO_POPULATION;
		return;
	}

	int SectionID = -1;
	int OptionID = -1;

	bool ShouldEndSearch = false;

	bool BoolReturnType = false;

	SIZE_T SectionLength = strlen(Section) + 3;

	if (SectionLength < 3)
		return;

	char* Data = (char*)malloc(SectionLength);
	memset(Data, 0, SectionLength);


	_snprintf(Data, (size_t)SectionLength, (const char*)"[%s]", Section);

	LastError = NO_OPTION_FOUND;

	for (size_t i = 0; i < LinesInFile.size(); i++)
	{
		if (LinesInFile[i].find(std::string(Data)) != -1)
		{
			SectionID = i;

			for (size_t e = i + 1; e < LinesInFile.size(); e++)
			{
				if (LinesInFile[e].find('[') != -1)
					break;

				std::string SpacelessOption = removeSpaces(LinesInFile[e]);
				size_t EqualOccurance = std::count(SpacelessOption.begin(), SpacelessOption.end(), '=');

				if (EqualOccurance > 1 || EqualOccurance <= 0)
				{
					LastError = UNK_ERROR;
					ShouldEndSearch = true;
					break;
				}

				std::vector<std::string> Options = split(SpacelessOption, '=');



				if (Options.size() == 2 && (Options[1].length() >= 4 && Options[1].length() <= 6))
				{
					if (Options[0] == std::string(Option))
					{

						std::string NewValue = std::string(Value);
						NewValue.append("\xD");

						std::string NewOption = Options[0] + " = " + NewValue;
						LinesInFile[e] = NewOption;

						LastError = SUCCESS;

						ShouldEndSearch = true;
						break;
					}
				}
				else
				{
					LastError = UNK_ERROR;
					ShouldEndSearch = true;
					break;
				}
			}
			break;
		}
		if (ShouldEndSearch)
			break;
	}

	if (LastError == NO_OPTION_FOUND && SectionID != -1)
	{
		int Count = this->GetSectionItemCount(Section) + 1;

		std::string NewValue = std::string(Value);
		NewValue.append("\xD");
		LinesInFile.insert(LinesInFile.begin() + SectionID + Count, std::string(Option) + " = " + NewValue);
	}

	if (LastError == NO_OPTION_FOUND && SectionID == -1)
	{
		LinesInFile.insert(LinesInFile.begin() + LinesInFile.size(), "[" + std::string(Section) + "]");

		std::string NewValue = std::string(Value);
		NewValue.append("\xD");

		LinesInFile.insert(LinesInFile.begin() + LinesInFile.size(), std::string(Option) + " = " + NewValue);
	}
}
INI::INI(const char* Path, bool IgnoreFileExist)
{
	MemoryBuffer LocalInstance;
	IniPointer = NULL;
	IniLength = 0;
	strcpy_s(this->INIPath, Path);
	isPopulated = false;
	FoundFile = false;

	if (CReadFile(this->INIPath, LocalInstance)) {

		FoundFile = true;


		IniLength = LocalInstance.GetDataLength() + 1;
		IniPointer = (char*)malloc(IniLength);

		memset(IniPointer, 0, IniLength);

		memcpy(IniPointer, LocalInstance.GetData(), IniLength);

		isPopulated = true;

		std::stringstream AllFile(IniPointer);
		std::string segment;

		std::vector<int> IdsToDelete;

		while (std::getline(AllFile, segment, '\n'))
		{
			if (segment.length() > 1)
				LinesInFile.push_back(segment);
		}

		LastError = FILE_READ;

		for (int i = 0; i < LinesInFile.size(); i++)
		{
			if (LinesInFile[i][0] == '[')
			{
				std::string SpacelessOption = removeSpaces(LinesInFile[i]);

				size_t OpenBracket = std::count(SpacelessOption.begin(), SpacelessOption.end(), '[');
				size_t CloseBracket = std::count(SpacelessOption.begin(), SpacelessOption.end(), ']');

				if (OpenBracket > 1 || CloseBracket > 1) {

					LastError = UNK_ERROR;
					IdsToDelete.push_back(i);

					continue;
				}

			}
			else
			{
				std::string SpacelessOption = removeSpaces(LinesInFile[i]);

				size_t EqualOccurance = std::count(SpacelessOption.begin(), SpacelessOption.end(), '=');

				if (EqualOccurance > 1 || EqualOccurance <= 0)
				{

					LastError = UNK_ERROR;
					IdsToDelete.push_back(i);

					continue;
				}

				std::vector<std::string> Options = split(SpacelessOption, '=');

				if (Options.size() != 2)
				{

					LastError = UNK_ERROR;
					IdsToDelete.push_back(i);
					continue;
				}

				if ((Options[1].find("true") == -1) && (Options[1].find("false") == -1))
				{

					LastError = UNK_ERROR;
					IdsToDelete.push_back(i);

					continue;

				}
				else if (Options[1].length() < 4 || Options[1].length() > 6)
				{

					LastError = UNK_ERROR;
					IdsToDelete.push_back(i);

					continue;
				}
			}
		}

		std::vector<std::string> tempLinesInFile;

		for (int e = 0; e < IdsToDelete.size(); e++)
		{
			LinesInFile[IdsToDelete[e]] = "";
		}

		for (int i = 0; i < LinesInFile.size(); i++) {

			if (LinesInFile[i] != "")
				tempLinesInFile.push_back(LinesInFile[i]);
		}


		LinesInFile = tempLinesInFile;
	}
	else
		LastError = NO_FILE_READ;

	if (IgnoreFileExist)
	{
		LastError = FILE_READ;
		isPopulated = true;
	}
}

INI::~INI()
{
	LastError = (INI_ERRORS)0;
	if (IniPointer)
	{
		free(IniPointer);
		IniPointer = NULL;
	}

	isPopulated = false;
}