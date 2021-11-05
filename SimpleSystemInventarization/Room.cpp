
#include "Room.hpp" 
#include <algorithm>

Room::Room(const std::string& name_): BaseObject(name_)
{
}

Item* Room::showItem(size_t index) const
{
	return items.at(index);
}

void Room::addItem(Item* item)
{
	items.push_back(item);
}

void Room::eraseItem(Item* item)
{
	std::erase(items, item);
}

bool Room::isEmpty()
{
	return items.empty();
}

Item* Room::findItem(const std::string& name)
{
	size_t SIZE = items.size();
	for (size_t i = 0; i < SIZE; ++i) {
		if (name == items[i]->getName())
			return items[i];
	}
	return nullptr;
}

Item* Room::findItem(int64_t inventoryNumber)
{
	size_t SIZE = items.size();
	for (size_t i = 0; i < SIZE; ++i) {
		if (inventoryNumber == items[i]->getInventoryNumber())
			return items[i];
	}
	return nullptr;
}

 bool Room::operator<(const Room& other)
{
	 return  name < other.name;
}
