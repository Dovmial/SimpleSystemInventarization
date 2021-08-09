
#include <iostream>
#include "InterfaceManager.hpp"
#include "ITequipment.hpp"
 

int main() {
	InterfaceManager cli;
	cli.CLIshowHeader();
	std::cout << cli.CLIshowMenuRoom() << " - is choosen\n";
	return 0;
}