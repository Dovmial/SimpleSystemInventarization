#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include <string>

class BaseComponent {
public:
	BaseComponent() = delete;
	BaseComponent(const std::string& description = "") ;

	virtual std::string getDescription()const noexcept;
	void setDescription(const std::string& description) noexcept;
private:
	std::string description;
};

class CPU: public BaseComponent{
public:
	CPU() = delete;
	CPU(float frequency_, std::string description_ = "");

	float getFrequency()const noexcept;
	void setFrequency(const float& frequency) noexcept;
protected:
	float frequency; //частота GHz
};

class Motherboard: public BaseComponent {
public:
	Motherboard() = delete;
	Motherboard(std::string descripton = "");
};

class GrahiphicCard: public BaseComponent {
public:
	GrahiphicCard() = delete;
	GrahiphicCard(float videoRam_, std::string description_ = "");

	float getVideoRam()const noexcept;
	void setVideoRam(const float& videoRam) noexcept;
private:
	float videoRam;
};

class RAM: public BaseComponent {
public:
	RAM() = delete;
	RAM(float valueRam_, std::string description_ = "");

	float getValueRam()const noexcept;
	void setValueRam(const float& valueRam) noexcept;
private:
	float valueRam;
};

class StorageDevice: BaseComponent {
public:
	StorageDevice() = delete;
	StorageDevice(float valueVolume_, std::string description_ = "");

		float getFrequency()const noexcept;
		void setFrequency(const float& valueRam) noexcept;
private:
	float valueVolume;
};

#endif