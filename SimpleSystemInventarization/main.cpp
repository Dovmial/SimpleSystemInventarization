#include "ITequipment.hpp"
#include <iostream>
#include <iomanip>
int main() {
	PC pc307("lenovo G570");
	pc307.setCPU("Intel i5 570", 2.7f);
	pc307.setOperationSystem("Win 7 sp1 pro");
	pc307.setRAM(16.f);
	pc307.setStorageDevVol(232.f);

	auto [mb, _cpu, ram, sd, gc, os] = pc307.getPCinfo();
	std::cout << "----------" << pc307.getName() << "----------------\n";
	std::cout << std::setw(20) << "Motherboard: " << mb << '\n';
	std::cout << std::setw(20) << "CPU: " << _cpu.first << " " << _cpu.second << " GHz\n";
	std::cout << std::setw(20) << "RAM: " << ram << "GB\n";
	std::cout << std::setw(20) << "Graphic card: " << gc.first << " " << gc.second << " GB\n";
	std::cout << std::setw(20) << "Storage device: " << sd << " GB\n";
	std::cout << std::setw(20) << "Operation system: " << os
		<< "\n--------------------------------" << "\n\n";
}