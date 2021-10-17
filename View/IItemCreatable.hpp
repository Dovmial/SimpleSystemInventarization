#pragma once
#include "../SimpleSystemInventarization/Item.hpp"

struct IItemCreatable {
	virtual std::unique_ptr<Item> createItem() = 0;
};