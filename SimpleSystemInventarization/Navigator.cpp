#include "Navigator.hpp"

Navigator::Navigator(const std::string& building, const std::string& room)
	:location({ building, room })
{
}

auto Navigator::getCurrentLocation() const -> std::pair<std::string, std::string>
{
	return std::make_pair(location.buildingName, location.roomName);
}

void Navigator::setCurrentLocation(const std::string& building, const std::string& room)
{
	location.buildingName = building;
	location.roomName = room;
}

void Navigator::setCurrentRoom(const std::string& room)
{
	location.roomName = room;
}

Location Navigator::getLocation() const
{
	return location;
}

void Navigator::setCurrentBuilding(const std::string& building)
{
	location.buildingName = building;
	location.roomName = "Virtual room";
}