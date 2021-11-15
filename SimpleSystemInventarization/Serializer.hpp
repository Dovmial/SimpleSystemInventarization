#pragma once
#include "DataManager.hpp"
#include <fstream>

class Serialazer {
public:
	Serialazer(DataManager* dm) { dataManager = dm; };
	~Serialazer() {};


	void operator()(std::vector<Building*> buildings)
	{
		
		const size_t SIZE{ buildings.size() };
		size_t countRooms{1};
		std::ofstream file(m_path);
		file << SIZE << '\n';

		for (size_t i{1}; i < SIZE; ++i) {
			file << buildings[i]->getName()<<";\n";
			countRooms = buildings[i]->size();
			for (size_t j{ 1 }; j < countRooms; ++j)
				file << countRooms-1<<' '<<buildings[i]->getRoom(j) << ';';
			file << '\n';
		}

		file.close();
	}
	
private:
	std::string m_path = "data.ssi";
	DataManager* dataManager;
};