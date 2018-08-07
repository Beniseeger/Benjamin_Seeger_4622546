#pragma once

#include <string>

namespace ConsoleUtils
{

	int readInteger();
	long readLong();
	double readDouble();
	std::string readString();
	time_t readTime();
	int readSaveInteger(std::string message);
};

