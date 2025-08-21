#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitCoinExchange
{
	private:
		std::map<std::string, float> _data;
	public:
		BitCoinExchange(const std::string& file);
		BitCoinExchange(const BitCoinExchange& other);
		BitCoinExchange& operator=(const BitCoinExchange& other);
		~BitCoinExchange();

		void checkPrices(const std::string& file) const;
};

#endif
