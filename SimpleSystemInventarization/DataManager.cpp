#include "DataManager.hpp"
#include "ITequipmentFabric.hpp"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
	

}

/*
			PC LenovoG580("Laptop lenovo G580");
	LenovoG580.setCPU("Intel i5 570", 2.7f);
	LenovoG580.setOperationSystem("Win 7 sp1 pro");
	LenovoG580.setRAM(16.f);
	LenovoG580.setStorageDevVol(232.f);
	Printer mfuHP1132("MFU HP 1132", "CE285A");

	//real objects
	Item pc307(&LenovoG580, 110041931);
	pc307.addSignService("Clean", "15.12.2017");

	Item pc308(&LenovoG580, 110041930);
	pc308.addSignService("Fixing loops", "18.10.2015");
	pc308.addSignService("Clean", "02.05.2019");

	Item printer307(&mfuHP1132, 5101340087);
	printer307.addSignProblemsSolutions(
		"Broken cartridge", "23.02.2020", "new cartridge");
			*/
std::shared_ptr<ITequipment>
DataManager::createITequipment(std::string_view name, typeITEquipment typeITE)
{
	switch (typeITE) {
	case typeITEquipment::typePC:
	{
		//get parameters for constructtion
		PCfabric pcFabric;
		return move(pcFabric.create());//диалоговое окно с вводом характеристик)
	}
	case typeITEquipment::typeMonitor:
	{
		MonitorFabric monitorFabric;
		return move(monitorFabric.create());
	}
	}
}

std::unique_ptr<Item> 
DataManager::createItem(
	std::shared_ptr<ITequipment> equipment_, int64_t inventoryNumber_
)
{

	return std::unique_ptr<Item>();
}

std::unique_ptr<Item> DataManager::createNewItem(
	std::string_view name_, typeITEquipment type, int64_t inventoryNumber_
)
{
	createITequipment(name_, type);
	return std::unique_ptr<Item>();
}

