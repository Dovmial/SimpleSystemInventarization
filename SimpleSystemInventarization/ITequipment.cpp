#include "ITequipment.hpp"
#include <sstream>
#include <iomanip>



ITequipment::ITequipment(const std::string& name_): BaseObject(name_)
{
}

PC::PC(const std::string& name_): ITequipment(name_),
motherboard(""), _cpu("", 0.f), ram(0.f), 
storageDeviceVolume(0.f), graphicCard("", 0.f),
operationSystem("")
{
}
/*
PCinfo PC::getPCinfo() const
{
	return std::tuple(
		motherboard, _cpu, ram,
		storageDeviceVolume, graphicCard, operationSystem);
}
*/
std::string PC::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(20) << "Motherboard: " << motherboard << '\n';
	ssInfo << std::setw(20) << "CPU: "
		<< _cpu.first << " " << _cpu.second << " GHz\n";
	ssInfo << std::setw(20) << "RAM: " << ram << "GB\n";
	ssInfo << std::setw(20) << "Graphic card: "
		<< graphicCard.first << " " << graphicCard.second << " GB\n";
	ssInfo << std::setw(20) << "Storage device: "
		<< storageDeviceVolume << " GB\n";
	ssInfo << std::setw(20) << "Operation system: " << operationSystem<<'\n';
	return ssInfo.str();
}

void PC::setMotherboard(const std::string& mb)
{
	motherboard = mb;
}

void PC::setCPU(const std::string& nameCPU, float frequencyGHz)
{
	_cpu = std::pair(nameCPU, frequencyGHz);
}

void PC::setRAM(float ramGB)
{
	this->ram = ramGB;
}

void PC::setStorageDevVol(float volGB)
{
	storageDeviceVolume = volGB;
}

void PC::setGraphicCard(const std::string& nameGCard, float volGCard)
{
	graphicCard = std::pair(nameGCard, volGCard);
}

void PC::setOperationSystem(const std::string& opSys)
{
	operationSystem = opSys;
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
	ssInfo << std::setw(15) << "Diagonal: " << getDiagonal() << '\n';
	return ssInfo.str();
}

Printer::Printer(const std::string& name_, std::string cartridge_):
	cartridge(cartridge_), ITequipment(name_)
{
}

void Printer::setCartridge(const std::string& cartridge)
{
	this->cartridge = cartridge;
}

std::string Printer::getCartridge() const
{
	return cartridge;
}

std::string Printer::getInfo() const
{
	std::stringstream ssInfo;
	ssInfo << std::setw(15) << "Cartridge: " << getCartridge() << '\n';
	return ssInfo.str();
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
	return getSomeInfo() + '\n';
}
