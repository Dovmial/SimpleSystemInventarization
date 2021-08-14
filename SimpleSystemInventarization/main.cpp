
#include "Item.hpp"
#include <iostream>
#include <iomanip>

void printItem(Item* item) {
	auto pc = reinterpret_cast<PC*>(item->getITequipment());
	auto [mb, _cpu, ram, sd, gc, os] = pc->getPCinfo();
	std::cout << "------" << pc->getName() << " --- #"
		<<item->getInventoryNumber()<<"--------- \n";
	std::cout << std::setw(20) << "Motherboard: " << mb << '\n';
	std::cout << std::setw(20) << "CPU: " << _cpu.first << " " << _cpu.second << " GHz\n";
	std::cout << std::setw(20) << "RAM: " << ram << "GB\n";
	std::cout << std::setw(20) << "Graphic card: " << gc.first << " " << gc.second << " GB\n";
	std::cout << std::setw(20) << "Storage device: " << sd << " GB\n";
	std::cout << std::setw(20) << "Operation system: " << os
		<< "\n--------------------------------" << "\n\n";
	
	auto [servInfoBegin, servInfoEnd] = item->getServiceInfoView();
	
	while (servInfoBegin != servInfoEnd) {
		std::cout << "--Service: " << (*servInfoBegin)->getDescription()
			<< "  ----  " << (*servInfoBegin)->getDate() << " --\n\n";
		++servInfoBegin;
	}
}

void splitter() {
	std::cout << '\n';
	for (size_t i{}; i < 40; ++i) {
		std::cout<<"Ü ";
	}
	std::cout << '\n';
	for (size_t i{}; i < 40; ++i) {
		std::cout << " ß";
	}
	std::cout << '\n';
}
int main() {
	PC LenovoG580("Laptop lenovo G570");
	LenovoG580.setCPU("Intel i5 570", 2.7f);
	LenovoG580.setOperationSystem("Win 7 sp1 pro");
	LenovoG580.setRAM(16.f);
	LenovoG580.setStorageDevVol(232.f);

	Item pc_307(&LenovoG580, 110041931);
	pc_307.addSignService("Clean", "15.12.2017");


	Item pc_308(&LenovoG580, 110041930);
	pc_308.addSignService("Fixing loops", "18.10.2015");
	pc_308.addSignService("Clean", "02.05.2019");
	printItem(&pc_307);
	splitter();
	printItem(&pc_308);
}