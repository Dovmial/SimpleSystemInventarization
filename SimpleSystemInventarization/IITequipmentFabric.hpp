#pragma once

#include "BaseObject.hpp"
#include "ITequipment.hpp"
#include <memory>
#include <tuple>


struct  IITequipmentFabric {
	virtual std::shared_ptr<ITequipment> create() = 0; //fabric method
};

using ComplectComponents = std::tuple
<MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

class  PCfabric: public IITequipmentFabric {
public:
	PCfabric();
	PCfabric(const std::string& name, PC::TypePC info_,
		std::shared_ptr<ComplectComponents> complect_);
public:
	void setComponents(std::shared_ptr<ComplectComponents> complect);
	void setInfo(const std::string& name_, PC::TypePC type_);
	std::shared_ptr<ITequipment> create() override;
private:
	std::string name;
	PC::TypePC type;
	std::shared_ptr<ComplectComponents> complect;
};


class MonitorFabric: public IITequipmentFabric
{
public:
	MonitorFabric() {};
	MonitorFabric(std::pair<std::string, float> &&info_);
public:
	void setInfo(std::pair<std::string, float>&& info_);
	std::shared_ptr<ITequipment> create() override;
private:
	std::pair<std::string, float> info;
};

class PrinterFabric : public IITequipmentFabric
{
public:
	PrinterFabric();
	PrinterFabric(std::tuple<std::string, Cartridge, Printer::PrinterType>&& info);
public:
	std::shared_ptr<ITequipment> create() override;
	void setInfo(std::tuple<std::string, Cartridge, Printer::PrinterType>&& info_);
private:
	std::tuple<std::string, Cartridge, Printer::PrinterType> info;
};

class  OtherFabric : public IITequipmentFabric
{
public:
	OtherFabric();
	OtherFabric(std::pair<std::string, std::string>&& info_);
	std::shared_ptr<ITequipment> create() override;
	void setInfo(std::pair< std::string, std::string>&& someInfo);
private:
	std::pair< std::string, std::string> info;
};