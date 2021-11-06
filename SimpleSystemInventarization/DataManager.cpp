#include "DataManager.hpp"
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
{
	buildings.push_back(std::move(std::make_unique<Build>("Virtual building")));
	currentLocation = std::make_unique<Navigator>(
		buildings[0]->getName(),
		buildings[0]->getRoom(0)->getName()
	);
}

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

Item* DataManager::createItem(
	typeITEquipment type,
	int64_t inventoryNumber_,
	const std::string& nameBuilding, 
	const std::string& nameRoom
	)
{
	devices.push_back({
		std::make_unique<Item>(createITequipment(type),inventoryNumber_),
		nameBuilding,
		nameRoom
		}
	);
	return devices.back().item.get();
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

void DataManager::setCurrentLocationInfo(std::pair<std::string, std::string> location)
{
	currentLocation->setCurrentLocation(location.first, location.second);
}

auto DataManager::getCurrentLocationInfo() const -> std::pair<std::string, std::string>
{
	return currentLocation->getCurrentlocation();
}

void DataManager::setCurrentRoomLocationInfo(const std::string& room)
{
	currentLocation->setCurrentRoom(room);
}

void DataManager::setCurrentBuildingLocationInfo(const std::string& building)
{
	currentLocation->setCurrentBuilding(building);
}

void DataManager::addBuilding(const std::string& nameBuilding)
{
	buildings.push_back(std::make_unique<Build>(nameBuilding));
}

Room* DataManager::getCurrentRoom() const
{
	Build* build = getCurrentBuilding();
	int index = 
		build->findRoom(currentLocation->getCurrentlocation().second);
	return build->getRoom(index);
}

Build* DataManager::getBuilding(const std::string& nameBuilding) const
{
	auto iter = find_if(begin(buildings), end(buildings),
		[&](std::unique_ptr<Build> const& obj)-> bool {
			return obj->getName() == nameBuilding;
		});
	if (iter == end(buildings))
		return nullptr;
	else
		return iter->get();
}

Build* DataManager::getCurrentBuilding() const
{
	return getBuilding(currentLocation->getCurrentlocation().first);
}

std::vector<std::string> DataManager::getListBuildingNames() const
{ 
	const size_t SIZE = buildings.size();
	std::vector<std::string> buildingNames(SIZE);
	for (int i{ 0 }; i < SIZE; ++i) {
		buildingNames[i] = buildings[i]->getName();
	}
	return buildingNames;
}

std::vector<std::string> DataManager::getListRoomNames() const
{
	auto building{ getCurrentBuilding() };
	size_t SIZE{ building->size() };
	std::vector<std::string> roomNames(SIZE);
	for (int i{}; i < SIZE; ++i) {
		roomNames[i] = building->getRoom(i)->getName();
	}
	return roomNames;
}
