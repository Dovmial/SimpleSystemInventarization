#include "DeviceLocation.hpp"

DeviceLocation::DeviceLocation(std::unique_ptr<Item> item_, std::pair<size_t, size_t> locationIndexes)
    :item{ std::move(item_) },
    location{ locationIndexes }
{
}

Item* DeviceLocation::getItem() const
{
    return item.get();
}

size_t DeviceLocation::getRoomIndex() const
{
    return location.second;
}

size_t DeviceLocation::getBuildingIndex() const
{
    return location.first;
}

std::pair<size_t, size_t> DeviceLocation::getLocationIndexes() const
{
    return location;
}

void DeviceLocation::setLocationIndexes(const std::pair<size_t, size_t> location_)
{
    location = location_;
}

void DeviceLocation::setRoomIndex(size_t roomIndex)
{
    location.second = roomIndex;
}

void DeviceLocation::setBuildingIndex(size_t buildingIndex)
{
    location.first = buildingIndex;
}

XMLElement* DeviceLocation::serialize(XMLDocument& xmlDoc) const
{
    XMLElement* pDevice{ xmlDoc.NewElement("Device") };
    pDevice->SetAttribute("buildingIndex", location.first);
    pDevice->SetAttribute("roomIndex", location.second);

    auto pItem{ item->serialize(xmlDoc) };
    pDevice->InsertEndChild(pItem);

    return pDevice;
}
