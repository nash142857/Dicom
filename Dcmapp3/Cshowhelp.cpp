// Cshowhelp.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowhelp.h"
#include "afxdialogex.h"


// Cshowhelp 对话框

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



// Cshowhelp 消息处理程序



BOOL Cshowhelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * font = new CFont();
	font -> CreateFont(30,0,0,0,700,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Courier New"); 
	text.SetFont(font);
	text.SetWindowTextW(L"     欢迎来到\n\n脑部图像研究系统");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
