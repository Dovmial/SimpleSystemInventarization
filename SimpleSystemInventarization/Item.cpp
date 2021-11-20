#include "Item.hpp"
#include <tuple>
#include <sstream>

Item::Item(std::shared_ptr<ITequipment> equipment_, int64_t inventoryNumber_) :
	equipment(equipment_),
	inventoryNumber(inventoryNumber_)
{}
std::string Item::getName() const
{
	return getITequipment()->getName();
}
/*
Item::~Item()
{
	for (const auto& serv : services) {
		delete serv;
	}
	for (const auto& probSol : problemsSolutions) {
		delete probSol;
	}
}
*/
void Item::addSignService(std::string description, std::string date)
{
	services.push_back(std::make_shared<ServiceInfo>(description, date));
}
void Item::addSignProblemsSolutions(
	std::string problem,
	std::string date,
	std::string solution)
{
	problemsSolutions.push_back(
		std::make_shared<ProblemSolutionInfo>(problem, date, solution)); 
}

void Item::removeSignService(int index)
{
	services.erase(begin(services) + index);
}

void Item::removeSignProblemSolution(int index)
{
	problemsSolutions.erase(begin(problemsSolutions) + index);
}

std::shared_ptr<ITequipment> Item::getITequipment() const
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

std::pair<SIiterator, SIiterator> Item::getServiceInfo()
{
	return std::pair(begin(services), end(services));
}

std::pair<PSiterator, PSiterator> Item::getProblemsSolutions()
{
	return std::pair(begin(problemsSolutions), end(problemsSolutions));
}

std::pair<SIiteratorConst, SIiteratorConst> 
Item::getServiceInfoView() const
{
	return std::pair(cbegin(services), cend(services));
}

std::pair<PSiteratorConst, PSiteratorConst> 
Item::getProblemsSolutionsView() const
{
	return std::pair(cbegin(problemsSolutions), cend(problemsSolutions));
}

XMLElement* Item::serialize(XMLDocument& xmlDoc) const
{
	XMLElement* pItem{ xmlDoc.NewElement("Item") };
	pItem->SetAttribute("inventoryNumber", inventoryNumber);

	XMLElement* pITequipment{equipment->serialize(xmlDoc)};
	pItem->InsertEndChild(pITequipment);

	XMLElement* pServices{ xmlDoc.NewElement("Services") };
	pItem->InsertEndChild(pServices);

	for (auto& service : services) {
		XMLElement* pService{ xmlDoc.NewElement("ServiceInfo") };
		pService->SetAttribute("date", service->getDate().c_str());
		pService->SetText(service->getDescription().c_str());
		pServices->InsertEndChild(pService);
	}

	XMLElement* pProblemSolutions{ xmlDoc.NewElement("ProblemSolutions") };
	pItem->InsertEndChild(pProblemSolutions);

	for (auto& problemSolution : problemsSolutions) {
		XMLElement* pProblemSolution{ xmlDoc.NewElement("ProblemSolution") };

		XMLElement* pProblem{ xmlDoc.NewElement("Problem") };
		pProblem->SetText(problemSolution->getDescription().c_str());
		pProblemSolution->InsertEndChild(pProblem);

		if (problemSolution->getSolution().length()) {
			XMLElement* pSolution{ xmlDoc.NewElement("Solution") };
			pSolution->SetText(problemSolution->getSolution().c_str());
			pProblemSolution->InsertEndChild(pSolution);
		}

		if (problemSolution->getDate().length()) {
			XMLElement* pDate{ xmlDoc.NewElement("Date") };
			pDate->SetText(problemSolution->getDate().c_str());
			pProblemSolution->InsertEndChild(pDate);
		}

		pProblemSolutions->InsertEndChild(pProblemSolution);
	}

	return pItem;
}


