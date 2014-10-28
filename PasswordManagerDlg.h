
// PasswordManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Des.h"


// CPasswordManagerDlg �Ի���
class CPasswordManagerDlg : public CDialogEx
{
// ����
public:
	CPasswordManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PASSWORDMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
