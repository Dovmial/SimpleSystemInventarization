#include "IITequipmentFabric.hpp"

PCfabric::PCfabric(): 
	complect(nullptr), info(std::tuple("", PC::TypePC::SystemBlock))
{
}

PCfabric::PCfabric(
	std::tuple<std::string, PC::TypePC>&& info_,
	std::shared_ptr<ComplectComponents>&& complect_):
	info(std::move(info_)), complect(std::move(complect_))
{
}

void PCfabric::setComponents(std::shared_ptr<ComplectComponents>&& complect_)
{
	complect = std::move(complect_);
}

void PCfabric::setInfo(const std::string& name, const PC::TypePC& typePC)
{
	info = std::make_tuple(name, typePC);
}

std::shared_ptr<ITequipment> PCfabric::create()
{
	auto pc{ std::make_shared<PC>(info) };
	auto& [type, motherBoard, _cpu, graphCard, ram, storDevice, operSystem] = *complect;
	pc->setTypePC(type);
	pc->setMotherboard(motherBoard);
	pc->setCPU(_cpu);
	pc->setGraphicCard(graphCard);
	pc->setRAM(ram);
	pc->setStorageDevice(storDevice);
	pc->setOperationSystem(operSystem);

	return std::move(pc);
}

MonitorFabric::MonitorFabric(std::pair<std::string, float> &&info_): 
	info(std::move(info_))
{
}

void MonitorFabric::setInfo(const std::string &name, float diagonal)
{
	info = std::make_pair(name, diagonal);
}

std::shared_ptr<ITequipment> MonitorFabric::create()
{
	auto monitor{ std::make_shared<Monitor>(info) };
	return std::move(monitor);
}

PrinterFabric::PrinterFabric():
	PrinterFabric(std::tuple("", Cartridge(""), false))
{
}

PrinterFabric::PrinterFabric(std::tuple<std::string, Cartridge, bool>&& info_):
	info(std::move(info_))
{
}

std::shared_ptr<ITequipment> PrinterFabric::create()
{
	auto printer{ std::make_shared<Printer>(info) };
	return std::move(printer);
}

void PrinterFabric::setInfo(std::tuple<std::string, Cartridge, bool>&& info_)
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

void OtherFabric::setInfo(
	const std::string& name, const std::string& someInfo)
{
	info = make_pair(name, someInfo);
}
