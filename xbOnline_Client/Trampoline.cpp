#include "main.h"

Tampoline* Tramps;

//int Tampoline::CallFunction(int FunctionID, long long Param1, long long Param2, long long Param3, long long Param4, bool ping)
//{
//	void* ptr = ResolveFunction(FunctionID);
//
//	if (ping)
//		return ((int(*)(...))ptr)(Param1, Param2, Param3, Param4);
//	else
//		return CallFunction((int)FunctionID, Param1, Param2, Param3, Param4, true);
//
//	return 0;
//}
int Tampoline::CallFunction(int FunctionID, long long Param1, long long Param2, long long Param3, long long Param4, bool ping)
{
	void* ptr = ResolveFunction(FunctionID);

	if (ping)
		return ((int(*)(...))ptr)(Param1, Param2, Param3, Param4);
	else
		//CallFunc(FunctionID, Param1, Param2, Param3, Param4, 1, 0,0);
		return CallFunction((int)FunctionID, Param1, Param2, Param3, Param4, true);

	return 0;
}

void Tampoline::RegisterFunction(int Address, int ID)
{
	RegisterCount++;

	this->Address.resize(RegisterCount + 1);

	long long address = Address;
	address = (address << 32) | ID;

	this->Address[RegisterCount] = address;
}

void* Tampoline::ResolveFunction(int ID)
{
	for (int i = 0; i <= RegisterCount; i++)
	{
		if (ID == (this->Address[i] & 0xFFFFFFFF)) {
			return (void*)(this->Address[i] >> 32);
		}
	}
	return (void*)-1;
}

Tampoline::Tampoline()
{
	RegisterCount = 0;
}
