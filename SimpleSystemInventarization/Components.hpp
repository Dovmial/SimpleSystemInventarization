#pragma once
#include "BaseObject.hpp"
#include "Iinfo.hpp"


class Components : public BaseObject, public Iinfo{
public:
	Components() = delete;
	Components(const std::string& name);
};


class  MotherBoard : public Components{
public:
	MotherBoard() = delete;
	MotherBoard(const std::string& name);
	virtual std::string getInfo() const override;
};

class  CPU: public Components {
public:
	CPU() = delete;
	CPU(const std::string& name, float frequency_ = -1.f);
	float getFrequency() const;
	void setFrequency(float frequency_);
	virtual std::string getInfo() const override;
private:
	float frequency;
};

class  RAM : public Components{
public:
	RAM() = delete;
	RAM(float volume_, const std::string& name = "");
	float getVolume() const;
	void setVolume(float volume_);
	virtual std::string getInfo() const override;
private:
	float volume;
};

class StorageDevice : public Components {
public:
	enum class typeStorageDevice {
		HDD = 1,
		SSD
	};
	StorageDevice() = delete;
	StorageDevice(
		float  volume_,
		const std::string& name = "",
		typeStorageDevice tSD = typeStorageDevice::HDD);
	StorageDevice(std::tuple <
		float,
		const std::string,
		typeStorageDevice> data);
	virtual std::string getInfo() const override;
	
public:
	void setTypeStorDev(typeStorageDevice type);
	void setVolume(float volume_);
	typeStorageDevice getStorageDeviceType();
	float getVolume() const;

private:
	typeStorageDevice sdType;
	float volume;
};

class  GraphicCard : public Components {
public:
	GraphicCard() = delete;
	GraphicCard(
		const std::string& name,
		float volume = -1.f);
	float getVolume() const;
	void setVolume(float volume_);
	virtual std::string getInfo() const override;
private:
	float volume;
};

class  Cartridge : public Components {
public:
	Cartridge() = delete;
	Cartridge(const std::string& name);
	virtual std::string getInfo() const override;
	//add counter reloaded
};

