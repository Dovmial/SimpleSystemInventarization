#pragma once

#include "ITequipment.hpp"
#include <memory>

class ITequipmentFabric {
public:
	virtual std::shared_ptr<ITequipment> create() = 0;
};

class PCfabric: public ITequipmentFabric {
public:
	std::shared_ptr<ITequipment> create() override {
		
		auto pc{std::make_shared<PC>(name)};
		pc->setMotherboard();
		pc->setCPU();
		pc->setGraphicCard();
		pc->setRAM();
		pc->setStorageDevVol();
		pc->setOperationSystem();

		return std::move(pc);
	}
private:
	
};


class MonitorFabric: public ITequipmentFabric
{
public:
	std::shared_ptr<ITequipment> create() override {
		auto monitor{ std::make_shared<Monitor>(name) };
		monitor->setDiagonal();
		return std::move(monitor);
	}

private:

};

class PrinterFabric : public ITequipmentFabric
{
public:
	std::shared_ptr<ITequipment> create() override {
		auto printer{ std::make_shared<Printer>(name) };
		printer->setCartridge();
		printer->setIsMFU();
		return std::move(monitor);
	}

private:

};

class OtherFabric : public ITequipmentFabric
{
public:
	std::shared_ptr<ITequipment> create() override {
		auto other{ std::make_shared<OtherEquipment>(name) };
		return std::move(other);
	}

private:

};