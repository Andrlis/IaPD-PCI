#include "PCI_Info.h"


bool PCI_Info::getDeviceInfoFromPCI(){
	dev_info = SetupDiGetClassDevs(0, "PCI", NULL,
		DIGCF_ALLCLASSES | DIGCF_PRESENT);

	if (dev_info == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	else return TRUE;
}

std::vector<DeviceInfo> PCI_Info::getDeviceInfo(){
	dev_info_data.cbSize = sizeof(dev_info_data);

	std::vector<DeviceInfo> devInf;

	while (SetupDiEnumDeviceInfo(dev_info, count, &dev_info_data)) {
		DeviceInfo dev;
		size = 0;
		ptype = 0;
		

		SetupDiGetDeviceRegistryProperty(dev_info, &dev_info_data,				//Получение информации об устройстве: производитель
			SPDRP_HARDWAREID, &ptype, (BYTE*)pbuffer,
			512, &size);
		
		setIDs(std::string(pbuffer), &dev);
		
		count++;

		devInf.push_back(dev);
	}

	return devInf;
}

void PCI_Info::destoyInfoList(){
	SetupDiDestroyDeviceInfoList(dev_info);
}

void PCI_Info::setIDs(std::string infoStr, DeviceInfo* devInf){
	std::string str = infoStr.substr(infoStr.find("VEN_") + 4,
		infoStr.find("&DEV") - infoStr.find("VEN_") - 4);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	devInf->vendorId = str;


	str = infoStr.substr(infoStr.find("DEV_") + 4,
		infoStr.find("&SUB") - infoStr.find("DEV_")-4);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	devInf->deviceId = str;
}



void PCI_Info::getIdsInfo(){
	std::ifstream devInfoFile("pci.ids.txt");
	if (!devInfoFile.is_open()){
		std::cerr << GetLastError();
	}

	std::string buf;
	while (std::getline(devInfoFile, buf)){
		fileInfo.push_back(buf);
	}
	devInfoFile.close();
}

//void PCI_Info::setDeviceInfo(DeviceInfo* device){
//	
//	std::regex regVEN;
//	std::regex regDEV;
//		
//	regVEN = std::regex(std::string("(?<=^" + device->vendorId + ")(.+)"), std::regex_constants::basic);
//	regDEV = std::regex(std::string("(?<=^\t" + device->deviceId + ")(.+)"), std::regex_constants::basic);
//
//	for (int i = 0; i < fileInfo.size(); i++){
//
//		std::smatch match;
//		if (std::regex_match(fileInfo.at(i), match, regVEN)){
//			device->vendorInfo = match[1];
//			for (int j = i + 1; j < fileInfo.size(); j++){
//
//				if (std::regex_match(fileInfo.at(j), match, regDEV)){
//					device->deviceInfo = match[1];
//					break;
//				}
//			}
//		}
//		
//	}
//}

void PCI_Info::setDeviceInfo(DeviceInfo* device){

	for (int i = 0; i < fileInfo.size(); i++){
		std::string str = fileInfo.at(i).substr(0, device->vendorId.length());
		std::string str1 = device->vendorId;

		if (str.compare(0,str1.length(),str1)==0){
			device->vendorInfo = fileInfo.at(i).substr(str1.length()+1, fileInfo.at(i).length() - str1.length());
			for (int j = i + 1; j < fileInfo.size(); j++){
				str = fileInfo.at(j).substr(1, device->deviceId.length());
				str1 = device->deviceId;

				if (str.compare(0, str1.length(), str1) == 0){
					device->deviceInfo = fileInfo.at(j).substr(str1.length() + 1, fileInfo.at(j).length() - str1.length());;
					break;
				}
			}
		}

	}
}