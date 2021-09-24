#include "Menu.hpp"
#include <sstream>
#include <iostream>
#include <string_view>

int Menu::menuChoiceTypeCreator()
{
	std::stringstream menu;
	menu << "\t1 - PC\n"
		<< "\t2 - Monitor\n"
		<< "\t3 - Printer\n"
		<< "\t4 - Other\n"
		<< "\t0 - exit\n"
		<< "Enter type of equipment: ";
	return getChoiceMenu(menu.str());
}

std::string Menu::getString(std::string_view request)
{
	std::cout << request;
	std::string str;
	std::getline(std::cin, str);
	return str;
}

float Menu::getNumberF(std::string_view request)
{
	std::cout << request;
	float number;
	std::cin >> number;
	return number;
}

int Menu::getChoiceMenu(std::string_view menu)
{
	std::cout << menu;
	int choice;
	//TODO: add checks
	std::cin >> choice;
	return choice;
}