#ifndef __ROOM__HPP___
#define __ROOM__HPP___

#include <vector>
#include <string>
#include "Item.hpp"
#include "BaseObject.hpp"
#include "DataManager.hpp"
#include <memory>

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS


class  Room: public BaseObject{

public:
	Room() = delete;
	DECLSPEC Room(const std::string& name_);
		//, std::shared_ptr<DataManager> dm);
	DECLSPEC Item* showItem(size_t index) const ;
	DECLSPEC void addItem(std::unique_ptr<Item> item);
	DECLSPEC void eraseItem(Item* item);
	DECLSPEC bool isEmpty();
	DECLSPEC bool operator<(const Room& other);
private:
	std::vector<std::unique_ptr<Item>> items;
	//std::shared_ptr<DataManager> dataManager;

};

#endif // !__ROOM__HPP___