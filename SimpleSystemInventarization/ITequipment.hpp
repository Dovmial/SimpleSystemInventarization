
#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <string>
#include <utility>
#include <tuple>
#include "BaseObject.hpp"
#include "Components.hpp"
#include "Iinfo.hpp"

class ITequipment: public BaseObject, public Iinfo{
public:
	ITequipment() = delete;
	ITequipment(const std::string& name_);
};

/*
using PCinfo = std::tuple<
	std::string,
	std::pair<std::string, float>,
	float, float,
	std::pair<std::string, float>,
	std::string
>;*/

using TypeStorDev = StorageDevice::typeStorageDevice;
class PC : public ITequipment {
public:
	enum TypePC {
		SystemBlock = 1,
		Laptop,
		Monoblock
	};

	PC() = delete;
	PC(const std::string &name_, TypePC typePC_);
	PC(std::tuple<std::string, TypePC> baseInfo);
	//PCinfo getPCinfo() const; //todo delete

	virtual std::string getInfo()const override;
	TypePC getTypePC() const;

public:
	void setMotherboard(const MotherBoard& mb);
	void setCPU(const CPU& _cpu);
	void setRAM(const RAM& ram);
	void setStorageDevice(const StorageDevice& sd);
	void setGraphicCard(const GraphicCard& GraphicCard);
	void setOperationSystem(const std::string& opSys);
public:
	void setTypePC(TypePC typePC_);
	TypePC getTypePC() const;
	std::string typePCtoStr() const;

private:
	TypePC typePC;
	MotherBoard motherboard;
	CPU _cpu;
	RAM ram;
	StorageDevice storageDevice;
	GraphicCard graphicCard;
	std::string operationSystem;
};

class Monitor :public ITequipment {
public:
	Monitor() = delete;
	Monitor(const std::string& name_, float diagonal_ = -1.f);
	Monitor(std::pair<std::string, float>&& info);
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
		Cartridge&& cartridge,
		bool isMFU_ = false
	);
	Printer(std::tuple<std::string, Cartridge, bool>&& info);
public:
	void setCartridge(Cartridge&& cartridge_);
	Cartridge getCartridge() const;
	virtual std::string getInfo()const override;
	void setIsMFU(bool isMFU_);
	bool getIsMFU() const;
private:
	Cartridge cartridge;
	bool isMFU; //add 3d printer
};

class OtherEquipment : public ITequipment {
public:
	OtherEquipment() = delete;
	OtherEquipment(const std::string& name_, const std::string& someInfo_ = "");
	OtherEquipment(std::pair<std::string, std::string>&& info_);

	void setSomeInfo(const std::string& someInfo_);
	std::string getSomeInfo() const;
	virtual std::string getInfo()const override;
private:
	std::string someInfo;
};
#endif