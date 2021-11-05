#ifndef __DEVICELOCATION__HPP__
#define __DEVICELOCATION__HPP__

#include <string>
#include "Item.hpp"
#include <memory>

struct Location {
	std::string buildingName;
	std::string roomName;
};

struct  DeviceLocation {
	std::unique_ptr<Item> item;
	Location location;
};

#endif
