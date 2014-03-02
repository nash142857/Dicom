// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Dcmapp3Dlg.h"

// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnBnClickedOk()
{
	CString username, password;
	GetDlgItemText(IDC_EDIT1, username);
	GetDlgItemText(IDC_EDIT4, password);
	if(username == "test" && password == "test"){
		CDcmapp3Dlg::login_state = true;
		CDcmapp3Dlg::username = username;
		AfxMessageBox(L"登录成功");
		OnOK();
	}
	else
		{
		AfxMessageBox(L"登录失败");	
	}
	// TODO: 在此添加控件通知处理程序代码
}
