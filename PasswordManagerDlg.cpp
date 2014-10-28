
// PasswordManagerDlg.cpp : ʵ���ļ�
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


// CPasswordManagerDlg �Ի���



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


// CPasswordManagerDlg ��Ϣ��������

BOOL CPasswordManagerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon ( m_hIcon, TRUE );			// ���ô�ͼ��
    SetIcon ( m_hIcon, FALSE );		// ����Сͼ��

    // TODO: �ڴ����Ӷ���ĳ�ʼ������

    mOpType = eDES_OpTypeEncrypt;
    updateButtonState();
    resetDesc();

    mPassword.SetWindowTextA ( mTip );
    mPassword.SetLimitText ( 10 );

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPasswordManagerDlg::OnPaint()
{
    if ( IsIconic() )
    {
        CPaintDC dc ( this ); // ���ڻ��Ƶ��豸������

        SendMessage ( WM_ICONERASEBKGND, reinterpret_cast<WPARAM> ( dc.GetSafeHdc() ), 0 );

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics ( SM_CXICON );
        int cyIcon = GetSystemMetrics ( SM_CYICON );
        CRect rect;
        GetClientRect ( &rect );
        int x = ( rect.Width() - cxIcon + 1 ) / 2;
        int y = ( rect.Height() - cyIcon + 1 ) / 2;

        // ����ͼ��
        dc.DrawIcon ( x, y, m_hIcon );
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPasswordManagerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR> ( m_hIcon );
}



void CPasswordManagerDlg::OnBnClickedButton1()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
    mOpType = mOpType == eDES_OpTypeEncrypt ? eDES_OpTypeDecrypt : eDES_OpTypeEncrypt;
    updateButtonState();
}

void CPasswordManagerDlg::updateButtonState()
{
    mType.SetWindowText ( mOpType == eDES_OpTypeEncrypt ? _T ( "����" ) : _T ( "����" ) );
}


//void CPasswordManagerDlg::OnBnDropDownButton1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
//	//@TN
//		*pResult = 0;
//	// TODO: �ڴ����ӿؼ�֪ͨ�����������
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
    // TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

    CDialogEx::OnDropFiles ( hDropInfo );

    // TODO: Add your message handler code here and/or call default
    char szFileName[MAX_PATH + 1] = {0};//����ק���ļ��ľ���·��
    UINT nFiles = DragQueryFile ( hDropInfo, 0xFFFFFFFF, NULL, 0 ); //����ק���ļ��ĸ���
    for ( UINT i = 0; i < nFiles; i++ )
    {
        DragQueryFile ( hDropInfo, i, szFileName, MAX_PATH ); //��ק���ļ���

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
        std::string desc = "����ļ��� ";
        desc.append ( outFile );
        mDescribe.SetWindowTextA ( desc.c_str() );

        std::string cmd = "notepad ";
        cmd.append ( outFile.c_str() );
		system ( cmd.c_str() );
		system ( "exit" );
        //DES_Encrypt()
    }
    // �����˴���ק���������ͷŷ������Դ
    CDialog::OnDropFiles ( hDropInfo );
}


void CPasswordManagerDlg::OnStnClickedDesc()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
}

void CPasswordManagerDlg::resetDesc()
{
    mDescribe.SetWindowTextA ( _T ( "�뽫�ļ���ק�˴�!" ) );
}


void CPasswordManagerDlg::OnEnChangeEdit1()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
    // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


    // TODO:  �ڴ����ӿؼ�֪ͨ�����������
}
/** @brief ֻʹ����ǰ7λ... **/
const char* CPasswordManagerDlg::mTip = "���ڴ˴���������";


void CPasswordManagerDlg::OnEnSetfocusEdit1()
{
    // TODO: �ڴ����ӿؼ�֪ͨ�����������
    char buffer[128] = {0,};
    mPassword.GetWindowTextA ( buffer, 128 );
    if ( !strcmp ( buffer, mTip ) )
        mPassword.SetWindowTextA ( "" );
}


void CPasswordManagerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	exit(0);
}