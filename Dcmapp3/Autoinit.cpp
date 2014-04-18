#include "stdafx.h"
#include "ImageMatrix.h"
#include "Autoinit.h"
#include "ADOConn.h"
#include "common.h"
const char * Autoinit::basedirname = "E:\\research\\";
const char * Autoinit::lastmodify = "E:\\research\\last_modify.txt";
#define All_file "E:\\research\\*"
void Autoinit::init(){
	try{
		std::vector <std::pair<std::string, CTime> > res;
		getdir(res);
		shared_ptr <ADOConn> dbmanager = ADOConn::sharedSingleton();
		for(auto i = res.begin(); i != res.end(); ++i){
			const string patient_dir = basedirname + i -> first;
			std::string name = ImageMatrix::get_patientname(patient_dir);
			int pwicount = CommonLib::getfilenum(basedirname + i -> first + "\\MTT");
			int dwicount = CommonLib::getfilenum(basedirname + i -> first + "\\ADC");
			dbmanager -> addPatient(i -> first, name, patient_dir, pwicount, dwicount, i -> second);
		}
		save_modify();
	}	
	catch(CException *e){
		TCHAR szError[100];
		e -> GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
}
void Autoinit::getdir(std::vector <std::pair<std::string, CTime> > & res){
	res.clear();
	WIN32_FIND_DATA fileinfo;
	FILETIME lastmod;
	lastmod = get_last_modify();
	HANDLE handle =  FindFirstFile(_T(All_file), &fileinfo);
	do{
		if(fileinfo.dwFileAttributes == is_dir && fileinfo.cFileName[0] != '.'){
			FILETIME tmp;
			FileTimeToLocalFileTime(&fileinfo.ftLastWriteTime, &tmp);
			fileinfo.ftLastWriteTime = tmp;
			SYSTEMTIME lastwritetime;
			FileTimeToSystemTime(&tmp, &lastwritetime);
			CTime ctimelastwritetime(int(lastwritetime.wYear), int(lastwritetime.wMonth),int(lastwritetime.wDay), int(lastwritetime.wHour),int(lastwritetime.wMinute), int(lastwritetime.wSecond));   
			if(cmp(fileinfo.ftLastWriteTime, lastmod)){
				res.push_back(std::make_pair(CommonLib::wstr_to_stdstring(fileinfo.cFileName), ctimelastwritetime));
			}
		}
	}while(FindNextFile(handle, &fileinfo));
}
FILETIME Autoinit::get_last_modify(){//throw exception
	std::ifstream fin(lastmodify);
	FILETIME res;
	fin >> res.dwHighDateTime >> res.dwLowDateTime;
	fin.close();
	return res;
}
void Autoinit::save_modify(){
	SYSTEMTIME now;
	GetLocalTime(&now);
	FILETIME file_now;
	SystemTimeToFileTime(&now, &file_now);
	std::ofstream out(lastmodify);
	out << file_now.dwHighDateTime << " " << file_now.dwLowDateTime << "\n";
}
