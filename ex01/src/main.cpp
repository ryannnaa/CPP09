#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./RPN <expression>" << std::endl;
		return (1);
	}
	try
	{
		RPN rpn;
		rpn.calculate(argv[1]);
		int result = rpn.getResult();
		std::cout << result << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
