#ifndef __SERIALIZER__HPP__
#define __SERIALIZER__HPP__

#include "Building.hpp"
#include <memory>
#include "tinyxml2.h"
#include "Navigator.hpp"

using namespace tinyxml2;

class Serializer {
public:

	Serializer();
	~Serializer();

	int decodeBuilding(std::vector<std::unique_ptr<Building>>& buildings);
	int encodeBuilding(std::vector<std::unique_ptr<Building>>& buildings);

	int encode(DeviceLocation* device);
private:
	std::string path;
};
#endif