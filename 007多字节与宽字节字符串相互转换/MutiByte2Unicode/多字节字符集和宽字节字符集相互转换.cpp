#include<windows.h>
#include<tchar.h>
int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,//A handle to the current instance of the application
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,//The command line for the application, excluding the program name. To retrieve the entire command line, use the GetCommandLine function.
	_In_  int nCmdShow
)
//这是主函数
{
	//宽字节字符集
	wchar_t *p1 = L"中国";//宽字节字符集
	TCHAR *p2 = L"计算机组成原理";//TCHAR自适应字符集，在不同的字符集上TCHAR表示不同的字符集。w_char 和char
	TCHAR *p3 = _TEXT("哈哈哈哈哈");//将常量转换为自适应字符集--推荐使用



	////1.Unicode下CString转换为char *
	////方法一： 使用API：WideCharToMultiByte进行转换
	//	CString str = _T("你好，世界！Hello,World");
	////注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	//int n = str.GetLength();
	////获取宽字节字符的大小，大小是按字节计算的
	//int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	////为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	//char * pFileName = new char[len + 1];   //以字节为单位
	//										//宽字节编码转换成多字节编码
	//WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), pFileName, len, NULL, NULL);
	//pFileName[len + 1] = ‘\0‘;   //多字节字符以’\0′结束

	//方法二：使用函数：T2A、W2A
	//	CString str = _T("你好，世界！Hello,World");
	////声明标识符
	//USES_CONVERSION;
	////调用函数，T2A和W2A均支持ATL和MFC中的字符转换
	//char * pFileName = T2A(str);
	////char * pFileName = W2A(str); //也可实现转换

	//注意：有时候可能还需要添加引用#include
	//	2、Unicode下char *转换为CString

	//	方法一：使用API：MultiByteToWideChar进行转换
	//	char * pFileName = "你好，世界！Hello,World";
	////计算char *数组大小，以字节为单位，一个汉字占两个字节
	//int charLen = strlen(pFileName);
	////计算多字节字符的大小，按字符计算。
	//int len = MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, NULL, 0);
	////为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
	//TCHAR *buf = new TCHAR[len + 1];
	////多字节编码转换成宽字节编码
	//MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, buf, len);
	//buf[len] = ‘\0‘; //添加字符串结尾，注意不是len+1
	//				 //将TCHAR数组转换为CString
	//CString pWideChar;
	//pWideChar.Append(buf);
	////删除缓冲区
	//delete[]buf;


	//Unicode与多字节字符集转换
	
}

/*1.多字节字符集
 *各国在 ASCII的基础上制定了自己的字符集，这些从ANSI标准派生的字符集被习惯的统称为ANSI字符集，
 *它们正式的名称应该是MBCS(Multi-Byte Chactacter System，即多字节字符系统)
 *
 *2unicode字符集
 *　Unicode的学名 是"Universal Multiple-Octet Coded Character Set"，简称为UCS.
 *nicode字符集有多种编码形式，它固定使用16 bits（两个字节、一个字）来表示一个字符，共可以表示65536个字符。
 *
 *L是用来标志一个字符(串)为宽字符(串)，而在Unicode方式下，则要对字符(串)常量前添加L来告诉编译器它是宽字符。MS为我们定义了好几个相关的宏：_T（定义于tchar.h）、_TEXT（同样定义于tchar.h）。
　　TEXt()：如果定义了Unicode，标识字符为Unicode;否则，为ANSI字符集。
 *
 *
 *windows为多字节和宽字节提供了两套api函数，分别是--A和——W函数
*/

