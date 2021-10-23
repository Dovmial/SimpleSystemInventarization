#ifndef __BASEOBJECT__HPP__
#define __BASEOBJECT__HPP__


#include <string>

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS


class DECLSPEC BaseObject {
public:
	BaseObject() = delete;
	BaseObject(const std::string& name_);
	void setName(const std::string& name_);
	std::string getName() const;
protected:
	std::string name;
};

#endif