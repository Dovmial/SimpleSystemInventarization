#ifndef SOURCE_HPP_
#define SOURCE_HPP_

#include <string>

enum class IT_Tech {
	PC, Monitor, MFU,
	Printer, Scaner,
	Server, Other
};

struct Info {
	std::string type;

};

class BaseComponent {
public:
	virtual void showInfo = 0;
private:
	int quntity;
	bool exist;
	std::string description
};

struct InfoPC : public Info {
	Motherboard motherboard;
	CPU mCpu;
	RAM ram;
	GraphicsCard graphicsCard;
	HDD hdd;
	SSD ssd;

};
#endif // !SOURCE_HPP_
