#pragma once


// Cshowsavpiclocal �Ի���

class Cshowsavpiclocal : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowsavpiclocal)

public:
	Cshowsavpiclocal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cshowsavpiclocal();

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString versionname;
	DECLARE_MESSAGE_MAP()
public:
	void setversion(const CString & version){
		versionname = version;
	}
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
};
