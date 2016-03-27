//////////////////////////////////////////////////////////////////////////////////
//Version: 20130614                                                            ///
//(Matrix class for the basic matrix operations)                               ///    
//                                                                             ///
//                                                by  Xin-Chun Zhang(UESTC)    ///
//                                                   irving_zhang@163.com      ///
//                                                  Update data: 2013-6-14     ///
//////////////////////////////////////////////////////////////////////////////////

#ifndef _AFX_MATRIX_HEADER_
#define _AFX_MATRIX_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define   TINY 1.0e-20

//�����࣬���ھ��������
class CMatrix  
{
public:
	double **m_mat;//����ָ��
	int m_row;//���������
	int m_col;

public:
	CMatrix();
	CMatrix(int);//���ع��캯�������ڹ��췽��
	CMatrix(int,int);//���ع��캯�������ڹ���ָ���к��еľ���
	CMatrix (const CMatrix &);//��ʽ���ƹ��캯��
	virtual ~CMatrix();//��������

public:
	void SetSize(int);//�趨�����ά��
	void SetSize(int,int);//�趨������к���
	double MaxMod();//����ģֵ������ֵ������Ԫ��
	CMatrix Cholesky();//Cholesky�ֽ⣬��ȡ�����Ǿ���

public:
	//����Ϊ����������
	CMatrix& operator =(CMatrix &);//����ֵ
	CMatrix operator +(CMatrix &);//����ӷ�
	CMatrix operator -(CMatrix &);//�������
	CMatrix operator *(CMatrix &);//����˷�
	CMatrix operator /(double);//�������һ����
	CMatrix operator !();//��������
	CMatrix operator ~();//����ת��
	double & operator ()(int,int);//ȡ����ĳ��ĳ�е�Ԫ��
	CMatrix operator *(double);//�����������
	friend CMatrix operator *(double d , CMatrix& m) {return m * d;}//����������
	

//Dolittle�ֽ��������
protected:
	void MatInverse(double** mat, int dim);
	void MatLudcmp(double** mat, int, int*, double*);
	void MatLubksb(double** mat, int, int*, double*);
};

#endif // _AFX_MATRIX_HEADER_
