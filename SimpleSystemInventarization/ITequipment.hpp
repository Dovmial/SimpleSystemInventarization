#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <vector>
#include <iostream>
#include <string>
#include "Information.hpp"

class ITequipment {
public:
	virtual void showInfo() = 0;
	void setName(const std::string& name);
	virtual void setInfo(Info* info) = 0;
protected:
	std::string name;
};

class PC : public ITequipment {
public:
	virtual void setInfo(InfoPC* info) {
		this->info = info;
	}
private:
	InfoPC* info;
};

class Monitor : public ITequipment {
public:

private:
	InfoMonitor* infoMonitor;
};

class Printer : public ITequipment {
public:

private:
	InfoPrinter* infoPrinter;
};

class OtherDevice : public ITequipment {
public:
private:
	InfoOtherDevice* infoOtherDevice;
};
#endif // !_ITEQUIPMENT_HPP_