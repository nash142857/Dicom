#pragma once


// Cshowsavepic �Ի���

class Cshowsavepic : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowsavepic)

public:
	Cshowsavepic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cshowsavepic();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
