#ifndef __NAVIGATOR__HPP__
#define __NAVIGATOR__HPP__

#include <utility>
#include <string>
#include "Location.hpp"

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

class INavigator {
public:
	virtual auto getCurrentlocation() const
		->std::pair < std::string, std::string > = 0;
	virtual void setCurrentLocation(
		const std::string& building, const std::string& room) = 0;
};

class  Navigator: public INavigator
{
public:
	Navigator(const std::string& building, const std::string& name);
	auto getCurrentlocation() const
		->std::pair < std::string, std::string > override;
	void setCurrentLocation(
		const std::string& building, const std::string& room) override;
private:
	Location location;
};

#endif
