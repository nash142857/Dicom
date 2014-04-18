#pragma once
#include "afxwin.h"
#include <map>
#include <string>
#include <memory>
using std::string;
using std::map;
using std::shared_ptr;
// Csetparam �Ի���

class Csetparam : public CDialogEx
{
	DECLARE_DYNAMIC(Csetparam)

public:
	Csetparam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Csetparam();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
		explain["psetnum"] = "PWI��������";
		explain["pslicenum"] = "PWI����ÿ��������Ƭ��";
		explain["te"] = "PWI������Ƭ��ȡʱ����";
		explain["tr"] = "PWI�������ݻ�ȡʱ����";
		explain["stdnum"] = "��ȡ��עǰ��׼ͼ����������";
		explain["pmask"] = "�ж�MASK��PWI�ź�ֵ��Ӧ���ڵİٷֱ�";
		explain["ck"] = "PWI�����4���еĲ��캯����3������ϵ������";
		explain["ttype"] = "0��ʾ1.5T�ͺţ�1��ʾ3.0T�ͺ�";
		explain["x"] = "PWI�����7����2�����Ͷ�Ӧ��3������";
		explain["pr"] = "PWI�����8���У�����n�õ��ĳ���";
		explain["ro"] = "����cbv��cbf�õ��ĳ���";
		explain["hsv"] = "����cbv��cbf�õ��ĳ���";
		explain["hlv"] = "����cbv��cbf�õ��ĳ���";
		explain["coef"] = "���㾭�鳣��K0ʱ�õ���100";
		explain["cbfc"] = "����CBFʱ���õ��ĳ���60";
		explain["mttc"] = "����MTTʱ�õ��ĳ���60";
		explain["tmax_th"] = "�ж�PWI����ʱ����ֵΪ6��";
		explain["vp_th"] = "����VP����ֵΪ3ml";
		explain["dsetnum"] = "DWI��������";
		explain["dslicenum"] = "DWIÿ�����ݵ���Ƭ��";
		explain["b"] = "ADC����";
		explain["adcmin"] = "�ж�mask��adc��Ч��Χ";
		explain["adcmax"] = "�ж�mask��adc��Ч��Χ";
		explain["adc_th"] = "�ж�DWI�����ADC��ֵ";
		explain["vd_th"] = "����Vd����ֵΪ1ml";
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
