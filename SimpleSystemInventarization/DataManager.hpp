#pragma once
#include "Item.hpp"
#include <vector>
#include <memory>
#include "IITequipmentFabric.hpp"

class DataManager {
public:
	enum typeITEquipment {
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
private:
	std::shared_ptr<ITequipment> createITequipment(typeITEquipment typeITE);
private:
	std::vector<std::shared_ptr<PC>> equipPC;
	std::vector<std::shared_ptr<Monitor>> equipMonitor;
	std::vector<std::shared_ptr<Printer>> equipPrinter;
	std::vector<std::shared_ptr<OtherEquipment>> equipOther;
	std::vector<std::unique_ptr<Item>> items;
private:
	std::unique_ptr<PCfabric> pcFabric;
	std::unique_ptr<MonitorFabric> monitorFabric;
	std::unique_ptr<PrinterFabric> printerFabric;
	std::unique_ptr<OtherFabric> otherFabric;
};
