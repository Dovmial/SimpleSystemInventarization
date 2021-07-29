#include "ITequipment.hpp"

ITequipment::ITequipment(int64_t inventarNumber_) :
	inventarNumber(inventarNumber_) {}

int64_t ITequipment::getInventarNumber() const noexcept {
	return inventarNumber;
}
void ITequipment::setInventarNumber() noexcept {
	this->inventarNumber = inventarNumber;
}

PC::PC(Components* components_, int64_t inentarNumber) :
	components(components_), ITequipment(inentarNumber)
{}

Monitor::Monitor(float screenDiagonal_, int64_t inventarNumber_) :
	screenDiagonal(screenDiagonal_),
	ITequipment(inventarNumber_)
{}

Laptop::Laptop(Components* components_,
	float screenDiagonal_,
	int64_t inventarNumber_) :

	PC(components_, inventarNumber_),
	Monitor(screenDiagonal_)
{}

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


void Printer::show() const noexcept{
	std::cout << "\n\nPrinter\n"
		<< "\tcartridge: " << getCartridge()->getName() << '\n'
		<< "\tid: " << getCartridge()->getIdCartridge() << '\n'
		<< "\tcount refilling: " << getCartridge()->getCountRefilling() << '\n'
		<< "\tinvertar number: " << getInventarNumber() << '\n';
}