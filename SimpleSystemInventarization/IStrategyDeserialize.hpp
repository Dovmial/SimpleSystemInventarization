#ifndef __ISTRATEGYDESERIALIZE__HPP__
#define __ISTRATEGYDESERIALIZE__HPP__

#include "DataManager.hpp"

struct IStrategyDeserialize {
	virtual Item* StrategyParseXMLElement(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location) = 0;
};


class StrategyParsePC : public IStrategyDeserialize
{
public:

	Item* StrategyParseXMLElement(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location) override;
};

class StrategyParseMonitor: public IStrategyDeserialize
{
public:

	Item* StrategyParseXMLElement(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location) override;
};

class StrategyParsePrinter : public IStrategyDeserialize
{
public:

	Item* StrategyParseXMLElement(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location) override;
};

class StrategyParseOther : public IStrategyDeserialize
{
public:

	Item* StrategyParseXMLElement(
		DataManager* dm,
		XMLElement* parent,
		int64_t itemNumber,
		const std::pair<size_t, size_t>& location) override;
};
#endif

