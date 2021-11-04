
#include <algorithm>
#include "Build.hpp"

Build::Build(const std::string& name) :
	BaseObject{ name }
{
}

void Build::addRoom(const std::string& nameRoom)
{
	auto room{ std::make_unique<Room>(nameRoom) };
	rooms.push_back(std::move(room));
	std::sort(begin(rooms), end(rooms));
}

bool Build::removeRoom(const std::string& nameRoom)
{
	int index = findRoom(nameRoom);
	if (index == -1 || !rooms[index]->isEmpty()) {//remove only for an empty room
		return false;
	}
	rooms.erase(begin(rooms) + index);
	return true;
}

int Build::findRoom(const std::string& nameRoom)
{
	if (rooms.empty()) {
		return -1;
	}
	size_t size{ rooms.size() };
	
	for (size_t i{ }; i < size; ++i) {
		if (rooms[i]->getName() == nameRoom) {
			return i;
		}
	}
}

Room* Build::findItem(const std::string& name)
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(name))
			return rooms[i].get();
	}
	return nullptr;
}

Room* Build::findItem(int64_t inventoryNumber)
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(inventoryNumber))
			return rooms[i].get();
	}
	return nullptr;
}
