#ifndef _MANAGERAPP_HPP_
#define _MANAGERAPP_HPP_

#include "Interfaces.hpp"
#include "Build.hpp"
#include "Menu.hpp"
#include <map>
class ManagerApp {//: public BaseInterface{
public:

	//bool synñhronization();
	bool load();
	bool save();
	
private:
	std::map < std::string, Build*> builds;
};
#endif