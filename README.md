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
   ![image1](img/img1.png)
   ![image2](img/img2.png)

3. **将payload.c转换为纯hex编码**

   1、打开第二步所生成的payload.c
   
   2、复制**引号内**数据(注意！不要复制整个文件，只需要""双引号内的内容)
   
   3、使用在线工具CyberChef将数据转换为纯hex(地址：https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto'))
   ![image3](img/img3.png)
   

4. **LoaderMaker生成新的shellcodeLoader**

   参数如下：
   ![image4](img/img4.png)
      LoaderMaker.exe是生成器
      
      download.dat是CyberChef生成的hex文件
      
      bypassloader.exe是最终我们生成的免杀shellcode加载器
   ```
   LoaderMaker.exe download.dat bypassLoader.exe
   
   ```
   直接执行bypassLoader.exe,上线成功
   ![image5](img/img5.png)
   
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
