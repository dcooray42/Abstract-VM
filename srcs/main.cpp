#include "Operand.hpp"
#include "FactoryMethod.hpp"
#include "ErrorException.hpp"
#include <iostream>

int	main(void)
{
	try
	{
		int	i = 5;
		if (i < 0)
			throw ErrorException("Nique ta mere");
	}
	catch (std::exception const & out)
	{
		std::cerr << out.what() << std::endl;
	}
	return (0);
}
