#include "Serializer.hpp"
#include "DeviceLocation.hpp"


Serializer::Serializer()
	: path{ fs::current_path() / "../source/data.xml"},
	xmlDoc{ std::make_unique<XMLDocument>() }
{
}

Serializer::~Serializer()
{
}

int Serializer::decodeBuilding(std::vector<std::unique_ptr<Building>>& buildings)
{
	XMLError eResult{ xmlDoc->LoadFile(path.string().c_str()) };
	if (eResult != XML_SUCCESS) {
		return eResult;
	}

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

XMLElement* Serializer::encodeBuildings(const std::vector<std::unique_ptr<Building>>& buildings)
{
	XMLElement* pBuildings{ xmlDoc->NewElement("Buildings") };
	pBuildings->SetAttribute("count", buildings.size()-1);

	for (size_t i{ 1 }; i < buildings.size(); ++i) {

		XMLElement* pBuilding{ xmlDoc->NewElement("Building") };
		pBuilding->SetAttribute("name", buildings[i]->getName().c_str());
		pBuilding->SetAttribute("count", buildings[i]->size()-1);
		pBuildings->InsertEndChild(pBuilding);

		for (size_t j{ 1 }; j < buildings[i]->size(); ++j) {
			XMLElement* pRoom{ xmlDoc->NewElement("Room") };
			pRoom->SetAttribute("name", buildings[i]->getRoom(j)->getName().c_str());
			pBuilding->InsertEndChild(pRoom);
		}
	}
	return pBuildings;
}

XMLElement* Serializer::encodeDevices(const std::vector<DeviceLocation>& devices)
{
	XMLElement* pDevices{ xmlDoc->NewElement("Devices") };
	XMLElement* pDevice;
	for (const auto& device : devices) {
		pDevice = device.serialize(*xmlDoc);
		pDevices->InsertEndChild(pDevice);
	}
	return pDevices;
}

void Serializer::createXMLDocument(
	const std::vector<std::unique_ptr<Building>>& buildings,
	const std::vector<DeviceLocation>			& devices
)
{
	auto pRoot		{ InitXMLDocument	(		  )	};
	auto pBuildings	{ encodeBuildings	(buildings) };
	auto pDevices	{ encodeDevices		(devices  )	};

	pRoot->InsertEndChild(pBuildings);
	pRoot->InsertEndChild(pDevices);
}

int Serializer::saveXMLDocument() {
	
	
	XMLError eResult{ xmlDoc->SaveFile(path.string().c_str()) };
	if (eResult != XML_SUCCESS) {
		return static_cast<int>(eResult);
	}
	return 0;
}

void Serializer::clearXMLDocument()
{
	xmlDoc->Clear();
}

bool Serializer::isCompareXML()
{
	auto xmlFile{ std::make_unique<XMLDocument>() };
	if (fs::exists(path)) {
		xmlFile->Parse(path.string().c_str());
		return xmlFile == xmlDoc;
	}
}

XMLNode* Serializer::InitXMLDocument() {
	XMLDeclaration* pDeclaration{ xmlDoc->NewDeclaration() };
	xmlDoc->InsertFirstChild(pDeclaration);

	XMLNode* pRoot{ xmlDoc->NewElement("Root") };
	xmlDoc->InsertEndChild(pRoot);

	return pRoot;
}

void Serializer::setPathToXMLFile(const std::string& path_)
{
	path = path_;
}
