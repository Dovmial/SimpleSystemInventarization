#pragma once
#include "BaseObject.hpp"
class Components : public BaseObject{
public:
	Components() = delete;
	Components(const std::string& name) : BaseObject(name) {
	}
};


class MotherBoard : public Components{
	MotherBoard() = delete;
	MotherBoard(const std::string& name) : Components(name) {
	}
};

class CPU: public Components {
	CPU() = delete;
	CPU(const std::string& name, float frequency_ = -1.f):
		frequency(frequency_),
		Components(name){}
	float getFrequency() const;
	void setFrequency() const;
private:
	float frequency;
};

class RAM : public Components{
public:
	RAM() = delete;
	RAM(const std::string& name = "", float volume_ = -1.f) :
		volume(volume_),
		Components(name) {}
	float getVolume() const;
	void setVolume(float volume_);
private:
	float volume;
};

class StorageDeveice : public Components {
public:
	enum typeStorageDevice {
		HDD = 1,
		SSD
	};
	StorageDeveice() = delete;
	StorageDeveice(
		float  volume,
		const std::string& name = "",
		typeStorageDevice tSD = HDD);
public:
	void setTypeStorDev(typeStorageDevice type);
	void setVolume(float volume_);
	typeStorageDevice getStorageDeviceType();
	float getVolume() const;

private:
	typeStorageDevice sdType;
	float volume;
};

class GraphicCard : public Components {
	GraphicCard() = delete;
	GraphicCard(
		const std::string& name,
		float volume = -1.f);
	float getVolume() const;
	void setVolume(float volume_);
private:
	float volume;
};

