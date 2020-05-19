
// StaffDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Staff.h"
#include "StaffDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStaffDlg 对话框



CStaffDlg::CStaffDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STAFF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStaffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStaffDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStaffDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD, &CStaffDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CStaffDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_MODEFY, &CStaffDlg::OnBnClickedModefy)
	ON_BN_CLICKED(IDC_SAVE, &CStaffDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CStaffDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CStaffDlg 消息处理程序

BOOL CStaffDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	//对listControl初始化
	/*
	 * int InsertColumn( 
	   int nCol, 
	   LPCTSTR lpszColumnHeading, 
	   int nFormat = LVCFMT_LEFT, 
	   int nWidth = -1, 
	   int nSubItem = -1  
	);
	 */
	//关联一个控件到变量指针pList中.也可以在对话框中使用右键“关联变量”来添加 列
	CListCtrl*pList = (CListCtrl*)GetDlgItem(IDC_LIST4);//返回的是基类指针，需要强制类型转换
	pList->InsertColumn(0, _T("工号"), LVCFMT_CENTER, 200);
	pList->InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 200);
	pList->InsertColumn(2, _T("工资"), LVCFMT_CENTER, 200);
	pList->InsertColumn(4, _T("雇佣日期"), LVCFMT_CENTER,250);

	//设置列表背景色
	pList->SetOutlineColor(RGB(199,237,208));
	pList->SetBkColor(RGB(199, 237, 208));//当插入文字时候，背景颜色会改变，设置文字颜色即可
	pList->SetTextBkColor(RGB(199, 237, 208));
	pList->SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//设置可以打勾样式,选中全行,表格
	//pList->SetBkImage()//设置背景图片
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStaffDlg::OnPaint()
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
HCURSOR CStaffDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStaffDlg::OnBnClickedOk()//重写ok键，使得回车不退出
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();//注释掉
}


void CStaffDlg::OnBnClickedAdd()//单击添加按钮，添加员工信息
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl*pList = (CListCtrl*)GetDlgItem(IDC_LIST4);//返回的是基类指针，需要强制类型转换

	
	
	//获取EditControl的信息显示到ListControl中
	CString str;
	GetDlgItemText(IDC_NUMBER, str);

	//排除重复的员工号
	int i = 0;
	int nCount = pList->GetItemCount();
	while (i<nCount)
	{
		if (pList->GetItemText(i, 0) == str)
		{
			AfxMessageBox(_T("插入的员工号码重复，请重新输入"));
			//使用ctrl+D键可以查看控件的顺序，点击可以修改。
			SetFocus();//设置焦点在要输入的工号位置
			return;
		}
		i++;
	}
	
	pList->InsertItem(0, str);//插入一行,并设置好第一列

	GetDlgItemText(IDC_NAME, str);//设置好第二列
	pList->SetItemText(0, 1, str);

	GetDlgItemText(IDC_SALARY, str);//设置好第二列
	pList->SetItemText(0, 2, str);

	GetDlgItemText(IDC_DATETIMEPICKER3, str);//设置好第二列
	pList->SetItemText(0, 3, str);
	
	
	/*先使用InsertItem()插入行，然后使用SetItemText()设置子列的内容
	 * BOOL SetItemText( 
	   int nItem, 
	   int nSubItem, 
	   LPCTSTR lpszText  
	);

	 */
}


void CStaffDlg::OnBnClickedDelete()//单击删除按钮
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl*pList = (CListCtrl*)GetDlgItem(IDC_LIST4);//返回的是基类指针，需要强制类型转换
	/*if(!pList->GetSelectedCount())
	{
		AfxMessageBox(_T("请先选中行"));
		return;
		
	}*/
	int nSelect = pList->GetSelectionMark();//获取选中行的标号
	if (nSelect==-1)
	{
		AfxMessageBox(_T("请先选中行"));
	}
	if (AfxMessageBox(_T("您确定要删除吗？"),MB_YESNO)==IDYES)
	{
		pList->DeleteItem(nSelect);

	}
	
	
}


void CStaffDlg::OnBnClickedModefy()//单击修改
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CStaffDlg::OnBnClickedSave()//保存按钮的功能
{
	// TODO: 在此添加控件通知处理程序代码
	//将用户的输入保存到一个文件中
	CFile f;
	CFileException e;
	TCHAR* pszFileName = _T("./Staff_File.txt");
	if (!f.Open(pszFileName, CFile::shareDenyNone | CFile::modeWrite | CFile::modeCreate, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
	}
	
	//test写入数据
	//const char*p1 = "计算机组成原理";
	//f.Write(p1,strlen(p1));
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST4);
	int i = 0, nCount = pList->GetItemCount();
	SData data;
	while (i < nCount)//需要通过一个结构体中转
	{
		data.nNumb = _wtoi(pList->GetItemText(i, 0));
		pList->GetItemText(i, 1, data.sName, _countof(data.sName));
		data.fSala = (float)_wtof(pList->GetItemText(i, 2));
		f.Write(&data, sizeof(data));
		++i;
	}

	
	f.Close();


}


void CStaffDlg::OnBnClickedLoad()//加载文件
{
	// TODO: 在此添加控件通知处理程序代码
	CFile f;
	CFileException e;
	TCHAR* pszFileName = _T("./Staff_File.txt");
	if (!f.Open(pszFileName, CFile::modeRead , &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
		return;
	}

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST4);
	int i = 0, nCount = pList->GetItemCount();
	SData data;
	CString str;
	while (f.Read(&data,sizeof(data))==sizeof(data))//需要通过一个结构体中转
	{
		str.Format(_T("%d"), data.nNumb);
		pList->InsertItem(i, str);
		pList->SetItemText(i, 1, data.sName);
		str.Format(_T("%d"), data.fSala);
		pList->SetItemText(i, 2, str);
		str.Format(_T("%d年%d月%d日"),data.tDate.GetYear(),data.tDate.GetMonth(),data.tDate.GetDay());
		pList->SetItemText(i, 3, str);
		
		++i;
	}
	f.Close();
	
}

//修改的功能实现请参考192  12分钟后