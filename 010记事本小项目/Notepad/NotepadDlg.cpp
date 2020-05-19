
// NotepadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Notepad.h"
#include "NotepadDlg.h"
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


// CNotepadDlg 对话框



CNotepadDlg::CNotepadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT, m_edit);
}

BEGIN_MESSAGE_MAP(CNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, &CNotepadDlg::OnFileExit)
	ON_WM_DROPFILES()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_EDIT_CLEAR, &CNotepadDlg::OnEditClear)
	ON_COMMAND(ID_EDIT_COPY, &CNotepadDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CNotepadDlg::OnEditCut)
	ON_COMMAND(ID_EDIT_DATA, &CNotepadDlg::OnEditData)
	ON_COMMAND(ID_EDIT_FIND, &CNotepadDlg::OnEditFind)
	ON_COMMAND(ID_EDIT_FIND_NEXT, &CNotepadDlg::OnEditFindNext)
	ON_COMMAND(ID_EDIT_PASTE, &CNotepadDlg::OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, &CNotepadDlg::OnEditUndo)
	ON_COMMAND(ID_EIDT_GOTO, &CNotepadDlg::OnEidtGoto)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CNotepadDlg::OnEditSelectAll)
END_MESSAGE_MAP()


// CNotepadDlg 消息处理程序

BOOL CNotepadDlg::OnInitDialog()
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

	//设置用户自定义的图标
	
	
	// TODO: 在此添加额外的初始化代码

	

	//设置窗口控件随着窗口大小变换
	CWnd*p = GetDlgItem(IDC_TEXT);
	RECT rect;
	GetClientRect(&rect);
	p->MoveWindow(&rect, FALSE);

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)//系统命令消息，最大化，最小化，关闭，改变大小等消息
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

void CNotepadDlg::OnPaint()
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
HCURSOR CNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotepadDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//注释，默认去掉回车键关闭窗口
	CDialogEx::OnOK();
}


void CNotepadDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//注释，默认去掉ESC关闭窗口
	CDialogEx::OnCancel();
}


void CNotepadDlg::OnFileExit()//菜单-文件-退出的消息处理函数
{
	// TODO: 在此添加命令处理程序代码
	EndDialog(ID_APP_EXIT);//退出应用程序
}


void CNotepadDlg::OnDropFiles(HDROP hDropInfo)//拖动文件到对话框，产生的WM_DROPFILE消息处理函数
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	TCHAR sFile[256];
	int nCount = DragQueryFile(hDropInfo, 0, sFile, _countof(sFile));
	CFile file;//打开文件可能是非Unicode，这里需要设置
	if(!file.Open(sFile,CFile::modeRead))
	{
		AfxMessageBox(_T("打开文件失败，请检查文件是否存在"));
		return;
	}
	TCHAR buffer[256];
	UINT nRet = 0;
	CString str;
	while (nRet = file.Read(buffer, sizeof(buffer)-1))
	{
		buffer[nRet] = _T('\0');//读的文件加上\0
		str += buffer;
		
	}
	SetDlgItemText(IDC_TEXT,str);
	file.Close();
	
	
	
	CDialogEx::OnDropFiles(hDropInfo);
}


void CNotepadDlg::OnSize(UINT nType, int cx, int cy)//当点击最大最小按钮或者改变串口大小时，会发送WM_SIZE消息，
{//使控件随着窗口大小变换
	
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//设置窗口控件随着窗口大小变换
	CWnd*p = GetDlgItem(IDC_TEXT);
	if(p)
	{
		RECT rect;
		GetClientRect(&rect);
		p->MoveWindow(&rect, FALSE);
	}
	
	
}


void CNotepadDlg::OnClose()//系统关闭消息处理函数
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDCANCEL);
	CDialogEx::OnClose();
}


void CNotepadDlg::OnEditClear()//删除功能
{
	// TODO: 在此添加命令处理程序代码
	m_edit.Clear();
}


void CNotepadDlg::OnEditCopy()
{
	// TODO: 在此添加命令处理程序代码
	m_edit.Copy();
}


void CNotepadDlg::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	m_edit.Cut();
}


void CNotepadDlg::OnEditData()//插入时间日期
{
	// TODO: 在此添加命令处理程序代码
	CTime time = CTime::GetCurrentTime();
	CString str = time.Format(_T("%Y年%m月%d日 %H:%M"));
	m_edit.ReplaceSel(str, TRUE);
}


void CNotepadDlg::OnEditFind()
{
	// TODO: 在此添加命令处理程序代码
}


void CNotepadDlg::OnEditFindNext()
{
	// TODO: 在此添加命令处理程序代码
}


void CNotepadDlg::OnEditPaste()//粘贴功能
{
	// TODO: 在此添加命令处理程序代码
	m_edit.Paste();
}


void CNotepadDlg::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	m_edit.Undo();
}


void CNotepadDlg::OnEidtGoto()
{
	// TODO: 在此添加命令处理程序代码
}


void CNotepadDlg::OnEditSelectAll()//全选功能
{
	// TODO: 在此添加命令处理程序代码
	m_edit.SetSel(0, -1);
	m_edit.SetFocus();
}
