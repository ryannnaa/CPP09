#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <deque>

class PmergeMe
{
	private:
		std::vector<int> _unsorted;
		std::deque<int> _deqSorted;
		std::vector<int> _vecSorted;		
		double _deq;
		double _vec;
	public:
		PmergeMe();
		PmergeMe(const std::vector<int>& v);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void vecSort();
		void deqSort();
		void print();
};


#endif
