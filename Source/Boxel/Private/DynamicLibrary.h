#pragma once

#include "UnrealEd.h"


class DynamicLibrary {
public:

	DynamicLibrary();
	DynamicLibrary(const FString& libName);
	~DynamicLibrary();

	void setLibName(const FString& libName);
	bool load();
	void unload();
	bool loaded() const;
	void* loadFunction(const char* funcName) const;

	const FString& getLibName() const;
	FString getLibExtension() const;

private:
	FString libName;

	void* lib;

	void* loadLibrary();
};
