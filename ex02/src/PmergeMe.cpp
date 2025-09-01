#include "PmergeMe.hpp"
#include <deque>
#include <iomanip>
#include <iostream>
#include <sys/time.h>
#include <utility>
#include <vector>

static double getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}	

template <typename Container>
static void merge(Container& c, int left, int mid, int right)
{
	Container tmp;

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

static std::vector<std::size_t> insertionOrder(std::size_t n)
{
	static const int JACOBSTHAL[] = {
		    0, 1, 1, 3, 5, 11, 21, 43, 85, 171,
		    341, 683, 1365, 2731, 5461, 10923,
		    21845, 43691, 87381, 174763, 349525
	};

	std::vector<std::size_t> order;
	if (n == 0)
		return (order);
	std::vector<bool> used(n, false);

	for (size_t i = 1; JACOBSTHAL[i] <= static_cast<int>(n); i++)
	{
		std::size_t index = JACOBSTHAL[i] - 1;
		if (!used[index])
		{
			order.push_back(index);
			used[index] = true;
		}

		std::size_t start;
		start = (i > 1) ? JACOBSTHAL[i - 1] : 1;
		for (std::size_t j = start; j < static_cast<std::size_t>(JACOBSTHAL[i]); j++)
		{
			std::size_t blankIndex = j - 1;
			if (!used[blankIndex])
			{
				order.push_back(blankIndex);
				used[blankIndex] = true;
			}
		}
	}

	for (size_t k = 0; k < n; k++)
		if (!used[k])
			order.push_back(k);
	return (order);
}

template <typename Container>
static void insertElements(Container &c, int element, int upperBound)
{
	std::size_t right;
	if (upperBound == -1)
		right = c.size();
	else
	{
		typename Container::iterator it = std::lower_bound(c.begin(), c.end(), upperBound);
		right = std::distance(c.begin(), it);
	}
	std::size_t left = 0;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (c[mid] < element)
			left = mid + 1;
		else
			right = mid;
	}
	c.insert(c.begin() + left, element);
}

static std::deque<int> jdeqInsert(std::deque<std::pair <int, int> > &c, int remainder)
{
	if (remainder != -1)
		c.push_back(std::make_pair(-1, remainder));

	std::vector<std::size_t> order;
	std::size_t size = c.size();
	order = insertionOrder(size);
	
	std::deque<int> dSorted;
	if (remainder -= -1)
		size -= 1;	
       	for (std::size_t i = 0; i < size; i++)
		dSorted.push_back(c[i].first);

	for (std::size_t j = 0; j < order.size(); j++)
	{
		std::size_t index = order[j];
		insertElements(dSorted, c[index].second, c[index].first);
	}

	return (dSorted);
}

static std::vector<int> jvecInsert(std::vector<std::pair <int, int> > &c, int remainder)
{
	if (remainder != -1)
		c.push_back(std::make_pair(-1, remainder));

	std::vector<std::size_t> order;
	std::size_t size = c.size();
	order = insertionOrder(size);
	
	std::vector<int> vSorted;
	if (remainder != -1)
		size -= 1;	
       	for (std::size_t i = 0; i < size; i++)
		vSorted.push_back(c[i].first);

	for (std::size_t j = 0; j < order.size(); j++)
	{
		std::size_t index = order[j];
		insertElements(vSorted, c[index].second, c[index].first);
	}

	return (vSorted);
}

PmergeMe::PmergeMe()
	: _deq(0), _vec(0)
{}

PmergeMe::PmergeMe(const std::vector<int>& v)
	: _unsorted(v), _deq(0), _vec(0)
{}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _unsorted(other._unsorted), _deqSorted(other._deqSorted), _vecSorted(other._vecSorted), _deq(other._deq), _vec(other._vec)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_unsorted = other._unsorted;
		_deqSorted = other._deqSorted;
		_vecSorted = other._vecSorted;
		_deq = other._deq;
		_vec = other._vec;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::deqSort()
{
	std::size_t i = _unsorted.size();
	if (i == 1)
	{
		std::deque<int> tmp(_unsorted.begin(), _unsorted.end());
		_deqSorted = tmp;
		return ;
	}

	int remainder = -1;
	if (i % 2 != 0)
	{
		remainder = _unsorted.back();
		i -= 1;
	}

	double start_time = getTime();

	std::deque<std::pair<int, int> > tmp;
	for (std::size_t j = 1; j < i; j += 2)
	{
		int a = _unsorted[j];
		int b = _unsorted[j - 1];
		std::pair<int, int> p;
		p = (a > b) ? std::make_pair(a, b) : std::make_pair(b, a);
		tmp.push_back(p);
	}

	mergeSort(tmp, 0, tmp.size() - 1);
	_deqSorted = jdeqInsert(tmp, remainder);
	_deq = getTime() - start_time;
}

void PmergeMe::vecSort()
{
	std::size_t i = _unsorted.size();
	if (i == 1)
	{
		_vecSorted = _unsorted;
		return ;
	}

	int remainder = -1;
	if (i % 2 != 0)
	{
		remainder = _unsorted.back();
		i -= 1;
	}

	double start_time = getTime();

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
	// for (std::size_t k = 0; k < i/2; k++)
	// 	std::cout << "First: " << tmp[k].first << " Second: " << tmp[k].second << std::endl;
	// if (remainder != -1)
	// 	std::cout << "Remainder: " << remainder << std::endl;
	_vecSorted = jvecInsert(tmp, remainder);
	_vec = getTime() - start_time;
}

void PmergeMe::print()
{
	std::cout << "Before: ";
	for (std::size_t i = 0; i < _unsorted.size(); i++)
		std::cout << " " << _unsorted[i];

	std::cout << "\nAfter: ";
	for (std::size_t i = 0; i < _vecSorted.size(); i++)
		std::cout << " " << _vecSorted[i];

	std::cout << "\nTime to process a range of " << _unsorted.size() 
		<< " elements with std::deque : " << std::fixed << std::setprecision(5) << _deq/1000 << " ms";

	std::cout << "\nTime to process a range of " << _unsorted.size() 
		<< " elements with std::vector : " << std::fixed << std::setprecision(5) << _vec/1000 << " ms" << std::endl;
}
