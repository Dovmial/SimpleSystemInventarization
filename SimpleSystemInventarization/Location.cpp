#include "Location.hpp"

bool Location::operator==(const Location& other) const
{
    return building.first == other.building.first && room.first == other.room.first;
}

