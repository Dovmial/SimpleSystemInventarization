#ifndef _INFORMATION_HPP_
#define _INFORMATION_HPP_

#include <string>
#include <iomanip>

struct Info {
	virtual void getInfoCLI() = 0;
};

class InfoPC : public  Info {
public:
	void getInfoCLI() const;
	void setMotherBoard(const std::string& mb);
	void setCPU(const std::string& name, float freq);
	void setGraphicCard(const std::string& name, float videoRam = -1.);
	void setRAM(float ram);
	void setStorageDevice(float sdVolume);
	void setOperSystem(const std::string& operSystem);
private:
	std::string motherBoard;
	struct CPU {
		std::string name;
		float frequency;
	}_cpu;
	struct GraphicCard {
		std::string name;
		float videoRam;
	}graphicCard;
	float ram;
	float storageDevice;
	std::string operSystem;
};

class InfoPrinter : public  Info {
public:
	void getInfoCLI();
	void setCartridge(const std::string& cartridge);
private:
	std::string cartridge;
};

class InfoMonitor : public  Info {
public:
	void getInfoCLI();
	void setScreenDiagonal(float sDiagonal);
private:
	float screenDiagonal;
};

class InfoOtherDevice : public  Info {
public:
	void getInfoCLI();
	void setSomeInfo(const std::string& someInfo);
private:
	std::string someInfo;
};
#endif