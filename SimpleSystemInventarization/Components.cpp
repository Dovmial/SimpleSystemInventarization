#include "Components.hpp"

BaseComponent::BaseComponent(const std::string& description)
	: description(description) {}
std::string BaseComponent::getDescription() const noexcept
{
	return description;
}

void BaseComponent::setDescription(const std::string& description) noexcept
{
	this->description = description;
}

//CPU
CPU::CPU(float frequency_, std::string description_) :
	BaseComponent(description_),
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

Motherboard::Motherboard(std::string descripton) :
	BaseComponent(descripton) {}

// GrahiphicCard
GrahiphicCard::GrahiphicCard(float videoRam_, std::string description_) :
	BaseComponent(description_),
	videoRam(videoRam_)
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


RAM::RAM(float valueRam_, std::string description_) :
	BaseComponent(description_),
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

StorageDevice::StorageDevice(float valueVolume_, std::string description_) :
	BaseComponent(description_),
	valueVolume(valueVolume_)
{};

float StorageDevice::getFrequency()const noexcept
{
	return valueVolume;
}
void StorageDevice::setFrequency(const float& valueRam) noexcept
{
	this->valueVolume = valueRam;
}
