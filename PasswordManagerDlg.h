
// PasswordManagerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Des.h"


// CPasswordManagerDlg 对话框
class CPasswordManagerDlg : public CDialogEx
{
// 构造
public:
	CPasswordManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PASSWORDMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void updateButtonState();
	void resetDesc();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton mType;
	eDES_OpType mOpType;
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnDropDownButton1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnStnClickedDesc();
	afx_msg void OnEnChangeEdit1();
	CEdit mPassword;

	static const char* mTip;
	afx_msg void OnEnSetfocusEdit1();
	CEdit mDescribe;
	afx_msg void OnBnClickedButton2();
};
