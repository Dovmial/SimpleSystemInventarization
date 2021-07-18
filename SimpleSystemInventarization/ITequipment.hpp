#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <vector>
#include <iostream>
#include "Components.hpp"

class ITequipment {
public:
	ITequipment() = delete;
	ITequipment(int64_t inventarNumber_) :
		inventarNumber(inventarNumber_) {}

	int64_t getInventarNumber() const noexcept {
		return inventarNumber;
	}
	void setInventarNumber() noexcept {
		this->inventarNumber = inventarNumber;
	}

protected:
	int64_t inventarNumber;
};

using Components = std::vector<BaseComponent*>;

class PC : public ITequipment {
public:
	PC() = delete;
	PC(Components components_, int64_t inentarNumber = -1) :
		components(components_), ITequipment(inentarNumber)
	{}
protected:
	Components components;
};

class Monitor : public ITequipment {
public:
	Monitor() = delete;
	Monitor(float screenDiagonal_, int64_t inventarNumber_ = -1) :
		screenDiagonal(screenDiagonal_),
		ITequipment(inventarNumber_)
	{}
protected:
	float screenDiagonal;
};

class Laptop : virtual public PC, virtual public Monitor {
public:
	Laptop() = delete;
	Laptop(Components components_, float screenDiagonal_, int64_t inventarNumber_) :
		PC(components_, inventarNumber_),
		Monitor(screenDiagonal_)
	{}
	void show() noexcept {
		for (const auto& comp : components) {
			std::cout << comp->getDescription() << std::endl;
		}
		std::cout << "Screen diagonal: " << screenDiagonal << "\"\n";
		std::cout << "Inventar number: "<<PC::getInventarNumber() << '\n';
	}
};
/*
class Printer : public ITequipment {
public:
	Printer() = delete;

private:

};
class Scanner : public ITequipment {

};

class MFU : virtual public Printer, virtual public Scanner {

};
*/
#endif // !_ITEQUIPMENT_HPP_