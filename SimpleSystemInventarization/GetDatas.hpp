#pragma once

#include <tuple>
#include <string>
#include <utility>

using DataPC = std::tuple<
	std::pair<std::string, size_t>, //info(name, type)
	std::string, //motheboard
	std::pair<std::string, float>, //cpu
	std::pair<std::string, float>, //graphicCard
	float, //ram
	std::tuple<float, std::string, size_t>, //storageDevice
	std::string>; //operSystem

class PCgetDatas {
public:
	PCgetDatas(DataPC&& dataPC_);
	DataPC getData() const;
private:
	DataPC dataPC;
};

class MonitorGetDatas {
public:
	MonitorGetDatas(const std::string&, float);
	std::pair <std::string, float> getData();
private:
	std::pair<std::string, float> monitorData;
};

using DataPrinter = std::tuple<std::string, std::string, bool>;
class PrinterGetDatas {
public:
	PrinterGetDatas(const DataPrinter& dataPrinter);
	std::tuple<std::string, std::string, bool> getData();
private:
	DataPrinter dataPrinter;
};

class OtherGetDatas{
public:
	OtherGetDatas(const std::string &name, const std::string& other);
	std::pair<std::string, std::string> getData();
private:
	std::pair<std::string, std::string> dataOther;
};
