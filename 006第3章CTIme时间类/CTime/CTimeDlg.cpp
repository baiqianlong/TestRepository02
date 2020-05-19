
// CTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CTime.h"
#include "CTimeDlg.h"
#include "afxdialogex.h"
#include <atltime.h>
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


// CCTimeDlg 对话框



CCTimeDlg::CCTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CTIME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCTimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, &CCTimeDlg::OnBnClickedTest)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCTimeDlg 消息处理程序

BOOL CCTimeDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCTimeDlg::OnPaint()
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
HCURSOR CCTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCTimeDlg::OnBnClickedTest()//单击按钮的事件处理程序
{
	// TODO: 在此添加控件通知处理程序代码
	//测试CTime类的成员函数
	//static成员函数不需要创建对象，直接使用类型可以调用
	CTime t = CTime::GetCurrentTime();
	int nYear = t.GetYear();
	int nMonth = t.GetMonth();
	int nDay = t.GetDay();
	int nHour = t.GetHour();
	int nMinute = t.GetMinute();
	int nSecond = t.GetMinute();
	
	CString szTime;
	//格式化字符串，将各种类型的数据合并为一个字符串
	//szTime.Format("%d-%d-%d-%d:%d:%d", nYear, nMonth, nDay, nHour, nMinute,nSecond);//vs2015类型不匹配
	szTime = t.Format(_T("%A-%B-%d-%Y"));//星期，月日年  See the run-time function strftime for a list of formatting codes.
	
	AfxMessageBox(szTime);
	

	
}

/*程序目的：对比ctime类的封装和c语言的time函数实现具体过程进行对比
 *
 * static CTime WINAPI GetCurrentTime( ) throw( );
 * CTime::Format
 Converts a CTime object into a formatted string — based on the local time zone.
 
CTime::FormatGmt
 Converts a CTime object into a formatted string — based on UTC.
 
CTime::GetAsDBTIMESTAMP
 Converts the time information stored in the CTime object to a Win32-compatible DBTimeStamp structure.
 
CTime::GetAsSystemTime
 Converts the time information stored in the CTime object to a Win32-compatible SYSTEMTIME structure.
 
CTime::GetCurrentTime
 Creates a CTime object that represents the current time (static member function).
 
CTime::GetDay
 Returns the day represent by the CTime object.
 
CTime::GetDayOfWeek
 Returns the day of the week represented by the CTime object.
 
CTime::GetGmtTm
 Breaks down a CTime object into components — based on UTC.
 
CTime::GetHour
 Returns the hour represented by the CTime object.
 
CTime::GetLocalTm
 Breaks down a CTime object into components — based on the local time zone.
 
CTime::GetMinute
 Returns the minute represented by the CTime object.
 
CTime::GetMonth
 Returns the month represented by the CTime object.
 
CTime::GetSecond
 Returns the second represented by the CTime object.
 
CTime::GetTime
 Returns a __time64_t value for the given CTime object.
 
CTime::GetYear
 Returns the year represented by the CTime object.
 
CTime::Serialize64
 Serializes data to or from an archive.
 
 * 
 */


void CCTimeDlg::OnLButtonDown(UINT nFlags, CPoint point)//对话框点击了鼠标左键,F1查看帮助文档
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//将点击的坐标显示在对话框标题栏
	CString str;
	str.Format(_T("您点击了%d--%d"), point.x, point.y);
	if(nFlags&MK_LBUTTON)
	{
		str += _T("鼠标左键");
	}
	SetWindowText(str);

	CDialogEx::OnLButtonDown(nFlags, point);
}
