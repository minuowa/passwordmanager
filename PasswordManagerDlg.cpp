
// PasswordManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PasswordManager.h"
#include "PasswordManagerDlg.h"
#include "afxdialogex.h"
#include "Des.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPasswordManagerDlg 对话框



CPasswordManagerDlg::CPasswordManagerDlg ( CWnd* pParent /*=NULL*/ )
    : CDialogEx ( CPasswordManagerDlg::IDD, pParent )
{
    m_hIcon = AfxGetApp()->LoadIcon ( IDR_MAINFRAME );
}

void CPasswordManagerDlg::DoDataExchange ( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Control ( pDX, IDC_BUTTON1, mType );
	DDX_Control ( pDX, IDC_EDIT1, mPassword );
	DDX_Control(pDX, IDC_EDIT2, mDescribe);
}

BEGIN_MESSAGE_MAP ( CPasswordManagerDlg, CDialogEx )
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED ( IDC_BUTTON1, &CPasswordManagerDlg::OnBnClickedButton1 )
//	ON_NOTIFY(BCN_DROPDOWN, IDC_BUTTON1, &CPasswordManagerDlg::OnBnDropDownButton1)
    ON_WM_DROPFILES()
    ON_EN_CHANGE ( IDC_EDIT1, &CPasswordManagerDlg::OnEnChangeEdit1 )
    ON_EN_SETFOCUS ( IDC_EDIT1, &CPasswordManagerDlg::OnEnSetfocusEdit1 )
	ON_BN_CLICKED(IDC_BUTTON2, &CPasswordManagerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPasswordManagerDlg 消息处理程序

BOOL CPasswordManagerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon ( m_hIcon, TRUE );			// 设置大图标
    SetIcon ( m_hIcon, FALSE );		// 设置小图标

    // TODO: 在此添加额外的初始化代码

    mOpType = eDES_OpTypeEncrypt;
    updateButtonState();
    resetDesc();

    mPassword.SetWindowTextA ( mTip );
    mPassword.SetLimitText ( 10 );

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPasswordManagerDlg::OnPaint()
{
    if ( IsIconic() )
    {
        CPaintDC dc ( this ); // 用于绘制的设备上下文

        SendMessage ( WM_ICONERASEBKGND, reinterpret_cast<WPARAM> ( dc.GetSafeHdc() ), 0 );

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics ( SM_CXICON );
        int cyIcon = GetSystemMetrics ( SM_CYICON );
        CRect rect;
        GetClientRect ( &rect );
        int x = ( rect.Width() - cxIcon + 1 ) / 2;
        int y = ( rect.Height() - cyIcon + 1 ) / 2;

        // 绘制图标
        dc.DrawIcon ( x, y, m_hIcon );
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPasswordManagerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR> ( m_hIcon );
}



void CPasswordManagerDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    mOpType = mOpType == eDES_OpTypeEncrypt ? eDES_OpTypeDecrypt : eDES_OpTypeEncrypt;
    updateButtonState();
}

void CPasswordManagerDlg::updateButtonState()
{
    mType.SetWindowText ( mOpType == eDES_OpTypeEncrypt ? _T ( "加密" ) : _T ( "解密" ) );
}


//void CPasswordManagerDlg::OnBnDropDownButton1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
//	//@TN
//		*pResult = 0;
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}
void getOutFileName ( const char* name, std::string& out )
{
    static const char* newFlag = "_2";
    std::string orignalName = name;
    std::string ext, path, filename;
    int pos = orignalName.find_last_of ( '.' );
    ext = orignalName.substr ( pos );
    if ( !ext.empty() )
    {
        out = orignalName.insert ( pos, newFlag );
    }
    else
    {
        out = orignalName.append ( newFlag );
    }
}

void CPasswordManagerDlg::OnDropFiles ( HDROP hDropInfo )
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CDialogEx::OnDropFiles ( hDropInfo );

    // TODO: Add your message handler code here and/or call default
    char szFileName[MAX_PATH + 1] = {0};//被拖拽的文件的绝对路径
    UINT nFiles = DragQueryFile ( hDropInfo, 0xFFFFFFFF, NULL, 0 ); //被拖拽的文件的个数
    for ( UINT i = 0; i < nFiles; i++ )
    {
        DragQueryFile ( hDropInfo, i, szFileName, MAX_PATH ); //拖拽的文件名

        std::string originalFile = szFileName;
        std::string outFile;
        getOutFileName ( originalFile.c_str(), outFile );
        char buffer[128] = {0,};
        mPassword.GetWindowTextA ( buffer, 128 );
        if ( mOpType == eDES_OpTypeEncrypt )
        {
            DES_Encrypt ( ( char* ) originalFile.c_str(), buffer, ( char* ) outFile.c_str() );
        }
        else
        {
            DES_Decrypt ( ( char* ) originalFile.c_str(), buffer, ( char* ) outFile.c_str() );
        }
        std::string desc = "输出文件： ";
        desc.append ( outFile );
        mDescribe.SetWindowTextA ( desc.c_str() );

        std::string cmd = "notepad ";
        cmd.append ( outFile.c_str() );
		system ( cmd.c_str() );
		system ( "exit" );
        //DES_Encrypt()
    }
    // 结束此次拖拽操作，并释放分配的资源
    CDialog::OnDropFiles ( hDropInfo );
}


void CPasswordManagerDlg::OnStnClickedDesc()
{
    // TODO: 在此添加控件通知处理程序代码
}

void CPasswordManagerDlg::resetDesc()
{
    mDescribe.SetWindowTextA ( _T ( "请将文件拖拽此处!" ) );
}


void CPasswordManagerDlg::OnEnChangeEdit1()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。


    // TODO:  在此添加控件通知处理程序代码
}
/** @brief 只使用了前7位... **/
const char* CPasswordManagerDlg::mTip = "请在此处输入密码";


void CPasswordManagerDlg::OnEnSetfocusEdit1()
{
    // TODO: 在此添加控件通知处理程序代码
    char buffer[128] = {0,};
    mPassword.GetWindowTextA ( buffer, 128 );
    if ( !strcmp ( buffer, mTip ) )
        mPassword.SetWindowTextA ( "" );
}


void CPasswordManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
