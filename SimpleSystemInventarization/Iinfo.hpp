#pragma once
#ifdef MODEL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
struct DECLSPEC Iinfo {
	virtual std::string getInfo() const = 0;
};