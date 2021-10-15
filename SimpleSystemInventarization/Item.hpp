#ifndef _ITEM_HPP__
#define _ITEM_HPP__

#include <vector>
#include <string>
#include <memory>
#include "ITequipment.hpp"
#include "ServiceInfo.hpp"


using ServiceInfoContainer = std::vector<std::shared_ptr<ServiceInfo>>;
using ProblemSolutionContainer = std::vector<std::shared_ptr<ProblemSolutionInfo>>;
using SIiterator = ServiceInfoContainer::iterator;
using SIiteratorConst = ServiceInfoContainer::const_iterator;
using PSiterator = ProblemSolutionContainer::iterator;
using PSiteratorConst = ProblemSolutionContainer::const_iterator;

/*Item - эквивалент реального оборудования*/
class Item {
//maybe add ID
public:
	Item() = delete;
	Item(std::shared_ptr<ITequipment> equipment_, int64_t inventoryNumber_);
	//~Item();

	void addSignService(std::string description, std::string date);
	void addSignProblemsSolutions(
		std::string problems,
		std::string date = "",
		std::string solution = "");

	//void setITequipment(ITequipment* eq);
	std::shared_ptr <ITequipment> getITequipment()const;

	void setIventoryNumber(int64_t);
	int64_t getInventoryNumber() const;

	std::pair<SIiterator, SIiterator> getServiceInfo();
	std::pair<PSiterator, PSiterator> getProblemsSolutions();
	std::pair<SIiteratorConst, SIiteratorConst> getServiceInfoView() const;
	std::pair<PSiteratorConst, PSiteratorConst> getProblemsSolutionsView() const;
	void getPrintInfoItem() const;
private:
	std::shared_ptr<ITequipment> equipment;
	int64_t inventoryNumber;
	
	//profilactic/service - date
	ServiceInfoContainer services;
	
	//problem - solution - date
	ProblemSolutionContainer problemsSolutions;
};
#endif // !_ITEM_HPP__
