#pragma once
#include "StdAfx.h"
#include "DCMConst.h"
#include "ImageMatrix.h"


ImageMatrix::ImageMatrix(void)
{

}

ImageMatrix::ImageMatrix(DcmDataset* dataset)
{
	Uint16 bitsAllocated;
	Uint16 bitsStored;
	const char * name;
	dataset->findAndGetString(DCM_PatientID,name);
	patientid.Format(L"%s",name);
	dataset->findAndGetString(DCM_PatientName,name);
	patientname = name;
	dataset->findAndGetUint16(DCM_BitsAllocated,bitsAllocated);
	dataset->findAndGetUint16(DCM_BitsStored,bitsStored);
	dataset->findAndGetUint16(DCM_Columns,mColumns);
	dataset->findAndGetUint16(DCM_Rows,mRows);
	dataset->findAndGetFloat64(DCM_WindowCenter,mWindowCenter);
	dataset->findAndGetFloat64(DCM_WindowWidth,mWindowWidth);
	dataset->findAndGetFloat32(PWI_COE_KEY,PWICoe);
	dataset->findAndGetFloat64(DCM_PixelSpacing,pixelSpacing);
	dataset->findAndGetFloat64(DCM_SliceThickness,sliceThickness);
	unsigned long count;
	kind = (bitsAllocated == 16)?1:0;
	if(bitsAllocated == 16 && bitsAllocated == bitsStored){
		const Uint16 *pixData;
		dataset->findAndGetUint16Array(DCM_PixelData, pixData, &count);
		if(count != mColumns * mRows){
			printf("Unsupported File Format");
			return;
		}
		mPixLength = 16;
		mPixData16 = (Uint16 *)malloc(sizeof(Uint16) * count);
		for(size_t i = 0; i < count; i++)
			mPixData16[i] = pixData[i];
	}
	else if(bitsAllocated == 8 && bitsAllocated == bitsStored){
		const Uint8 *pixData;
		dataset->findAndGetUint8Array(DCM_PixelData, pixData, &count);
		if(count != mColumns * mRows){
			printf("Unsupported File Format");
			return;
		}
		mPixData8 = (Uint8 *)malloc(sizeof(Uint8) * count);
		for(size_t i = 0; i < count; i++)
			mPixData8[i] = pixData[i];
	}
	else printf("Unsupported File Format");
}

ImageMatrix::~ImageMatrix(void)
{
	if(mPixData8 != NULL)
		delete mPixData8;
	if(mPixData16 != NULL)
		delete mPixData16;
}

Uint16 ImageMatrix::getColumns()
{
	return mColumns;
}

Uint16 ImageMatrix::getRows()
{
	return mRows;
}

double ImageMatrix::getWinCenter()
{
	return mWindowCenter;
}

double ImageMatrix::getWinWidth()
{
	return mWindowWidth;
}

Uint16 ImageMatrix::getUint16Pixel(int row, int column)
{
	if(row >= mRows || column >= mColumns)
		return 0;
	return mPixData16[row * mColumns + column];
}

void ImageMatrix::setUint16Pixel(int row, int column, Uint16 pixelValue)
{
	if(row >= mRows || column >= mColumns)
		return;
	mPixData16[row * mColumns + column] = pixelValue;
}

Uint8 ImageMatrix::getUint8Pixel(int row, int column)
{
	if(row >= mRows || column >= mColumns)
		return 0;
	return mPixData8[row * mColumns + column];
}

Uint16* ImageMatrix::getUint16Data()
{
	return mPixData16;
}

Uint8* ImageMatrix::getUint8Data()
{
	return mPixData8;
}
std::string ImageMatrix::get_patientname(const std::string & dirpath){
	std::string filepath = dirpath + "\\ADC\\ADC_1";
	DcmFileFormat *pDicomFile = new DcmFileFormat();
	OFCondition oc = pDicomFile->loadFile(filepath.c_str());
	if(oc.good()){
		DcmDataset *pDataset = pDicomFile->getDataset();
		const char * name;
		pDataset -> findAndGetString(DCM_PatientName, name);
		std::string res(name);
		delete pDataset;
		return res;
	}
	else
	return "fuck";
}