
#include "Room.hpp" 
#include <algorithm>

Room::Room(const std::string& name_): BaseObject(name_)
{
}

Item* Room::showItem(size_t index) const
{
	return items.at(index).get();
}

void Room::addItem(std::unique_ptr<Item> item)
{
	items.push_back(std::move(item));
}

void Room::eraseItem(Item* item)
{
	/*
	auto erItem = find(begin(items), end(items), item);
	items.erase(erItem);
	*/
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
			return items[i].get();
	}
	return nullptr;
}

Item* Room::findItem(int64_t inventoryNumber)
{
	size_t SIZE = items.size();
	for (size_t i = 0; i < SIZE; ++i) {
		if (inventoryNumber == items[i]->getInventoryNumber())
			return items[i].get();
	}
	return nullptr;
}

 bool Room::operator<(const Room& other)
{
	 return  name < other.name;
}
