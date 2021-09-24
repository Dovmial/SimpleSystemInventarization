
#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <string>
#include <utility>
//#include <tuple>
#include "BaseObject.hpp"

class ITequipment: public BaseObject {
public:
	ITequipment() = delete;
	ITequipment(const std::string& name_);
	virtual std::string getInfo()const = 0;
};

/*
using PCinfo = std::tuple<
	std::string,
	std::pair<std::string, float>,
	float, float,
	std::pair<std::string, float>,
	std::string
>;*/

class PC : public ITequipment {
public:

	PC() = delete;
	PC(const std::string& name_);

	//PCinfo getPCinfo() const; //todo delete
	virtual std::string getInfo()const override;
	void setMotherboard(const std::string& mb);
	void setCPU(const std::string& nameCPU, float frequencyGHz);
	void setRAM(float ramGB);
	void setStorageDevVol(float vol);
	void setGraphicCard(const std::string& nameGCard, float volGCard);
	void setOperationSystem(const std::string& opSys);

private:
	std::string motherboard;
	std::pair<std::string, float> _cpu;
	float ram;
	float storageDeviceVolume;
	std::pair<std::string, float> graphicCard;
	std::string operationSystem;
};

class Monitor :public ITequipment {
public:
	Monitor() = delete;
	Monitor(const std::string& name_, float diagonal_ = -1.f);
	void setDiagonal(float diagonal);
	float getDiagonal() const;
	virtual std::string getInfo()const override;
private:
	float diagonal;
};

class Printer :public ITequipment {
public:
	Printer() = delete;
	Printer(const std::string& name_,
		const std::string& cartridge = "",
		bool isMFU_ = false
	);
	void setCartridge(const std::string& cartridge);
	std::string getCartridge() const;
	virtual std::string getInfo()const override;
	void setIsMFU(bool isMFU_);
	bool getIsMFU() const;
private:
	std::string cartridge;
	bool isMFU;
};

class OtherEquipment : public ITequipment {
public:
	OtherEquipment() = delete;
	OtherEquipment(const std::string& name_);
	void setSomeInfo(const std::string& someInfo_);
	std::string getSomeInfo() const;
	virtual std::string getInfo()const override;
private:
	std::string someInfo;
};
#endif