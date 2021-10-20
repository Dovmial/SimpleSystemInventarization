#include "GetDataEquipment.hpp"

PCgetData::PCgetData()
{}

DataPC PCgetData::getData()
{
	return dataPC;
}

void PCgetData::setData(const DataPC& dataPC_)
{
	dataPC = dataPC_;
}

MonitorGetData::MonitorGetData()
{}

void MonitorGetData::setData(const std::string& name, float diagonal)
{
	monitorData = std::make_pair(name, diagonal);
}

std::pair<std::string, float> MonitorGetData::getData()
{
	return std::move(monitorData);
}

PrinterGetData::PrinterGetData()
{}

DataPrinter PrinterGetData::getData()
{
	return std::move(dataPrinter);
}

void PrinterGetData::setData(
	const std::string& name,
	const std::string& cartridge,
	Printer::PrinterType type)
{
	dataPrinter = std::make_tuple(name, cartridge, type);
}

OtherGetData::OtherGetData()
{
}

std::pair<std::string, std::string> OtherGetData::getData()
{
	return move(dataOther);
}

void OtherGetData::setData(const std::string& name, const std::string& otherData)
{
	dataOther = std::make_pair(name, otherData);
}
