#pragma once
#include "resource.h"
#include <dwmapi.h> 
#pragma comment(lib, "dwmapi.lib") 

#define TRANSPARENT_COLOR RGB (200, 201, 202)

// CSettingDlg �Ի���

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

private:
	CMFCButton m_btnOK;
	CMFCButton m_btnCancel;
	//HACCEL m_hAccel;

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

public:
	UINT m_length;//����ʱ��
	UINT m_times;//�������
	int m_filters;//�����㷨
	int m_figure;//����ͼ��
//	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
