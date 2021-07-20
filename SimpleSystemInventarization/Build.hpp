#ifndef _BUILD_HPP_
#define _BUILD_HPP_

#include "Room.hpp"
#include <vector>
class Build {
public:
	void addRoom();
	void deleteRoom();
	void renameRoom();
	void displayAllRooms();
	void displayRoom();
private:
	std::vector<Room*> rooms;
};
#endif // !_BUILD_HPP_

