#include "StdAfx.h"
#include "DCMPatientInfo.h"
#include <deque>
#include <vector>
#include <set>
#include <utility>
using namespace std;

deque <int> queue;
bool *flags;
#define PWI_TYPE	100
#define DWI_TYPE	101

#define no_pwi
DCMPatientInfo::~DCMPatientInfo(void)
{
	if(mDWIImageList != NULL) delete[] mDWIImageList;
	if(mPWIImageList != NULL) delete[] mPWIImageList;
}

DCMPatientInfo::DCMPatientInfo(DcmDataset** DWIDataSet, const int& DWICount, DcmDataset** PWIDataSet, const int& PWICount)
{
	mDWIVolumn = mPWIVolumn = -1;//初始化 mDWIVolumn = -1;
	//DWICount 和 PWICount 分别表示的是对应图片的数量*/
	mDWINum = DWICount;
	maxadc = 600;//initial adc parameter
	cutpointnum = 20;//initial cut point num parameter
	mDWIImageList = (ImageMatrix**)malloc(DWICount * sizeof(ImageMatrix*));
	for (int i = 0; i < DWICount; i++) {
		ImageMatrix *image = new ImageMatrix(DWIDataSet[i]);
		mDWIImageList[i] = image;
	}
	mDWIWidth = mDWIImageList[0]->getColumns();
	mDWIHeight = mDWIImageList[0]->getRows();
	mPatientID = mDWIImageList[0]->getid();
	mPatientName  = mDWIImageList[0] ->getname();
#ifndef no_pwi
	mPWINum = PWICount;
	mPWIImageList = (ImageMatrix**)malloc(PWICount * sizeof(ImageMatrix*));
	for (int i = 0; i < PWICount; i++) {
		ImageMatrix *image = new ImageMatrix(PWIDataSet[i]);
		mPWIImageList[i] = image;
	}
	mPWIWidth = mPWIImageList[0]->getColumns();
	mPWIHeight = mPWIImageList[0]->getRows();
#endif
}

bool test_volumnCompare(Float64 unitVolumn, int count, int type){
	static const int tes_max_grid = 10;
	if(type == DWI_TYPE){
		return count > tes_max_grid;
	}
}
double DCMPatientInfo::getDWIVolumn()
{
	if (mDWIVolumn > 0) return mDWIVolumn;
	flags = (bool *)malloc(sizeof(bool) * mDWIWidth * mDWIHeight * mDWINum);
	memset(flags,false,sizeof(bool) * mDWIWidth * mDWIHeight * mDWINum);
	ImageMatrix *image = mDWIImageList[0];
	Float64 pixelArea = image->pixelSpacing * image->pixelSpacing;
	Float64 unitHeight = image->sliceThickness;
	Float64 unitVolumn = unitHeight* pixelArea / 1000;//unitHeight每一unit的实际体积
	double sum = 0;
	for (int i = 0; i < mDWINum; i++){
		for(int j = 0; j < mDWIWidth; j++)
			for (int k = 0; k < mDWIHeight; k++) {
				int index = getIndex(i,j,k,DWI_TYPE);
				if (!flags[index]) {
					int count = 0;
					queue.clear();
					vector <int> res; // bfs point
					floodFill(i, j, k, &count, DWI_TYPE, res);
				//	cutpoint(res, DWI_TYPE); // cut the point
					if (volumnCompare(unitVolumn, count, DWI_TYPE)){
						sum += res.size();
						for(const int & tIndex : res){ // render the pixel 
							int tImageIndex = tIndex / (mDWIWidth * mDWIHeight);
							int tRow = tIndex % (mDWIWidth * mDWIHeight) / mDWIWidth;
							int tColumn = tIndex % (mDWIWidth * mDWIHeight) % mDWIWidth;
							mDWIImageList[tImageIndex] -> setUint16Pixel(tRow, tColumn, 10000); // for special render
						}
					}
					count = 0;
				}
			}
	}
	free(flags);
	sum -= cutadcfloor();
	mDWIVolumn = sum * unitVolumn;
	return mDWIVolumn;
}

