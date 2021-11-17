#ifndef __ISERIALIZE__HPP__
#define __ISERIALIZE__HPP__

#include "tinyxml2.h"
using namespace tinyxml2;

struct ISerialize {
	virtual XMLElement* serialize(XMLDocument& doc) = 0;
	//void deserialize(DeviceLocation);
};

#endif
