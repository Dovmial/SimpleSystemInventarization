#pragma once
#include "Item.hpp"
#include <vector>
#include <memory>
#include "IITequipmentFabric.hpp"
#include "GetDataEquipment.hpp"

//$(SolutionDir)bin\$(Platform)\$(Configuration)\
//$(SolutionDir)bin\$(Platform)\$(Configuration)\intermediate\$(ProjectName)\

//Singleton

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

using DataPC = std::tuple<
	std::pair<std::string, PC::TypePC>, //0-info (name/type)
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
	
	std::unique_ptr<Item> createItem(
		typeITEquipment type,
		int64_t inventoryNumber_ = -1
	);

	void setDataMonitor	(const std::string& name, float diagonal);
	void setDataPC(DataPC& data);

	void setDataPrinter(
		const std::string& name, const std::string& cartridge, Printer::PrinterType data);
	void setDataOther(const std::string& name, const std::string& otherInfo);
private:
	std::shared_ptr<ITequipment> createITequipment(typeITEquipment typeITE);

/*private:
	std::vector<std::shared_ptr<PC>> equipPC;
	std::vector<std::shared_ptr<Monitor>> equipMonitor;
	std::vector<std::shared_ptr<Printer>> equipPrinter;
	std::vector<std::shared_ptr<OtherEquipment>> equipOther;
	std::vector<std::unique_ptr<Item>> items;
	*/
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
};
