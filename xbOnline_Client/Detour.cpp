#include "main.h"

unsigned char Detour::DetourSection[0xF000] = { 0 };

int Detour::DetourCount = 0;

void __declspec(naked) Detour::GLPR(void)
{
	__asm
	{
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}

void Detour::PatchInJump(unsigned int Address, void* Destination, bool Linked)
{
	if (!Address || !Destination) return;

	unsigned int DestinationAddress = (DWORD)(Destination);

	unsigned int Instructions[4];

	Instructions[0] = 0x3D600000 + ((DestinationAddress >> 16) & 0xFFFF); // lis r11, Destination

	if ((DestinationAddress & 0x8000))
	{
		Instructions[0]++; // No negatives please
	}

	Instructions[1] = 0x396B0000 + (DestinationAddress & 0xFFFF); // addi r11, r11, Destination

	Instructions[2] = 0x7D6903A6; // mtctr r11

	Instructions[3] = 0x4E800420 + Linked; // bctr bctrl

	Tramps->CallFunction(memcpy_Function, (int)Address, (int)Instructions, (sizeof(DWORD) * 4), 0, false);
}

void Detour::DetourFunction(unsigned int Address, void* Destination, void* Stub)
{
	unsigned int StubInstructions[8] = { 0 };
	unsigned int SaveStubAddress = (DWORD)(Stub);
	unsigned int BranchAddress = (Address + 0x10);

	StubInstructions[0] = 0x3D600000 + (BranchAddress >> 16);

	if (BranchAddress & 0x8000)
	{
		StubInstructions[0]++;
	}

	StubInstructions[1] = 0x396B0000 + (BranchAddress & 0xFFFF);

	StubInstructions[2] = 0x7D6903A6;

	CopyOriginalInstructions(Address, SaveStubAddress, (DWORD*)StubInstructions);

	StubInstructions[7] = 0x4E800420;

	Tramps->CallFunction(memcpy_Function, (int)SaveStubAddress, (int)StubInstructions, sizeof(StubInstructions), 0, false);

	PatchInJump(Address, Destination, false);
}

void Detour::CopyOriginalInstructions(unsigned int Address, unsigned int SaveStub, DWORD* StubInstructions)
{
	for (int i = 0; i < 4; i++) //copy the original instructions
	{
		unsigned int InstructionPointer = (Address + (i * 4));
		unsigned int Instruction = *(DWORD*)InstructionPointer;
		unsigned int CurrentStubInstructionPointer = SaveStub + ((i + 3) * 4);

		if ((Instruction & 0x48000003) == 0x48000001)// bl
		{
			StubInstructions[i + 3] = RelinkGPLR(Instruction & ~0x48000003, CurrentStubInstructionPointer, InstructionPointer); //relink GPLR to local
		}
		else
		{
			StubInstructions[i + 3] = Instruction;
		}
	}
}

unsigned int Detour::RelinkGPLR(unsigned int Offset, unsigned int SaveStubAddress, unsigned int OriginalAddress)
{
	unsigned int Instruction = 0;
	unsigned int InstructionToReplace = 0;
	unsigned int GPLRStub = (DWORD)GLPR;

	Offset = Offset & 0x2000000 ? Offset | 0xFC000000 : Offset; // Get the bl offset
	InstructionToReplace = *(DWORD*)(OriginalAddress + Offset); // Get the address // OriginalAddress + Offset = branch address
	for (int i = 0; i < 20; i++)
	{
		if (*(DWORD*)(GPLRStub + (4 * i)) == InstructionToReplace) // Find the instruction from the offset in our stub
		{
			unsigned int NewOffset = ((GPLRStub + (4 * i)) - (int)SaveStubAddress);
			Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
		}
	}
	return Instruction;
}

void Detour::RestoreFunction()
{
	if (Hooked && MmIsAddressValid((void*)Address)) {
		Hooked = false;

		Tramps->CallFunction(memcpy_Function, (int)Address, (int)OriginalBytes, 16, 0, false);
	}
}

void* Detour::HookFunction(unsigned int FuncAddress, unsigned int OurDestination)
{
	if (MmIsAddressValid((void*)FuncAddress))  {
		Hooked = true;
		IndexDetour = DetourCount;

		DetourCount += 32;

		OrStub = (int*)&DetourSection[IndexDetour];

		Address = FuncAddress;

		Tramps->CallFunction(memcpy_Function, (int)OriginalBytes, (int)Address, 16, 0, false);

		DetourFunction((DWORD)Address, (void*)OurDestination, (DWORD*)(DWORD)&OrStub[0]);

		return (void*)(int)&OrStub[0];
	}
	return (void*)-1;
}


void* Detour::HookFunction(PLDR_DATA_TABLE_ENTRY Module, char* ImportedModuleName, unsigned int Ordinal, unsigned int PatchAddress)
{
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);

	VOID* headerBase = Module->XexHeaderBase;

	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL) return (void*)-1;

	unsigned int result = 2;
	char* stringTable = (char*)(importDesc + 1);
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);
	for (unsigned int x = 0; x < importDesc->ModuleCount; x++) {
		unsigned int* importAdd = (unsigned int*)(importTable + 1);
		for (unsigned int y = 0; y < importTable->ImportTable.ImportCount; y++) {
			unsigned int value = *((unsigned int*)importAdd[y]);
			if (value == address) {
				*(int*)((unsigned int*)importAdd[y]) = PatchAddress;

				HookFunction((unsigned int)importAdd[y + 1], PatchAddress);

				result = S_OK;
			}
		}

		importTable = (XEX_IMPORT_TABLE_ORG*)(((unsigned char*)importTable) + importTable->TableSize);
	}
	return (void*)result;
}


void* Detour::HookFunction(char* Module, char* ImportedModuleName, unsigned int Ordinal, unsigned int PatchAddress)
{
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (void*)HookFunction(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);

}
