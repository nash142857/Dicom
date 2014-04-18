#pragma once


// Cshowsavepic 对话框

class Cshowsavepic : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowsavepic)

public:
	Cshowsavepic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cshowsavepic();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
