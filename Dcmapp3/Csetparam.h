#pragma once
#include "afxwin.h"
#include <map>
#include <string>
#include <memory>
using std::string;
using std::map;
using std::shared_ptr;
// Csetparam 对话框

class Csetparam : public CDialogEx
{
	DECLARE_DYNAMIC(Csetparam)

public:
	Csetparam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Csetparam();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	static const  std::string paramfilename;
	void setconfig();
	DECLARE_MESSAGE_MAP()
private: 
	void update_input();
	shared_ptr <CStatic> explain_label;
public:
	static map <string, string> explain;//explain english to chinese
	void init_map(){
		static bool flag = false;//init flag
		if(flag)return;
		flag = true;
		explain["psetnum"] = "PWI数据总数";
		explain["pslicenum"] = "PWI名字每组数据切片数";
		explain["te"] = "PWI相邻切片获取时间间隔";
		explain["tr"] = "PWI两套数据获取时间间隔";
		explain["stdnum"] = "获取灌注前标准图像的套数编号";
		explain["pmask"] = "判断MASK的PWI信号值不应低于的百分比";
		explain["ck"] = "PWI处理第4步中的差异函数的3个经验系数常数";
		explain["ttype"] = "0表示1.5T型号，1表示3.0T型号";
		explain["x"] = "PWI处理第7步中2种类型对应的3个常数";
		explain["pr"] = "PWI处理第8步中，计算n用到的常数";
		explain["ro"] = "计算cbv和cbf用到的常数";
		explain["hsv"] = "计算cbv和cbf用到的常数";
		explain["hlv"] = "计算cbv和cbf用到的常数";
		explain["coef"] = "计算经验常熟K0时用到的100";
		explain["cbfc"] = "计算CBF时候用到的常数60";
		explain["mttc"] = "计算MTT时用到的常数60";
		explain["tmax_th"] = "判断PWI病灶时的阈值为6秒";
		explain["vp_th"] = "过滤VP的阈值为3ml";
		explain["dsetnum"] = "DWI数据总数";
		explain["dslicenum"] = "DWI每套数据的切片数";
		explain["b"] = "ADC常数";
		explain["adcmin"] = "判断mask的adc有效范围";
		explain["adcmax"] = "判断mask的adc有效范围";
		explain["adc_th"] = "判断DWI病灶的ADC阈值";
		explain["vd_th"] = "过滤Vd的阈值为1ml";
	}
	virtual BOOL OnInitDialog();
	int Psetnum;
	int Pslicenum;
	int TE;
	int TR;
	int STDNum;
	double Pmask;
	double ck1;
	double ck2;
	double ck3;
	int TType;
	double x00;
	double x01;
	double x02;
	double x10;
	double x11;
	double x12;
	double pr;
	double ro;
	double hsv;
	double hlv;
	int coef;
	int cbfc;
	int mttc;
	int Tmax_th;
	double VP_th;
	int Dsetnum;
	int Dslicenum;
	int b;
	double adcmin;
	double adcmax;
	double adc_th;
	double VD_th;
	int gethash(){
		double rt = 0;
		rt += Psetnum;
		rt *= 10;
		rt += Pslicenum; 
		rt *= 10;
		rt += TE;
		rt *= 10;
		rt += TR;
		rt *= 10;
		rt += STDNum;
		rt *= 10;
		rt += Pmask;
		rt *= 10;
		rt += ck1;
		rt *= 10;
		rt += ck2;
		rt *= 10;
		rt += ck3;
		rt *= 10;
		rt += TType;
		rt *= 10;
		rt += x00;
		rt *= 10;
		rt += x01;
		rt *= 10;
		x02 += x02;
		rt *= 10;
		rt += x10;
		rt *= 10;
		rt += x11;
		rt *= 10;
		rt += x12;
		rt *= 10;
		rt += pr;
		rt *= 10;
		rt += ro;
		rt *= 10;
		rt += hsv;
		rt *= 10;
		rt += hlv;
		rt *= 10;
		rt += coef;
		rt *= 10;
		rt += cbfc;
		rt *= 10;
		rt +=mttc;
		rt *= 10;
		rt += Tmax_th;
		rt *= 10;
		rt += VP_th;
		rt *= 10;
		rt += Dsetnum;
		rt *= 10;
		rt += b;
		rt *= 10;
		rt += adcmin;
		rt *= 10;
		rt += adcmax;
		rt *= 10;
		rt += adc_th;
		rt *= 10;
		rt += VD_th;
		return (int)rt;
	}
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
};
