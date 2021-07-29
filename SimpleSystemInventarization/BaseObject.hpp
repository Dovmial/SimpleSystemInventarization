#ifndef _BASEOBJECT_HPP_
#define _BASEOBJECT_HPP_

#include <string>
class BaseObject {
public:
	BaseObject(std::string name_);
	std::string getName() const noexcept;
	void setName(std::string name_) noexcept;
protected:
	std::string name;
};
#endif // !_BASEOBJECT_HPP_

