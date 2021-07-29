#ifndef _BUILD_HPP_
#define _BUILD_HPP_

#include "Room.hpp"
#include "BaseObject.hpp"
#include <map>

class Build: public BaseObject {
public:
	Build() = delete;
	Build(std::string name_);
	Build(std::string name_, std::map<std::string, Room*> rooms_);
	void addRoom(Room* room);
	void deleteRoom(const std::string& nameOfdelElem);
private:
	std::map<std::string, Room*> rooms;
};
#endif // !_BUILD_HPP_

