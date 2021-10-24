#include "Build.hpp"

Build::Build(const std::string& name, std::shared_ptr<DataManager> dm) :
	dataManager{ dm },
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
	if (index == -1 || !rooms[index]->isEmpty()) {
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
