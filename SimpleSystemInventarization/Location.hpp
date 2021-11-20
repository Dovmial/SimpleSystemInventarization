#ifndef __LOCATION__HPP__
#define __LOCATION__HPP__

#include <string>
#include <utility>

struct Location {
	std::pair<size_t, std::string> building;
	std::pair<size_t, std::string> room;

	bool operator==(const Location& other) const;
};

#endif