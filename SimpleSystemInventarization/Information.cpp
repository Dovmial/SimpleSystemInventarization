
#include  "Information.hpp"

#include <string>
#include <iomanip>
#include <iostream>

void InfoPC::getInfoCLI() const {
	std::cout << std::setw(20) << "Motherboard: " << motherBoard;
	std::cout << std::setw(20) <<
		"\nCPU: " << _cpu.name << ' ' << _cpu.frequency << "GHz\n";
	std::cout << std::setw(20) <<
		"Graphic card: " << graphicCard.name << ", "
		<< graphicCard.videoRam << "GB\n";
	std::cout << std::setw(20) << "Ram: " << ram << "GB\n";
	std::cout << std::setw(20)
		<< "Storage device: " << storageDevice << " GB\n";
	std::cout << std::setw(20) << operSystem << '\n';
}
void InfoPC::setMotherBoard(const std::string& mb) {
	motherBoard = mb;
}
void InfoPC::setCPU(const std::string& name, float freq) {
	_cpu.name = name;
	_cpu.frequency = freq;
}

void InfoPC::setGraphicCard(const std::string& name, float videoRam = -1.) {
	graphicCard.name = name;
	graphicCard.videoRam = videoRam;
}
void InfoPC::setRAM(float ram) {
	this->ram = ram;
}

void InfoPC::setStorageDevice(float sdVolume) {
	storageDevice = sdVolume;
}

void InfoPC::setOperSystem(const std::string& operSystem) {
	this->operSystem = operSystem;
}

void InfoPrinter::getInfoCLI() {
	std::cout << cartridge;
}
void InfoPrinter::setCartridge(const std::string& cartridge) {
	this->cartridge = cartridge;
}


void InfoMonitor::getInfoCLI() {
	std::cout << screenDiagonal;
}
void InfoMonitor::setScreenDiagonal(float sDiagonal) {
	screenDiagonal = sDiagonal;
}

void InfoOtherDevice::getInfoCLI() {
	std::cout << someInfo;
}
void InfoOtherDevice::setSomeInfo(const std::string& someInfo) {
	this->someInfo = someInfo;
}