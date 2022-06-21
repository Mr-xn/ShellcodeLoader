# ShellcodeLoader

Windows平通用免杀shellcode加载器。

## 功能特点

1. 使用MFC框架编写shellcodeLoader模板；
2. 使用简洁的C++开发LoaderMaker生成器；
3. 截至发布日期，该shellcodeLoader可免杀国内外主流杀毒软件；
```
   .--. .-.         .-.  .-.                 .-.      .-.                   .-.           
: .--': :         : :  : :                 : :      : :                   : :           
`. `. : `-.  .--. : :  : :   .--.  .--.  .-' : .--. : :    .--.  .--.   .-' : .--. .--. 
 _`, :: .. :' '_.': :_ : :_ '  ..'' .; :' .; :' '_.': :__ ' .; :' .; ; ' .; :' '_.': ..'
`.__.':_;:_;`.__.'`.__;`.__;`.__.'`.__.'`.__.'`.__.':___.'`.__.'`.__,_;`.__.'`.__.':_;  
                                                                                        
```
## 项目构成
   LoaderMaker.exe(shellcodeloader生成器)
   
   ShellcodeLoader.exe(shellcodeloader模板文件)
## 编译环境

   环境:生成器使用C++实现，加载器使用MFC开发，VS2022静态编译。

   方法:下载源码，使用visual studio进行编译。也可以从[realse](https://github.com/ByPassAVTeam/ShellcodeLoader/releases/)下载release版本直接使用。


## 使用方法

1. **打开生成器查看帮助**

  ```
  C:\>LoaderMaker.exe
 .--. .-.         .-.  .-.                 .-.      .-.                   .-.
: .--': :         : :  : :                 : :      : :                   : :
`. `. : `-.  .--. : :  : :   .--.  .--.  .-' : .--. : :    .--.  .--.   .-' : .--. .--.
 _`, :: .. :' '_.': :_ : :_ '  ..'' .; :' .; :' '_.': :__ ' .; :' .; ; ' .; :' '_.': ..'
`.__.':_;:_;`.__.'`.__;`.__;`.__.'`.__.'`.__.'`.__.':___.'`.__.'`.__,_;`.__.'`.__.':_;

[*]usage:
[*]LoaderMaker.exe <shellcode.c>  <outfile.exe>
[*]example:
[*]LoaderMaker.exe shellcode.bin loader.exe

C:\>
```

2. **使用CobaltStrike生成payload.c文件**

   1、点击生成payload
   

3. **将payload.c转换为纯hex编码**

   

4. **LoaderMaker生成新的shellcodeLoader**

   xxx

   
## 部分免杀效果展示

 **火绒**
VT检测效果
[图]

 **360**
[图]

 **腾讯电脑管家**
VT检测效果
[图]

 **Windows Defender**
VT检测效果
[图]

 **金山毒霸**
VT检测效果
[图]
