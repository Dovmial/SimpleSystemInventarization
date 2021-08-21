
#include "Room.hpp" 

Room::Room(const std::string& name_) : BaseObject(name_)
{
}

void Room::addItem(Item* item)
{
	items.push_back(item);
}

void Room::eraseItem(Item* item)
{
	auto erItem = find(begin(items), end(items), item);
	items.erase(erItem);
}
