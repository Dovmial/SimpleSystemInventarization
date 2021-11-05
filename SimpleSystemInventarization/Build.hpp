
#ifndef __BUILD__HPP___
#define __BUILD__HPP___

#include <memory>
#include "BaseObject.hpp"
#include "Room.hpp"


#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS


class  Build: public BaseObject{

public:
	Build() = delete;
	DECLSPEC Build(const std::string& name);
	DECLSPEC void addRoom(const std::string& nameRoom);
	DECLSPEC bool removeRoom(const std::string& nameRoom);
	DECLSPEC int findRoom(const std::string& nameRoom);
	DECLSPEC Room* findItem(const std::string& name);
	DECLSPEC Room* findItem(int64_t inventoryNumber);
	DECLSPEC Room* getRoom(int index);
	
private:
	std::vector<std::unique_ptr<Room>> rooms;
};

#endif
