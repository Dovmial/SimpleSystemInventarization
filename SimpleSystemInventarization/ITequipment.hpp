
#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <string>
#include <utility>
#include <tuple>
class ITequipment {
public:
	ITequipment() = delete;
	ITequipment(std::string name_);
	void setName(std::string name_);
	std::string getName() const;
protected:
	std::string name;
};

using PCinfo = std::tuple<
	std::string,
	std::pair<std::string, float>,
	float, float,
	std::pair<std::string, float>,
	std::string>;

class PC : public ITequipment {
public:

	PC() = delete;
	PC(std::string name_);

	PCinfo getPCinfo() const;

	void setMotherboard(std::string mb);
	void setCPU(std::string nameCPU, float frequencyGHz);
	void setRAM(float ramGB);
	void setStorageDevVol(float vol);
	void setGraphicCard(std::string nameGCard, float volGCard);
	void setOperationSystem(std::string opSys);

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
	void setDiagonal(float diagonal);
	float getDiagonal() const;
private:
	float diagonal;
};

class Printer :public ITequipment {
public:
	void setCartridge(std::string cartridge);
	std::string getCartridge() const;
private:
	std::string cartridge;
};

class OtherEquipment : public ITequipment {
public:
	void setSomeInfo(std::string someInfo_);
	std::string getSomeInfo() const;
private:
	std::string someInfo;
};
#endif