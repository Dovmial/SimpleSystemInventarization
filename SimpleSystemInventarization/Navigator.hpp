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

struct INavigator {
public:
	virtual auto getCurrentLocationString	() const->std::pair < std::string, std::string >  = 0;
	virtual auto getCurrentLocationIndexes	() const->std::pair < size_t, size_t >			  = 0;

	virtual void setCurrentRoom				(const std::pair<size_t, std::string>& room_)	  = 0;
	virtual void setCurrentBuilding			(const std::pair<size_t, std::string>& building_) = 0;
	virtual void setCurrentLocation			(
		std::pair<size_t,std::string> building_,
		std::pair<size_t, std::string> room_) = 0;
};

class  Navigator : public INavigator
{
public:
	Navigator(
		const std::pair<size_t, std::string>& building,
		const std::pair<size_t, std::string>& room
	);
	auto getCurrentLocationString() const
		->std::pair < std::string, std::string > override;
	auto getCurrentLocationIndexes() const->std::pair < size_t, size_t > override;

	void setCurrentLocation(
		std::pair<size_t, std::string> building,
		std::pair<size_t, std::string> room
	) override;

	void setCurrentRoom		(const std::pair<size_t,std::string>& room_		) override;
	void setCurrentBuilding (const std::pair<size_t, std::string>& building_) override;

	Location getLocation() const;

private:
	Location location;
};

#endif
