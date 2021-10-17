
#include "Room.hpp" 
/*
Room::Room(const std::string& name_, std::shared_ptr<DataManager> dm) :
	dataManager(dm),
	BaseObject(name_)
{
}
*/

Room::Room(const std::string& name_): BaseObject(name_)
{

}

Item* Room::showItem(size_t index)
{
	return items.at(index).get();
}

void Room::addItem(std::unique_ptr<Item> item)
{
	items.push_back(move(item));
}

void Room::eraseItem(Item* item)
{
	auto erItem = find(begin(items), end(items), item);
	items.erase(erItem);
}
