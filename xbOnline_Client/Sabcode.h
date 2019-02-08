#pragma once

#if defined(DEVKIT)

#else
enum inst_opcodes
{
	inst_lds = 1,
	inst_ldcs = 2,
	inst_ld = 3,
	inst_ldc = 4,
	inst_add = 5,
	inst_addc = 6,
	inst_div = 7,
	inst_divc = 8,
	inst_mul = 9,
	inst_mulc = 10,
	inst_sub = 11,
	inst_subc = 12,
	inst_or = 13,
	inst_orc = 14,
	inst_and = 15,
	inst_andc = 16,
	inst_not = 17,
	inst_notc = 18,
	inst_xor = 19,
	inst_xorc = 20,
	inst_st8c = 21,
	inst_st4c = 22,
	inst_st2c = 23,
	inst_st1c = 24,
	inst_st8 = 25,
	inst_st4 = 26,
	inst_st2 = 27,
	inst_st1 = 28,
	inst_rd8c = 29,
	inst_rd4c = 30,
	inst_rd2c = 31,
	inst_rd1c = 32,
	inst_rd8 = 33,
	inst_rd4 = 34,
	inst_rd2 = 35,
	inst_rd1 = 36,
	inst_nop = 37,
	inst_ret = 38,
	inst_jmp = 39,
	inst_jmpc = 40,
	inst_cmp = 41,
	inst_cmpc = 42,
	inst_ccmpc = 43,
	inst_ccmp = 44,
	inst_call = 45,
	inst_callc = 46,
	inst_cbranch = 47,
	inst_syscall = 48,
	inst_slwc = 49,
	inst_srwc = 50
};

enum inst_branchopcodes
{
	inst_beq = 1,
	inst_bne = 2,
	inst_ble = 3,
	inst_bge = 4,
	inst_bgt = 5,
	inst_blt = 6,
	inst_cbeq = 7,
	inst_cbne = 8,
	inst_cble = 9,
	inst_cbge = 10,
	inst_cbgt = 11,
	inst_cblt = 12
};

struct instruct_finder
{
	std::string inst;
	inst_opcodes opcd;
};

struct instruct_branch_finder
{
	std::string inst;
	inst_branchopcodes opcd;
};

enum registers : unsigned char
{
	r0,
	r1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	r12,
	r13,
	r14,
	r15,
	r16,
	r17,
	r18,
	r19,
	r20,
	r21,
	r22,
	r23,
	r24,
	r25,
	r26,
	r27,
	r28,
	r29,
	r30,
	r31,
};
struct instructionBits
{
	int bits[32];
};


class Instruction
{

public:
	Instruction();
	~Instruction();
	int getValueFromBits(int from, int To);
	void parseInstruction(unsigned int instruction);
	int getnthBit(int data, int nth);
	inst_opcodes getInstructionType();

	signed int getRegister611();
	signed short getRegister622();
	signed int getRegister1116();
	signed int getRegister1621();
	signed short getValue1632();
	signed short getRegister2532();
	signed short getRegister2225();


private:
	instructionBits bits;
};


extern instruct_finder inst_dictionary[49];
extern instruct_branch_finder inst_branch_dictionary[12];

typedef struct _bitConditions
{
	unsigned char GT : 1;
	unsigned char LT : 1;
	unsigned char ET : 1;
	unsigned char padding : 5;
}bitConditions;


typedef union cr
{
	bitConditions states;
	unsigned char cReg;
}_cr;


enum interrupts
{
	PROGRAM_EXIT = 1,
	PROGRAM_RETURN = 2,
	PROGRAM_INST_EXEC = 3,
};

void InitRam();

void InitStack();

void InitRegisters();

extern unsigned char  deviceRam[10000];
extern unsigned char  systemStack[10000];

//Registers
extern unsigned long long lr;
extern unsigned long long ip;
extern unsigned long long r[32];
extern cr crRegs[7];
extern std::vector<unsigned long long> callstack;

interrupts exec_vm(Instruction* parser, unsigned int instruction, unsigned long long * pos);

unsigned long long RunCode(int* Code, int Size);
#endif 

