// Cshowsavepic.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowsavepic.h"
#include "afxdialogex.h"
#include "Cshowsavpiclocal.h"
#include "Cnamesavefile.h"
// Cshowsavepic 对话框

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


// Cshowsavepic 消息处理程序


void Cshowsavepic::OnBnClickedOk()
{

	Cnamesavefile localdig;
	localdig.DoModal();
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void Cshowsavepic::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
