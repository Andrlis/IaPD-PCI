#include<iostream>
#include <locale>
#include <iomanip>
#include "PCI_Info.h"

#pragma comment( lib, "setupapi.lib" )

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	PCI_Info pcInfo;
	pcInfo.getDeviceInfoFromPCI();

	cout << setw(10) << left << "#" << setw(15) << left << "VendorID" << setw(50) << left << "Vendor" << setw(15) << left << "DeviceID" << setw(50) << left << "Device" << endl;
	for (int i = 0; i < 150; i++) cout << "-";
	cout << endl;

	vector<DeviceInfo>deviceInfo = pcInfo.getDeviceInfo();
	pcInfo.getIdsInfo();
	for (int i = 0; i < deviceInfo.size(); i++){
		pcInfo.setDeviceInfo(&deviceInfo.at(i));
	}

	for (int i = 0; i < deviceInfo.size(); i++){

		cout << setw(10) << left << i + 1
			<< setw(15) << left << deviceInfo.at(i).vendorId
			<< setw(50) << left << deviceInfo.at(i).vendorInfo
			<< setw(15) << left << deviceInfo.at(i).deviceId
			<< setw(50) << left << deviceInfo.at(i).deviceInfo << endl;
	}
	pcInfo.destoyInfoList();

	system("pause");
	return EXIT_SUCCESS;
}