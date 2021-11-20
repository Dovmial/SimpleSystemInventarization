#ifndef __DEVICELOCATION__HPP__
#define __DEVICELOCATION__HPP__

#include "Item.hpp"
#include "ISerialize.hpp"
#include <memory>


#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

class DECLSPEC DeviceLocation : public ISerialize {

public:
	DeviceLocation(std::unique_ptr<Item> item, std::pair<size_t, size_t> locationIndexes);

	auto getItem			 () const->Item*;
	auto getRoomIndex		 () const->size_t;
	auto getBuildingIndex	 () const->size_t;
	auto getLocationIndexes  () const->std::pair<size_t, size_t>;

	void setLocationIndexes	 (const std::pair<size_t, size_t> location_);
	void setRoomIndex		 (size_t roomIndex);
	void setBuildingIndex	 (size_t buildingIndex);

	XMLElement* serialize	 (XMLDocument& xmlDoc) const override;
private:
	std::unique_ptr<Item> item;
	std::pair<size_t, size_t> location;
};

#endif