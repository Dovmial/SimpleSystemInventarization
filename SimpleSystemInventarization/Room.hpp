#ifndef __ROOM__HPP___
#define __ROOM__HPP___

#include <vector>
#include <string>
#include "Item.hpp"
#include "BaseObject.hpp"

class Room: public BaseObject{
private:
	std::vector<Item*> items;
public:
	Room() = delete;
	Room(const std::string& name_);

	void addItem(Item* item);
	void eraseItem(Item* item);
};

#endif // !__ROOM__HPP___