#include "Components.hpp"

Components::Components(const std::string& name): BaseObject(name)
{
}

MotherBoard::MotherBoard(const std::string& name) : Components(name)
{
}

std::string MotherBoard::getInfo() const
{
	return std::string("MotherBoard: " + name + '\n');
}

CPU::CPU(const std::string& name, float frequency_) :
	frequency(frequency_),
	Components(name)
{
}

float CPU::getFrequency() const
{
	return frequency;
}

void CPU::setFrequency(float frequency_)
{
	frequency = frequency_;
}

std::string CPU::getInfo() const
{
	return std::string("CPU: " + name + " "
		+ std::to_string(frequency) + " GHz\n");
}

RAM::RAM(float volume_, const std::string& name) :
	volume(volume_),
	Components(name)
{}

float RAM::getVolume() const
{
	return volume;
}

void RAM::setVolume(float volume_)
{
	volume = volume_;
}

std::string RAM::getInfo() const
{
	return std::string("RAM: " + (!name.empty()?(name+" ") : "") 
		+ std::to_string(volume) + " GB\n");
}

StorageDevice::StorageDevice(
	float volume_,
	const std::string& name,
	typeStorageDevice tSD
): volume(volume_), sdType(tSD), Components(name)
{
}

StorageDevice::StorageDevice(
	std::tuple<float, const std::string, size_t> data):
	volume(std::get<0>(data)),
	sdType(static_cast<StorageDevice::typeStorageDevice>(std::get<2>(data))),
	Components(std::get<1>(data))
{
	
}

std::string StorageDevice::getInfo() const
{
	return std::string("Storage device: " + (!name.empty() ? (name + " ") : "")
		+ std::to_string(volume) + " GB\n");
}

void StorageDevice::setTypeStorDev(typeStorageDevice type)
{
	sdType = type;
}

void StorageDevice::setVolume(float volume_)
{
	volume = volume_;
}

StorageDevice::typeStorageDevice StorageDevice::getStorageDeviceType()
{
	return sdType;
}

float StorageDevice::getVolume() const
{
	return volume;
}

GraphicCard::GraphicCard(const std::string& name, float volume_):
	volume(volume_), Components(name)
{
}

float GraphicCard::getVolume() const
{
	return volume;
}

void GraphicCard::setVolume(float volume_)
{
	volume = volume_;
}

std::string GraphicCard::getInfo() const
{
	return std::string("Graphic card: " + name + " "
		+ std::to_string(volume) + " GB\n");
}

Cartridge::Cartridge(const std::string& name): Components(name)
{
}

std::string Cartridge::getInfo() const
{
	return std::string("Cartridge: " + name + '\n');
}
