#include "ITequipment.hpp"

ITequipment::ITequipment(int64_t inventarNumber_) :
	inventarNumber(inventarNumber_) {}

int64_t ITequipment::getInventarNumber() const noexcept {
	return inventarNumber;
}
void ITequipment::setInventarNumber() noexcept {
	this->inventarNumber = inventarNumber;
}

PC::PC(Components components_, int64_t inentarNumber) :
	components(components_), ITequipment(inentarNumber)
{}

Monitor::Monitor(float screenDiagonal_, int64_t inventarNumber_) :
	screenDiagonal(screenDiagonal_),
	ITequipment(inventarNumber_)
{}

Laptop::Laptop(Components components_,
	float screenDiagonal_,
	int64_t inventarNumber_) :

	PC(components_, inventarNumber_),
	Monitor(screenDiagonal_)
{}

void Laptop::show() noexcept {
	std::cout << "\n\nLaptop\n";
	for (const auto& comp : components) {
		std::cout << comp->getName() << std::endl;
	}
	
	std::cout << "Screen diagonal: " << screenDiagonal << "\"\n";
	std::cout << "Inventar number: " << PC::getInventarNumber() << '\n';
}

Printer::Printer(Cartridge* cartridge_, int64_t inventarNumber) :
	cartridge(cartridge_),
	ITequipment(inventarNumber)
{}

Cartridge* Printer::getCartridge() const {
	return cartridge;
}

void Printer::setCartridge(Cartridge* cartridge) {
	this->cartridge = cartridge;
}
