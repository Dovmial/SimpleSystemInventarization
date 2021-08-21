
#ifndef __BUILD__HPP___
#define __BUILD__HPP___

#include <set>
#include "BaseObject.hpp"
#include "Room.hpp"

class Build: public BaseObject{
private:
	std::set<Room*> rooms;
public:
	Build() = delete;
	Room* createRoom();
	void addRoom();
	void eraseRoom();
	void findItem(const std::string& name);
	void findItem(int64_t inventoryNumber);
};

#endif
