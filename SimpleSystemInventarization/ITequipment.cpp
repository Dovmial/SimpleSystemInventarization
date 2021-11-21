#include "ITequipment.hpp"
#include <sstream>
#include <iomanip>

ITequipment::ITequipment(const std::string& name_): BaseObject(name_)
{}

/*
PC::PC(const std::string& name_, TypePC typePC_) :
	typePC(typePC_), ITequipment(name_),
	motherboard(MotherBoard("")), _cpu(CPU("")), ram(RAM(0.f)),
	storageDevice(0.f), graphicCard("", 0.f),
	operationSystem("")
{
}
*/
PC::PC(const std::string& name_, TypePC type_,
	std::shared_ptr<ComplectComponents> complect) :
	typePC{ type_ },
	motherboard{ "" },
	_cpu{ "" },
	ram{ 0.0 },
	storageDevice{ 0.0 },
	graphicCard{""},
	ITequipment(name_)
{
	setComplectComponents(complect);
}


std::string PC::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(16) << typePCtoStr() << ": " << name << '\n';
	ssInfo << motherboard.getInfo();
	ssInfo << _cpu.getInfo();
	ssInfo << ram.getInfo();
	ssInfo << graphicCard.getInfo();
	ssInfo << storageDevice.getInfo();
	ssInfo << "Operation system: " << operationSystem << '\n';
	return ssInfo.str();
}

typeDevice PC::getType() const 
{
	return typeDevice::PC_TYPE;
}

XMLElement* PC::serialize(XMLDocument& xmlDoc) const
{
	XMLElement* pPC{ xmlDoc.NewElement("PC") };
	pPC->SetAttribute("typePC", static_cast<int>(typePC));
	pPC->SetAttribute("name", name.c_str());
	XMLElement* pMotherboard{ xmlDoc.NewElement("Motherboard") };
	pMotherboard->SetAttribute("name", motherboard.getName().c_str());
	pPC->InsertEndChild(pMotherboard);

	XMLElement* pCPU{ xmlDoc.NewElement("CPU") };
	pCPU->SetAttribute("name", _cpu.getName().c_str());
	pCPU->SetAttribute("frequency", _cpu.getFrequency());
	pPC->InsertEndChild(pCPU);

	XMLElement* pGraphicCard{ xmlDoc.NewElement("GraphicCard") };
	pGraphicCard->SetAttribute("name", graphicCard.getName().c_str());
	pGraphicCard->SetAttribute("volume", graphicCard.getVolume());
	pPC->InsertEndChild(pGraphicCard);

	XMLElement* pRAM{ xmlDoc.NewElement("RAM") };
	pRAM->SetAttribute("name", ram.getName().c_str());
	pRAM->SetAttribute("volume", ram.getVolume());
	pPC->InsertEndChild(pRAM);

	XMLElement* pStorageDevice{ xmlDoc.NewElement("StorageDevice") };
	pStorageDevice->SetAttribute(
		"typeStorageDevice",+
		static_cast<int>(storageDevice.getStorageDeviceType())
	);
	pStorageDevice->SetAttribute("name", storageDevice.getName().c_str());
	pStorageDevice->SetAttribute("volume", storageDevice.getVolume());
	pPC->InsertEndChild(pStorageDevice);

	XMLElement* pOperationSystem{ xmlDoc.NewElement("OperationSystem") };
	pOperationSystem->SetText(operationSystem.c_str());
	pPC->InsertEndChild(pOperationSystem);
	return pPC;
}

void PC::setTypePC(TypePC typePC_)
{
	typePC = typePC_;
}

std::shared_ptr<ComplectComponents> PC::getComplectComponents() const
{
	
	auto components{ std::make_shared<ComplectComponents>(
		std::make_tuple(
			motherboard, _cpu, graphicCard,
			ram, storageDevice, operationSystem)
		)
	};
	return components;
}

void PC::setComplectComponents(std::shared_ptr<ComplectComponents> complect)
{
	auto& [ motherBoard, _cpu, graphCard, ram, storDevice, operSystem] = *complect;
	setMotherboard(motherBoard);
	setCPU(_cpu);
	setGraphicCard(graphCard);
	setRAM(ram);
	setStorageDevice(storDevice);
	setOperationSystem(operSystem);
}

void PC::setMotherboard(const MotherBoard& mb)
{
	motherboard = mb;
}

void PC::setCPU(const CPU& _cpu)
{
	this->_cpu = _cpu;
}

void PC::setRAM(const RAM& ram_)
{
	ram = ram_;
}

