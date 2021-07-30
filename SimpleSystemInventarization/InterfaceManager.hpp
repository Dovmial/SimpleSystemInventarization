#ifndef _INTERFACE_MANAGER_HPP_
#define _INTERFACE_MANAGER_HPP_

#include "Menu.hpp"
#include <iostream>

class InterfaceManager {
public:
	//cli

	void CLIshowHeader() {
		std::cout << "\n\t\tSOME APP HEADER\n\n";
	}
	int CLIshowMenuRoom() {
		return cli.RoomMenu();
	}
private:
	Menu cli;
	//gui
};
#endif // !_INTERFACE_MANAGER_HPP_

