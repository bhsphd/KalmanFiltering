
// Nonlinear_Filtering.h : Nonlinear_Filtering Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CNonlinear_FilteringApp:
// �йش����ʵ�֣������ Nonlinear_Filtering.cpp
//

class CNonlinear_FilteringApp : public CWinAppEx
{
public:
	CNonlinear_FilteringApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNonlinear_FilteringApp theApp;
