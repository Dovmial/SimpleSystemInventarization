#include "BaseObject.hpp"

BaseObject::BaseObject(std::string name_): name(name_)
{
}

std::string BaseObject::getName() const noexcept
{
	return name;
}

void BaseObject::setName(std::string name_) noexcept
{
	name = name_;
}
