#include "Serializer.hpp"

Serializer::Serializer(): path("data.xml")
{
}

Serializer::~Serializer()
{
}

int Serializer::decodeBuilding(std::vector<std::unique_ptr<Building>>& buildings)
{
	XMLDocument xmlDoc;
	XMLError eResult{ xmlDoc.LoadFile(path.c_str()) };
	if (eResult != XML_SUCCESS) {
		return eResult;
	}

	XMLNode* pRoot{ xmlDoc.FirstChildElement("Root") };
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

int Serializer::encodeBuilding(std::vector<std::unique_ptr<Building>>& buildings)
{
	XMLDocument xmlFile;
	XMLDeclaration* pDeclaration{ xmlFile.NewDeclaration() };
	xmlFile.InsertFirstChild(pDeclaration);

	XMLNode* pRoot{ xmlFile.NewElement("Root") };
	xmlFile.InsertEndChild(pRoot);

	XMLElement* pBuildings{ xmlFile.NewElement("Buildings") };
	pBuildings->SetAttribute("count", buildings.size());
	pRoot->InsertEndChild(pBuildings);

	for (size_t i{ 1 }; i < buildings.size(); ++i) {

		XMLElement* pBuilding{ xmlFile.NewElement("Building") };
		pBuilding->SetAttribute("name", buildings[i]->getName().c_str());
		pBuilding->SetAttribute("count", buildings[i]->size());
		pBuildings->InsertEndChild(pBuilding);

		for (size_t j{ 1 }; j < buildings[i]->size(); ++j) {
			XMLElement* pRoom{ xmlFile.NewElement("Room") };
			pRoom->SetAttribute("name", buildings[i]->getRoom(j)->getName().c_str());
			pBuilding->InsertEndChild(pRoom);
		}
	}
	XMLError eResult{ xmlFile.SaveFile("data.xml") };
	if (eResult != XML_SUCCESS) {
		return static_cast<int>(eResult);
	}
}

int Serializer::encode(DeviceLocation* device)
{
	XMLDocument xmlDoc;

	auto type{ device->item->getITequipment()->getType() };
	switch (type) {
	case MONITOR_TYPE:

	}
}

