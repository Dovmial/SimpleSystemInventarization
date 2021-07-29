#include "Components.hpp"

BaseComponent::BaseComponent(const std::string& name_)
	: name(name_) {}
std::string BaseComponent::getName() const noexcept
{
	return name;
}

void BaseComponent::setName(const std::string& name) noexcept
{
	this->name = name;
}

//CPU
CPU::CPU(float frequency_, std::string name_) :
	BaseComponent(name_),
	frequency(frequency_)
{};

float CPU::getFrequency()const noexcept
{
	return frequency;
}
void CPU::setFrequency(const float& frequency) noexcept
{
	this->frequency = frequency;
}

//Motherboard

Motherboard::Motherboard(std::string name_) :
	BaseComponent(name_) {}

// GrahiphicCard
GrahiphicCard::GrahiphicCard(float videoRam_, std::string name_) :
	videoRam(videoRam_),
	BaseComponent(name_)
{};

float  GrahiphicCard::getVideoRam()const noexcept
{
	return videoRam;
}
void  GrahiphicCard::setVideoRam(const float& videoRam) noexcept
{
	this->videoRam = videoRam;
}

//RAM
RAM::RAM(float valueRam_, std::string name_) :
	BaseComponent(name_),
	valueRam(valueRam_)
{};

float RAM::getValueRam()const noexcept
{
	return valueRam;
}
void RAM::setValueRam(const float& valueRam) noexcept
{
	this->valueRam = valueRam;
}

//StorageDevice

StorageDevice::StorageDevice(float valueVolume_, std::string name_) :
	BaseComponent(name_),
	valueVolume(valueVolume_)
{};

float StorageDevice::getVolume()const noexcept
{
	return valueVolume;
}
void StorageDevice::setVolume(const float& volume) noexcept
{
	this->valueVolume = volume;
}

Cartridge::Cartridge(int countRefilling_, int id_,std::string name_) :
BaseComponent(name_), countRefilling(countRefilling_), id(id_) {}

int Cartridge::getCountRefilling() const noexcept
{
	return countRefilling;
}

int Cartridge::getIdCartridge() const noexcept
{
	return id;
}

void Cartridge::setContRefilling(int countRefilling) noexcept
{
	this->countRefilling = countRefilling;
}

void Cartridge::setIdCartridge(int id) noexcept
{
	this->id = id;
}
