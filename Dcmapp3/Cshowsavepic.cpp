// Cshowsavepic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowsavepic.h"
#include "afxdialogex.h"
#include "Cshowsavpiclocal.h"
#include "Cnamesavefile.h"
// Cshowsavepic �Ի���

IMPLEMENT_DYNAMIC(Cshowsavepic, CDialogEx)

Cshowsavepic::Cshowsavepic(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cshowsavepic::IDD, pParent)
{

}

Cshowsavepic::~Cshowsavepic()
{
}

void Cshowsavepic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cshowsavepic, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cshowsavepic::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cshowsavepic::OnBnClickedCancel)
END_MESSAGE_MAP()


// Cshowsavepic ��Ϣ�������


void Cshowsavepic::OnBnClickedOk()
{

	Cnamesavefile localdig;
	localdig.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void Cshowsavepic::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
