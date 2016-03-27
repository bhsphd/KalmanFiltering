// SettingDlg.cpp : ʵ���ļ�
//

#pragma once
#include "stdafx.h"
#include "Nonlinear_Filtering.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{

	m_length = 25;
	m_times = 1;
	m_filters = 0;
	m_figure = 0;
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LENGTH, m_length);
	DDX_Text(pDX, IDC_TIMES, m_times);
	DDX_Radio(pDX, IDC_EKF, m_filters);
	DDX_Radio(pDX, IDC_RMSE, m_figure);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������


//void CSettingDlg::OnBnClickedOk()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnOK();
//}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ�������Ի����ʼ��ΪWindows Aero���
	OSVERSIONINFOEX osver = {0};
	osver.dwOSVersionInfoSize = sizeof(osver);
	osver.dwMajorVersion = 5;

	DWORDLONG dwlConditionMask = 0;
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER);

	if (VerifyVersionInfo(&osver, VER_MAJORVERSION, dwlConditionMask))//�жϲ���ϵͳ�汾�����ﵽVista���ϰ汾������ʾAeroЧ��
	{
		SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_LAYERED);
		SetLayeredWindowAttributes(TRANSPARENT_COLOR, 0, LWA_COLORKEY);
		BOOL bDwm ;
		DwmIsCompositionEnabled (&bDwm);
		if (bDwm)
		{  
			MARGINS mrg = {-1};//{-1};  
			DwmExtendFrameIntoClientArea(m_hWnd , &mrg);
			SetBackgroundColor(TRANSPARENT_COLOR);
			CMFCVisualManager ::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
			CMFCButton ::EnableWindowsTheming ();
		} 
	}

	    // Load accelerators 
    //m_hAccel = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)); //��ݼ���id
    //ASSERT(m_hAccel); 

	return TRUE;

	// �쳣: OCX ����ҳӦ���� FALSE
}

/*BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg) 
{ 
    if (WM_KEYFIRST <= pMsg->message && 
        pMsg->message <= WM_KEYLAST) 
    { 
        HACCEL hAccel = m_hAccel; 
        if (hAccel && 
            ::TranslateAccelerator(m_hWnd, hAccel, pMsg)) 
            return TRUE; 
    } 
    return CDialog::PreTranslateMessage(pMsg); 
}*/