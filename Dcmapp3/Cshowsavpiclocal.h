#pragma once


// Cshowsavpiclocal 对话框

class Cshowsavpiclocal : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowsavpiclocal)

public:
	Cshowsavpiclocal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cshowsavpiclocal();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString versionname;
	DECLARE_MESSAGE_MAP()
public:
	void setversion(const CString & version){
		versionname = version;
	}
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
};
