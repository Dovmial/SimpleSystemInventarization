#include "ITequipment.hpp"
#include <sstream>
#include <iomanip>



ITequipment::ITequipment(const std::string& name_): BaseObject(name_)
{
}


PC::PC(const std::string& name_, TypePC typePC_): typePC(typePC_), ITequipment(name_),
motherboard(MotherBoard("")), _cpu(CPU("")), ram(RAM(0.f)),
storageDevice(0.f), graphicCard("", 0.f),
operationSystem("")
{
}

PC::PC(std::tuple<std::string, TypePC> baseInfo): 
	PC(std::get<0>(baseInfo), std::get<1>(baseInfo))
{
}


std::string PC::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(20) << typePCtoStr() << ": " << name << '\n';
	ssInfo << std::setw(20) << motherboard.getInfo();
	ssInfo << std::setw(20) << _cpu.getInfo();
	ssInfo << std::setw(20) << ram.getInfo();
	ssInfo << std::setw(20) << graphicCard.getInfo();
	ssInfo << std::setw(20) << storageDevice.getInfo();
	ssInfo << std::setw(20) << "Operation system: " << operationSystem << '\n';
	return ssInfo.str();
}


void PC::setTypePC(TypePC typePC_)
{
	typePC = typePC_;
}

void PC::setMotherboard(const MotherBoard& mb)
{
	motherboard = std::move(mb);
}

void PC::setCPU(const CPU& _cpu)
{
	this->_cpu = std::move(_cpu);
}

void PC::setRAM(const RAM& ram_)
{
	ram = std::move(ram_);
}

std::string PC::typePCtoStr() const
{
	switch (typePC)
	{
	case SystemBlock:
		return "System block";
	case Laptop:
		return "Laptop";
	case Monoblock:
		return "Monoblock";
	}
}

void PC::setStorageDevice(const StorageDevice& sd)
{
	storageDevice = std::move(sd);
}

void PC::setGraphicCard(const GraphicCard& gc)
{
	graphicCard = std::move(gc);
}

void PC::setOperationSystem(const std::string& opSys)
{
	operationSystem = opSys;
}

PC::TypePC PC::getTypePC() const
{
	return typePC;
}

Monitor::Monitor(std::pair<std::string, float>&& info):
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

Printer::Printer
(const std::string& name_, Cartridge&& cartridge_, bool isMFU_):
	cartridge(cartridge_), isMFU(isMFU_), ITequipment(name_)
{
}

Printer::Printer(std::tuple<std::string, Cartridge, bool>&& info):
	cartridge(std::get<1>(info)),
	isMFU(std::get<2>(info)),
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
	ssInfo << std::setw(15) << "Type: " << (isMFU ? "MFU\n" : "Printer\n")
		<< std::setw(15) << "Cartridge: " << cartridge.getName() << '\n';
	return ssInfo.str();
}

void Printer::setIsMFU(bool isMFU_)
{
	isMFU = isMFU_;
}

bool Printer::getIsMFU() const
{
	return isMFU;
}

OtherEquipment::OtherEquipment(const std::string& name_, const std::string& someInfo_)
: someInfo(someInfo_), ITequipment(name_)
{
}

OtherEquipment::OtherEquipment(std::pair<std::string, std::string>&& info) :
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
