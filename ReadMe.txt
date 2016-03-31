================================================================================
Introduction for Nonlinear_Filtering
===============================================================================

This is a demo for the performance comparison of different Kalman filters. All rights reserved by Xin-Chun Zhang.

Nonlinear_Filtering.vcxproj
It is the main file compiled by VC++ compiler, including the compile platform, configuration and functions. etc.

Nonlinear_Filtering.vcxproj.filters
    ����ʹ�á�Ӧ�ó����򵼡����ɵ� VC++ ��Ŀɸѡ���ļ���
    �������й���Ŀ�ļ���ɸѡ��֮��Ĺ�����Ϣ���� IDE �У�ͨ�����ֹ��������ض��ڵ����Է�����ʽ��ʾ����������չ�����ļ������磬��.cpp���ļ��롰Դ�ļ���ɸѡ��������

Nonlinear_Filtering.h
����Ӧ�ó������Ҫͷ�ļ���������������Ŀ�ض���ͷ�ļ�(���� Resource.h)�������� CNonlinear_FilteringApp Ӧ�ó����ࡣ

Nonlinear_Filtering.cpp
���ǰ���Ӧ�ó����� CNonlinear_FilteringApp ����ҪӦ�ó���Դ�ļ���

Nonlinear_Filtering.rc
���ǳ���ʹ�õ����� Microsoft Windows ��Դ���б������� RES ��Ŀ¼�д洢��ͼ�ꡢλͼ�͹�ꡣ���ļ�����ֱ���� Microsoft Visual C++ �н��б༭����Ŀ��Դλ�� 2052 �С�

res\Nonlinear_Filtering.ico
��������Ӧ�ó���ͼ���ͼ���ļ�����ͼ���������Ҫ��Դ�ļ� Nonlinear_Filtering.rc �С�

res\Nonlinear_Filtering.rc2
���ļ��������� Microsoft Visual C++ �н��б༭����Դ����Ӧ�ý���������Դ�༭���༭��������Դ���ڴ��ļ��С�

/////////////////////////////////////////////////////////////////////////////

��������ܴ���:
��Ŀ������׼ MFC ���档

MainFrm.h, MainFrm.cpp
��Щ�ļ���������� CMainFrame������������
CFrameWnd ���������� SDI ��ܹ��ܡ�

/////////////////////////////////////////////////////////////////////////////

Ӧ�ó����򵼴���һ���ĵ����ͺ�һ����ͼ:

Nonlinear_FilteringDoc.h��Nonlinear_FilteringDoc.cpp - �ĵ�
��Щ�ļ����� CNonlinear_FilteringDoc �ࡣ�༭��Щ�ļ�������������ĵ����ݲ���ʵ���ļ�����ͼ���(ͨ�� CNonlinear_FilteringDoc::Serialize)��

Nonlinear_FilteringView.h��Nonlinear_FilteringView.cpp - �ĵ�����ͼ
��Щ�ļ����� CNonlinear_FilteringView �ࡣ
CNonlinear_FilteringView �������ڲ鿴 CNonlinear_FilteringDoc ����





/////////////////////////////////////////////////////////////////////////////

��������:

ActiveX �ؼ�
Ӧ�ó��������ʹ�� ActiveX �ؼ���֧�֡�

��ӡ����ӡԤ��֧��
Ӧ�ó�������ͨ���� MFC ����� CView ���еĳ�Ա���������������ڴ����ӡ����ӡ���úʹ�ӡԤ������Ĵ��롣

/////////////////////////////////////////////////////////////////////////////

������׼�ļ�:

StdAfx.h��StdAfx.cpp
��Щ�ļ�����������Ϊ Nonlinear_Filtering.pch ��Ԥ����ͷ (PCH) �ļ�����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
���Ǳ�׼ͷ�ļ����������µ���Դ ID��
Microsoft Visual C++ ��ȡ�����´��ļ���

Nonlinear_Filtering.manifest
	Ӧ�ó����嵥�ļ��� Windows XP ��������Ӧ�ó���
	���ض��汾���г��򼯵������ԡ����س���ʹ�ô�
	��Ϣ�ӳ��򼯻�������ʵ��ĳ��򼯻�
	��Ӧ�ó������˽����Ϣ��Ӧ�ó����嵥����Ϊ�����·ַ�����Ϊ
	��Ӧ�ó����ִ���ļ���װ����ͬ�ļ����е��ⲿ .manifest �ļ�������
	Ҳ��������Դ����ʽ�����ڸÿ�ִ���ļ��С� 
/////////////////////////////////////////////////////////////////////////////

����ע��:

Ӧ�ó�����ʹ�á�TODO:��ָʾӦ��ӻ��Զ����Դ���벿�֡�

���Ӧ�ó����ڹ���� DLL ��ʹ�� MFC������Ҫ���·�����Щ MFC DLL�����Ӧ�ó������õ����������ϵͳ�ĵ�ǰ�������ò�ͬ������Ҫ���·�����Ӧ�ı��ػ���Դ MFC100XXX.DLL���й�����������ĸ�����Ϣ����μ� MSDN �ĵ����й� Redistributing Visual C++ applications (���·��� Visual C++ Ӧ�ó���)���½ڡ�

/////////////////////////////////////////////////////////////////////////////
