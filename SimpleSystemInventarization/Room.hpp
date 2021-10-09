#ifndef __ROOM__HPP___
#define __ROOM__HPP___

#include <vector>
#include <string>
#include "Item.hpp"
#include "BaseObject.hpp"
#include "DataManager.hpp"
#include <memory>

class Room: public BaseObject{
private:
	std::vector<std::unique_ptr<Item>> items;
	std::shared_ptr<DataManager> dataManager;

public:
	Room() = delete;
	Room(const std::string& name_, std::shared_ptr<DataManager> dm);

	void addItem(DataManager::typeITEquipment type, int64_t inventoryNumber);
	void eraseItem(Item* item);
};

#endif // !__ROOM__HPP___