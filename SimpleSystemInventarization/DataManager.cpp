#include "DataManager.hpp"
#include <memory>
#include <algorithm>
#include <fstream>

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
	buildings.push_back(std::move(std::make_unique<Building>("Virtual building")));
	currentLocation = std::make_unique<Navigator>(
		buildings[0]->getName(),
		buildings[0]->getRoom(0)->getName()
	);
	load();
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
	Item* newItem{ devices.back().item.get() };
	this->getCurrentRoom()->addItem(newItem);
	return newItem;
}

//unusable   (for edit)
void DataManager::setItem(Item* item)
{
	auto iter = findItem(item);
	if(iter != devices.end())
		iter->item.reset(item);
}

void DataManager::eraseItem(std::vector<DeviceLocation>::iterator&& iter) {
	
	getCurrentRoom()->eraseItem(iter->item.get());
	devices.erase(iter);
}

void DataManager::update()
{
	size_t SIZE{ devices.size() };
	std::unique_ptr<Navigator> navigator;
	Room* room;
	std::vector<bool> flagsDevicePlacement(SIZE);

	for (auto& building : buildings) {
		for (size_t i{}; i < building->size(); ++i) {
			room = building->getRoom(i);
			room->clear();
			navigator->setCurrentLocation(
				building->getName(), building->getRoom(i)->getName()
			);
			for (size_t j{}; j < SIZE && !flagsDevicePlacement[j]; ++j) {
				if(devices[j].location == navigator->getLocation())
					room->addItem(devices[j].item.get());
			}
		}
	}
}

void DataManager::serialize()
{
	const size_t SIZE{ buildings.size() };
	size_t countRooms{ };
	std::ofstream file("data.ssi");
	if (!file.is_open())
		throw std::exception("File is not open!");
	file << SIZE << '\n';

	for (size_t i{ 1 }; i < SIZE; ++i) {
		file << buildings[i]->getName() << "\n";
		countRooms = buildings[i]->size();
		file << countRooms - 1 << ' ';
		for (size_t j{ 1 }; j < countRooms; ++j)
			file<<buildings[i]->getRoom(j)->getName() << ';';
		file << '\n';
	}

	file.close();
}

void DataManager::load()
{
	std::ifstream file("data.ssi");
	if (!file.is_open())
		throw std::exception("File is not open!");
	size_t countBuildings{};
	file >> countBuildings;
	buildings.reserve(countBuildings);
	file.get();

	std::string buf;
	for (size_t i{ 1 }; i < countBuildings; ++i) {
		std::getline(file, buf);
		addBuilding(buf);
		buf.clear();

		size_t countRooms{};

		file >> countRooms;
		file.get();
		char ch;
		for (size_t j{}; j < countRooms; ++j) {
			while (file.get(ch) && ch != ';') {
				buf += ch;
			}
			buildings[i]->addRoom(buf);
			buf.clear();
		}
		file.get();
	}
	file.close();
}

std::vector<DeviceLocation>::iterator DataManager::findItem(Item* item)
{
	auto iter = std::find_if(begin(devices), end(devices),
		[&](DeviceLocation& const obj) -> bool {
			return obj.item.get() == item;
		});
	return iter;
}

std::vector<const DeviceLocation*>
DataManager::findItemByName(const std::string& nameItem) const
{
	std::vector<const DeviceLocation*> resultFound;
	const auto SIZE = devices.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (devices[i].item->getName() == nameItem) {
			resultFound.push_back(&devices[i]);
		}
	}
	return resultFound;
}
std::vector<const DeviceLocation*>
DataManager::findItemByNumber(int64_t numberItem) const
{
	std::vector<const DeviceLocation*> resultFound;
	const auto SIZE = devices.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (devices[i].item->getInventoryNumber() == numberItem)
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

void DataManager::setCurrentLocationInfo(std::pair<std::string, std::string> location)
{
	currentLocation->setCurrentLocation(location.first, location.second);
}

auto DataManager::getCurrentLocationInfo() const -> std::pair<std::string, std::string>
{
	return currentLocation->getCurrentLocation();
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
	buildings.push_back(std::make_unique<Building>(nameBuilding));
}

Room* DataManager::getCurrentRoom() const
{
	Building* build = getCurrentBuilding();
	int index = 
		build->findRoom(currentLocation->getCurrentLocation().second);
	return build->getRoom(index);
}

Building* DataManager::getBuilding(const std::string& nameBuilding) const
{
	for (const auto& building : buildings) {
		if (building->getName() == nameBuilding)
			return building.get();
	}
	return nullptr;//!!!!
}

Building* DataManager::getCurrentBuilding() const
{
	return getBuilding(currentLocation->getCurrentLocation().first);
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
