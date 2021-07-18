
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
	Application SSI(Laptop(compLaptop, 19, 4101340041));
	SSI.start();

	return 0;
}