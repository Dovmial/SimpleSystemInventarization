#pragma once
#include "../SimpleSystemInventarization/Item.hpp"

struct IItemCreatable {
	virtual Item* createItem() = 0;
};