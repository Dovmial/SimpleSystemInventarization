
#include <algorithm>
#include "Build.hpp"

Build::Build(const std::string& name) :
	BaseObject(name)
{
	rooms.push_back(std::make_unique<Room>("Virtual room"));
}

void Build::addRoom(const std::string& nameRoom)
{
	auto room{ std::make_unique<Room>(nameRoom) };
	rooms.push_back(std::move(room));
	std::sort(begin(rooms)+1, end(rooms));
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

int Build::findRoom(const std::string& nameRoom) const
{
	size_t size{ rooms.size() };
	
	for (size_t i{ }; i < size; ++i) {
		if (rooms[i]->getName() == nameRoom) {
			return i;
		}
	}
	return -1;
}

Room* Build::findItem(const std::string& name) const
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(name))
			return rooms[i].get();
	}
	return nullptr;
}

Room* Build::findItem(int64_t inventoryNumber) const
{
	size_t SIZE = rooms.size();
	for (size_t i{}; i < SIZE; ++i) {
		if (rooms[i]->findItem(inventoryNumber))
			return rooms[i].get();
	}
	return nullptr;
}

Room* Build::getRoom(int index) const
{
	return rooms[index].get();
}

bool Build::isExistRoom(const std::string& nameRoom) const
{
	return findRoom(nameRoom) != -1;
}

size_t Build::size() const
{
	return rooms.size();
}
