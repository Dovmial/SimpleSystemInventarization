#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <vector>
#include "ITequipment.hpp"

class Room {
public:
	Room(){}
	Room(std::string name_) : name(name_) {}

	void addEquipment(ITequipment* object, int count) {
		auto item = std::make_pair(object, count);
		equipments.push_back(item);
	}

	void move(ITequipment* object, Room* room);
	ITequipment* find();
	void displayEquipments();
	void deleteEqipment();

private:
	std::vector<std::pair<ITequipment*, int>> equipments;
	std::string name;
};
#endif
