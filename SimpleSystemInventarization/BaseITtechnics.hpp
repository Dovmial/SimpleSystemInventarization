#ifndef BASEITTECHNICS_HPP
#define BASEITTECHNICS_HPP

#include "BaseObject.hpp"

class BaseITtechnics: public BaseObject
{
public:
	BaseITtechnics() = delete;
	BaseITtechnics(uint64_t inventNumb, std::string name, std::string description);
	BaseITtechnics(int inventNumb, std::string name, std::string description);
	auto getInventarNumber()const	->uint64_t;
	auto getName()const				->std::string;
	void setInventarNumber(uint64_t inventNumb);
	void setName(std::string name_);
private:
	uint64_t inventarNumber;
	std::string name;
};

#endif // !BaseITtechnics_HPP

