#include "stdafx.h"
#include "common.h"
std::string wstr_to_stdstring(wchar_t * pwszSrc)//把wchar*转换称char* 
{ 
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if(nLen <= 0) return std::string("");
	char * pszDst = new char[nLen];
	if(NULL == pszDst) return std::string("");
	 WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	 pszDst[nLen - 1] = 0;
	 std::string tmp(pszDst);	 
	 delete [] pszDst;
	 return tmp;
}
CStringW CStrA2CStrW(const CStringA &cstrSrcA){
    int len = MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len];
    memset(wstr, 0, len*sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, wstr, len);
    CStringW cstrDestW = wstr;
    delete[] wstr; 
    return cstrDestW;
}
std::string ito_string(long num){
	std::string res = "";
	while(num){
		res += '0' + num % 10;
		num /= 10;
	}
	int l = res.length();
	for(int i = 0; i < l / 2; ++i){
		char tmp = res[i];
		res[i] = res[l - 1 - i];
		res[l - 1 - i] = tmp;
	}
	return res;
}
inline LPCTSTR string_to_lpsctr(const std::string & str){
	int nLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	WCHAR * buff = new WCHAR[nLen];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buff, nLen);
	LPCTSTR res(buff);
	return res;
}
int getfilenum(const std::string & dir){
	const std::string file_attr = dir + "\\*";
	CFileFind find;
	BOOL ret = find.FindFile(string_to_lpsctr(file_attr));
	int num = 0;
	while(ret){
		ret = find.FindNextFileW();
		if(find.IsDots() || find.IsDirectory()) continue;
		++num;
	}
	return num;
}
int string_to_i(const std::string & str){
	int res = 0;
	for(size_t i = 0; i < str.size(); ++i)
		res = 10 * res + (str[i] - '0');
	return res;
}
CTime string_to_ctime(const std::string & standard){
	int ctime[6] = {0};
	int res = 0; 
	int cnt = 0;
	for(size_t i = 0; i < standard.size(); ++i){
		if(standard[i] == '-' || standard[i] == ':'){
			ctime[cnt++] = res;
			res = 0;
		}
		else
		res = 10 * res + (standard[i] - '0');
	}
	ctime[cnt++] = res;
	return CTime(ctime[0],ctime[1],ctime[2],ctime[3],ctime[4],ctime[5]);
}
std::shared_ptr <DCMPatientInfo> get_patient_info(const Patient_information & patient_data){
	int dwiCount = patient_data.dwicount;
	DcmDataset** DWIDatasetList = (DcmDataset**)malloc(dwiCount*sizeof(DcmDataset*));
	for (int i = 0; i < dwiCount; i++) {
		DcmFileFormat *pDicomFile = new DcmFileFormat();
		char path[100];
		std::string s = patient_data.dir + "\\ADC\\ADC_%d";
		sprintf(path, s.c_str(),i + 1);
		OFCondition oc = pDicomFile->loadFile(path);
		if(oc.good()){
			DcmDataset *pDataset = pDicomFile->getDataset();
			DWIDatasetList[i] = pDataset;
			Uint16 column, row;
			unsigned long count;
			const UINT16 * pixData;
			pDataset->findAndGetUint16(DCM_Columns,column);
			pDataset->findAndGetUint16(DCM_Rows,row);
			pDataset->findAndGetUint16Array(DCM_PixelData, pixData, &count);
		}
	}
	int pwiCount = patient_data.pwicount;
	DcmDataset** PWIDatasetList = (DcmDataset**)malloc(pwiCount*sizeof(DcmDataset*));
	for (int i = 0; i < pwiCount; i++) {
		DcmFileFormat *pDicomFile = new DcmFileFormat();
		char path[100];
		std::string s = patient_data.dir + "\\MTT\\MTT_%d";
		sprintf(path, s.c_str(),i +	1);
		OFCondition oc = pDicomFile->loadFile(path);
		if(oc.good()){
			DcmDataset *pDataset = pDicomFile->getDataset();
			PWIDatasetList[i] = pDataset;
			Uint16 column, row;
			unsigned long count;
			const UINT16 * pixData;
			pDataset->findAndGetUint16(DCM_Columns,column);
			pDataset->findAndGetUint16(DCM_Rows,row);
			pDataset->findAndGetUint16Array(DCM_PixelData, pixData, &count);
		}
	}
	std::shared_ptr<DCMPatientInfo> mInfo(new DCMPatientInfo(DWIDatasetList, dwiCount, PWIDatasetList, pwiCount));
	return mInfo;
}