#pragma once

typedef struct _KINTERRUPT {
	void * ServiceRoutine; // function *
	void * ServiceContext;
	DWORD SpinLock;
	DWORD ServiceCount;
	BYTE BusIrql;
	BYTE Irql;
	BYTE Connected : 1; // this bitfield may need swapping
	BYTE Mode : 7;
	BYTE TargetNumber;
} KINTERRUPT, *PKINTERRUPT; // 20

typedef struct _KTRAP_FRAME {
	STACK_FRAME_HEADER Header;
	ULONGLONG Gpr0;
	ULONGLONG Gpr1;
	ULONGLONG Gpr2;
	ULONGLONG Gpr3;
	ULONGLONG Gpr4;
	ULONGLONG Gpr5;
	ULONGLONG Gpr6;
	ULONGLONG Gpr7;
	ULONGLONG Gpr8;
	ULONGLONG Gpr9;
	ULONGLONG Gpr10;
	ULONGLONG Gpr11;
	ULONGLONG Gpr12;
	ULONGLONG Gpr13;
	ULONGLONG Gpr14;
	ULONGLONG Gpr15;
	ULONGLONG Gpr16;
	ULONGLONG Gpr17;
	ULONGLONG Gpr18;
	ULONGLONG Gpr19;
	ULONGLONG Gpr20;
	ULONGLONG Gpr21;
	ULONGLONG Gpr22;
	ULONGLONG Gpr23;
	ULONGLONG Gpr24;
	ULONGLONG Gpr25;
	ULONGLONG Gpr26;
	ULONGLONG Gpr27;
	ULONGLONG Gpr28;
	ULONGLONG Gpr29;
	ULONGLONG Gpr30;
	ULONGLONG Gpr31;
	union {
		struct {
			BYTE OldIrql;
			PKINTERRUPT InterruptObject;
			BYTE InterruptIrql;
		} asIrq;
		BYTE ExceptionRecord[80];
	};
	ULONGLONG Ctr;
	DWORD Lr;
	DWORD Iar;
	DWORD Cr;
	DWORD Msr;
	DWORD Xer;
	DWORD UserModeControl;
} KTRAP_FRAME, *PKTRAP_FRAME; // 448


extern DWORD XamChallengeSize, XoscChallengeSize ;
extern BYTE LastChallengeBufferXosc[ 0x1000 ];
extern BYTE LastChallengeBufferXam[ 0x1000 ];

extern DWORD CheckXamChallengeSize, CheckXoscChallengeSize;
extern BYTE CheckLastChallengeBufferXosc[ 0x1000 ];
extern BYTE CheckLastChallengeBufferXam[ 0x1000 ];




void SetUpHandler();


