// Win2MFC.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win2MFC.h"

class myApplication:public CWinApp
{
	BOOL InitInstance()//此处添加断点，查看调用堆栈，是操作系统调用WinMain()函数，在winMain函数中调用InitInstance()函数
	{
		AfxMessageBox(_T("这是一个纯手写的MFC应用程序"));
		return TRUE;
	}
};

myApplication theApp;//创建一个应用程序对象


/*
 *1.新建一个win32项目，删除主函数中的所有代码，添加上述内容
 *	从CWinApp类派生出一个应用程序类
 *	使用应用程序类定义全局变量theApp
 *2.在预定义头文件stdafx.h删除windows.h头文件，然后添加mfc头文件
 *3. 在项目--属性中设置--“在静态库中使用MFC”
 *4.在CWinApp派生类中重写InitInstance函数作为程序启动代码。
 *
 *InitInstance()函数是虚函数，每个应用程序类都需要重写，pThread是只想theApp全局变量的指针变量
 *pThread->InitInstance()会自动调用到派生类中，这里是多态。
 */