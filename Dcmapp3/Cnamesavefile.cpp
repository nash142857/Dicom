// Cnamesavefile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cnamesavefile.h"
#include "afxdialogex.h"
#include "Cshowsavpiclocal.h"
// Cnamesavefile �Ի���
IMPLEMENT_DYNAMIC(Cnamesavefile, CDialogEx)

Cnamesavefile::Cnamesavefile(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cnamesavefile::IDD, pParent)
	, versionname(_T(""))
{

}

Cnamesavefile::~Cnamesavefile()
{
}

void Cnamesavefile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, versionname);
}


BEGIN_MESSAGE_MAP(Cnamesavefile, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Cnamesavefile::OnBnClickedCancel)
	ON_BN_CLICKED(ID_SAVE_CANCEL, &Cnamesavefile::save_to_local)
END_MESSAGE_MAP()




// Cnamesavefile ��Ϣ�������


void Cnamesavefile::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void Cnamesavefile::save_to_local()
{

	UpdateData(true);
	Cshowsavpiclocal issavelocal;
	issavelocal.setversion(versionname);
	if(issavelocal.DoModal() == IDOK){
		OnOK();
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
