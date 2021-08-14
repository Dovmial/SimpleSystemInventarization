#include "serviceInfo.hpp"

ServiceInfo::ServiceInfo() : description(""), date("")
{
}

ServiceInfo::ServiceInfo(const std::string& description_,
	const std::string& date_): description(description_), date(date_)
{
}

void ServiceInfo::setDescription(const std::string& description)
{
	this->description = description;
}

void ServiceInfo::setDate(const std::string& date)
{
	this->date = date;
}

std::string ServiceInfo::getDescription() const
{
	return description;
}

std::string ServiceInfo::getDate() const
{
	return date;
}

ProblemSolutionInfo::ProblemSolutionInfo(): solution(""), ServiceInfo()
{
}

ProblemSolutionInfo::ProblemSolutionInfo(
	const std::string& description,
	const std::string& date,
	const std::string& solution_):
	solution(solution_), ServiceInfo(description, date)
{
}

void ProblemSolutionInfo::setSolution(const std::string& solution)
{
}

std::string ProblemSolutionInfo::getSolution() const
{
	return std::string();
}
