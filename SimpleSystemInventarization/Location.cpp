#include "Location.hpp"

bool Location::operator==(const Location& other) const
{
    return
    buildingName == other.buildingName &&
    roomName == other.roomName;
}
