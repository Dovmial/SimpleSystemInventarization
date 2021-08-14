#ifndef _ITEM_HPP__
#define _ITEM_HPP__

#include <vector>
#include <string>
#include "ITequipment.hpp"
#include "ServiceInfo.hpp"


using ServiceInfoContainer = std::vector<ServiceInfo*>;
using ProblemSolutionContainer = std::vector<ProblemSolutionInfo*>;
using SIiterator = ServiceInfoContainer::iterator;
using SIiteratorConst = ServiceInfoContainer::const_iterator;
using PSiterator = ProblemSolutionContainer::iterator;
using PSiteratorConst = ProblemSolutionContainer::const_iterator;

class Item {
//maybe add ID
public:
	Item() = delete;
	Item(ITequipment* equipment_, int64_t inventoryNumber_ = -1);
	~Item();

	void addSignService(std::string description, std::string date);
	void addSignProblemsSolutions(
		std::string problems,
		std::string date = "",
		std::string solution = "");

	//void setITequipment(ITequipment* eq);
	ITequipment* getITequipment()const;

	void setIventoryNumber(int64_t);
	int64_t getInventoryNumber() const;

	std::pair<SIiterator, SIiterator> getServiceInfoBegin();
	std::pair<PSiterator, PSiterator> getProblemsSolutions();
	std::pair<SIiteratorConst, SIiteratorConst> getServiceInfoView() const;
	std::pair<PSiteratorConst, PSiteratorConst> 
		getProblemsSolutionsView() const;

private:
	ITequipment* equipment;
	int64_t inventoryNumber;
	
	//profilactic/service - date
	ServiceInfoContainer services;
	
	//problem - solution - date
	ProblemSolutionContainer problemsSolutions;
};
#endif // !_ITEM_HPP__
