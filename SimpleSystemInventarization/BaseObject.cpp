#include "BaseObject.hpp"

BaseObject::BaseObject(const std::string& name_) : name(name_)
{}

void BaseObject::setName(const std::string& name_)
{
	name = name_;
}

std::string BaseObject::getName() const
{
	return name;
}
