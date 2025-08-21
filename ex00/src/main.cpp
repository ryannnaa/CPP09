#include "BitCoinExchange.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc <file>" << std::endl;
		return (1);
	}
	try
	{
		BitCoinExchange btc("data.csv");
		btc.checkPrices(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
