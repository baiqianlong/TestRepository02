
// NotepadDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CNotepadDlg 对话框
class CNotepadDlg : public CDialogEx
{
// 构造
public:
	CNotepadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnFileExit();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// edit控件关联的成员变量
	CEdit m_edit;
	afx_msg void OnClose();
	afx_msg void OnEditClear();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditData();
	afx_msg void OnEditFind();
	afx_msg void OnEditFindNext();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnEidtGoto();
	afx_msg void OnEditSelectAll();
};
