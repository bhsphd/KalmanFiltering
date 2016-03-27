
// Nonlinear_FilteringView.cpp : CNonlinear_FilteringView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Nonlinear_Filtering.h"
#endif

#include "Nonlinear_FilteringDoc.h"
#include "Nonlinear_FilteringView.h"
#include "SettingDlg.h"
#include <cmath>
#include "resource.h"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNonlinear_FilteringView

IMPLEMENT_DYNCREATE(CNonlinear_FilteringView, CView)

BEGIN_MESSAGE_MAP(CNonlinear_FilteringView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNonlinear_FilteringView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CNonlinear_FilteringView::OnSetting)
	//ON_BN_CLICKED(IDOK, &CNonlinear_FilteringView::OnBnClickedOk)
	ON_COMMAND(ID_PLOT, &CNonlinear_FilteringView::OnPlot)
	ON_COMMAND(ID_HELPER, &CNonlinear_FilteringView::OnHelper)
END_MESSAGE_MAP()

// CNonlinear_FilteringView ����/����

CNonlinear_FilteringView::CNonlinear_FilteringView()
{
	// TODO: �ڴ˴���ӹ������
	m_length = 25;
	m_times = 1;
	m_filters = 0;
	m_figure = 0;
	//  m_select = 0;
	filterGraph = NULL;
	//m_progress.SetPos(0);
}

/*void CNonlinear_FilteringView::DeleteObj(CGraphSeries &series)
{
	filterGraph->RemoveAllSeries();
}*/

CNonlinear_FilteringView::~CNonlinear_FilteringView()
{
}

double CNonlinear_FilteringView::RootMSE(CMatrix a, int n)//��CM�����n���������ľ������, lenΪ���鳤��
{
	if (n <= 0 || n > dim)
		exit(1);
	
	double ArraySum = 0.0;

	for (int i = 1; i <= a.m_col; ++i)
	{
		ArraySum += pow(a(n, i), 2);
	}

	return sqrt(ArraySum / a.m_col);
}

double CNonlinear_FilteringView::VelPosMSE(CMatrix a)
{
	double ArraySum = 0.0;


	for (int i = 1; i <= a.m_col; ++i)
	{
		ArraySum += pow(a(1, i), 2);
	}

	return sqrt(ArraySum / a.m_col);
}

void CNonlinear_FilteringView::GetExcuteProgPath(CString &pszPath)
{
	const int nPathBufferSize = MAX_PATH;
	TCHAR tchPathBuffer[nPathBufferSize];
	memset( (void*)tchPathBuffer, TEXT('\0'), nPathBufferSize * sizeof(TCHAR) );
	GetModuleFileName( NULL, tchPathBuffer, nPathBufferSize );
 
	CString strExcuteFilePath = tchPathBuffer;
	if ( strExcuteFilePath.Right(1) == _T("\\") )
	{
		strExcuteFilePath.Left( strExcuteFilePath.GetLength() - 1 );
	}
	strExcuteFilePath = strExcuteFilePath.Left( strExcuteFilePath.ReverseFind( '\\' ) );
	pszPath = strExcuteFilePath;
}

BOOL CNonlinear_FilteringView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CNonlinear_FilteringView ����
void CNonlinear_FilteringView::OnDraw(CDC* pDC)
{
	CNonlinear_FilteringDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if(NULL != filterGraph && graphComplete)
		filterGraph->DrawGraph(pDC);
	
	UpdateWindow();
}


void CNonlinear_FilteringView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	graphComplete = FALSE;
}


// CNonlinear_FilteringView ��ӡ


void CNonlinear_FilteringView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNonlinear_FilteringView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CNonlinear_FilteringView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CNonlinear_FilteringView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CNonlinear_FilteringView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNonlinear_FilteringView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNonlinear_FilteringView ���

#ifdef _DEBUG
void CNonlinear_FilteringView::AssertValid() const
{
	CView::AssertValid();
}

