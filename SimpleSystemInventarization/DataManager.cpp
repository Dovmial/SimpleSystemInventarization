#include "DataManager.hpp"
#include "IITequipmentFabric.hpp"
#include "GetDataEquipment.hpp"
#include <memory>



DataManager::DataManager() :
	pcFabric		{ std::make_unique<PCfabric>		()},
	monitorFabric	{ std::make_unique<MonitorFabric>	()},
	printerFabric	{ std::make_unique<PrinterFabric>	()},
	otherFabric		{ std::make_unique<OtherFabric>		()},
	pcGetData		{ std::make_unique<PCgetData>		()},
	monitorGetData	{ std::make_unique<MonitorGetData>	()},
	printerGetData	{ std::make_unique<PrinterGetData>	()},
	otherGetData	{ std::make_unique<OtherGetData>	()}
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
using ComplectComponents = std::tuple
<MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

std::shared_ptr<ITequipment>
DataManager::createITequipment(typeITEquipment typeITE)
{
	switch (typeITE) {
	case typeITEquipment::typePC: {
		//get parameters for construction

		auto [infoOfPCPair,
			nameOfMotherBoard,
			_cpuPair, GraphicCardPair,
			ramVolume, storageDeviceTuple,
			operSystem] = pcGetData->getData();

		auto info{ std::make_pair(infoOfPCPair.first,  //name pc
			infoOfPCPair.second) }; //typePC

		ComplectComponents components{
			MotherBoard(nameOfMotherBoard),
			CPU(_cpuPair.first, _cpuPair.second), //name, frequency
			GraphicCard(GraphicCardPair.first, GraphicCardPair.second), //name, volume
			RAM(ramVolume),
			StorageDevice(
				std::get<0>(storageDeviceTuple), //volume
				std::get<1>(storageDeviceTuple), //name
				std::get<2>(storageDeviceTuple)), //type
			operSystem
		};

		pcFabric->setComponents(std::make_shared<ComplectComponents>(components));
		pcFabric->setInfo(info.first, info.second);
		return std::move(pcFabric->create());
	}

	case typeITEquipment::typeMonitor:
		monitorFabric->setInfo(monitorGetData->getData());
		return std::move(monitorFabric->create());

	case typeITEquipment::typePrinter: {
		auto [name, cartridge, type] = printerGetData->getData();
		printerFabric->setInfo(std::make_tuple(name, Cartridge(cartridge), type));
		return std::move(printerFabric->create());
	}

	case typeITEquipment::typeoOtherITEquipment:
		otherFabric->setInfo(otherGetData->getData());
		return std::move(otherFabric->create());
	}
}


std::unique_ptr<Item> DataManager::createItem(typeITEquipment type, int64_t inventoryNumber_)
{
	return std::make_unique<Item>(createITequipment(type), inventoryNumber_);
}

void DataManager::setDataPC(DataPC& data) {
	pcGetData->setData(data);
}

void DataManager::setDataMonitor(const std::string& name, float diagonal)
{
	monitorGetData->setData(name, diagonal);
}

void DataManager::setDataPrinter(
	const std::string& name,
	const std::string& cartridge,
	Printer::PrinterType type)
{
	printerGetData->setData(name, cartridge, type);
}

void DataManager::setDataOther(const std::string& name, const std::string& otherInfo)
{
	otherGetData->setData(name, otherInfo);
}
