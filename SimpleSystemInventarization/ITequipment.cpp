#include "ITequipment.hpp"

PC::PC(std::string name_): ITequipment(name_),
motherboard(""), _cpu("", 0.f), ram(0.f), 
storageDeviceVolume(0.f), graphicCard("", 0.f),
operationSystem("")
{
}

PCinfo PC::getPCinfo() const
{
	return std::make_tuple(
		motherboard, _cpu, ram,
		storageDeviceVolume, graphicCard, operationSystem);
}

void PC::setMotherboard(std::string mb)
{
	motherboard = mb;
}

void PC::setCPU(std::string nameCPU, float frequencyGHz)
{
	_cpu = std::make_pair(nameCPU, frequencyGHz);
}

void PC::setRAM(float ramGB)
{
	this->ram = ramGB;
}

void PC::setStorageDevVol(float volGB)
{
	storageDeviceVolume = volGB;
}

void PC::setGraphicCard(std::string nameGCard, float volGCard)
{
	graphicCard = std::make_pair(nameGCard, volGCard);
}

void PC::setOperationSystem(std::string opSys)
{
	operationSystem = opSys;
}

ITequipment::ITequipment(std::string name_): name(name_)
{
}

void ITequipment::setName(std::string name_)
{
	name = name_;
}

std::string ITequipment::getName() const
{
	return name;
}

void Monitor::setDiagonal(float diagonal)
{
	this->diagonal = diagonal;
}

float Monitor::getDiagonal() const
{
	return diagonal;
}

void Printer::setCartridge(std::string cartridge)
{
	this->cartridge = cartridge;
}

std::string Printer::getCartridge() const
{
	return cartridge;
}

void OtherEquipment::setSomeInfo(std::string someInfo)
{
	this->someInfo = someInfo;
}

std::string OtherEquipment::getSomeInfo() const
{
	return someInfo;
}
