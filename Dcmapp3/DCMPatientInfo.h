#pragma once
#include "ImageMatrix.h"
class DCMPatientInfo
{
private:
	CString mPatientID;
	CString mPatientName;
	double mPWIVolumn;
	double mDWIVolumn;
	int mDWINum;
	int mPWINum;
	int mDWIWidth;
	int mDWIHeight;
	int mPWIWidth;
	int mPWIHeight;
	int getIndex(int imageIndex, int row, int column, int type);//得出一个点对应整体的编号
	void floodFill(int imageIndex, int row, int column, int *count, int type);//在这个点BFS
	bool checkADC(int index);
	bool checkPWI(int index);
	bool check(int index, int type);
	bool volumnCompare(Float64 unitVolumn, int pixelCount, int type);
	DCMPatientInfo(void);
public:
	ImageMatrix** mDWIImageList;
	ImageMatrix** mPWIImageList;
	~DCMPatientInfo(void);
	DCMPatientInfo(DcmDataset** DWIDataSet, const int& DWICount, DcmDataset** PWIDataSet, const int& PWICount);
	CString getID(){
		return mPatientID;
	}
	CString getPatientname(){
		return mPatientName;
	}
	double getDWIVolumn();//得到DWI的值
	double getPWIVolumn();//得到PWI的值
};

