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

using ComplectComponents = std::tuple
<MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

std::shared_ptr<ITequipment>
DataManager::createITequipment(typeITEquipment typeITE)
{
	switch (typeITE) {
	case typeITEquipment::typePC: {
		//get parameters for construction
		
		auto [name, type,
			nameOfMotherBoard,
			_cpuPair, GraphicCardPair,
			ramVolume, storageDeviceTuple,
			operSystem] = pcGetData->getData();

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
		pcFabric->setInfo(name, type);
		return pcFabric->create();
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

void DataManager::setDataPC(const DataPC& data) {
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
