
// PasswordManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPasswordManagerApp:
// �йش����ʵ�֣������ PasswordManager.cpp
//

class CPasswordManagerApp : public CWinApp
{
public:
	CPasswordManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPasswordManagerApp theApp;