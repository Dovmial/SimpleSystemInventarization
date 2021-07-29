#include "Build.hpp"

Build::Build(std::string name_): BaseObject(name_)
{}
Build::Build(std::string name_, std::map<std::string, Room*> rooms_) :
	rooms(rooms_),
	BaseObject(name_)
{}

void Build::addRoom(Room* room)
{
	rooms.insert({ room->getName(), room });
}

void Build::deleteRoom(const std::string& nameOfdelElem)
{
	rooms.erase(nameOfdelElem);
}
