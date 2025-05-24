#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"includes_lib.h"
namespace DNSfiles {
	uint8_t Read_uint8();
	std::vector<std::string> viewFile(const char* const FileName, bool showError = 1);
	void setWeb();
	void setDNS();
}