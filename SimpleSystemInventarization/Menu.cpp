#include "Menu.hpp"
#include <iostream>

enum ActionRoom {

	EXIT,
	ADD,
	LOAD,
	SAVE,
	SHOW,
	EDIT,
	FIND,
	BACK,
	NEXT
};
int Menu::RoomMenu()
{
	int answear{};
	std::cout << "\t1 - Add new room\n"
		<< "\t2 - load room\n"
		<< "\t3 - save room\n"
		<< "\t4 - show info about room\n"
		<< "\t5 - edit room\n"
		<< "\t6 - find room\n"
	//	<< "\t7 - back to buildings\n"
		<< "\t0 - Exit.\n\t>>> ";
	std::cin >> answear;
	switch (answear) {
	case ActionRoom::LOAD:
		break;
	case ActionRoom::SAVE:
		break;
	case ActionRoom::SHOW:
		break;
	case ActionRoom::EDIT:
		break;
	case ActionRoom::ADD:
		break;
	case ActionRoom::EXIT:
		exit(0);
		break;
	default:
		break;
	}
	return answear;
}
