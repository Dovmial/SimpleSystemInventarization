#ifndef __SERIALIZER__HPP__
#define __SERIALIZER__HPP__

#include "Building.hpp"
#include <memory>
#include "tinyxml2.h"
#include "Navigator.hpp"
#include "DeviceLocation.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using namespace tinyxml2;

class Serializer {
public:

	Serializer();
	~Serializer();

	fs::path getPath()const;
	XMLDocument* getXMLDocument() const;

	XMLElement* encodeBuildings(const std::vector<std::unique_ptr<Building>>& buildings);
	XMLElement* encodeDevices(const std::vector<DeviceLocation>& devices);

	void createXMLDocument(
		const std::vector<std::unique_ptr<Building>>& buildings,
		const std::vector<DeviceLocation>& devices
	);
	int	 saveXMLDocument();
	
	void clearXMLDocument();
	bool isCompareXML();
public:
	void setPathToXMLFile(const std::string& path_);
private:
	XMLNode* InitXMLDocument();

	fs::path path;
	std::unique_ptr<XMLDocument> xmlDoc;
};
#endif