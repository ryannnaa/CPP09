#include "PmergeMe.hpp"
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

template <typename Container>
static void merge(Container& c, int left, int mid, int right)
{
	Container tmp;
	tmp.reserve(right - left + 1);

	int i = left, j = mid + 1;
	while (i <= mid && j <= right)
	{
		if (c[i].first <= c[j].first)
			tmp.push_back(c[i++]);
		else
			tmp.push_back(c[j++]);
	}

	while (i <= mid)
		tmp.push_back(c[i++]);

	while (j <= right)
		tmp.push_back(c[j++]);

	for (std::size_t pos = 0; pos < tmp.size(); pos++)
		c[left + pos] = tmp[pos];
}

template <typename Container>
static void mergeSort(Container& c, int left, int right)
{
	if (left >= right)
		return ;

	int mid = left + (right - left) / 2;
	mergeSort(c, left, mid);
	mergeSort(c, mid + 1, right);
	merge(c, left, mid, right);
}

PmergeMe::PmergeMe()
	: _deq(0), _vec(0)
{}

PmergeMe::PmergeMe(const std::vector<int>& v)
	: _unsorted(v), _deq(0), _vec(0)
{}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _unsorted(other._unsorted), _sorted(other._sorted), _deq(other._deq), _vec(other._vec)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_unsorted = other._unsorted;
		_sorted = other._sorted;
		_deq = other._deq;
		_vec = other._vec;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::vecSort()
{
	std::size_t i = _unsorted.size();
	if (i == 1)
	{
		_sorted = _unsorted;
		return ;
	}

	int remainder = -1;
	if (i % 2 != 0)
	{
		remainder = _unsorted.back();
		i -= 1;
	}

	std::vector<std::pair<int, int> > tmp;
	for (std::size_t j = 1; j < i; j += 2)
	{
		int a = _unsorted[j];
		int b = _unsorted[j - 1];
		std::pair<int, int> p;
		p = (a > b) ? std::make_pair(a, b) : std::make_pair(b, a);
		tmp.push_back(p);
	}

	mergeSort(tmp, 0, tmp.size() - 1);
	for (std::size_t k = 0; k < i/2; k++)
		std::cout << "First: " << tmp[k].first << " Second: " << tmp[k].second << std::endl;
	if (remainder != -1)
		std::cout << "Remainder: " << remainder << std::endl;
}

void PmergeMe::print()
{
	std::cout << "Before: ";
	for (std::size_t i = 0; i < _unsorted.size(); i++)
		std::cout << " " << _unsorted[i];
	std::cout << "\nAfter: ";
	for (std::size_t i = 0; i < _sorted.size(); i++)
		std::cout << " " << _sorted[i];
	std::cout << "\nTime to process a range of " << _unsorted.size() << " elements with std::deque : " << _deq << " us";
	std::cout << "\nTime to process a range of " << _unsorted.size() << " elements with std::vector : " << _vec << " us" << std::endl;
}
