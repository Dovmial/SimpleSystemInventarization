
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
	DECLSPEC int findRoom(const std::string& nameRoom) const;
	DECLSPEC Room* findItem(const std::string& name) const;
	DECLSPEC Room* findItem(int64_t inventoryNumber) const;
	DECLSPEC Room* getRoom(int index) const;
	DECLSPEC bool  isExistRoom(const std::string& nameRoom )const;
	
private:
	std::vector<std::unique_ptr<Room>> rooms;
};

#endif
