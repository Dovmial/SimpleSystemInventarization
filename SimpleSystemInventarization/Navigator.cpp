#include "Navigator.hpp"

Navigator::Navigator(
	const std::pair<size_t, std::string>& building,
	const std::pair<size_t, std::string>& room)
{
	location.building = building;
	location.room	  = room;
}

auto Navigator::getCurrentLocationString() const -> std::pair<std::string, std::string>
{
	return std::make_pair(location.building.second, location.room.second);
}

auto Navigator::getCurrentLocationIndexes() const -> std::pair<size_t, size_t>
{
	return std::pair<size_t, size_t>(location.building.first, location.room.first);
}

void Navigator::setCurrentLocation(
	std::pair<size_t, std::string> building,
	std::pair<size_t, std::string> room)
{
	location.building = building;
	location.room = room;
}

void Navigator::setCurrentRoom(const std::pair<size_t, std::string>& room)
{
	location.room = room;
}

Location Navigator::getLocation() const
{
	return location;
}

void Navigator::setCurrentBuilding(const std::pair<size_t, std::string>& building )
{
	location.building = building;
	location.room = {0, "Virtual room" };
}

