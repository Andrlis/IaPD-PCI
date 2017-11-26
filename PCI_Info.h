#pragma once
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>

#pragma comment( lib, "setupapi.lib" )

struct DeviceInfo {
	std::string vendorId;
	std::string deviceId;
	std::string deviceInfo;
	std::string vendorInfo;
};

class PCI_Info
{
private:
	int count = 0;
	char* ptr;

	DWORD ptype = 0;
	DWORD size = 0;
	DWORD index = 0;

	SP_DEVINFO_DATA dev_info_data;
	HDEVINFO dev_info;

	char pbuffer[512];

	std::vector<std::string> fileInfo;

public:
	bool getDeviceInfoFromPCI();						//Получение информации об устройствах, подключенных к PCI
	std::vector<DeviceInfo> getDeviceInfo();			//Обработка получнных данных
	void destoyInfoList();								//Удаление информации об у-вах и освобождение памяти
	void setIDs(std::string, DeviceInfo*);
	void setDeviceInfo(DeviceInfo*);
	void getIdsInfo();
};

