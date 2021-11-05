#ifndef __ROOM__HPP___
#define __ROOM__HPP___

#include <vector>
#include <string>
#include "Item.hpp"
#include "BaseObject.hpp"
#include <memory>

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS


class Room: public BaseObject{

public:
	Room() = delete;
	DECLSPEC Room(const std::string& name_);
	DECLSPEC Item* showItem(size_t index) const ;
	DECLSPEC void addItem(Item* item);
	DECLSPEC void eraseItem(Item* item);
	DECLSPEC bool isEmpty();
	DECLSPEC Item* findItem(const std::string& name);
	DECLSPEC Item*  findItem(int64_t inventoryNumber);
	DECLSPEC bool operator<(const Room& other);
	
private:
	std::vector<Item*> items;
};

#endif // !__ROOM__HPP___