#ifndef __DESERIALIZER__HPP__
#define __DESERIALIZER__HPP__

#include "tinyxml2.h"
#include "DataManager.hpp"
#include "IStrategyDeserialize.hpp"
#include <filesystem>

using namespace tinyxml2;
namespace fs = std::filesystem;

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS


class DECLSPEC Deserializer {
public:
	Deserializer(DataManager* dm, const fs::path& path_, XMLDocument* xmlDoc_);

	int loadData();
	
	Item* StrategyParseDevice(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location);

	void setStrategyParse(std::unique_ptr<IStrategyDeserialize> strategy_);

private:
	void decodeAllServiceInformation(Item* item, XMLElement* parent);
	int	loadXMLDocument();
	int decodeBuilding(std::vector<std::unique_ptr<Building>>& buildings);
	int decodeDevices(std::vector<DeviceLocation>& devices);
private:
	DataManager* dataManager;
	fs::path path;
	XMLDocument* xmlDoc;
	std::unique_ptr<IStrategyDeserialize> strategy;
};

#endif
