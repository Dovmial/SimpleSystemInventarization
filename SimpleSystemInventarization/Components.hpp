#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include <string>

class BaseComponent {
public:
	BaseComponent() = delete;
	BaseComponent(const std::string& name = "");

	std::string getName()const noexcept;
	void setName(const std::string& name) noexcept;
private:
	std::string name;
};

class CPU : public BaseComponent {
public:
	CPU() = delete;
	CPU(float frequency_, std::string name_ = "");

	float getFrequency()const noexcept;
	void setFrequency(const float& frequency) noexcept;
protected:
	float frequency; //частота GHz
};

class Motherboard : public BaseComponent {
public:
	Motherboard() = delete;
	Motherboard(std::string descripton = "");
};

class GrahiphicCard : public BaseComponent {
public:
	GrahiphicCard() = delete;
	GrahiphicCard(float videoRam_, std::string name_ = "");
	float getVideoRam()const noexcept;
	void setVideoRam(const float& videoRam) noexcept;
	bool isExist();
private:
	float videoRam;
};

class RAM : public BaseComponent {
public:
	RAM() = delete;
	RAM(float valueRam_, std::string name_ = "");

	float getValueRam()const noexcept;
	void setValueRam(const float& valueRam) noexcept;
private:
	float valueRam;
};

class StorageDevice : BaseComponent {
public:
	StorageDevice() = delete;
	StorageDevice(float valueVolume_, std::string name_ = "");

	float getVolume()const noexcept;
	void setVolume(const float& volume) noexcept;
private:
	float valueVolume;
};

class Cartridge : public BaseComponent {
public:
	Cartridge() = delete;
	Cartridge(int countRefilling_, int id_ = -1, std::string name_ = "");

	int getCountRefilling() const noexcept;
	int getIdCartridge()const noexcept;
	void setContRefilling(int countRefilling) noexcept;
	void setIdCartridge(int id) noexcept;

private:
	int countRefilling; //количество заправок
	int id;
};
#endif