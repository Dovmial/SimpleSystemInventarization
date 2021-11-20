#include "IStrategyDeserialize.hpp"


Item* StrategyParsePC::StrategyParseXMLElement(DataManager* dataManager, XMLElement* parent, int64_t itemNumber, const std::pair<size_t, size_t>& location)
{
	XMLElement* pPC { parent->FirstChildElement("PC") };
	auto pcType		{ pPC->IntAttribute("typePC")	  };

	auto type{ [&]()->PC::TypePC {
		switch (pcType) {
		case 1:
			return PC::TypePC::SystemBlock;
		case 2:
			return PC::TypePC::Laptop;
		case 3:
			return  PC::TypePC::Monoblock;
		}
	}() };

	auto name{ std::string(pPC->Attribute("name")) };
	XMLElement* pMotherBoard{ pPC->FirstChildElement("Motherboard") };
	auto motherboard{ std::string (pMotherBoard->Attribute("name")) };

	XMLElement* pCPU{ pPC->FirstChildElement("CPU") };
	auto _cpu{ std::make_pair(
		std::string(pCPU->Attribute("name")),
		pCPU->FloatAttribute("frequency")
	)};

	XMLElement* pGraphicCard{ pPC->FirstChildElement("GraphicCard") };
	auto graphicCard{ std::make_pair(
		std::string(pGraphicCard->Attribute("name")),
		pGraphicCard->FloatAttribute("volume")
	)};

	XMLElement* pRAM{ pPC->FirstChildElement("RAM") };
	auto ram{pRAM->FloatAttribute("volume")};

	XMLElement* pStorageDevice{ pPC->FirstChildElement("StorageDevice") };
	auto typeSD{ pStorageDevice->IntAttribute("typeStorageDevice") };
	auto storageDevice{ std::make_tuple(
		pStorageDevice->FloatAttribute("volume"),
		std::string(pStorageDevice->Attribute("name")),
		[&]()->StorageDevice::typeStorageDevice {
			switch (typeSD) {
			case 1:
				return StorageDevice::typeStorageDevice::HDD;
			case 2: 
				return StorageDevice::typeStorageDevice::SSD;
			}
		}())
	};
	auto operationSystem{ std::string( pPC->FirstChildElement("OperationSystem")->GetText()) };
	auto data{
		std::make_tuple(
			name, type,
			motherboard, _cpu,
			graphicCard, ram,
			storageDevice,
			operationSystem)
	};
	dataManager->setDataPC(std::move(data));
	auto item{ std::move(
		dataManager->createItem(
			DataManager::typeITEquipment::typePC,
			itemNumber,
			location
	)) };
	return item;
}

Item* StrategyParseMonitor::StrategyParseXMLElement(
	DataManager* dataManager,
	XMLElement* parent,
	int64_t itemNumber,
	const std::pair<size_t, size_t>& location)
{
	XMLElement* pMonitor{ parent->FirstChildElement("Monitor") };
	auto name{ pMonitor->Attribute("name") };
	auto diagonal{ pMonitor->FloatAttribute("diagonal") };
	dataManager->setDataMonitor(name, diagonal);
	auto item{ dataManager->createItem(
		DataManager::typeITEquipment::typeMonitor,
		itemNumber,
		location
	) };

	return item;
}

Item* StrategyParsePrinter::StrategyParseXMLElement(DataManager* dataManager, XMLElement* parent, int64_t itemNumber, const std::pair<size_t, size_t>& location)
{
	XMLElement* pPrinter{ parent->FirstChildElement("Printer") };
	auto type{ pPrinter->IntAttribute("type") };
	auto name{ pPrinter->Attribute	 ("name") };

	XMLElement* pCartridge{ pPrinter->FirstChildElement("Cartridge") };
	auto cartridge{ pCartridge ? pCartridge->GetText() : "" };

	auto printerType{ [&]()->Printer::PrinterType {
		switch (type) {
		case 1: 
			return Printer::PrinterType::PRINTER;
		case 2:
			return Printer::PrinterType::MFU;
		case 3:
			return  Printer::PrinterType::PRINTER3D;
		}
	}() };

	dataManager->setDataPrinter(name, cartridge, printerType);
	auto item{ std::move(dataManager->createItem(
		DataManager::typeITEquipment::typePrinter,
		itemNumber,
		location
		)
	) };
	return item;
}

Item* StrategyParseOther::StrategyParseXMLElement(DataManager* dataManager, XMLElement* parent, int64_t itemNumber, const std::pair<size_t, size_t>& location)
{
	XMLElement* pOther{ parent->FirstChildElement("Other")};
	auto name{ std::string(pOther->Attribute("name"	)) };

	XMLElement* pSomeInfo{ pOther->FirstChildElement("SomeInfo" ) };
	auto otherInfo{ pSomeInfo ? std::string(pSomeInfo->GetText()) : "" };

	dataManager->setDataOther(name, otherInfo);
	auto item{
		dataManager->createItem(
			DataManager::typeITEquipment::typeoOtherITEquipment,
			itemNumber,
			location
		) };
	return item;
}
