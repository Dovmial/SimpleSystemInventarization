
#include <iostream>
#include "ITequipment.hpp"
 
class Application
{
public:
	Application(Laptop laptop_) : laptop(laptop_) {}
	void start() {
		laptop.show();
	}
private:
	Laptop laptop;
};
int main() {
	
	CPU cpuLaptop(2.4f, "2.4 GHz");
	RAM ramLaptop(16.f, "16 GB");
	Components compLaptop = { &cpuLaptop, &ramLaptop };
	Application SSI(Laptop(compLaptop, 19));
	SSI.start();

	Cartridge cartridge(10, 308, "TK-1140");
	Printer printer(&cartridge, 4101345892);
	std::cout << "\n\nPrinter\n"
		<< "\tcartridge: " << printer.getCartridge()->getName()<<'\n'
		<< "\tid: " << printer.getCartridge()->getIdCartridge() << '\n'
		<< "\tcount refilling: " << printer.getCartridge()->getCountRefilling() << '\n'
		<<"\tinvertar number: "<< printer.getInventarNumber()<< '\n';
	return 0;
}