#ifndef __COMPONENTS__HPP__
#define __COMPONENTS__HPP__
#include "BaseObject.hpp"
#include "Iinfo.hpp"

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

class DECLSPEC Components : public BaseObject, public Iinfo{
public:
	Components() = delete;
	Components(const std::string& name);
};


class DECLSPEC MotherBoard : public Components{
public:
	MotherBoard() = delete;
	MotherBoard(const std::string& name);
	virtual std::string getInfo() const override;
};

class DECLSPEC CPU: public Components {
public:
	CPU() = delete;
	CPU(const std::string& name, float frequency_ = -1.f);
	float getFrequency() const;
	void setFrequency(float frequency_);
	virtual std::string getInfo() const override;
private:
	float frequency;
};

class DECLSPEC RAM : public Components{
public:
	RAM() = delete;
	RAM(float volume_, const std::string& name = "");
	float getVolume() const;
	void setVolume(float volume_);
	virtual std::string getInfo() const override;
private:
	float volume;
};

class DECLSPEC StorageDevice : public Components {
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
	typeStorageDevice getStorageDeviceType() const;
	std::string getStorageDeviceTypeStr() const;
	float getVolume() const;

private:
	typeStorageDevice sdType;
	float volume;
};

class DECLSPEC GraphicCard : public Components {
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

class DECLSPEC Cartridge : public Components {
public:
	Cartridge() = delete;
	Cartridge(const std::string& name);
	virtual std::string getInfo() const override;
	//add counter reloaded
};
#endif