#include "GetDatas.hpp"

PCgetDatas::PCgetDatas(DataPC&& dataPC_):
	dataPC(move(dataPC_))
{
}

std::tuple<
	std::pair<std::string, size_t>, //0-info
	std::string, //1-motherboard
	std::pair<std::string, float>, //2-cpu
	std::pair<std::string, float>, //3-graphicCard
	float, //4-ram
	std::tuple <float, std::string, size_t>, //5-storageDevice
	std::string> //6-operationSystem
	PCgetDatas::getDataPC() const
{
	return dataPC;
}

MonitorGetDatas::MonitorGetDatas(const std::string& name, float diagonal) :
	monitorData(std::make_pair(name, diagonal))
{
}

std::pair<std::string, float> MonitorGetDatas::getData()
{
	return move(monitorData);
}

PrinterGetDatas::PrinterGetDatas(const DataPrinter& dataPrinter_):
	dataPrinter(dataPrinter_)
{

}

std::tuple<std::string, std::string, bool> PrinterGetDatas::getData()
{
	return move(dataPrinter);
}

OtherGetDatas::OtherGetDatas(
	const std::string& name, const std::string& other) :
	dataOther(std::make_pair(name, other))
{
}

std::pair<std::string, std::string> OtherGetDatas::getData()
{
	return move(dataOther);
}
