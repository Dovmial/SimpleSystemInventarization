#pragma once
//todo: #ifndef

#include "BaseITtechnics.hpp"
#include "Source.hpp"

class PC: public BaseITtechnics {
	PC() = delete;
	PC(uint64_t inventNumb, std::string name, Info& info_)
		:BaseITtechnics(inventNumb, name), info(info_)
	{}
	PC(int inventNumb, std::string name, Info& info_)
		:PC(static_cast<uint64_t>(inventNumb), name, info_)
	{}
public:
	void setInfo(Info& info) {
		this->info = info;
	}
	Info& getInfo()const {
		return info;
	}
private:
	Info& info; //std::shared_ptr<Info>
};
