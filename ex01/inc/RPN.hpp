#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
	private:
		std::stack<int> _items;
		void applyOperator(const std::string& op);
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void calculate(const std::string& input);
		int getResult() const;
};

#endif
