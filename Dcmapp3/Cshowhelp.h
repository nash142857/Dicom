#pragma once
#include "afxwin.h"


// Cshowhelp �Ի���

class Cshowhelp : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowhelp)

public:
	Cshowhelp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cshowhelp();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	CStatic text;
	virtual BOOL OnInitDialog();
};