std::string PC::typePCtoStr() const
{
	switch (typePC)
	{
	case PC::TypePC::SystemBlock:
		return "System block";
	case PC::TypePC::Laptop:
		return "Laptop";
	case PC::TypePC::Monoblock:
		return "Monoblock";
	}
}

void PC::setStorageDevice(const StorageDevice& sd)
{
	storageDevice = sd;
}

void PC::setGraphicCard(const GraphicCard& gc)
{
	graphicCard = gc;
}

void PC::setOperationSystem(const std::string& opSys)
{
	operationSystem = opSys;
}

PC::TypePC PC::getTypePC() const
{
	return typePC;
}

Monitor::Monitor(std::pair<const std::string, float>&& info):
	diagonal(info.second), ITequipment(info.first)
{
}

Monitor::Monitor(const std::string& name_, float diagonal_):
	diagonal(diagonal_), ITequipment(name_)
{
}

void Monitor::setDiagonal(float diagonal)
{
	this->diagonal = diagonal;
}


float Monitor::getDiagonal() const
{
	return diagonal;
}

std::string Monitor::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(15) << "Diagonal: " << diagonal << '\n';
	return ssInfo.str();
}

typeDevice Monitor::getType() const
{
	return typeDevice::MONITOR_TYPE;
}

XMLElement* Monitor::serialize(XMLDocument& xmlDoc) const
{
	XMLElement* pMonitor{ xmlDoc.NewElement("Monitor") };
	pMonitor->SetAttribute("name", getName().c_str());
	pMonitor->SetAttribute("diagonal", getDiagonal());
	return pMonitor;
}

Printer::Printer(const std::string& name_, Cartridge&& cartridge_, PrinterType type_):
	cartridge(cartridge_), type(type_), ITequipment(name_)
{
}

Printer::Printer(const std::tuple<std::string, Cartridge, PrinterType>& info):
	cartridge(std::get<1>(info)),
	type(std::get<2>(info)),
	ITequipment(std::get<0>(info))
{
}

void Printer::setCartridge(Cartridge&& cartridge_)
{
	cartridge = std::move(cartridge_);
}

Cartridge Printer::getCartridge() const
{
	return cartridge;
}

std::string Printer::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(15) << "Type: " << printerTypeToStr()<<'\n'
		<< std::setw(15) << "Cartridge: " << cartridge.getName() << '\n';
	return ssInfo.str();
}

std::string Printer::printerTypeToStr() const
{
	switch (type)
	{
	case Printer::PrinterType::PRINTER:
		return std::string("Printer");
	case Printer::PrinterType::MFU:
		return std::string("MFU");
	case Printer::PrinterType::PRINTER3D:
		return std::string("3D-Printer");
	}
}

Printer::PrinterType Printer::getPrinterType() const
{
	return type;
}

typeDevice Printer::getType()const {
	return typeDevice::PRINTER_TYPE;
}

XMLElement* Printer::serialize(XMLDocument& xmlDoc) const
{
	XMLElement* pPrinter{ xmlDoc.NewElement("Printer") };
	pPrinter->SetAttribute("type", static_cast<int>(getType()));
	pPrinter->SetAttribute("name", getName().c_str());

	XMLElement* pCartridge{ xmlDoc.NewElement("Cartridge") };
	pCartridge->SetText(getCartridge().getName().c_str());
	pPrinter->InsertEndChild(pCartridge);
	return pPrinter;
}

OtherEquipment::OtherEquipment(const std::string& name_, const std::string& someInfo_)
: someInfo(someInfo_), ITequipment(name_)
{
}

OtherEquipment::OtherEquipment(const std::pair<const std::string, std::string>& info) :
	someInfo(info.second), ITequipment(info.first)
{
}

void OtherEquipment::setSomeInfo(const std::string& someInfo)
{
	this->someInfo = someInfo;
}

std::string OtherEquipment::getSomeInfo() const
{
	return someInfo;
}

std::string OtherEquipment::getInfo() const
{
	return std::string(name + " " + someInfo + '\n');
}

typeDevice OtherEquipment::getType()const {
	return typeDevice::OTHER_TYPE;
}

XMLElement* OtherEquipment::serialize(XMLDocument& xmlDoc) const
{
	XMLElement* pOther{ xmlDoc.NewElement("Other") };
	pOther->SetAttribute("name", getName().c_str());
	XMLElement* pSomeInfo{ xmlDoc.NewElement("SomeInfo") };
	pSomeInfo->SetText(getSomeInfo().c_str());
	pOther->InsertEndChild(pSomeInfo);
	return pOther;
}
