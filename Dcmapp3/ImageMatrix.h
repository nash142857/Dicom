#pragma once
#include "DCMHeaders.h"
#include <string>
class ImageMatrix
{
private:
	CString patientid;
	CString patientname;
	Uint16 mRows;
	Uint16 mColumns;
	//数据源指针
	Uint16 *mPixData16;
	Uint8 *mPixData8;
	double mWindowCenter;
	double mWindowWidth;
	int mPixLength;
	bool kind;
public:
	ImageMatrix(void);
	ImageMatrix(DcmDataset *dataset);
	~ImageMatrix(void);
	CString getname(){
		return patientname;
	}
	CString getid(){
		return patientid;
	}
	Uint16 getRows();
	Uint16 getColumns();
	double getWinCenter();
	double getWinWidth();
	static std::string get_patientname(const std::string &);//get a file's patient name
	//得到[row,column]处的pixel data
	//get pixel data of the position
	Uint8 getUint8Pixel(int row, int column);
	Uint16 getUint16Pixel(int row, int column);
	void setUint16Pixel(int row, int column, Uint16 pixelValue);
	//得到数据指针
	Uint8* getUint8Data();
	Uint16* getUint16Data();
	CString mContentTime;
	CString mTestInfo;
	Uint8 mIndex;
	Float64 pixelSpacing;//每个像素之间的实际距离 单位是毫米
	Float64 sliceThickness;//切片厚度
	Float32 PWICoe;//一个PWI系数
};
