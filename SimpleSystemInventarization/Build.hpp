
#ifndef __BUILD__HPP___
#define __BUILD__HPP___

#include <set>
#include "BaseObject.hpp"
#include "Room.hpp"
#include "DataManager.hpp"
#include <memory>

class Build: public BaseObject{
private:
	std::set<std::unique_ptr<Room>> rooms;//vector
	std::shared_ptr<DataManager> dataManager;
	std::unique_ptr<Room> createRoom(
		const DataManager& dm, const std::string& name);
public:
	Build() = delete;
	Build(const std::string& name, std::shared_ptr<DataManager> dm);
	void addRoom();
	void eraseRoom();
	void findItem(const std::string& name);
	void findItem(int64_t inventoryNumber);
	
};

#endif
