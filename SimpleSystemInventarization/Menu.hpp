#pragma once
#include <string>
#include <string_view>

class Menu {

public:
	int menuChoiceTypeCreator();

	std::string getString(std::string_view request);

	//request datas from a user
	float getNumberF(std::string_view request);

	int getChoiceMenu(std::string_view menu);
private:

};