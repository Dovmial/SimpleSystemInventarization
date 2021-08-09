#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <vector>
#include <utility>
#include "ITequipment.hpp"
#include "BaseObject.hpp"

class Room : public BaseObject{
public:
	Room() = delete;
	Room(std::string name_) : BaseObject(name_) {}

	void addEquipment(ITequipment* object, int count) {
		std::pair item(object, count);
		equipments.push_back(item);
	}
	void move(ITequipment* object, Room* room);
	void rename();
	ITequipment* find();
	void deleteEqipment();
private:
	std::vector<std::pair<ITequipment*, int>> equipments;
};
#endif
