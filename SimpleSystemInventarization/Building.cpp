
#include <algorithm>
#include "Building.hpp"

Building::Building(const std::string& name) :
	BaseObject(name)
{
	rooms.push_back(std::make_unique<Room>("Virtual room"));
}

void Building::addRoom(const std::string& nameRoom)
{
	auto room{ std::make_unique<Room>(nameRoom) };
	rooms.push_back(std::move(room));
	std::sort(begin(rooms)+1, end(rooms), 
		[&](std::unique_ptr<Room> const & obj1, std::unique_ptr<Room>& obj2) -> bool {
			return obj1->getName() < obj2->getName();
		});
}

bool Building::removeRoom(const std::string& nameRoom)
{
	int index = findRoom(nameRoom);
	if (index == -1 || !rooms[index]->isEmpty()) {//remove only for an empty room
		return false;
	}
	rooms.erase(begin(rooms) + index);
	return true;
}

int Building::findRoom(const std::string& nameRoom) const
{
	size_t size{ rooms.size() };
	
	for (size_t i{ }; i < size; ++i) {
		if (rooms[i]->getName() == nameRoom) {
			return i;
		}
	}
	return -1;
}

Room* Building::findItem(const std::string& name) const
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(name))
			return rooms[i].get();
	}
	return nullptr;
}

Room* Building::findItem(int64_t inventoryNumber) const
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(inventoryNumber))
			return rooms[i].get();
	}
	return nullptr;
}

Room* Building::getRoom(int index) const
{
	return rooms.at(index).get();
}

bool Building::isExistRoom(const std::string& nameRoom) const
{
	return findRoom(nameRoom) != -1;
}

size_t Building::size() const
{
	return rooms.size();
}
