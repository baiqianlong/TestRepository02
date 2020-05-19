

#include<windows.h>
#include <stdio.h>
#include "resource.h"

//登录对话框的回调函数
INT_PTR CALLBACK LogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
);

INT_PTR CALLBACK MSGProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
);




int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,//A handle to the current instance of the application
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,//The command line for the application, excluding the program name. To retrieve the entire command line, use the GetCommandLine function.
	_In_  int nCmdShow
)
//这是主函数
{
	//创建登录对话框
	
	if((DialogBox(hInstance, MAKEINTRESOURCE(104), NULL, LogProc))==IDCANCEL)
	{
		return 0;//当登录对话框点击取消按钮，退出程序
	}
	//创建一个对话框
	DialogBox(hInstance, MAKEINTRESOURCE(101), NULL, MSGProc);

	
	return 0;
}


INT_PTR CALLBACK MSGProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)//对话框窗口过程函数
{
	switch (uMsg)
	{
	case WM_INITDIALOG://如果case里面定义了语句必须加{}
		{
			//还没有显示出来对话框，初始化
			//设置对话框位置居中
			RECT rect;
			GetWindowRect(hwndDlg, &rect);
			int cx = GetSystemMetrics(SM_CXFULLSCREEN);
			int cy = GetSystemMetrics(SM_CYFULLSCREEN);//获取全屏幕的高和宽
			//左上角坐标
			int x = (cx - rect.right) / 2;//屏幕的宽度减去对话框的宽度/2
			int y = (cy - rect.bottom) / 2;

			MoveWindow(hwndDlg, x, y, rect.right , rect.bottom, FALSE);


			SetWindowText(hwndDlg, LPCSTR("INITDIALOG更改对话框的标题"));
			break;
		}
	case WM_CLOSE:
		//系统关闭消息alt+F4,或者右上角的X号
		EndDialog(hwndDlg, IDCANCEL);
	case WM_LBUTTONDOWN://左键点击出来
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			char s[128];
			sprintf_s(s, "点击的x=%d,y=%d", x, y);
			SetWindowText(hwndDlg, LPCSTR(s));//在标题栏上显示出来

			break;		
		}//鼠标左键单击消息，坐标隐藏在lParam中
	case WM_MOUSEMOVE://鼠标移动消息
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		char s[128];
		sprintf_s(s, "移动时候的x=%d,y=%d", x, y);
		//判断是否按下ctrl键
		if(wParam&MK_CONTROL)
		{
			strcat_s(s, "--按下了ctrl键+");
		}
		//判断是否按下了shift键
		if (wParam&MK_SHIFT)
		{
			strcat_s(s, "--按下了shift键+");
		}
		SetWindowText(hwndDlg, LPCSTR(s));//在标题栏上显示出来
		break;
		}

	
		
	case WM_COMMAND://按钮，快捷键，鼠标点击按钮消息。F12查看消息类型
		if(LOWORD(wParam)==IDCANCEL)
		{
			EndDialog(hwndDlg, IDCANCEL);
		}
		if(LOWORD(wParam)==IDOK)
		{
			//MessageBox(hwndDlg, LPCSTR("点击了确定按钮"), LPCSTR("提示"), MB_OK);
		}
	}
	
	return FALSE;
}

//登录对话框的回调函数
INT_PTR CALLBACK LogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		if(LOWORD(wParam)==IDCANCEL)//取消按钮结束对话框
		{
			EndDialog(hwndDlg, IDCANCEL);
		}
		if (LOWORD(wParam) == IDOK)//点击登录按钮来登录，结束本对话框，显示程序对话框
		{
			//判断用户名和密码是否正确
			char sName[128];
			char sPasswd[128];
			GetDlgItemText(hwndDlg, IDC_NAME, sName, 128);
			GetDlgItemText(hwndDlg, IDC_PASSWD, sPasswd, 128);
			//用户名和密码是否正确
			if (strcmp(sName,"admin") || strcmp(sPasswd,"123456"))//相同时，返回值都是0
			{
				MessageBox(hwndDlg, LPCSTR("密码或者用户名错误"), LPCSTR("错误提示"), MB_OK);
			}
			else
			{
				EndDialog(hwndDlg, IDOK);
				
			}
			break;	
			
		}

		//获取焦点图标
	case WM_SETFOCUS:
		SetDlgItemText(hwndDlg, IDC_STATUS, LPCSTR("请输入用于名和密码"));
		return TRUE;
		
	}
	
	return FALSE;//用户处理过的消息都返回TRUE,用户没有处理的消息都返回FALSE，操作系统内核默认处理
}


/*
 *在对话框消息中，wParam和lParam中参数经常用于表示不同的消息，
 *如在WM_RBUTTONDOWN中wParam用于表示是否按住某一个键盘键，lParam用于传递坐标的xy。
 *
 *2.小写的bool类型是c++中的类型，占有1个字节。BOOL类型是Visual C++的类型，占有4个字节。
 *
 *3.组合使用|与运算，判断是否按下使用&与运算
 *
 *GetSystemMetrics()函数获取操作系统的窗口，屏幕的系统度量信息
 *
 *添加登录对话框
 *
 *
*/

