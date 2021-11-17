#ifndef __DATAMANAGER__HPP__
#define __DATAMANAGER__HPP__

#include <vector>
#include <memory>
#include "Item.hpp"
#include "IITequipmentFabric.hpp"
#include "GetDataEquipment.hpp"
#include "Building.hpp"
#include "Navigator.hpp"
#include "Serializer.hpp"


//$(SolutionDir)bin\$(Platform)\$(Configuration)\
//$(SolutionDir)bin\$(Platform)\$(Configuration)\intermediate\$(ProjectName)\

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

using DataPC = std::tuple<
	std::string, PC::TypePC, //0-info (name/type)
	std::string, //1-motherboard
	std::pair<std::string, float>, //2-cpu
	std::pair<std::string, float>, //3-graphicCard
	float, //4-ram
	std::tuple <float, std::string, StorageDevice::typeStorageDevice>, //5-storageDevice
	std::string>; //6-operationSystem

class DECLSPEC DataManager {
public:
	 enum class typeITEquipment {
		typePC = 1,
		typeMonitor,
		typePrinter,
		typeoOtherITEquipment
	};
	 DataManager();
	~DataManager();

	 Item* createItem(
		typeITEquipment type, 
		int64_t inventoryNumber_,
		const std::string& nameBuilding,
		const std::string& nameRoom
	);
	void setItem(Item* item);
	std::vector<DeviceLocation>::iterator findItem(Item* item);
	std::vector<const DeviceLocation*> findItemByName(const std::string& nameItem) const;
	std::vector<const DeviceLocation*> findItemByNumber(int64_t numberItem) const;
	void eraseItem(std::vector<DeviceLocation>::iterator&& iter);
	void update();

	
	int load();
	void save();

	void setDataMonitor(const std::string& name, float diagonal);
	void setDataPC(const DataPC& data);
	void setDataPrinter(
	const std::string& name, const std::string& cartridge, Printer::PrinterType data);
	void setDataOther(const std::string& name, const std::string& otherInfo);

public:
	void setCurrentLocationInfo(std::pair<std::string, std::string> location);
	auto getCurrentLocationInfo() const->std::pair<std::string, std::string>;
	void setCurrentRoomLocationInfo(const std::string& room);
	void setCurrentBuildingLocationInfo(const std::string& building);
	
public:
	void addBuilding(const std::string& nameBuilding);
	std::vector <std::unique_ptr<Building>>& getRefBuildings();
	Room* getCurrentRoom() const;
	Building* getBuilding(const std::string& nameBuilding) const;
	Building* getCurrentBuilding()const;
	std::vector<std::string> getListBuildingNames() const;
	std::vector<std::string> getListRoomNames() const;

private:
	std::shared_ptr<ITequipment> createITequipment(typeITEquipment typeITE);
private:
	std::vector<std::unique_ptr<Building>> buildings;
	std::vector<DeviceLocation> devices; // maybe std::list
private:
	std::unique_ptr<PCfabric> pcFabric;
	std::unique_ptr<MonitorFabric> monitorFabric;
	std::unique_ptr<PrinterFabric> printerFabric;
	std::unique_ptr<OtherFabric> otherFabric;
private:
	std::unique_ptr<MonitorGetData> monitorGetData;
	std::unique_ptr<PCgetData> pcGetData;
	std::unique_ptr<PrinterGetData> printerGetData;
	std::unique_ptr<OtherGetData> otherGetData;
private:
	std::unique_ptr<INavigator> currentLocation;
	std::unique_ptr<Serializer> serializer;
};
#endif