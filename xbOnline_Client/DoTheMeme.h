

extern "C"
{
	NTSTATUS NtSetSystemTime(
		PFILETIME SystemTime,  // LARGE_INTEGER
		PFILETIME PreviousTime // LARGE_INTEGER
	);
}

NTSTATUS doWriteFlashFileInternal(BYTE* buffer, char* fileName, DWORD len);

void WriteDank();