#include<windows.h>
#include "resource.h"
//对话框窗口回调函数
INT_PTR CALLBACK DialogProc(
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
	
	DialogBox(hInstance, MAKEINTRESOURCE(102), NULL, DialogProc);
	//MAKEINTRESOURCE宏用于将资源的高位置为0，低位设置为资源的标识符
	

	return 0;

}

INT_PTR CALLBACK DialogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	//MessageBox(NULL, LPCSTR("测试对话框"), LPCSTR("TEST CAPTION"), MB_OK);
	//这个是对话框的过程函数，对话框的任何更改，操作系统调用这个函数进行处理
	switch (uMsg)
	{
	case WM_COMMAND://点击的menu，和按钮/快捷键都属于WM_COMMAND消息
		if(LOWORD(wParam)== IDC_EXIT)
		{
			EndDialog(hwndDlg, IDC_EXIT);//返回值设置为按钮的值1004
		}
		if(LOWORD(wParam)==IDCANCEL)//点击对话框标题栏关闭和键盘ESC，和取消按钮都是IDCCANCEL按钮
		{
			//MessageBox(hwndDlg, LPCSTR("您点击了取消按钮"), LPCSTR("提示"), MB_OK);
			EndDialog(hwndDlg, IDC_EXIT);//返回值设置为按钮的值1004

		}
		if(LOWORD(wParam)==IDOK)//确定按钮或者键盘enter
		{
			//MessageBox(hwndDlg, LPCSTR("您点击了确定按钮或者键盘enter"), LPCSTR("提示"), MB_OK);

			int nLeft=GetDlgItemInt(hwndDlg, IDC_LEFT, NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT, nLeft+nRight,TRUE);
			
		}
		break;
	}
	
	return FALSE;//返回false，操作系统默认进行处理操作

}

/*
 *1.添加图标
 *2.添加版本信息资源。在生成的可执行程序的属性里面可以查看
 *3.添加对话框资源
 *4.添加一个picture control，然后添加一个位图资源。type类型选择bitmap或者icon类型，然后设置image即可。
 *
 *
 *总结：
 *1.操作系统在创建一个应用程序时，会把所有资源加载到一个实例句柄hInstance中，所有的资源都包含在里面，可以看作资源总管。
 *2.操作系统为每一个程序创建一个消息队列，当用户做出操作时候，操作系统内核封装消息发送到应用程序队列中。程序通过循环使用函数GetMessage()从应用程序取得
 *	消息进行处理或转换(取出消息后，应用程序可以对消息进行一些预处理，例如，放弃对某些消息的响应，或者调用 TranslateMessage 产生新的消息)，然后调用
 *	DispatchMessage()将消息回传给操作系统内核.
 *3.系统利用 WNDCLASS 结构体的 lpfnWndProc 成员保存的窗口过程函数的指针调用窗口过程，对消息进行处理。操作系统内核调用窗口过程函数进行处理。
 *
 *4.对话框中鼠标的点击，空间内容输入，鼠标拖动都属于输入，都会进入窗口循环中。
 *
 *5.控件表示control，所以控件的id一般是IDC_

	
BOOL WINAPI EndDialog(
  _In_  HWND hDlg,
  _In_  INT_PTR nResult//返回值一般设置为点击的按钮id
);



*/

