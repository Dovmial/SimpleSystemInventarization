#ifndef BASEOBJECT_HPP_
#define BASEOBJECT_HPP_

#include <string>
#include <cstdint>

class BaseObject {
public:
	BaseObject() = delete;
	BaseObject(std::string description) : description(description)
	{}
	void setDescription(std::string description) {
		this->description = description;
	}
	auto getDescriptio()const->std::string {
		return description;
	}
	virtual void show() = 0;
private:
	std::string description;
};
#endif // !BASEOBJECT_HPP_
