#include "BitCoinExchange.hpp"
#include <iostream>
#include <iomanip>
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
		return (30);
	else
		return (31);
}

static bool isValidDate(const std::string& line)
{
	if (line.size() != 10 || line[4] != '-' || line[7] != '-')
		return (false);

	std::istringstream iss(line.substr(0, 4));
	int valueY;
	if (!(iss >> valueY))
		return (false);
	
	std::istringstream iss1(line.substr(5, 2));
	int valueM;
	if (!(iss1 >> valueM) || valueM < 1 || valueM > 12)
		return (false);

	int daysInMonth = checkDays(valueY, valueM);
	std::istringstream iss2(line.substr(8, 2));
	int valueD;
	if (!(iss2 >> valueD) || valueD < 1 || valueD > daysInMonth)
		return (false);

	return (true);
}

BitCoinExchange::BitCoinExchange(const std::string& file)
{
	std::ifstream content(file.c_str());
	if (!content.is_open())	
		throw std::runtime_error("could not open CSV file");
	
	std::string line;
	std::getline(content, line);
	while (std::getline(content, line))
	{
		std::istringstream iss(line.c_str());
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
	std::ifstream content(file.c_str());
	if (!content.is_open())
		throw std::runtime_error("could not open file.");

	std::string line;
	std::getline(content, line);
	if (line != "date | value")
		throw std::invalid_argument("file must be headed by (date | value)");
	while (std::getline(content, line))
	{
		if (line.empty())
			continue;
		std::string::size_type pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string key = line.substr(0, pos);
		if (!isValidDate(key))
		{
			std::cerr << "Error: invalid date" << std::endl;
			continue;
		}

		std::istringstream iss(line.substr(pos + 3));
		float value;
		if (!(iss >> value) || !(iss >> std::ws).eof())
		{
			std::cerr << "Error: invalid number." << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

        std::map<std::string, float>::const_iterator it = _data.find(key);
        if (it != _data.end())
        {
            float amount = it->second * value;
            std::cout << key << " => " << std::fixed << std::setprecision(2) << value << " = " << amount << std::endl;
        }
        else 
        {
            it = _data.lower_bound(key);
            if (it == _data.begin())
                std::cout << "No valid exchange found in database, earliest date is " << _data.begin()->first << std::endl;
            else
            {
                --it;
                float amount = it->second * value;
                std::cout << key << " => " << std::fixed << std::setprecision(2) << value << " = " << amount << std::endl;
            }
        }
	}
}
