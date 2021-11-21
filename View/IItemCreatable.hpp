#ifndef __IITEMCREATABLE__HPP__
#define __IITEMCREATABLE__HPP__
#include "../SimpleSystemInventarization/Item.hpp"

struct IItemCreatable {
	virtual Item* createItem() = 0;
};
#endif