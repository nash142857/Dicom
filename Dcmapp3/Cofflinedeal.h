#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <algorithm>
#include <utility>

// Cofflinedeal 对话框

class Cofflinedeal : public CDialogEx
{
	DECLARE_DYNAMIC(Cofflinedeal)

public:
	Cofflinedeal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cofflinedeal();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HANDLE handle_cal_control;
	void exec_once(){
		static bool flag = false;
		if(flag)return;
		flag = true;
		cal_mutex = CreateMutex(NULL, false, L"calmutex");
	}
	static bool is_cal_ing;
	static HANDLE cal_mutex;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton8();
	CProgressCtrl ProcessCtrl;
	static DWORD WINAPI  controlprocess(LPVOID lpParameter);
	CStatic ShowProcessStatusTxt;
};
