#include "PmergeMe.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

bool isPositiveInt(std::string token)
{
	if (token.empty())
		return (false);
	if (token.size() > 1 && token[0] == '0')
		return (false);
	if (token.size() >= 10 && token != "2147483647")
		return (false);
	for (int i = 0; token[i]; i++)
	{
		if (!std::isdigit(token[i]))
			return (false);
	}
	return (true);
}

void parseArguments(char **argv, std::vector<int>& v)
{
	for (int i = 1; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		std::string token;
		while (iss >> token)
		{
			if (!isPositiveInt(token))
				throw std::invalid_argument("positive integers only");
			v.push_back(std::atoi(token.c_str()));
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./PmergeMe <number sequence>" << std::endl;
		return (1);
	}
	try
	{
		std::vector<int> v;
		parseArguments(argv, v);

		PmergeMe test(v);
		test.vecSort();
		test.print();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
