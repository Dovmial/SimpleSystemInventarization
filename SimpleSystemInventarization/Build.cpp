#include "Build.hpp"

Build::Build(const std::string& name, std::shared_ptr<DataManager> dm) :
	dataManager{ dm },
	BaseObject{ name }
{
}
