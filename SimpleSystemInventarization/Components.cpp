#include "Components.hpp"
#include <sstream>
#include <iomanip>

Components::Components(const std::string& name): BaseObject(name)
{
}

MotherBoard::MotherBoard(const std::string& name) : Components(name)
{
}

std::string MotherBoard::getInfo() const
{
	std::stringstream sstr;
	sstr << std::setw(18) << "MotherBoard: " << name << '\n';
	return sstr.str();
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
	std::stringstream ss;
	ss << std::setw(18) << "CPU: " << name << ' ';
	ss << std::fixed << std::setprecision(2) << frequency<<"GHz\n";
	return ss.str();
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
	std::stringstream ss;
	ss << std::setw(18) << "RAM: " << (!name.empty() ? (name + " ") : "");
	ss << std::fixed << std::setprecision(0) << volume << " GB\n";
	return ss.str();
}

StorageDevice::StorageDevice(
	float volume_,
	const std::string& name,
	typeStorageDevice tSD
): volume(volume_), sdType(tSD), Components(name)
{
}

StorageDevice::StorageDevice(
	std::tuple<float, const std::string, typeStorageDevice> data):
	volume(std::get<0>(data)),
	sdType(static_cast<StorageDevice::typeStorageDevice>(std::get<2>(data))),
	Components(std::get<1>(data))
{
	
}

std::string StorageDevice::getInfo() const
{
	std::stringstream ss;
	ss << std::setw(16) << getStorageDeviceTypeStr() << ": "
		<< (!name.empty() ? (name + " ") : "");
	ss << std::fixed << std::setprecision(0) << volume << " GB\n";
	return ss.str();
}

void StorageDevice::setTypeStorDev(typeStorageDevice type)
{
	sdType = type;
}

void StorageDevice::setVolume(float volume_)
{
	volume = volume_;
}

StorageDevice::typeStorageDevice StorageDevice::getStorageDeviceType() const
{
	return sdType;
}

std::string StorageDevice::getStorageDeviceTypeStr() const
{
	switch (sdType)
	{
	case typeStorageDevice::HDD:
		return std::string("HDD");
	case typeStorageDevice::SSD:
		return std::string("SSD");
	}
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
	std::stringstream ss;
	ss << std::setw(18) << "Graphic card: " << name << ' ';
	ss << std::fixed << std::setprecision(0) << volume << " GB\n";
	return ss.str();
}

Cartridge::Cartridge(const std::string& name): Components(name)
{
}

std::string Cartridge::getInfo() const
{
	return std::string("Cartridge: " + name + '\n');
}
