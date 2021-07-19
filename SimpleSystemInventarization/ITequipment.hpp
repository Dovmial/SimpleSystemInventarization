#ifndef _ITEQUIPMENT_HPP_
#define _ITEQUIPMENT_HPP_

#include <vector>
#include <iostream>
#include "Components.hpp"

using Components = std::vector<BaseComponent*>;

class ITequipment {
public:
	ITequipment() = delete;
	ITequipment(int64_t inventarNumber_);
	int64_t getInventarNumber() const noexcept;
	void setInventarNumber() noexcept;
protected:
	int64_t inventarNumber;
};

class PC : public ITequipment {
public:
	PC() = delete;
	PC(Components components_, int64_t inentarNumber = -1);
protected:
	Components components;
};

class Monitor : public ITequipment {
public:
	Monitor() = delete;
	Monitor(float screenDiagonal_, int64_t inventarNumber_ = -1);
protected:
	float screenDiagonal;
};

class Laptop : virtual public PC, virtual public Monitor {
public:
	Laptop() = delete;
	Laptop(Components components_, float screenDiagonal_, int64_t inventarNumber_ = -1);
	void show() noexcept;
};

class Printer : public ITequipment {
public:
	Printer() = delete;
	Printer(Cartridge* cartridge_, int64_t inventarNumber = -1);
		
	Cartridge* getCartridge() const;
	void setCartridge(Cartridge* cartridge);
protected:
	Cartridge* cartridge;
};
class Scanner : public ITequipment {

};

class MFU : virtual public Printer, virtual public Scanner {

};

class OtherDevice : public ITequipment {

};
#endif // !_ITEQUIPMENT_HPP_