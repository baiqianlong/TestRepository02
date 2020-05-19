#include<windows.h>

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,//A handle to the current instance of the application
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,//The command line for the application, excluding the program name. To retrieve the entire command line, use the GetCommandLine function.
	_In_  int nCmdShow
)
//这是主函数
{
	//FindWindow函数
	
	HWND nRet = FindWindowW(NULL, LPCWSTR("C:/Users/baixiaolong/Desktop/11.txt - Notepad++"));//通过窗口名字查找窗口
	//如果窗口不存在，则返回值是NULL，查找到窗口则返回窗口句柄
	HWND nRet02 = FindWindowW(LPCWSTR("Notepad++"),NULL);//通过类名查找，点击启动spy++窗口

	
	int msgboxID = MessageBox(
		nRet02,//使用上面查找到的窗口句柄，作为父窗口
		(LPCWSTR)L"Resource not available\nDo you want to try again?",
		(LPCWSTR)L"Account Details",
		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
	);

	switch (msgboxID)
	{
	case IDCANCEL:
		// TODO: add code
		MessageBox(NULL, (LPCWSTR)L"你点击的是取消", (LPCWSTR)L"结果：",MB_CANCELTRYCONTINUE );
		break;
	case IDTRYAGAIN:
		// TODO: add code
		break;
	case IDCONTINUE:
		// TODO: add code
		break;
	}
	
}

/*
 * Messagbox()函数--图标使用高四位，按钮类型使用低4位
 * FindWindow()函数--来获取窗口的句柄
 *
 * 在类视图中右键--“添加”--“资源”--“图标”，就会自动把新图标使用到win32程序中，如果是多个图标，会自动选择id最小的图标
 */

