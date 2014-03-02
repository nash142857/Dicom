#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <string>
#include "DCMPatientInfo.h"
#include "Patient_information.h"
#include <memory>
#include <algorithm>
bool cmp(const Patient_information & a, const Patient_information & b);
std::string wstr_to_stdstring(wchar_t*   Msg);
CStringW CStrA2CStrW(const CStringA &cstrSrcA);
std::string ito_string(long num);
int getfilenum(const std::string & dir);
LPCTSTR string_to_lpsctr(const std::string & str);
int string_to_i(const std::string & str);
CTime string_to_ctime(const std::string & standard);
std::shared_ptr <DCMPatientInfo> get_patient_info(const Patient_information & patient_data);
