#include "DataManager.hpp"
#include <memory>
#include <algorithm>
#include <stdexcept>

DataManager::DataManager() :
	pcFabric		{ std::make_unique<PCfabric>		()},
	monitorFabric	{ std::make_unique<MonitorFabric>	()},
	printerFabric	{ std::make_unique<PrinterFabric>	()},
	otherFabric		{ std::make_unique<OtherFabric>		()},

	pcGetData		{ std::make_unique<PCgetData>		()},
	monitorGetData	{ std::make_unique<MonitorGetData>	()},
	printerGetData	{ std::make_unique<PrinterGetData>	()},
	otherGetData	{ std::make_unique<OtherGetData>	()},

	serializer		{ std::make_unique<Serializer>		()}
{
	buildings.push_back(std::move(std::make_unique<Building>("Virtual building")));

	currentLocation = std::make_unique<Navigator>(
		std::make_pair(0, buildings[0]->getName()),
		std::make_pair(0, buildings[0]->getRoom(0)->getName())
		);
}

DataManager::~DataManager()
{
	save();
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
	const std::pair<size_t, size_t>& locationIndexes
	)
{
	devices.push_back(
			DeviceLocation(
				std::make_unique<Item>(createITequipment(type), inventoryNumber_),
				locationIndexes
			)
	);
	Item* newItem{ devices.back().getItem() };
	auto room{ getBuildingByIndex(locationIndexes.first)->getRoom(locationIndexes.second) };
	room->addItem(newItem);
	return newItem;
}

void DataManager::eraseItem(std::vector<DeviceLocation>::iterator&& iter) {
	
	getCurrentRoom()->eraseItem(iter->getItem());
	devices.erase(iter);
}

void DataManager::update()
{
	size_t indexBuilding{};
	size_t indexRoom	{};
	Room* room			{};

	for (const auto& device: devices)
	{
		indexBuilding = device.getBuildingIndex ();
		indexRoom	  = device.getRoomIndex		();
		room = getBuildingByIndex(indexBuilding)->getRoom(indexRoom);
		room->clear();
		room->addItem(device.getItem());
	}
}


XMLDocument* DataManager::getXMLDocument() const
{
	return serializer->getXMLDocument();
}

fs::path DataManager::getPath() const
{
	return serializer->getPath();
}

int DataManager::save()
{	
	serializer->clearXMLDocument();
	serializer->createXMLDocument(buildings, devices);
	return serializer->saveXMLDocument();
}

std::vector<DeviceLocation>::iterator DataManager::findItem(Item* item)
{
	auto iter = std::find_if(begin(devices), end(devices),
		[&](DeviceLocation& const obj) -> bool {
			return obj.getItem() == item;
		});
	return iter;
}

std::vector<const DeviceLocation*>
DataManager::findItemByName(const std::string& nameItem) const
{
	std::vector<const DeviceLocation*> resultFound;
	const auto SIZE = devices.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (devices[i].getItem()->getName() == nameItem) {
			resultFound.push_back(&devices.at(i));
		}
	}
	return resultFound;
}
std::vector<const DeviceLocation*>
DataManager::findItemByNumber(int64_t numberItem) const
{
	std::vector<const DeviceLocation*> resultFound;
	const auto SIZE = devices.size();
	auto p{ &devices[0] };
	for (size_t i{}; i < SIZE; ++i) {
		if (devices[i].getItem()->getInventoryNumber() == numberItem)
			resultFound.push_back(&devices[i]);
	}
	return resultFound;
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

void DataManager::setCurrentLocationInfo(
	const std::pair<size_t, std::string>& building,
	const std::pair<size_t, std::string>& room)
{
	currentLocation->setCurrentLocation(building, room);
}

auto DataManager::getCurrentLocationNames() const -> std::pair<std::string, std::string>
{
	return currentLocation->getCurrentLocationString();
}

auto DataManager::getCurrentLocationIndexes() const -> std::pair<size_t, std::size_t>
{
	return currentLocation->getCurrentLocationIndexes();
}

void DataManager::setCurrentRoomLocationInfo(const std::pair<size_t, std::string>& room)
{
	currentLocation->setCurrentRoom(room);
}

void DataManager::setCurrentBuildingLocationInfo(const std::pair<size_t, std::string>& building)
{
	currentLocation->setCurrentBuilding(building);
}

void DataManager::addBuilding(const std::string& nameBuilding)
{
	buildings.push_back(std::make_unique<Building>(nameBuilding));
}

std::vector<std::unique_ptr<Building>>& DataManager::getRefBuildings()
{
	return std::ref(buildings);
}

Room* DataManager::getCurrentRoom() const
{
	auto [buildingIndex, roomIndex] = currentLocation->getCurrentLocationIndexes();
	return buildings[buildingIndex]->getRoom(roomIndex);
}

int DataManager::getBuildingIndex(const std::string& nameBuilding) const
{
	const int SIZE = static_cast<int>(buildings.size());
	for (int i{}; i < SIZE; ++i) {
		if (buildings[i]->getName() == nameBuilding)
			return i;
	}
	return -1;
}

Building* DataManager::getBuilding(const std::string& nameBuilding) const
{
	for (const auto& building : buildings) {
		if (building->getName() == nameBuilding)
			return building.get();
	}
	return nullptr;//!!!!
}

Building* DataManager::getBuildingByIndex(size_t index) const
{
	return buildings.at(index).get();
}

Building* DataManager::getCurrentBuilding() const
{
	return getBuildingByIndex(currentLocation->getCurrentLocationIndexes().first);
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

std::vector<DeviceLocation>& DataManager::getDevices()
{
	return devices;
}
