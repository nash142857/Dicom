#pragma once
#include "ImageMatrix.h"
#include <vector>
using std::vector;
class DCMPatientInfo
{
private:
	CString mPatientID;
	CString mPatientName;
	double mPWIVolumn;
	double mDWIVolumn;
	int mDWINum;
	int mPWINum;
	int getIndex(int imageIndex, int row, int column, int type);//�ó�һ�����Ӧ����ı��
	void floodFill(int imageIndex, int row, int column, int *count, int type, vector <int> & res);//�������BFS
	bool checkADC(int index);
	bool checkPWI(int index);
	bool check(int index, int type);
	bool volumnCompare(Float64 unitVolumn, int pixelCount, int type);
	DCMPatientInfo(void);
	void cutpoint(vector <int> & vt, int type);
	int cutadcfloor();//cut the discrete point
	int cutpointnum;
	int maxadc;
public:
	ImageMatrix** mDWIImageList;
	ImageMatrix** mPWIImageList;
	~DCMPatientInfo(void);
	void resetconfig(int _cutpointnum = 0, int _maxadc = 600){
		cutpointnum = _cutpointnum;
		maxadc = _maxadc;
		mPWIVolumn = mDWIVolumn = -1;
	}
	DCMPatientInfo(DcmDataset** DWIDataSet, const int& DWICount, DcmDataset** PWIDataSet, const int& PWICount);
	CString getID(){
		return mPatientID;
	}
	CString getPatientname(){
		return mPatientName;
	}
	double getDWIVolumn();//�õ�DWI��ֵ
	double getPWIVolumn();//�õ�PWI��ֵ
	int mDWIWidth;
	int mDWIHeight;
	int mPWIWidth;
	int mPWIHeight;
	vector < const UINT16 * > getDWIdata(){
		vector < const UINT16 * > res;
		for(int  i = 0; i < mDWINum; ++i){
			res.push_back(mDWIImageList[i] -> getUint16Data());
		}
		return res;
	}
};

