#include "IITequipmentFabric.hpp"

PCfabric::PCfabric(): 
	complect(nullptr), info(std::pair("", PC::TypePC::SystemBlock))
{
}

PCfabric::PCfabric(
	const std::pair<std::string, PC::TypePC>& info_,
	std::shared_ptr<ComplectComponents>&& complect_) :
	info(info_), complect(move(complect_))
{
}

void PCfabric::setComponents(std::shared_ptr<ComplectComponents>&& complect_)
{
	complect = std::move(complect_);
}

void PCfabric::setInfo(const std::string& name, const PC::TypePC& typePC)
{
	info.first = name;
	info.second = typePC;
}

std::shared_ptr<ITequipment> PCfabric::create()
{
	auto pc{ std::make_shared<PC>(info, complect) };
	return pc;
}

MonitorFabric::MonitorFabric(std::pair<std::string, float> &&info_): 
	info(std::move(info_))
{
}

void MonitorFabric::setInfo(std::pair<std::string, float>&& info_)
{
	info = std::move(info_);
}

std::shared_ptr<ITequipment> MonitorFabric::create()
{
	auto monitor{ std::make_shared<Monitor>(info) };
	return std::move(monitor);
}

PrinterFabric::PrinterFabric():
	PrinterFabric(std::tuple("", Cartridge(""), Printer::PrinterType::Printer))
{
}

PrinterFabric::PrinterFabric(std::tuple<std::string, Cartridge, Printer::PrinterType>&& info_):
	info(std::move(info_))
{
}

std::shared_ptr<ITequipment> PrinterFabric::create()
{
	auto printer{ std::make_shared<Printer>(info) };
	return printer;
}

void PrinterFabric::setInfo(std::tuple<std::string, Cartridge, Printer::PrinterType>&& info_)
{
	info = std::move(info_);
}

OtherFabric::OtherFabric(): OtherFabric(std::make_pair("", ""))
{
}

OtherFabric::OtherFabric(std::pair<std::string, std::string>&& info_):
	info(info_)
{
}

std::shared_ptr<ITequipment> OtherFabric::create()
{
	auto itEquip{ std::make_shared<OtherEquipment>(info) };
	return std::move(itEquip);
}

void OtherFabric::setInfo(std::pair< std::string, std::string>&& info_)
{
	info = move(info_);
}
