
#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <string>
#include <utility>
#include <tuple>
#include "BaseObject.hpp"
#include "Components.hpp"
#include "Iinfo.hpp"
#include "IinfoType.hpp"
#include <memory>
#include "ISerialize.hpp"

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

class DECLSPEC ITequipment: public BaseObject, public Iinfo, public IInfoType, public ISerialize {
public:
	ITequipment() = delete;
	ITequipment(const std::string& name_);
};

/*using PCinfo = std::tuple<
	std::string,
	std::pair<std::string, float>,
	float, float,
	std::pair<std::string, float>,
	std::string
>;*/

using  ComplectComponents = std::tuple
<MotherBoard, CPU, GraphicCard, RAM, StorageDevice, std::string>;

class  DECLSPEC  PC : public ITequipment {
public:
	//TODO: class laptop, monoblock with diagonal
	enum class TypePC {
		SystemBlock = 1,
		Laptop,
		Monoblock
	};


	PC() = delete;
	//PC(const std::string &name_, TypePC typePC_);
	PC(const std::string& name_, TypePC baseInfo,
		std::shared_ptr<ComplectComponents> complect);

	virtual std::string getInfo()const override;
	virtual typeDevice getType() const override;
	virtual XMLElement* serialize(XMLDocument& xmlDoc) const override;
public:
	auto getComplectComponents() const->std::shared_ptr<ComplectComponents>;
	void setComplectComponents(std::shared_ptr<ComplectComponents> complect);
	void setMotherboard(const MotherBoard& mb);
	void setCPU(const CPU& _cpu);
	void setRAM(const RAM& ram);
	void setStorageDevice(const StorageDevice& sd);
	void setGraphicCard(const GraphicCard& GraphicCard);
	void setOperationSystem(const std::string& opSys);
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
class  DECLSPEC  Monitor :public ITequipment {
public:
	Monitor() = delete;
	Monitor(const std::string& name_, float diagonal_ = -1.f);
	Monitor(std::pair<const std::string, float>&& info);
	void setDiagonal(float diagonal);
	float getDiagonal() const;
	virtual std::string getInfo()const override;
	virtual typeDevice getType()const override;
	virtual XMLElement* serialize(XMLDocument& xmlDoc) const override;
private:
	float diagonal;
};

class DECLSPEC  Printer :public ITequipment {
public:
	enum class PrinterType {
		PRINTER = 1,
		MFU,
		PRINTER3D
	};
	Printer() = delete;
	Printer(const std::string& name_,
		Cartridge&& cartridge,
		PrinterType type);
	Printer(const std::tuple<std::string, Cartridge, PrinterType>& info);
public:
	void setCartridge(Cartridge&& cartridge_);
	Cartridge getCartridge() const;
	std::string printerTypeToStr() const;
	PrinterType getPrinterType() const;
	virtual std::string getInfo()const override;
	virtual typeDevice getType()const override;
	virtual XMLElement* serialize(XMLDocument& xmlDoc)const override;
private:
	Cartridge cartridge;
	PrinterType type;
};

class  DECLSPEC  OtherEquipment : public ITequipment {
public:
	OtherEquipment() = delete;
	OtherEquipment(const std::string& name_, const std::string& someInfo_ = "");
	OtherEquipment(const std::pair<const std::string, std::string>& info_);

	void setSomeInfo(const std::string& someInfo_);
	std::string getSomeInfo() const;
	virtual std::string getInfo()const override;
	virtual typeDevice getType()const override;
	virtual XMLElement* serialize(XMLDocument& xmlDoc) const override;
private:
	std::string someInfo;
};
#endif