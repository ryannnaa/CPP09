#include "RPN.hpp"
#include <cstdlib>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <string>


static bool isNumber(const std::string& s)
{
	return (s.size() == 1 && std::isdigit(s[0]));
}

RPN::RPN()
{}

RPN::RPN(const RPN& other)
	: _items(other._items)
{}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_items = other._items;
	}
	return (*this);
}

RPN::~RPN()
{}

void RPN::applyOperator(const std::string& op)
{
	if (_items.size() < 2)
		throw std::runtime_error("Insufficient operands");
	if (op.size() != 1)
		throw std::invalid_argument("Invalid op");

	int b = _items.top();
	_items.pop();

	int a = _items.top();
	_items.pop();

	switch (op[0])
	{
		case '+':
			_items.push(a + b);
			break;
		case '-':
			_items.push(a - b);
			break;
		case '*':
			_items.push(a * b);
			break;
		case '/':
			_items.push(a / b);
			break;
		default:
			throw std::runtime_error("Invalid op");
	}
}

void RPN::calculate(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;
	while (iss >> token)
	{
		if (isNumber(token))
			_items.push(atoi(token.c_str()));
		else
			applyOperator(token);
	}
	if (_items.size() != 1)
		throw std::runtime_error("Invalid RPN expression");
}

int RPN::getResult() const
{
	if (_items.size() == 0)
		throw std::runtime_error("No result to return");
	return (_items.top());
}
