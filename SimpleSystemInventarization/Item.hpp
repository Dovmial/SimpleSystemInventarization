#ifndef _ITEMHPP_
#define _ITEMHPP_

#include <string>
#include "BaseObject.hpp" 
#include "ITequipment.hpp"
//adapter

class Item: public BaseObject {
public:
	Item() = delete;
	Item(ITequipment* item_);
private:
	
	int64_t invetoryNumber;
	Info* info;
};

#endif // !_ITEMHPP_
