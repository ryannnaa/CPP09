#include "PmergeMe.hpp"
#include <vector>
#include <deque>

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _vector(other._vector), _deque(other._deque)
{}

PmergeMe& operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::sort()
{
}

void PmergeMe::print()
{
}
