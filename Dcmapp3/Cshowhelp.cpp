// Cshowhelp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowhelp.h"
#include "afxdialogex.h"


// Cshowhelp �Ի���

IMPLEMENT_DYNAMIC(Cshowhelp, CDialogEx)

Cshowhelp::Cshowhelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cshowhelp::IDD, pParent)
{

}

Cshowhelp::~Cshowhelp()
{
}

void Cshowhelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT91, text);
}



// Cshowhelp ��Ϣ�������



BOOL Cshowhelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * font = new CFont();
	font -> CreateFont(30,0,0,0,700,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Courier New"); 
	text.SetFont(font);
	text.SetWindowTextW(L"     ��ӭ����\n\n�Բ�ͼ���о�ϵͳ");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
