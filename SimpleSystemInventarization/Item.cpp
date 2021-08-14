#include "Item.hpp"

Item::Item(ITequipment* equipment_, int64_t inventoryNumber_) :
	equipment(equipment_),
	inventoryNumber(inventoryNumber_)
{}

Item::~Item()
{
	for (const auto& serv : services) {
		delete serv;
	}
	for (const auto& probSol : problemsSolutions) {
		delete probSol;
	}
}

void Item::addSignService(std::string description, std::string date)
{
	services.push_back(new ServiceInfo(description, date));
}
void Item::addSignProblemsSolutions(
	std::string problem,
	std::string date,
	std::string solution)
{
	problemsSolutions.push_back(
		new ProblemSolutionInfo(problem, date, solution));
}

ITequipment* Item::getITequipment() const
{
	return equipment;
}

void Item::setIventoryNumber(int64_t invNumb)
{
	inventoryNumber = invNumb;
}

int64_t Item::getInventoryNumber() const
{
	return inventoryNumber;
}

std::pair<SIiterator, SIiterator> Item::getServiceInfoBegin()
{
	return std::make_pair(begin(services), end(services));
}

std::pair<PSiterator, PSiterator> Item::getProblemsSolutions()
{
	return std::make_pair(begin(problemsSolutions), end(problemsSolutions));
}

std::pair<SIiteratorConst, SIiteratorConst> 
Item::getServiceInfoView() const
{
	return std::make_pair(cbegin(services), cend(services));
}

std::pair<PSiteratorConst, PSiteratorConst> 
Item::getProblemsSolutionsView() const
{
	return std::make_pair(cbegin(problemsSolutions), cend(problemsSolutions));
}


