#pragma once
#include "afxcmn.h"
#include <string>
#include <vector>
#include "Patient_information.h"
#include <memory>
#include <algorithm>
#include "ADOConn.h"
#include "afxwin.h"
// CShowCalProcess �Ի���

class CShowCalProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CShowCalProcess)

public:
	CShowCalProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowCalProcess();
	static std::vector <Patient_information> res;
	static std::string id, name;
// �Ի�������
	enum { IDD = IDD_DIALOG5 };
	void set(std::string _id, std::string _name){
		id = _id;
		name = _name;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	static DWORD WINAPI  getonlinedata(LPVOID lpParameter);

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl ProcessCtrl;
	virtual BOOL OnInitDialog();
	CStatic doing;
	afx_msg void OnBnClickedButton1();
	CButton cancel_button;
	handle_t handle;
	static bool finished;
};
