#include "Navigator.hpp"

Navigator::Navigator(const std::string& building, const std::string& room)
	:location({ building, room })
{
}

auto Navigator::getCurrentlocation() const -> std::pair<std::string, std::string>
{
	return std::make_pair(location.buildingName, location.roomName);
}

void Navigator::setCurrentLocation(const std::string& building, const std::string& room)
{
	location.buildingName = building;
	location.roomName = room;
}