#include "DataManager.hpp"
#include "IITequipmentFabric.hpp"
#include "GetDatas.hpp"
#include <memory>

using ComplectComponents = std::tuple
<MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

DataManager::DataManager() :
	pcFabric{ std::make_unique<PCfabric>() },
	monitorFabric{ std::make_unique<MonitorFabric>() },
	printerFabric{ std::make_unique<PrinterFabric>() },
	otherFabric{ std::make_unique<OtherFabric>() }
{}

DataManager::~DataManager()
{
}

/*
	PC LenovoG580("Laptop lenovo G580");
	LenovoG580.setCPU("Intel i5 570", 2.7f);
	LenovoG580.setOperationSystem("Win 7 sp1 pro");
	LenovoG580.setRAM(16.f);
	LenovoG580.setStorageDevVol(232.f);
	Printer mfuHP1132("MFU HP 1132", "CE285A");

	//real objects
	Item pc307(&LenovoG580, 110041931);
	pc307.addSignService("Clean", "15.12.2017");

	Item pc308(&LenovoG580, 110041930);
	pc308.addSignService("Fixing loops", "18.10.2015");
	pc308.addSignService("Clean", "02.05.2019");

	Item printer307(&mfuHP1132, 5101340087);
	printer307.addSignProblemsSolutions(
		"Broken cartridge", "23.02.2020", "new cartridge");
*/

std::shared_ptr<ITequipment>
DataManager::createITequipment(typeITEquipment typeITE)
{
	switch (typeITE) {
	case typeITEquipment::typePC: {
		//get parameters for construction

		auto& [infoOfPCPair,
			nameOfMotherBoard,
			_cpuPair, GraphicCardPair,
			ramVolume, storageDeviceTuple,
			operSystem] = PCgetDatas().getData();

		auto info{ std::make_pair(infoOfPCPair.first,  //name pc
		static_cast<PC::TypePC>(infoOfPCPair.second)) };

		ComplectComponents components{
			MotherBoard(nameOfMotherBoard),
			CPU(_cpuPair.first, _cpuPair.second), //name, frequency
			GraphicCard(GraphicCardPair.first, GraphicCardPair.second), //name, volume
			RAM(ramVolume),
			StorageDevice(
				std::get<0>(storageDeviceTuple), //volume
				std::get<1>(storageDeviceTuple), //name
				static_cast<StorageDevice::typeStorageDevice>
				(std::get<2>(storageDeviceTuple))), //type
			operSystem
		};

		pcFabric->setComponents(std::make_shared<ComplectComponents>(components));
		pcFabric->setInfo(info.first, info.second);
		return std::move(pcFabric->create());
	}

	case typeITEquipment::typeMonitor: 
		monitorFabric->setInfo(MonitorGetDatas().getData());
		return std::move(monitorFabric->create());

	case typeITEquipment::typePrinter: 
		printerFabric->setInfo(PrinterGetDatas().getData());
		return std::move(printerFabric->create());

	case typeITEquipment::typeoOtherITEquipment:
		otherFabric->setInfo(OtherGetDatas().getData());
		return std::move(otherFabric->create());
	}
}


std::unique_ptr<Item> DataManager::createItem(typeITEquipment type, int64_t inventoryNumber_)
{
	return std::make_unique<Item>(createITequipment(type), inventoryNumber_);
}
