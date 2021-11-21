#include "Serializer.hpp"
#include "DeviceLocation.hpp"


Serializer::Serializer()
	: path{ "./data/data.xml"},
	xmlDoc{ std::make_unique<XMLDocument>() }
{
}

Serializer::~Serializer()
{
}

fs::path Serializer::getPath() const
{
	return path;
}

XMLDocument* Serializer::getXMLDocument() const
{
	return xmlDoc.get();
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
	pDevices->SetAttribute("count", devices.size());
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
		return eResult;
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
