#pragma once
#include <string>
#include "Cshowperson.h"
// Cnamesavefile �Ի���
#include "common.h"

class Cnamesavefile : public CDialogEx
{
	DECLARE_DYNAMIC(Cnamesavefile)

public:
	Cnamesavefile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cnamesavefile();

// �Ի�������
	enum { IDD = IDD_DIALOG10 };
	void set_local_or_online(bool flag){ // write only
		local_or_online = flag;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	bool local_or_online;
	DECLARE_MESSAGE_MAP()
	CString versionname;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void save_to_local();
};
