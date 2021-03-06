#ifndef _ITEM_HPP__
#define _ITEM_HPP__

#include <vector>
#include <string>
#include <memory>
#include "ITequipment.hpp"
#include "ServiceInfo.hpp"
#include "ISerialize.hpp"


using ServiceInfoContainer = std::vector<std::shared_ptr<ServiceInfo>>;
using ProblemSolutionContainer = std::vector<std::shared_ptr<ProblemSolutionInfo>>;

using SIiterator = ServiceInfoContainer::iterator;
using SIiteratorConst = ServiceInfoContainer::const_iterator;
using PSiterator = ProblemSolutionContainer::iterator;
using PSiteratorConst = ProblemSolutionContainer::const_iterator;

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

/*Item - ?????????? ????????? ????????????*/
class DECLSPEC Item : public ISerialize{
//maybe add ID
public:
	Item() = delete;
	Item(std::shared_ptr<ITequipment> equipment_, int64_t inventoryNumber_);
	//~Item();
	std::string getName() const;
	void addSignService(std::string description, std::string date);
	void addSignProblemsSolutions(
		std::string problems,
		std::string date = "",
		std::string solution = "");
	void removeSignService(int index);
	void removeSignProblemSolution(int index);

	//void setITequipment(ITequipment* eq);
	std::shared_ptr <ITequipment> getITequipment()const;

	void setIventoryNumber(int64_t);
	int64_t getInventoryNumber() const;

	std::pair<SIiterator, SIiterator> getServiceInfo();
	std::pair<PSiterator, PSiterator> getProblemsSolutions();
	std::pair<SIiteratorConst, SIiteratorConst> getServiceInfoView() const;
	std::pair<PSiteratorConst, PSiteratorConst> getProblemsSolutionsView() const;
	
public:
	ServiceInfoContainer&& getServicesInformation();
	ProblemSolutionContainer&& getProblemsSolutionsInformation();
	void setServicesInformation(ServiceInfoContainer&& services_);
	void setProblemsSolutionsInformation(ProblemSolutionContainer&& problemsSolutions_);

	XMLElement* serialize(XMLDocument& xmlDoc)const  override;
private:
	std::shared_ptr<ITequipment> equipment;
	int64_t inventoryNumber;
	
	//profilactic/service - date
	ServiceInfoContainer services;
	
	//problem - solution - date
	ProblemSolutionContainer problemsSolutions;
};
#endif // !_ITEM_HPP__
