
#include "Item.hpp"
#include <iostream>
#include <iomanip>

void printItem(Item* item) {
	std::cout << "------" << item->getITequipment()->getName() << " --- #"
		<<item->getInventoryNumber()<<"--------- \n";
	
	std::cout << item->getITequipment()->getInfo() //polymorph function
		<< "--------------------------------" << "\n\n";

	auto [servInfoBegin, servInfoEnd] = item->getServiceInfoView();
	auto [probSolutionBegin, probSolutionEnd] =
		item->getProblemsSolutionsView();

	while (servInfoBegin != servInfoEnd) {
		std::cout << "--Service: " << (*servInfoBegin)->getDescription()
			<< "  ----  " << (*servInfoBegin)->getDate() << " --\n\n";
		++servInfoBegin;
	}

	while (probSolutionBegin != probSolutionEnd) {
		std::cout << "--Problem: " << (*probSolutionBegin)->getDescription()
			<<"\n--Solution: "<<(*probSolutionBegin)->getSolution()
			<< "\n----  " << (*probSolutionBegin)->getDate() << " --\n\n";
		++probSolutionBegin;
	}
}

void splitter() {
	std::cout << '\n';
	for (size_t i{}; i < 40; ++i) {
		std::cout << "Ü ";
	}
	std::cout << '\n';
	for (size_t i{}; i < 40; ++i) {
		std::cout << " ß";
	}
	std::cout << '\n';
}

void Application() {
	//description objects
	PC LenovoG580("Laptop lenovo G570");
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

	//show objects
	printItem(&pc307);
	splitter();
	printItem(&pc308);
	splitter();
	printItem(&printer307);
}

int main() {
	Application();
}