double DCMPatientInfo::getPWIVolumn()
{
#ifdef no_pwi
	return -1;
#endif
	if (mPWIVolumn > 0) return mPWIVolumn;

	flags = (bool *)malloc(sizeof(bool) * mPWIWidth * mPWIHeight * mPWINum);
	memset(flags, false, sizeof(bool) * mPWIWidth * mPWIHeight * mPWINum);
	bool test = flags[11];

	ImageMatrix *image = mPWIImageList[0];
	Float64 pixelArea = image->pixelSpacing * image->pixelSpacing;
	Float64 unitHeight = image->sliceThickness;
	Float64 unitVolumn = unitHeight * pixelArea / 1000;

	double sum = 0;
	vector <int> res;
	for (int i = 0; i < mPWINum; i++){
		for(int j = 0; j < mPWIWidth; j++)
			for (int k = 0; k < mPWIHeight; k++) {
				int index = getIndex(i,j,k,PWI_TYPE);
				if (!flags[index]) {
					int count = 0;
					queue.clear();
					floodFill(i, j, k, &count, PWI_TYPE, res);
					if(volumnCompare(unitVolumn, count, PWI_TYPE))
						sum+=count;
					count = 0;
				}
			}
	}
	free(flags);
	mPWIVolumn = sum * unitVolumn;
	return mPWIVolumn;
}

//private methods
bool DCMPatientInfo::volumnCompare(Float64 unitVolumn, int count, int type)
{
	if (count == 0) return false;
	if (type == PWI_TYPE) return unitVolumn * count >= 1;
	else return unitVolumn * count >= 1;// 1和1都是假定的值
}

int DCMPatientInfo::getIndex(int imageIndex, int row, int column, int type)
{
	if (type == DWI_TYPE){
		int t = mDWIWidth * mDWIHeight;
		return t*imageIndex + row * mDWIWidth + column;
	}
	else {
		int t = mPWIWidth * mPWIHeight;
		return t*imageIndex + row * mPWIWidth + column;
	}
}

void DCMPatientInfo::floodFill(int imageIndex, int row, int column, int *count, int type, vector <int> & res) 
{
	res.clear();
	int index = getIndex(imageIndex, row, column, type);
	if (!flags[index] && check(index, type)){
		queue.push_back(index);
		(*count)++;
	}
	flags[index] = true;
	int width, height, num;
	if (type == PWI_TYPE){
		width = mPWIWidth;
		height = mPWIHeight;
		num = mPWINum;
	}
	else {
		width = mDWIWidth;
		height = mDWIHeight;
		num = mDWINum;
	}
	while (!queue.empty()) {
		int tIndex = queue.front();
		res.push_back(tIndex);	//push_back bfs point
		int tImageIndex = tIndex / (width * height);
		int tRow = tIndex % (width * height) / width;
		int tColumn = tIndex % (width * height) % width;
		//up
		if (tImageIndex > 0) {
			int upIndex = getIndex(tImageIndex - 1, tRow, tColumn, type);
			if (!flags[upIndex] && check(upIndex, type)){
				queue.push_back(upIndex);
				(*count)++;
			}
			flags[upIndex] = true;
		}
		//down
		if (tImageIndex < num - 1) {
			int downIndex = getIndex(tImageIndex + 1, tRow, tColumn, type);
			if (flags[downIndex] == 0 && check(downIndex, type)){
				queue.push_back(downIndex);
				(*count)++;
			}
			flags[downIndex] = true;
		}
		//left
		if (tColumn > 0) {
			int leftIndex = getIndex(tImageIndex, tRow, tColumn - 1, type);
			if (flags[leftIndex] == 0 && check(leftIndex, type)){
				queue.push_back(leftIndex);
				(*count)++;
			}
			flags[leftIndex] = true;
		}
		//right
		if (tColumn < width - 1) {
			int rightIndex = getIndex(tImageIndex, tRow, tColumn + 1, type);
			if (flags[rightIndex] == 0 && check(rightIndex, type)){
				queue.push_back(rightIndex);
				(*count)++;
			}
			flags[rightIndex] = true;
		}
		//front
		if (tRow > 0) {
			int frontIndex = getIndex(tImageIndex, tRow - 1, tColumn, type);
			if (flags[frontIndex] == 0 && check(frontIndex, type)){
				queue.push_back(frontIndex);
				(*count)++;
			}
			flags[frontIndex] = true;
		}
		//back
		if (tRow < height - 1) {
			int backIndex = getIndex(tImageIndex, tRow + 1, tColumn, type);
			if (flags[backIndex] == 0 && check(backIndex, type)){
				queue.push_back(backIndex);
				(*count)++;
			}
			flags[backIndex] = true;
		}
		queue.pop_front();
	}
}

bool DCMPatientInfo::check(int index, int type)
{
	if (type == DWI_TYPE) return checkADC(index);
	else if (type == PWI_TYPE) return checkPWI(index);
	return false;
}

