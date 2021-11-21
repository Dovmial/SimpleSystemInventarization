#ifndef __SERVICEINFO__HPP__
#define __SERVICEINFO__HPP__

#include <string>

#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // MODEL_EXPORTS

class DECLSPEC ServiceInfo {
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

class DECLSPEC ProblemSolutionInfo: public ServiceInfo{
public:
	ProblemSolutionInfo();
	ProblemSolutionInfo(const std::string& description,
		const std::string& date, const std::string& solution = "");

	void setSolution(const std::string& solution_);
	std::string getSolution() const;
private:
	std::string solution;
};
#endif
