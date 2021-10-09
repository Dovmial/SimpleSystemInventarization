
#include "Room.hpp" 

Room::Room(const std::string& name_, std::shared_ptr<DataManager> dm) :
	dataManager(dm),
	BaseObject(name_)
{
}

void Room::addItem(DataManager::typeITEquipment type, int64_t inventoryNumber)
{
	auto item = dataManager->createItem(type, inventoryNumber);
	items.push_back(move(item));
}

void Room::eraseItem(Item* item)
{
	auto erItem = find(begin(items), end(items), item);
	items.erase(erItem);
}