bool DCMPatientInfo::checkADC(int index)
{
	int tImageIndex = index / (mDWIWidth * mDWIHeight);
	int tRow = index % (mDWIWidth * mDWIHeight) / mDWIWidth;
	int tColumn = index % (mDWIWidth * mDWIHeight) % mDWIWidth;
	
	ImageMatrix *image = mDWIImageList[tImageIndex];
	int pixel = image->getUint16Pixel(tRow, tColumn);
	
	if (pixel <= maxadc && pixel > 100) { // 这个根据阈值的区间改变
		//render
		//image->setUint16Pixel(tRow, tColumn, 5000);
		return true;
	}
	else return false;
}

bool DCMPatientInfo::checkPWI(int index)
{
	int tImageIndex = index / (mPWIWidth * mPWIHeight);
	int tRow = index % (mPWIWidth * mPWIHeight) / mPWIWidth;
	int tColumn = index % (mPWIWidth * mPWIHeight) % mPWIWidth;

	ImageMatrix *image = mPWIImageList[tImageIndex];
	int pixel = image->getUint16Pixel(tRow, tColumn);
	Float64 coe = image->PWICoe * 5000;
	//coe一个自定义系数
	if (pixel < 600){
		if (pixel * coe > 6) {
			//render
			image->setUint16Pixel(tRow, tColumn, 2000);//为了显示需求
			return true;
		}
		else return false;
	}
	else return false;
}
void DCMPatientInfo::cutpoint(vector <int> & vt, int type){
	if(type == DWI_TYPE){
		set <int> s;
		vector <int> res;
		for(int i = 0; i < vt.size(); ++i){
			s.insert(vt[i]);
		}
		for(int i = 0; i < vt.size(); ++i){
			int imgindex = vt[i] / (mDWIHeight * mDWIWidth);
			if(imgindex == 0 || imgindex == mDWINum - 1){
				if(s.find(vt[i] + mDWIHeight * mDWIWidth) != s.end() || 
				s.find(vt[i] - mDWIHeight * mDWIWidth) != s.end()){
					res.push_back(vt[i]);
				}
			}
			else if(s.find(vt[i] + mDWIHeight * mDWIWidth) != s.end() &&
				s.find(vt[i] - mDWIHeight * mDWIWidth) != s.end()){
				res.push_back(vt[i]);
			}
		}
		vt = res;
	}
}
int DCMPatientInfo::cutadcfloor(){
	int dx[] = {0, 0, -1, 1};
	int dy[] = {1, -1, 0, 0};
	bool * flag = new bool[mDWIHeight * mDWIWidth];
	int sum = 0;
	for(int i = 0; i < mDWINum; ++i){//for every img
		memset(flag, 0, sizeof(bool) * mDWIHeight * mDWIWidth);
		for(int j = 0; j < mDWIHeight; ++j)
			for(int k = 0; k < mDWIWidth; ++k){
				if(mDWIImageList[i] -> getUint16Pixel(j,k) == 10000 && !flag[j * mDWIWidth + k]){
					vector <int> tmp; 
					queue.clear();
					int tmp_sum = 1;
					flag[j * mDWIWidth + k] = true;
					queue.push_back(j * mDWIWidth + k);
					tmp.push_back(j * mDWIWidth + k);
					while(!queue.empty()){
						int st = queue.front();
						queue.pop_front();
						int x = st / mDWIWidth;
						int y = st % mDWIWidth;
						for(int dic = 0; dic < 4; ++dic){
							int xx = x + dx[dic];
							int yy = y + dy[dic];
							if(xx < 0 || x >= mDWIHeight || yy < 0 || yy >= mDWIWidth){
								continue;
							}
							if(mDWIImageList[i] -> getUint16Pixel(xx,yy) == 10000 && !flag[xx * mDWIWidth + yy]){
								flag[xx * mDWIWidth + yy] = true;
								++tmp_sum;
								queue.push_back(xx * mDWIWidth + yy);
								tmp.push_back(xx * mDWIWidth + yy);
							}
						}
					}
					if(tmp_sum <= cutpointnum){
						sum += tmp_sum;
						for(int o = 0;  o < tmp.size(); ++o){
							mDWIImageList[i] -> setUint16Pixel(tmp[o] / mDWIWidth, tmp[o] % mDWIWidth, 1000);
						}
					}
				}
			}
	}
	delete [] flag;
	return sum;
}
