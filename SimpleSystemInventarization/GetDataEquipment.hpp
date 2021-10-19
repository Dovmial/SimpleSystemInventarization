#pragma once

#include <tuple>
#include <string>
#include <utility>
#include "ITequipment.hpp"

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

using DataPC = std::tuple<
	std::string, PC::TypePC, //0-(name/type)
	std::string, //1-motherboard
	std::pair<std::string, float>, //2-cpu
	std::pair<std::string, float>, //3-graphicCard
	float, //4-ram
	std::tuple <float, std::string, StorageDevice::typeStorageDevice>, //5-storageDevice
	std::string>; //6-operationSystem

class DECLSPEC PCgetData {
public:
	PCgetData();
	auto getData()->DataPC;
	void setData(DataPC&& dataPC_);
private:
	DataPC dataPC;
};

class DECLSPEC MonitorGetData {
public:
	MonitorGetData();
	auto getData() -> std::pair <std::string, float>;
	void setData(const std::string& name, float diagonal);
private:
	std::pair<std::string, float> monitorData;
};

using DataPrinter = std::tuple < std::string, std::string, Printer::PrinterType >;
class DECLSPEC PrinterGetData {
public:
	PrinterGetData();
	DataPrinter getData();
	void setData(
		const std::string& name,
		const std::string& cartridge,
		Printer::PrinterType data);
private:
	DataPrinter dataPrinter;
};

class DECLSPEC OtherGetData{
public:
	OtherGetData();
	auto getData()->std::pair<std::string, std::string>;
	void setData(const std::string& name, const std::string& otherData);
private:
	std::pair<std::string, std::string> dataOther;
};
