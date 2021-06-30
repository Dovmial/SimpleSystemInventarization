
#include "BaseITtechnics.hpp"

BaseITtechnics::BaseITtechnics(uint64_t inventNumb, std::string name_, std::string description_)
    : BaseObject(description_), inventarNumber(inventNumb), name(name_)
{}

BaseITtechnics::BaseITtechnics(int inventNumb, std::string name_, std::string description_)
    : BaseITtechnics(static_cast<uint64_t>(inventNumb), name_, description_)
{}


auto BaseITtechnics::getInventarNumber() const -> uint64_t
{
    return inventarNumber;
}

auto BaseITtechnics::getName() const -> std::string
{
    return std::string();
}

void BaseITtechnics::setInventarNumber(uint64_t inventNumb)
{
    inventarNumber = inventNumb;
}

void BaseITtechnics::setName(std::string name_)
{
    name = name_;
}
