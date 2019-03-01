#include "main.h"

bool sabaCodeCritial = false;
CRITICAL_SECTION SabcodeSection;

#if defined(DEVKIT)

#else
unsigned char  deviceRam[10000];
unsigned char  systemStack[10000];

//Registers
unsigned long long lr;
unsigned long long ip;
unsigned long long r[32];
std::vector<unsigned long long> callstack;

cr crRegs[7];

void InitRam()
{
	memset(deviceRam, 0, 10000);
}

void InitStack()
{
	memset(systemStack, 0, 10000);
}

void InitRegisters()
{
	for (int i = 0; i < 32; i++)
		r[i] = 0;

	r[1] = (unsigned int)systemStack;

	for (int i = 9; i < 7; i++)
		crRegs[0].cReg = 0;

	lr = 0;
	ip = 0;
}

instruct_finder inst_dictionary[49] = { "lds", inst_lds,
"ldcs", inst_ldcs,
"ld", inst_ld,
"ldc", inst_ldc,
"add", inst_add,
"addc", inst_addc,
"div", inst_div,
"divc", inst_divc,
"mul", inst_mul,
"mulc", inst_mulc,
"sub", inst_sub,
"subc", inst_subc,
"or", inst_or,
"orc", inst_orc,
"and", inst_and,
"andc", inst_andc,
"not", inst_not,
"notc", inst_notc,
"xor", inst_xor,
"xorc", inst_xorc,
"st8c", inst_st8c,
"st4c", inst_st4c,
"st2c", inst_st2c,
"st1c", inst_st1c,
"st8", inst_st8,
"st4", inst_st4,
"st2", inst_st2,
"st1", inst_st1,
"rd8c", inst_rd8c,
"rd4c", inst_rd4c,
"rd2c", inst_rd2c,
"rd1c", inst_rd1c,
"rd8", inst_rd8,
"rd4", inst_rd4,
"rd2", inst_rd2,
"rd1", inst_rd1,
"nop", inst_nop,
"ret", inst_ret,
"jmp", inst_jmp,
"jmpc", inst_jmpc,
"ccmp", inst_ccmp,
"ccmpc", inst_ccmpc,
"cmp", inst_cmp,
"cmpc", inst_cmpc,
"call", inst_call,
"callc", inst_callc,
"syscall", inst_syscall,
"slwc", inst_slwc,
"srwc", inst_srwc };

instruct_branch_finder inst_branch_dictionary[12] = {
	"beq", inst_beq,
	"bne", inst_bne,
	"ble", inst_ble,
	"bge", inst_bge,
	"bgt", inst_bgt,
	"blt", inst_blt,
	"cbeq", inst_cbeq,
	"cbne", inst_cbne,
	"cble", inst_cble,
	"cbge", inst_cbge,
	"cbgt", inst_cbgt,
	"cblt", inst_cblt
};

int Instruction::getnthBit(int data, int nth)
{
	return ((data) >> nth) & 1;
}

int Instruction::getValueFromBits(int from, int To)
{
	int Value = 0;

	for (int i = from; i < To; ++i)
	{
		Value *= 2;
		if (bits.bits[i])
			++Value;
	}
	return Value;
}

void Instruction::parseInstruction(unsigned int instruction)
{
	for (int i = 31; i > -1; i--)
		bits.bits[31 - i] = getnthBit(instruction, i);
}

inst_opcodes Instruction::getInstructionType()
{
	return (inst_opcodes)getValueFromBits(0, 6);
}

int Instruction::getRegister611()
{
	return  getValueFromBits(6, 11);
}

signed short Instruction::getRegister622()
{
	return  getValueFromBits(6, 22);
}

signed short Instruction::getRegister2225()
{
	return  getValueFromBits(22, 25);
}

signed short Instruction::getRegister2532()
{
	return  getValueFromBits(25, 32);
}

signed int Instruction::getRegister1116()
{
	return  getValueFromBits(11, 16);
}

signed int Instruction::getRegister1621()
{
	return  getValueFromBits(16, 21);
}

signed short Instruction::getValue1632()
{
	return  getValueFromBits(16, 32);
}

Instruction::Instruction()
{

}

Instruction::~Instruction()
{

}

void pushLr(unsigned long long lr)
{
	callstack.push_back(lr);
}

