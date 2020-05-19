
// TimerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimerDlg 对话框



CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTimerDlg 消息处理程序

BOOL CTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//安装定时器,定时器的编号为1，时间为1000ms，向操作系统发送过一个WM_TIMER信号，调用OnTimer()函数
	SetTimer(1, 1000, NULL);


	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerDlg::OnTimer(UINT_PTR nIDEvent)//定时器消息
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//nIDEvent是定时器的编号，对不同的定时器使用不同的处理，需要判定(每个定时器发送的消息都是通过nIDEvent来接受的)
	if(nIDEvent==1)
	{
		CTime t = CTime::GetCurrentTime();//静态成员函数
		CString str;
		str.Format(_T("%d年-%d月-%d日-%d时-%d分-%d秒"), t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
		SetDlgItemText(IDC_EDIT1, str);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
/*
 * UINT_PTR SetTimer(
   UINT_PTR nIDEvent,
   UINT nElapse,
   void (CALLBACK* lpfnTimer
)(HWND,
   UINT,
   UINT_PTR,
   DWORD
) 
);
UINT_PTR SetTimer(
   UINT_PTR nIDEvent,
   UINT nElapse,
   void (CALLBACK* lpfnTimer
)(HWND,
   UINT,
   UINT_PTR,
   DWORD
) 
);

参数
--------------------------------------------------------------------------------

nIDEvent 
指定一个非零计时器标识符。 如果计时器标识符是唯一的，此相同值由 SetTimer返回。 否则， SetTimer 确定一个新的唯一值并返回它。 传递给具有NULL回调函数)的windows计时器(，该值必须是唯一的为与当前窗口中的其他windows计时器。 为回调计时器，该值必须是唯一的。所有的所有计时器处理。 因此，那么，当您创建回调计时器时，可能更大的返回值将可能与您指定的值不同。

nElapse 
以毫秒为单位指定超时值或间隔。

lpfnTimer 
指定处理 WM_TIMER 消息由应用程序提供的 TimerProc 回调函数的地址。 如果此参数是 NULL， WM_TIMER 消息在应用程序的消息队列放置并按 CWnd 对象的过程。

返回值
--------------------------------------------------------------------------------

新计时器的计时器标识符，如果函数运行成功。 此值可能存在也可能不与该值通过 nIDEvent 参数。 应用程序应始终通过将值返回给 KillTimer 成员函数杀害计时器。 非零，如果成功;否则，0。

 */