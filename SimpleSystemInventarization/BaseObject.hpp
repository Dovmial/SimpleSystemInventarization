#ifndef __BASEOBJECT__HPP__
#define __BASEOBJECT__HPP__

#include <string>

class BaseObject {
public:
	BaseObject() = delete;
	BaseObject(const std::string& name_);
	void setName(const std::string& name_);
	std::string getName() const;
protected:
	std::string name;
};

#endif