unsigned long long popLr()
{
	unsigned long long end = 0;

	if (!callstack.empty()) {

		end = callstack.back();

		callstack.pop_back();
	}
	else
		end = -1;

	return end;
}

void exec_ldc(unsigned long long* r, unsigned long long val)
{
	*r = val;
}

void exec_lds(unsigned long long* ra, unsigned long long* rb)
{
	*ra = (*rb << 16);
}

void exec_ldcs(unsigned long long* ra, unsigned long long value)
{
	*ra = (value << 16);
}

void exec_ld(unsigned long long* ra, unsigned long long* rb)
{
	*ra = *rb;
}

void exec_add(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb + *rc;
}

void exec_addc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb + value;
}

void exec_div(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb / *rc;
}

void exec_divc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb / value;
}

void exec_mul(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb * *rc;
}

void exec_mulc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb * value;
}

void exec_sub(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{

	*ra = *rb - *rc;
}

void exec_subc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb - value;
}

void exec_or(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb | *rc;
}

void exec_orc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb | value;
}

void exec_and(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb & *rc;
}

void exec_andc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb & value;
}

void exec_not(unsigned long long* ra, unsigned long long* rb)
{
	*ra = ~*rb;
}

void exec_notc(unsigned long long* ra, unsigned long long value)
{
	*ra = ~(unsigned long long)value;
}

void exec_xor(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	*ra = *rb ^ *rc;
}

void exec_xorc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = *rb ^ value;
}

void exec_st8c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{

	memcpy((void*)(*rb + value), (void*)ra, 0x8);
}

void exec_st4c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)(*rb + value), (void*)ra, 0x4);
}

void exec_st2c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)(*rb + value), (void*)ra, 0x2);
}

void exec_st1c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)(*rb + value), (void*)ra, 0x1);
}

void exec_st8(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)(*rb + *rc), (void*)*ra, 0x8);
}

void exec_st4(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)(*rb + *rc), (void*)ra, 0x4);
}

void exec_st2(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)(*rb + *rc), (void*)ra, 0x2);
}

void exec_st1(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)(*rb + *rc), (void*)ra, 0x1);
}

void exec_rd8c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)ra, (void*)(*rb + value), 0x8);
}

void exec_rd4c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)ra, (void*)(*rb + value), 0x4);
}

void exec_rd2c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)ra, (void*)(*rb + value), 0x2);

}

void exec_rd1c(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	memcpy((void*)ra, (void*)(*rb + value), 0x1);
}

void exec_rd8(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)ra, (void*)(*rb + *rc), 0x8);

}

void exec_rd4(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)ra, (void*)(*rb + *rc), 0x4);
}

void exec_rd2(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)ra, (void*)(*rb + *rc), 0x2);
}

void exec_rd1(unsigned long long* ra, unsigned long long* rb, unsigned long long* rc)
{
	memcpy((void*)ra, (void*)(*rb + *rc), 0x1);
}

void exec_ccmpc(cr* cr, signed long long* ra, signed short value)
{
	cr->cReg = 0;

	if (*ra == value)
	{
		cr->states.ET = 1;
		return;
	}

	if (*ra > value)
	{
		cr->states.GT = 1;
		return;
	}

	if (*ra < value)
	{
		cr->states.LT = 1;
		return;
	}
}

void exec_ccmp(cr* cr, signed long long* ra, signed long long* rb)
{
	cr->cReg = 0;

	if (*ra == *rb)
	{
		cr->states.ET = 1;
		return;
	}

	if (*ra > *rb)
	{
		cr->states.GT = 1;
		return;
	}

	if (*ra < *rb)
	{
		cr->states.LT = 1;
		return;
	}
}

void exec_cmpc(signed long long* ra, signed short value)
{
	crRegs[0].cReg = 0;

	if (*ra == value)
	{
		crRegs[0].states.ET = 1;
		return;
	}

	if (*ra > value)
	{
		crRegs[0].states.GT = 1;
		return;
	}

	if (*ra < value)
	{
		crRegs[0].states.LT = 1;
		return;
	}
}

void exec_cmp(signed long long* ra, signed long long* rb)
{
	crRegs[0].cReg = 0;

	if (*ra == *rb)
	{
		crRegs[0].states.ET = 1;
		return;
	}

	if (*ra > *rb)
	{
		crRegs[0].states.GT = 1;
		return;
	}

	if (*ra < *rb)
	{
		crRegs[0].states.LT = 1;
		return;
	}
}

