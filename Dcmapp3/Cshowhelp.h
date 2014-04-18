#pragma once
#include "afxwin.h"


// Cshowhelp 对话框

class Cshowhelp : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowhelp)

public:
	Cshowhelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cshowhelp();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	CStatic text;
	virtual BOOL OnInitDialog();
};
