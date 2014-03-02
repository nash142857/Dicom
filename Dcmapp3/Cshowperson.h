#pragma once
#include "DCMPatientInfo.h"
#include <memory>
#include "afxwin.h"

// Cshowperson 对话框

class Cshowperson : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowperson)

public:
	Cshowperson(CWnd* pParent = NULL);   // 标准构造函数
	void setdata(std::shared_ptr <DCMPatientInfo> _patient_data, std::string _id){
		id = _id;
		patient_data = _patient_data;
	}
	virtual ~Cshowperson();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	std::shared_ptr <DCMPatientInfo> patient_data;
	std::string id;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	double pwivalue;
	double dwivalue;
	double mismatch;
	CStatic picdata;
	afx_msg void OnPaint();
};