void exec_beq(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_bne(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.ET == 0)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_ble(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.LT == 1 || crRegs[0].states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_bge(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.GT == 1 || crRegs[0].states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_blt(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.LT == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_bgt(unsigned long long value, unsigned long long* pos)
{
	if (crRegs[0].states.GT == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cbeq(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cbne(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.ET == 0)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cble(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.LT == 1 || crReg->states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cbge(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.GT == 1 || crReg->states.ET == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cblt(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.LT == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_cbgt(cr* crReg, unsigned long long value, unsigned long long* pos)
{
	if (crReg->states.GT == 1)
		*pos = *pos + (value / 0x4);
	else
		*pos = *pos + 1;
}

void exec_syscall(unsigned long long* ra)
{
	int calladdr = (int)*ra;
	unsigned long long(*function)(...) = (unsigned long long(*)(...))calladdr;
	r[3] = function(r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10]);
}

void exec_slwc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = (*rb << value);
}

void exec_srwc(unsigned long long* ra, unsigned long long* rb, unsigned long long value)
{
	*ra = (*rb >> value);
}

interrupts exec_vm(Instruction* parser, unsigned int instruction, unsigned long long * pos)
{
	interrupts intp = PROGRAM_INST_EXEC;

	parser->parseInstruction(instruction);

	inst_opcodes codes = parser->getInstructionType();

	switch (codes)
	{
	case inst_lds:
		exec_lds(&r[parser->getRegister611()], &r[parser->getRegister1116()]);
		*pos = *pos + 1;
		break;
	case inst_ldcs:
		exec_ldcs(&r[parser->getRegister611()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_ld:
		exec_ld(&r[parser->getRegister611()], &r[parser->getRegister1116()]);
		*pos = *pos + 1;
		break;
	case inst_ldc:
		exec_ldc(&r[parser->getRegister611()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_add:
		exec_add(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_addc:
		exec_addc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_div:
		exec_div(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_divc:
		exec_divc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_mul:
		exec_mul(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_mulc:
		exec_mulc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_sub:
		exec_sub(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_subc:
		exec_subc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_or:
		exec_or(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_orc:
		exec_orc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_and:
		exec_and(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_andc:
		exec_andc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;

		break;

		exec_not(&r[parser->getRegister611()], &r[parser->getRegister1116()]);
		*pos = *pos + 1;
		break;
	case inst_notc:
		exec_notc(&r[parser->getRegister611()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_xor:

		exec_xor(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_xorc:
		exec_xorc(&r[parser->getRegister611()], &r[parser->getRegister1116()], (unsigned short)parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_st8c:
		exec_st8c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_st4c:
		exec_st4c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_st2c:
		exec_st2c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_st1c:
		exec_st1c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_st8:
		exec_st8(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_st4:
		exec_st4(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_st2:
		exec_st2(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_st1:
		exec_st1(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_rd8c:
		exec_rd8c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_rd4c:
		exec_rd4c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_rd2c:
		exec_rd2c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_rd1c:
		exec_rd1c(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_rd8:
		exec_rd8(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_rd4:
		exec_rd4(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_rd2:
		exec_rd2(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_rd1:
		exec_rd1(&r[parser->getRegister611()], &r[parser->getRegister1116()], &r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_nop:
		*pos = *pos + 1;
		break;
	case inst_ret:
	{
		unsigned long long lr = popLr();
		if (lr == -1)
			intp = PROGRAM_EXIT;
		else
			*pos = lr;
		break;
	}
	case inst_jmp:
	{
		signed short signedVal = (signed short)r[parser->getRegister611()];
		*pos = *pos + ((size_t)signedVal / 0x4);
		break;
	}
	case inst_jmpc:
	{
		signed short h = parser->getRegister622();
		*pos = (*pos) + (h / 0x4);

		break;
	}
	case inst_ccmp:
		exec_ccmp(&crRegs[parser->getRegister611()], (signed long long*)&r[parser->getRegister1116()], (signed long long*)&r[parser->getRegister1621()]);
		*pos = *pos + 1;
		break;
	case inst_ccmpc:
		exec_ccmpc(&crRegs[parser->getRegister611()], (signed long long*)&r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_cmp:
		exec_cmp((signed long long*)&r[parser->getRegister611()], (signed long long*)&r[parser->getRegister1116()]);
		*pos = *pos + 1;
		break;
	case inst_cmpc:
		exec_cmpc((signed long long*)&r[parser->getRegister611()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_call:
	{
		pushLr(*pos + 1);
		signed short NewPostion = (((signed short)r[parser->getRegister611()]) + ((signed short)*pos * 0x4)) / 0x4;
		*pos = NewPostion;
		break;
	}
	case inst_callc:
	{
		pushLr(*pos + 1);
		signed short NewPostion = (((signed short)parser->getRegister622()) + (((signed short)*pos) * 0x4)) / 0x4;
		*pos = NewPostion;
		break;
	}
	case inst_cbranch:
	{
		inst_branchopcodes branchcodes = (inst_branchopcodes)parser->getRegister2532();
		switch (branchcodes)
		{
		case inst_beq:
			exec_beq(parser->getRegister622(), pos);
			break;
		case inst_bne:
			exec_bne(parser->getRegister622(), pos);
			break;
		case inst_ble:
			exec_ble(parser->getRegister622(), pos);
			break;
		case inst_bge:
			exec_bge(parser->getRegister622(), pos);
			break;
		case inst_bgt:
			exec_bgt(parser->getRegister622(), pos);
			break;
		case inst_blt:
			exec_blt(parser->getRegister622(), pos);
			break;
		case inst_cbeq:
			exec_cbeq(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		case inst_cbne:
			exec_cbne(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		case inst_cble:
			exec_cble(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		case inst_cbge:
			exec_cbge(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		case inst_cbgt:
			exec_cbgt(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		case inst_cblt:
			exec_cblt(&crRegs[parser->getRegister2225()], parser->getRegister622(), pos);
			break;
		default:
			break;
		}
		break;
	}
	case inst_syscall:
		exec_syscall(&r[parser->getRegister611()]);
		*pos = *pos + 1;
		break;
	case inst_slwc:
		exec_slwc(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;
	case inst_srwc:
		exec_srwc(&r[parser->getRegister611()], &r[parser->getRegister1116()], parser->getValue1632());
		*pos = *pos + 1;
		break;

	default:
		*pos = *pos + 1;
		break;
	}
	return intp;
}


unsigned long long RunCode(int* Code, int Size)
{
	if (!sabaCodeCritial) {

		InitializeCriticalSection(&SabcodeSection);
		sabaCodeCritial = true;
	}

	EnterCriticalSection(&SabcodeSection);
	InitRam();
	InitStack();
	InitRegisters();

	Instruction* parser = new Instruction();

	for (ip = 0; ip < Size;)
	{
		if (exec_vm(parser, Code[(unsigned int)ip], &ip) == PROGRAM_EXIT)
			break;
	}

	delete parser;

	LeaveCriticalSection(&SabcodeSection);

	return r[3];


}
#endif 

void PrintRegister()
{
	printf("r00: 0x%016I64X r01: 0x%016I64X r02: 0x%016I64X r03: 0x%016I64X\n", r[0], r[1], r[2], r[3]);
	printf("r04: 0x%016I64X r05: 0x%016I64X r06: 0x%016I64X r07: 0x%016I64X\n", r[4], r[5], r[6], r[7]);
	printf("r08: 0x%016I64X r09: 0x%016I64X r10: 0x%016I64X r11: 0x%016I64X\n", r[8], r[9], r[10], r[11]);
	printf("r12: 0x%016I64X r13: 0x%016I64X r14: 0x%016I64X r15: 0x%016I64X\n", r[12], r[13], r[14], r[15]);
	printf("r16: 0x%016I64X r17: 0x%016I64X r18: 0x%016I64X r19: 0x%016I64X\n", r[16], r[17], r[18], r[19]);
	printf("r20: 0x%016I64X r21: 0x%016I64X r22: 0x%016I64X r23: 0x%016I64X\n", r[20], r[21], r[22], r[23]);
	printf("r24: 0x%016I64X r25: 0x%016I64X r26: 0x%016I64X r27: 0x%016I64X\n", r[24], r[25], r[26], r[27]);
	printf("r28: 0x%016I64X r29: 0x%016I64X r30: 0x%016I64X r31: 0x%016I64X\n", r[28], r[29], r[30], r[31]);
}



