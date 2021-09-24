#pragma once
#include "Item.hpp"
#include <vector>
#include <memory>
#include <string_view>

class DataManager {
public:
	enum typeITEquipment {
		typePC = 1,
		typeMonitor,
		typePrinter,
		typeMFU,
		typeoOtherITEquipment
	};
	DataManager();
	~DataManager();
	
	std::unique_ptr<Item> createItem(std::shared_ptr<ITequipment> equipment_,
		int64_t inventoryNumber_ = -1);

	std::unique_ptr<Item> createNewItem(
		std::string_view name_,
		typeITEquipment type,
		int64_t inventoryNumber_ = -1
	);
private:
	std::shared_ptr<ITequipment> createITequipment(
		std::string_view name, typeITEquipment typeITE
	);
	std::vector<std::shared_ptr<PC>> equipPC;
	std::vector<std::shared_ptr<Monitor>> equipMonitor;
	std::vector<std::shared_ptr<Printer>> equipPrinter;
	std::vector<std::shared_ptr<OtherEquipment>> equipOther;
	std::vector<std::unique_ptr<Item>> items;

};
