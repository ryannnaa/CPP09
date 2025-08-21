#include "BitCoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <utility>

static int checkDays(int valueY, int valueM)
{
	if (valueM == 2)
	{
		int days = (valueY % 4 == 0 && (valueY % 100 != 0 || valueY % 400 == 0)) ? 29 : 28;
		return (days);
	}
	else if (valueM == 4 || valueM == 6 || valueM == 9 || valueM == 11)
		return (31);
	else
		return (30);
}

static bool isValidDate(const std::string& line)
{
	if (line.size() != 10 || line[4] != '-' || line[7] != '-')
		return (1);

	std::istringstream iss(line.substr(0, 3);
	int valueY;
	if (!(iss >> valueY))
		return (1);
	
	std::istringstream iss(line.substr(4, 5);
	int valueM;
	if (!(iss >> valueM) || valueM < 1 || valueM > 12)
		return (1);

	daysInMonth = checkDays(valueY, valueM);
	std::istringstream iss(line.substr(6, 7);
	int valueD;
	if (!(iss >> valueD) || valueD < 1 || valueD > daysInMonth)
		return (1);
}

BitCoinExchange:BitCoinExchange(const std::string& file)
{
	std::ifstream content(file);
	if (!content.is_open())	
		throw std::runtime_error("could not open CSV file");
	
	std::string line;
	while (std::getline(content, line))
	{
		std::istringstream iss(line);

		std::string key;
		std::getline(iss, key, ',');
		if (key.size() != 10 || key[4] != '-' || key[7] != '-')
		       throw std::invalid_argument("bad input => " + key);	

		float value;
		if (!(iss >> value))
			throw std::invalid_argument("invalid number.");
		if (value < 0)
			throw std::invalid_argument("not a positive number.");
		_data.insert(std::make_pair(key, value));
	}
}

BitCoinExchange::BitCoinExchange(const BitCoinExchange& other)
	: _data(other._data)
{}

BitCoinExchange& BitCoinExchange::operator=(const BitCoinExchange& other)
{
	if (this != &other)
	{
		_data = other._data;
	}
	return (*this);
}

BitCoinExchange::~BitCoinExchange()
{}

void BitCoinExchange::checkPrices(const std::string& file) const
{
	std::ifstream content(file);
	if (!content.is_open())
		throw std::runtime_error("could not open file.");

	std::string line;
	std::getline(content, line);
	if (line != "date | value")
		throw std::invalid_argument("file must be headed by (date | value)");
	while (std::getline(content, line))
	{
		std::string::size_type pos = line.find(" | ");
		if (pos == std::string::npos)
			throw std::invalid_argument("date and value must be separated by ( | )");
		std::string key = line.substr(0, pos);
		if (!isValidDate(key))
			throw std::invalid_argument("bad input => " + key);
		std::istringstream iss(line,substr(pos + 3));
		float value;
		if (!(iss >> value))
			throw std::invalid_argument("invalid number.");
		if (value < 0)
			throw std::invalid_argument("not a positive number.");
		if (value > 10000)
			throw std::invalid_argument("too large a number.");
	}

}
