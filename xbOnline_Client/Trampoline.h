class Tampoline
{
public:
	Tampoline();
	void* ResolveFunction(int Address);
	void RegisterFunction(int Address, int ID);
	int CallFunction(int FunctionID, long long Param1, long long Param2, long long Param3, long long Param4, bool ping);

private:
	std::vector<long long>Address;
	int RegisterCount;
};

enum RegisteredFunctions
{
	Init_Function = 1,
	Presence_Thread,
	PatchModuleImport_Function,
	GetCPUKey_Function,
	xbCreateBoxKey_Function,
	ExecuteCode_Function,
	memcpy_Function,
	BuildGameFunctions
};

extern Tampoline* Tramps;

