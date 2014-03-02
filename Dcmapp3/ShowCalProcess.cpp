// ShowCalProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "ShowCalProcess.h"
#include "afxdialogex.h"
#include "Patient_information.h"
#include "common.h"
// CShowCalProcess 对话框

IMPLEMENT_DYNAMIC(CShowCalProcess, CDialogEx)
std::string CShowCalProcess::id = "";
std::string CShowCalProcess::name = "";
std::vector <Patient_information> CShowCalProcess::res;
CShowCalProcess::CShowCalProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowCalProcess::IDD, pParent)
{

}

CShowCalProcess::~CShowCalProcess()
{
}

void CShowCalProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, ProcessCtrl);
	DDX_Control(pDX, IDC_EDIT4, doing);
	DDX_Control(pDX, IDC_BUTTON1, cancel_button);
}


BEGIN_MESSAGE_MAP(CShowCalProcess, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CShowCalProcess::OnBnClickedButton1)
END_MESSAGE_MAP()


// CShowCalProcess 消息处理程序
struct threaddata{
	CStatic * text;
	CProgressCtrl * speed;
	CShowCalProcess * reverse_ptr;
};

BOOL CShowCalProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	finished = false;
	threaddata * tmp = new threaddata();
	tmp -> text = & doing;
	tmp -> speed = &ProcessCtrl;
	tmp -> reverse_ptr = this;
	handle = CreateThread(0, 0, getonlinedata, tmp, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
DWORD WINAPI  CShowCalProcess::getonlinedata(LPVOID lpParameter){

		//here to get data...
		threaddata * tmp = (threaddata *)(lpParameter);
		CProgressCtrl *Speed = tmp -> speed;
		CStatic * text = tmp -> text;
		text -> SetWindowTextW(L"开始计算");
		for (int i = 0; i < 1000; i++)  
		{  
			Speed -> SetPos(i);
			if(i == 250)
				text -> SetWindowTextW(L"正在计算ADC");
			else
			if(i == 500)
				text -> SetWindowTextW(L"正在计算MTT");
			else
				if(i == 750)
				text -> SetWindowTextW(L"正在计算结果");
			Sleep(10);
		}	  
		AfxMessageBox(L"计算完成");
		res.clear();
		std::shared_ptr <ADOConn> getcon = ADOConn::sharedSingleton();
		bool search_flag = true;
		res = getcon -> search_both(id, name);
		std::sort(res.begin(), res.end(), cmp);
		if(res.size() == 0){
			AfxMessageBox(L"找不到这样的人");
		}
		tmp -> reverse_ptr -> cancel_button.SetWindowTextW(L"完成");
		tmp -> reverse_ptr -> finished = true;
		return 0;
	}



void CShowCalProcess::OnBnClickedButton1()
{
	if(finished){
		OnOK();
	}
	else{
		TerminateThread(handle, 1);
		OnCancel();
	}
	// TODO: 在此添加控件通知处理程序代码
}
