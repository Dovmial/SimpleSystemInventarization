#include "Deserializer.hpp"

Deserializer::Deserializer(DataManager* dm, const fs::path& path_, XMLDocument* xmlDoc_)
	:dataManager(dm),
	path{path_},
	xmlDoc{xmlDoc_},
	strategy{nullptr}
{
}

int Deserializer::loadData()
{
	if (int error{ loadXMLDocument() }; error != 0)
		return error;
	decodeBuilding(dataManager->getRefBuildings());
	decodeDevices(dataManager->getDevices());
	return 0;
}

int Deserializer::loadXMLDocument()
{
	XMLError eResult{ xmlDoc->LoadFile(path.string().c_str()) };
	if (eResult != XML_SUCCESS) {
		return eResult;
	}
	return 0;
}

int Deserializer::decodeBuilding(std::vector<std::unique_ptr<Building>>& buildings)
{

	XMLNode* pRoot{ xmlDoc->FirstChildElement("Root") };
	if (!pRoot) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* pBuildings{ pRoot->FirstChildElement("Buildings") };
	if (!pBuildings) return XML_ERROR_PARSING_ELEMENT;

	const char* strSIZE{ pBuildings->Attribute("count") };
	if (!strSIZE) return XML_ERROR_PARSING_ATTRIBUTE;
	size_t countBuildings{ static_cast<size_t>(atoi(strSIZE)) };

	buildings.reserve(countBuildings);

	XMLElement* pBuilding{ pBuildings->FirstChildElement("Building") };
	if (!pBuilding) return XML_ERROR_PARSING_ELEMENT;
	const char* nameBuilding;
	const char* countRooms;
	const char* nameRoom;
	XMLElement* pRoom;
	while (pBuilding != nullptr) {
		nameBuilding = pBuilding->Attribute("name");
		if (!nameBuilding) return XML_ERROR_PARSING_ATTRIBUTE;

		countRooms = pBuilding->Attribute("count");
		if (!countRooms) return XML_ERROR_PARSING_ATTRIBUTE;

		buildings.push_back(std::move(std::make_unique<Building>(std::string(nameBuilding))));

		pRoom = pBuilding->FirstChildElement("Room");
		if (!pRoom) return XML_ERROR_PARSING_ELEMENT;

		while (pRoom != nullptr) {

			nameRoom = pRoom->Attribute("name");
			if (!nameRoom) return XML_ERROR_PARSING_ATTRIBUTE;
			buildings.back()->addRoom(std::string(nameRoom));

			pRoom = pRoom->NextSiblingElement("Room");
		}

		pBuilding = pBuilding->NextSiblingElement("Building");
	}
	return 0;
}

int Deserializer::decodeDevices(std::vector<DeviceLocation>& devices)
{
	XMLNode* pRoot{ xmlDoc->FirstChildElement("Root") };
	if (!pRoot) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* pDevices{ pRoot->FirstChildElement("Devices") };
	if (!pDevices) return XML_ERROR_PARSING_ELEMENT;

	const char* strSIZE{ pDevices->Attribute("count") };
	if (!strSIZE) return XML_ERROR_PARSING_ATTRIBUTE;
	size_t countDevices{ static_cast<size_t>(atoi(strSIZE)) };

	devices.reserve(countDevices);

	XMLElement* pDevice{ pDevices->FirstChildElement("Device") };
	if (!pDevice) return XML_ERROR_PARSING_ELEMENT;

	const char* buildingIndexSTR;
	const char* roomIndexSTR;

	XMLElement* pItem;
	size_t buildingIndex;
	size_t roomIndex;
	int64_t itemNumber;
	int itemType;
	Item* item{ nullptr };

	while (pDevice != nullptr) {
		buildingIndex = pDevice->IntAttribute("buildingIndex");
		roomIndex	  = pDevice->IntAttribute("roomIndex");

		pItem = pDevice->FirstChildElement("Item");
		if (!pItem) return XML_ERROR_PARSING_ELEMENT;

		itemNumber = pItem->Int64Attribute("inventoryNumber");
		itemType   = pItem->IntAttribute("type");

		switch (itemType) {
		case PC_TYPE:
			setStrategyParse(std::move(std::make_unique<StrategyParsePC>()));
			item = StrategyParseDevice(dataManager, pItem, itemNumber, std::make_pair(buildingIndex, roomIndex));
			break;
		case MONITOR_TYPE:
		{
			setStrategyParse(std::move(std::make_unique<StrategyParseMonitor>()));
			item = StrategyParseDevice(dataManager, pItem, itemNumber, std::make_pair(buildingIndex, roomIndex));
			break;
		}
		case PRINTER_TYPE:
			setStrategyParse(std::move(std::make_unique < StrategyParsePrinter>()));
			item = StrategyParseDevice(dataManager, pItem, itemNumber, std::make_pair(buildingIndex, roomIndex));
			break;
		case OTHER_TYPE:
			setStrategyParse(std::move(std::make_unique<StrategyParseOther>()));
			item = StrategyParseDevice(dataManager, pItem, itemNumber, std::make_pair(buildingIndex, roomIndex));
			break;
		}
		decodeAllServiceInformation(item, pItem);
		pDevice = pDevice->NextSiblingElement("Device");
	}

}

void Deserializer::decodeAllServiceInformation(Item* item, XMLElement* parent)
{

	XMLElement* pServices{ parent	->FirstChildElement("Services"	 ) };
	XMLElement* pService { pServices->FirstChildElement("ServiceInfo") };
	std::string date, description;

	while (pService != nullptr) {
		date = pService->Attribute("date");
		description = pService ? pService->GetText() : "";
		item->addSignService(description, date);
		pService = pService->NextSiblingElement("ServiceInfo");
	}

	XMLElement* pProblemSolutions{ parent->FirstChildElement("ProblemSolutions") };
	XMLElement* pProblemSolution{ pProblemSolutions->FirstChildElement("ProblemSolution") };
	std::string problem, solution;

	if (!pProblemSolution) {
		return;
	}

	XMLElement* pProblem{ pProblemSolution->FirstChildElement("Problem") };
	XMLElement* pSolution{ pProblemSolution->FirstChildElement("Solution") };
	XMLElement* pDate{ pProblemSolution->FirstChildElement("Date") };

	while (pProblemSolution != nullptr)
	{
		problem  = pProblem  ? pProblem ->GetText() : "";
		solution = pSolution ? pSolution->GetText() : "";
		date	 = pDate	 ? pDate	->GetText() : "";
		item->addSignProblemsSolutions(problem, date, solution);
		pProblemSolution = pProblemSolution->NextSiblingElement("ProblemSolution");
	}
}

Item* Deserializer::StrategyParseDevice(
	DataManager* dm,
	XMLElement* parent,
	int64_t itemNumber,
	const std::pair<size_t, size_t>& location)
{
	return strategy->StrategyParseXMLElement(dm, parent, itemNumber, location);
}

void Deserializer::setStrategyParse(std::unique_ptr<IStrategyDeserialize> strategy_)
{
	strategy = std::move(strategy_);
}