void CNonlinear_FilteringView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNonlinear_FilteringDoc* CNonlinear_FilteringView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNonlinear_FilteringDoc)));
	return (CNonlinear_FilteringDoc*)m_pDocument;
}
#endif //_DEBUG


// CNonlinear_FilteringView ��Ϣ�������


void CNonlinear_FilteringView::OnSetting()
{
	// TODO: �ڴ���������������
	CSettingDlg dlg;
	dlg.m_length = m_length;
	dlg.m_times = m_times;
	dlg.m_filters = m_filters;
	dlg.m_figure = m_figure;

	if (IDOK == dlg.DoModal())
	{
		m_length = dlg.m_length;
		m_times = dlg.m_times;
		m_filters = dlg.m_filters;
		m_figure = dlg.m_figure;
	}
}

void CNonlinear_FilteringView::OnPlot()
{
	// TODO: �ڴ���������������
	if (0 == m_figure)
	{
		filterGraph = new CGraph(BAR_GRAPH);	
	}
	else
	{
		filterGraph = new CGraph(LINE_GRAPH);//����ͼ
	}

	int axisXDist = m_length / 5;//λ�á��ٶ�RMSE��x���ȼ��

	if (m_filters <= 4)//ֻ�е����˲���
	{
		CMatrix arra(4, m_length + 1);
		CMatrix arra_sum(4, m_length + 1);			
		CMatrix posarray(1, m_length + 1);			
		CMatrix velarray(1, m_length + 1);
		
		if (0 == m_filters)//EKF + Barͼ
		{
			
			for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
			{
				rt.GenerateRealTrack(m_length);					
				ekf.EKFfiltering(rt.Z_Real, m_length);
				
				
				for (UINT j = 0; j < m_length + 1; ++j)
				{
					 	
					for (int k = 0; k < dim; ++k)						
					{							
						arra(k + 1, j + 1) = (((StoreData *)ekf.X.GetAt(j))->state)[k][0] - 
								(((StoreData *)rt.X.GetAt(j))->state)[k][0];
													
						arra_sum(k + 1, j + 1) += arra(k + 1, j + 1);						
					}						
					posarray(1, j + 1) = posarray(1, j + 1) + arra(1, j + 1) * arra(1, j + 1) + arra(3, j + 1) * arra(3, j + 1);						
					velarray(1, j + 1) = velarray(1, j + 1) + arra(2, j + 1) * arra(2, j + 1) + arra(4, j + 1) * arra(4, j + 1);					
				}
					
				ekf.EKFDelete(ekf.X);					
				rt.RealTrackDelete(rt.X);				
			}
			
			//set up legend
			filterGraph->SetLegend(0, "EKF");	
		}
			
		else if (1 == m_filters)//UKF + Barͼ			
		{
			
			for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
			{
				rt.GenerateRealTrack(m_length);
				ukf.UKFfiltering(rt.Z_Real, m_length);
			
				
				for (UINT j = 0; j < m_length + 1; ++j)
				{
					 
					for (int k = 0; k < dim; ++k)
					{
						arra(k + 1, j + 1) = (((StoreData *)ukf.X.GetAt(j))->state)[k][0] - 
							(((StoreData *)rt.X.GetAt(j))->state)[k][0];
						
						arra_sum(k + 1, j + 1) += arra(k + 1, j + 1);
					}
					posarray(1, j + 1) = posarray(1, j + 1) + arra(1, j + 1) * arra(1, j + 1) + arra(3, j + 1) * arra(3, j + 1);
					velarray(1, j + 1) = velarray(1, j + 1) + arra(2, j + 1) * arra(2, j + 1) + arra(4, j + 1) * arra(4, j + 1);
				}
				ukf.UKFDelete(ukf.X);
				rt.RealTrackDelete(rt.X);
			}
			
			//set up legend
			filterGraph->SetLegend(0, "UKF");
		}

		else if (2 == m_filters)//3��CKF + Barͼ
		{
			
			for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
			{
				rt.GenerateRealTrack(m_length);
				thirdckf.ThirdCKFfiltering(rt.Z_Real, m_length);
				
				
				for (UINT j = 0; j < m_length + 1; ++j)
				{
					 	
					for (int k = 0; k < dim; ++k)
					{
						arra(k + 1, j + 1) = (((StoreData *)thirdckf.X.GetAt(j))->state)[k][0] - 
							(((StoreData *)rt.X.GetAt(j))->state)[k][0];
						
						arra_sum(k + 1, j + 1) += arra(k + 1, j + 1);
					}
					posarray(1, j + 1) = posarray(1, j + 1) + arra(1, j + 1) * arra(1, j + 1) + arra(3, j + 1) * arra(3, j + 1);
					velarray(1, j + 1) = velarray(1, j + 1) + arra(2, j + 1) * arra(2, j + 1) + arra(4, j + 1) * arra(4, j + 1);
				}
				thirdckf.ThirdCKFDelete(thirdckf.X);
				rt.RealTrackDelete(rt.X);
			}
			
			//set up legend
			filterGraph->SetLegend(0, "Third-degree CKF");
		}
		
		else if (3 == m_filters)//3��CKF + Barͼ
		{
			
			for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
			{
				rt.GenerateRealTrack(m_length);
				ickf.ICKFfiltering(rt.Z_Real, m_length);
			
				
				for (UINT j = 0; j < m_length + 1; ++j)
				{
					 	
					for (int k = 0; k < dim; ++k)
					{
						arra(k + 1, j + 1) = (((StoreData *)ickf.X.GetAt(j))->state)[k][0] - 
							(((StoreData *)rt.X.GetAt(j))->state)[k][0];
						
						arra_sum(k + 1, j + 1) += arra(k + 1, j + 1);
					}
					posarray(1, j + 1) = posarray(1, j + 1) + arra(1, j + 1) * arra(1, j + 1) + arra(3, j + 1) * arra(3, j + 1);
					velarray(1, j + 1) = velarray(1, j + 1) + arra(2, j + 1) * arra(2, j + 1) + arra(4, j + 1) * arra(4, j + 1);
				}
				ickf.ICKFDelete(ickf.X);
				rt.RealTrackDelete(rt.X);
			}
			
			//set up legend
			filterGraph->SetLegend(0, "ECKF");
		}

		else if (4 == m_filters)//3��CKF + Barͼ
		{	
           
			for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
			{
				rt.GenerateRealTrack(m_length);
				fifthckf.FifthCKFfiltering(rt.Z_Real, m_length);
			
				
				for (UINT j = 0; j < m_length + 1; ++j)
				{
					 
					for (int k = 0; k < dim; ++k)
					{
						arra(k + 1, j + 1) = (((StoreData *)fifthckf.X.GetAt(j))->state)[k][0] - 
							(((StoreData *)rt.X.GetAt(j))->state)[k][0];
						
						arra_sum(k + 1, j + 1) += arra(k + 1, j + 1);
					}
					posarray(1, j + 1) = posarray(1, j + 1) + arra(1, j + 1) * arra(1, j + 1) + arra(3, j + 1) * arra(3, j + 1);
					velarray(1, j + 1) = velarray(1, j + 1) + arra(2, j + 1) * arra(2, j + 1) + arra(4, j + 1) * arra(4, j + 1);
				}
				fifthckf.FifthCKFDelete(fifthckf.X);
				rt.RealTrackDelete(rt.X);
			}
			
			//set up legend
			filterGraph->SetLegend(0, "Fifth-degree CKF");
		}

		CMatrix PosRMSE(1, m_length + 1);
		CMatrix VelRMSE(1, m_length + 1);

		arra_sum = arra_sum / m_times;
		
		
		for (UINT j = 1; j <= m_length + 1; ++j)//��m_times�εľ�ֵ
		{
			PosRMSE(1, j) = sqrt(posarray(1, j) / m_times);
			VelRMSE(1, j) = sqrt(velarray(1, j) / m_times);
		}

		//��ʼ��ͼ��صĲ���	
		if (0 == m_figure)
		{
			filterGraph->SetGraphTitle("��������������(RMSE)");
			filterGraph->SetXAxisAlignment(45);
			filterGraph->SetXAxisLabel("������");
			filterGraph->SetYAxisLabel("�������(ȡ��Ȼ����)");
		
			CGraphSeries *series1 = new CGraphSeries();		
			CGraphSeries *series2 = new CGraphSeries();		
			CGraphSeries *series3 = new CGraphSeries();		
			CGraphSeries *series4 = new CGraphSeries();
	
			series1->SetLabel("x��λ��");
			series2->SetLabel("x���ٶ�");
			series3->SetLabel("y��λ��");
			series4->SetLabel("y���ٶ�");
	
			filterGraph->SetGraphQuadType(3);
		
			CMatrix AxisRMSE(1, 4);
			 
			for (int m = 1; m <= dim; ++m)
			{
				AxisRMSE(1, m) = log(RootMSE(arra_sum, m));
			}

	
		
			//ʵ�������������Ӧ��ʾ�����ڽ�С������ȽϺ���
			double AxisLen = AxisRMSE.MaxMod();
			double TickStep = 0.0001;//��С�Ŀ�����ʾ�̶�
			double minTickValue = 0.0;
		
			while (AxisLen / TickStep > 10)
			{
				TickStep *= 10.0;
			}
		
			minTickValue = - TickStep * (int)ceil(AxisLen / TickStep);

			filterGraph->SetTickLimits(minTickValue, -minTickValue, TickStep);
	
			series1->SetData(0, AxisRMSE(1, 1) + minTickValue);
			series2->SetData(0, AxisRMSE(1, 2) + minTickValue);
			series3->SetData(0, AxisRMSE(1, 3) + minTickValue);
			series4->SetData(0, AxisRMSE(1, 4) + minTickValue);

			//set the colors of my bars
			//filterGraph->SetColor(0, BLUE);
			filterGraph->AddSeries(series1);
			filterGraph->AddSeries(series2);
			filterGraph->AddSeries(series3);
			filterGraph->AddSeries(series4);
		}

	
		else if (1 == m_figure)
		{
			//filterGraph = new CGraph(LINE_GRAPH);//����ͼ
			filterGraph->SetGraphTitle("λ�þ������");
			filterGraph->SetXAxisAlignment(0);	  
			filterGraph->SetXAxisLabel("ʱ��,k");	  
			filterGraph->SetYAxisLabel("λ�þ������RMSE");
	  
			double AxisLen = PosRMSE.MaxMod();
			double TickStep = 0.0001;	   
			double maxTickValue = 0.0;
	  
			while (AxisLen / TickStep > 10)		
			{			
				TickStep *= 10.0;		
			}
		
			maxTickValue = TickStep * (int)ceil(AxisLen / TickStep);
		
			filterGraph->SetTickLimits(0, maxTickValue, TickStep);
		
			CString str;
		
			
			for (UINT i = 0; i <= m_length; ++i)		
			{			
				CGraphSeries* series = new CGraphSeries();			
				str.Format("%d", i);

				if (i % axisXDist == 0)
				{				
					series->SetLabel(str);	
				}

				series->SetData(0, PosRMSE(1, i + 1));			
				filterGraph->AddSeries(series);			      
			}	
		}
			
		else if (2 == m_figure)	
		{
			filterGraph->SetGraphTitle("�ٶȾ������");
			filterGraph->SetXAxisAlignment(0);
			filterGraph->SetXAxisLabel("ʱ��,k");
			filterGraph->SetYAxisLabel("�ٶȾ������RMSE");

			double AxisLen = VelRMSE.MaxMod();
			double TickStep = 0.0001;
			double minTickValue = 0.0;
			while (AxisLen / TickStep > 10)
			{
				TickStep *= 10.0;
			}
		
			minTickValue = - TickStep * (int)ceil(AxisLen / TickStep);
		
			filterGraph->SetTickLimits(0, -minTickValue, TickStep);
		
			CString str;
			
			for (UINT i = 0; i <= m_length; ++i)
			{
				CGraphSeries* series = new CGraphSeries();
				str.Format("%d", i);
				
				if (i % axisXDist == 0)
				{				
					series->SetLabel(str);	
				}

				series->SetData(0, VelRMSE(1, i + 1));
				filterGraph->AddSeries(series);
			}
		}
		filterGraph->SetColor(0, BLUE);
	}

   else if (5 == m_filters)
   {
	   CMatrix arra_EKF(4, m_length + 1);
	   CMatrix arra_sum_EKF(4, m_length + 1);
	   CMatrix posarray_EKF(1, m_length + 1);
	   CMatrix velarray_EKF(1, m_length + 1);

	   CMatrix arra_UKF(4, m_length + 1);
	   CMatrix arra_sum_UKF(4, m_length + 1);
	   CMatrix posarray_UKF(1, m_length + 1);
	   CMatrix velarray_UKF(1, m_length + 1);

	   CMatrix arra_ThirdCKF(4, m_length + 1);
	   CMatrix arra_sum_ThirdCKF(4, m_length + 1);
	   CMatrix posarray_ThirdCKF(1, m_length + 1);
	   CMatrix velarray_ThirdCKF(1, m_length + 1);

	   CMatrix arra_ICKF(4, m_length + 1);
	   CMatrix arra_sum_ICKF(4, m_length + 1);
	   CMatrix posarray_ICKF(1, m_length + 1);
	   CMatrix velarray_ICKF(1, m_length + 1);

	   CMatrix arra_FifthCKF(4, m_length + 1);
	   CMatrix arra_sum_FifthCKF(4, m_length + 1);
	   CMatrix posarray_FifthCKF(1, m_length + 1);
	   CMatrix velarray_FifthCKF(1, m_length + 1);

	  
	   for (UINT i = 1; i <= m_times; ++i)//�Ѹ�ѭ�������ж��ڲ������Ӵ��������ȣ����Ƕ���ߴ��������Ч���а���
	   {
		   rt.GenerateRealTrack(m_length);
		   ekf.EKFfiltering(rt.Z_Real, m_length);
		   ukf.UKFfiltering(rt.Z_Real, m_length);
		   thirdckf.ThirdCKFfiltering(rt.Z_Real, m_length);
		   ickf.ICKFfiltering(rt.Z_Real, m_length);
		   fifthckf.FifthCKFfiltering(rt.Z_Real, m_length);

		  
		   for (UINT j = 0; j < m_length + 1; ++j)
		   {
			    
			   for (int k = 0; k < dim; ++k)
			   {
				   arra_EKF(k + 1, j + 1) = (((StoreData *)ekf.X.GetAt(j))->state)[k][0] - 
					   (((StoreData *)rt.X.GetAt(j))->state)[k][0];

				   arra_UKF(k + 1, j + 1) = (((StoreData *)ukf.X.GetAt(j))->state)[k][0] - 
					   (((StoreData *)rt.X.GetAt(j))->state)[k][0];

				   arra_ThirdCKF(k + 1, j + 1) = (((StoreData *)thirdckf.X.GetAt(j))->state)[k][0] - 
					   (((StoreData *)rt.X.GetAt(j))->state)[k][0];

				   arra_ICKF(k + 1, j + 1) = (((StoreData *)ickf.X.GetAt(j))->state)[k][0] - 
					   (((StoreData *)rt.X.GetAt(j))->state)[k][0];

				   arra_FifthCKF(k + 1, j + 1) = (((StoreData *)fifthckf.X.GetAt(j))->state)[k][0] - 
					   (((StoreData *)rt.X.GetAt(j))->state)[k][0];

				   arra_sum_EKF(k + 1, j + 1) += arra_EKF(k + 1, j + 1);
				   arra_sum_UKF(k + 1, j + 1) += arra_UKF(k + 1, j + 1);
				   arra_sum_ThirdCKF(k + 1, j + 1) += arra_ThirdCKF(k + 1, j + 1);
				   arra_sum_ICKF(k + 1, j + 1) += arra_ICKF(k + 1, j + 1);
				   arra_sum_FifthCKF(k + 1, j + 1) += arra_FifthCKF(k + 1, j + 1);
			   }
			   posarray_EKF(1, j + 1) += pow(arra_EKF(1, j + 1), 2) + pow(arra_EKF(3, j + 1), 2);

			   posarray_UKF(1, j + 1) += pow(arra_UKF(1, j + 1), 2) + pow(arra_UKF(3, j + 1), 2);

			   posarray_ThirdCKF(1, j + 1) += pow(arra_ThirdCKF(1, j + 1), 2) + pow(arra_ThirdCKF(3, j + 1), 2);

			   posarray_ICKF(1, j + 1) += pow(arra_ICKF(1, j + 1), 2) + pow(arra_ICKF(3, j + 1), 2);

			   posarray_FifthCKF(1, j + 1) += pow(arra_FifthCKF(1, j + 1), 2) + pow(arra_FifthCKF(3, j + 1), 2);

			  
			   velarray_EKF(1, j + 1) += pow(arra_EKF(2, j + 1), 2) + pow(arra_EKF(4, j + 1), 2);

			   velarray_UKF(1, j + 1) += pow(arra_UKF(2, j + 1), 2) + pow(arra_UKF(4, j + 1), 2);

			   velarray_ThirdCKF(1, j + 1) += pow(arra_ThirdCKF(2, j + 1), 2) + pow(arra_ThirdCKF(4, j + 1), 2);

			   velarray_ICKF(1, j + 1) += pow(arra_ICKF(2, j + 1), 2) + pow(arra_ICKF(4, j + 1), 2);

			   velarray_FifthCKF(1, j + 1) += pow(arra_FifthCKF(2, j + 1), 2) + pow(arra_FifthCKF(4, j + 1), 2);
		   }
		   rt.RealTrackDelete(rt.X);
		   ekf.EKFDelete(ekf.X);
		   ukf.UKFDelete(ukf.X);
		   thirdckf.ThirdCKFDelete(thirdckf.X);
		   ickf.ICKFDelete(ickf.X);
		   fifthckf.FifthCKFDelete(fifthckf.X);
	   }
		
	   CMatrix PosRMSE_EKF(4, m_length + 1);		
	   CMatrix VelRMSE_EKF(4, m_length + 1); 		
	   CMatrix PosRMSE(4, m_length + 1);		
	   CMatrix VelRMSE(4, m_length + 1);  
		
	   arra_sum_EKF = arra_sum_EKF / m_times;		
	   arra_sum_UKF = arra_sum_UKF / m_times;		
	   arra_sum_ThirdCKF = arra_sum_ThirdCKF / m_times;	
	   arra_sum_ICKF = arra_sum_ICKF / m_times;		
	   arra_sum_FifthCKF = arra_sum_FifthCKF / m_times;

	   
	   for (UINT j = 1; j <= m_length + 1; ++j)
	   {
		  
		   PosRMSE_EKF(1, j) = sqrt(posarray_EKF(1, j) / m_times);
		   VelRMSE_EKF(1, j) = sqrt(velarray_EKF(1, j) / m_times);

		   PosRMSE(1, j) = sqrt(posarray_UKF(1, j) / m_times);
		   VelRMSE(1, j) = sqrt(velarray_UKF(1, j) / m_times);

		   PosRMSE(2, j) = sqrt(posarray_ThirdCKF(1, j) / m_times);
		   VelRMSE(2, j) = sqrt(velarray_ThirdCKF(1, j) / m_times);

		   PosRMSE(3, j) = sqrt(posarray_ICKF(1, j) / m_times);
		   VelRMSE(3, j) = sqrt(velarray_ICKF(1, j) / m_times);

		   PosRMSE(4, j) = sqrt(posarray_FifthCKF(1, j) / m_times);
		   VelRMSE(4, j) = sqrt(velarray_FifthCKF(1, j) / m_times);
	   }
		   				 
	   CMatrix CRMSE(4, 5);
	       
	   for (int m = 1; m <= dim; ++m)		  
	   {			  
		   CRMSE(m, 1) = log(RootMSE(arra_sum_EKF, m));			 
		   CRMSE(m, 2) = log(RootMSE(arra_sum_UKF, m));			 
		   CRMSE(m, 3) = log(RootMSE(arra_sum_ThirdCKF, m));			 
		   CRMSE(m, 4) = log(RootMSE(arra_sum_ICKF, m));			
		   CRMSE(m, 5) = log(RootMSE(arra_sum_FifthCKF, m));		  
	   }

			   
	   if (0 == m_figure)		  
	   {		
		   filterGraph->SetGraphTitle("��������������(RMSE)");
		   filterGraph->SetXAxisAlignment(45);		
		   filterGraph->SetXAxisLabel("������");		
		   filterGraph->SetYAxisLabel("�������(ȡ��Ȼ����)");	
		
		   CGraphSeries *series1 = new CGraphSeries();		
		   CGraphSeries *series2 = new CGraphSeries();		
		   CGraphSeries *series3 = new CGraphSeries();		
		   CGraphSeries *series4 = new CGraphSeries();
			
		   series1->SetLabel("x��λ��");		
		   series2->SetLabel("x���ٶ�");		
		   series3->SetLabel("y��λ��");		
		   series4->SetLabel("y���ٶ�");
			
		   filterGraph->SetGraphQuadType(3);

	 
		   //ʵ�������������Ӧ��ʾ	  
		   double AxisLen = CRMSE.MaxMod();	   
		   double TickStep = 0.0001;	   
		   double minTickValue = 0.0;	  
		  
		   while (AxisLen / TickStep > 10)		
		   {			
			   TickStep *= 10.0;		
		   }
		
		   minTickValue = - TickStep * (int)ceil(AxisLen / TickStep);
		
		   filterGraph->SetTickLimits(minTickValue, -minTickValue, TickStep);	
		
		   series1->SetData(0, CRMSE(1, 1) + minTickValue);		
		   series1->SetData(1, CRMSE(1, 2) + minTickValue);		
		   series1->SetData(2, CRMSE(1, 3) + minTickValue);		
		   series1->SetData(3, CRMSE(1, 4) + minTickValue);		
		   series1->SetData(4, CRMSE(1, 5) + minTickValue);

		   series2->SetData(0, CRMSE(2, 1) + minTickValue);		
		   series2->SetData(1, CRMSE(2, 2) + minTickValue);		
		   series2->SetData(2, CRMSE(2, 3) + minTickValue);		
		   series2->SetData(3, CRMSE(2, 4) + minTickValue);		
		   series2->SetData(4, CRMSE(2, 5) + minTickValue);
		
		   series3->SetData(0, CRMSE(3, 1) + minTickValue);		
		   series3->SetData(1, CRMSE(3, 2) + minTickValue);		
		   series3->SetData(2, CRMSE(3, 3) + minTickValue);		
		   series3->SetData(3, CRMSE(3, 4) + minTickValue);		
		   series3->SetData(4, CRMSE(3, 5) + minTickValue);
		
		   series4->SetData(0, CRMSE(4, 1) + minTickValue);		
		   series4->SetData(1, CRMSE(4, 2) + minTickValue);		
		   series4->SetData(2, CRMSE(4, 3) + minTickValue);		
		   series4->SetData(3, CRMSE(4, 4) + minTickValue);		
		   series4->SetData(4, CRMSE(4, 5) + minTickValue);
  
		   filterGraph->AddSeries(series1);  
		   filterGraph->AddSeries(series2);   
		   filterGraph->AddSeries(series3); 
		   filterGraph->AddSeries(series4); 
	   }

	   else if (1 == m_figure)	
	   {			  
		   filterGraph->SetGraphTitle("λ�þ������");	  
		   filterGraph->SetXAxisAlignment(0);	  
		   filterGraph->SetXAxisLabel("ʱ��,k");	  
		   filterGraph->SetYAxisLabel("λ�þ������RMSE");
	  
		   double AxisLen = PosRMSE.MaxMod();//ͨ��EKF�����ϴ󣬲����ڹ۲������㷨	   
		   double TickStep = 0.0001;	  
		   double minTickValue = 0.0;
	 
		   while (AxisLen / TickStep > 10)		
		   {		
			   TickStep *= 10.0;		
		   }
		
		   minTickValue = - TickStep * (int)ceil(AxisLen / TickStep);
	
		   filterGraph->SetTickLimits(0, -minTickValue, TickStep);

		
		   CString str;
		   
		   for (UINT i = 0; i <= m_length; ++i)		
		   {			
			   CGraphSeries* series = new CGraphSeries();
			   str.Format("%d", i);
			
			   if (i % axisXDist == 0)
				{				
					series->SetLabel(str);	
				}
			
			   series->SetData(0, PosRMSE_EKF(1, i + 1));
			   series->SetData(1, PosRMSE(1, i + 1));
			   series->SetData(2, PosRMSE(2, i + 1));
			   series->SetData(3, PosRMSE(3, i + 1));
			   series->SetData(4, PosRMSE(4, i + 1));
			
			   filterGraph->AddSeries(series);
		   }
	}

	else if (2 == m_figure)
	{
		filterGraph->SetGraphTitle("�ٶȾ������");
	    filterGraph->SetXAxisAlignment(0);
	    filterGraph->SetXAxisLabel("ʱ��,k");
	    filterGraph->SetYAxisLabel("�ٶȾ������RMSE");

	    double AxisLen = VelRMSE.MaxMod();
	    double TickStep = 0.0001;
	    double minTickValue = 0.0;
	    while (AxisLen / TickStep > 10)
		{
			TickStep *= 10.0;
		}
		minTickValue = - TickStep * (int)ceil(AxisLen / TickStep);

		filterGraph->SetTickLimits(0, -minTickValue, TickStep);

		CString str;
	   
		for (UINT i = 0; i <= m_length; ++i)
		{
			CGraphSeries* series = new CGraphSeries();

			str.Format("%d", i);
			
			if (i % axisXDist == 0)
			{				
				series->SetLabel(str);	
			}

			series->SetData(0, VelRMSE_EKF(1, i + 1));
			series->SetData(1, VelRMSE(1, i + 1));
			series->SetData(2, VelRMSE(2, i + 1));
			series->SetData(3, VelRMSE(3, i + 1));
			series->SetData(4, VelRMSE(4, i + 1));

			filterGraph->AddSeries(series);
		}
	}
			
	   //set the colors of my bars
	   filterGraph->SetColor(0, BLUE);
	   filterGraph->SetColor(1, RED);
	   filterGraph->SetColor(2, YELLOW);
	   filterGraph->SetColor(3, TURQUOISE);
	   filterGraph->SetColor(4, CYAN);
			
	   //set up legend
	   filterGraph->SetLegend(0, "EKF");
	   filterGraph->SetLegend(1, "UKF");
	   filterGraph->SetLegend(2, "Third-degree CKF");
	   filterGraph->SetLegend(3, "ECKF");
	   filterGraph->SetLegend(4, "Fifth-degree CKF");

	}
   
   graphComplete = TRUE;
   Invalidate(TRUE);
}

void CNonlinear_FilteringView::OnHelper()
{
	// TODO: �ڴ���������������
	CString pszPath;
	GetExcuteProgPath(pszPath);//��ȡ��ǰ�ļ�·��
	ShellExecute(NULL,"open","help.pdf",NULL,pszPath,SW_SHOWNORMAL);
}
