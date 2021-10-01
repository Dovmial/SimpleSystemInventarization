#pragma once

#include "BaseObject.hpp"
#include "ITequipment.hpp"
#include <memory>

class IITequipmentFabric { 
public:
	virtual std::shared_ptr<ITequipment> create() = 0; //fabric method
};

using ComplectComponents = std::tuple
<PC::TypePC, MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

class PCfabric: public IITequipmentFabric {
public:
	PCfabric();
	PCfabric(
		std::tuple<std::string, PC::TypePC>&& info_,
		std::shared_ptr<ComplectComponents>&& complect_
	);

public:
	void setComponents(std::shared_ptr<ComplectComponents>&& complect);
	void setInfo(const std::string& name, const PC::TypePC& typePC);
	std::shared_ptr<ITequipment> create() override;
private:
	std::shared_ptr<ComplectComponents> complect;
	std::tuple<std::string, PC::TypePC> info;
};


class MonitorFabric: public IITequipmentFabric
{
public:
	MonitorFabric() {};
	MonitorFabric(std::pair<std::string, float> &&info_);
public:
	void setInfo(const std::string &name, float diagonal);
	std::shared_ptr<ITequipment> create() override;
private:
	std::pair<std::string, float> info;
};

class PrinterFabric : public IITequipmentFabric
{
public:
	PrinterFabric();
	PrinterFabric(std::tuple<std::string, Cartridge, bool>&& info);
public:
	std::shared_ptr<ITequipment> create() override;
	void setInfo(std::tuple < std::string, Cartridge, bool>&& info_);
private:
	std::tuple<std::string, Cartridge, bool> info;
};

class OtherFabric : public IITequipmentFabric
{
public:
	OtherFabric();
	OtherFabric(std::pair<std::string, std::string>&& info_);
	std::shared_ptr<ITequipment> create() override;
	void setInfo(
		const std::string& name, const std::string& someInfo);
private:
	std::pair< std::string, std::string> info;
};