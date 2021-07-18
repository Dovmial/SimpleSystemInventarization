#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <vector>
#include "Components.hpp"
#include <iostream>

class ITequipment {

};

using Components = std::vector<BaseComponent*>;
class PC: public ITequipment {
public:
	PC() = delete;
	PC(Components components_) : components(components_) {}
protected:
	Components components;
};

class Monitor : public ITequipment {
public:
	Monitor() = delete;
	Monitor(float screenDiagonal_) : screenDiagonal(screenDiagonal_) {}
protected:
	float screenDiagonal;
};

class Laptop : virtual public PC, virtual public Monitor {
public:
	Laptop() = delete;
	Laptop(Components components_, float screenDiagonal_) :
		PC(components_), Monitor(screenDiagonal_) {}
	void show() noexcept {
		for (const auto& comp : components) {
			std::cout << comp->getDescription() << std::endl;
		}
		std::cout << "Screen diagonal: " << screenDiagonal << "\"\n";
	}
};
#endif // !_ITEQUIPMENT_HPP_