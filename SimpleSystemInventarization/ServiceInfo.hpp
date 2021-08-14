#ifndef __SERVICEINFO_HPP__
#define __SERVICEINFO_HPP__

#include <string>

class ServiceInfo {
public:
	ServiceInfo();
	ServiceInfo(const std::string& description,
		const std::string& date);

	void setDescription(const std::string& description);
	void setDate(const std::string& date);

	std::string getDescription() const;
	std::string getDate() const;
protected:
	std::string description;
	std::string date;
};

class ProblemSolutionInfo: public ServiceInfo {
public:
	ProblemSolutionInfo();
	ProblemSolutionInfo(const std::string& description,
		const std::string& date, const std::string& solution = "");

	void setSolution(const std::string& solution);
	std::string getSolution() const;
private:
	std::string solution;
};
#endif
