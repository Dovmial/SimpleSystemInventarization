#ifndef __SERIALIZER__HPP__
#define __SERIALIZER__HPP__

#include "Location.hpp"
#include "Building.hpp"
#include <filesystem>

namespace fs = std::filesystem;

/*
class Serializer {
public:
	Serializer();
	//void setFileName(const std::string& fileName);
	/*
	{PC, Monitor, Printer, OtherEquipment}
	{Building, Room};
	
	std::string operator()(Building building);
	std::string operator()(Room room);
	std::string operator()(DeviceLocation device);
private:
	
private:
	fs::path pathToFile;
};
*/
#endif
