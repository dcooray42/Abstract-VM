# include "NamespaceAbstractVM.hpp"

void	AbstractVM::AbstractVM(int argc, char **argv)
{
	try
	{
		(void)argv;
		if (argc == 1)
			AbstractVM::withoutFile();
//		else if (argc == 2)
//			AbstractVM::withFile(argv[1]);
		else
			throw ErrorException("Error: Too many files");
	}
	catch (std::exception const & error)
	{
		std::cerr << error.what() << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void	AbstractVM::withoutFile(void)
{
	std::list<std::string> lst;
	std::string	str;

	while (std::getline(std::cin, str))
	{
		lst.push_back(str);
		if (!str.compare(";;"))
			break ;
	}
	try
	{
		if (str.compare(";;"))
			throw ErrorException("Error: Syntax");
	}
	catch (std::exception const & error)
	{
		std::cerr << error.what() << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	parser(lst);
}

void	AbstractVM::parser(std::list<std::string> & lst)
{
	std::list<IOperand const *> instructions;
	int	i = 1;
	int	status;
	std::list<std::string>::iterator	it;
	std::list<std::string>::iterator	ite = lst.end();
	std::string	str;

	for (it = lst.begin(); it != ite; it++)
	{
		str = *it;
		try
		{
			status = 0;
			status |= push(str, instructions);
			status |= pop(str, instructions);
			status |= dump(str, instructions);
			status |= assert(str, instructions);
			status |= (!str.compare(";;") ? 1 : 0);
			if (!status)
				throw ErrorException("Error: Syntax");
		}
		catch (std::exception const & error)
		{
			std::cerr << "Line " << i << ": " << error.what() << std::endl;
			std::exit(EXIT_SUCCESS);
		}
		i++;
	}
	flush(instructions);
}

int	AbstractVM::push_assert(std::string str, std::list<IOperand const *> & instructions)
{
	FactoryMethod	factoryMethod;

	if (!str.compare(0, 5, "int8("))
	{
		int	i = 0;

		str.erase(0, 5);
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (std::isdigit(str[i]))
			i++;
		if (str[i] != ')' || i == 0 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int8, str.substr(0, i)));
		return (1);
	}
	else if (!str.compare(0, 6, "int16("))
	{
		int	i = 0;

		str.erase(0, 6);
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (std::isdigit(str[i]))
			i++;
		if (str[i] != ')' || i == 0 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int16, str.substr(0, i)));
		return (1);
	}
	else if (!str.compare(0, 6, "int32("))
	{
		int	i = 0;

		str.erase(0, 6);
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (std::isdigit(str[i]))
			i++;
		if (str[i] != ')' || i == 0 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int32, str.substr(0, i)));
		return (1);
	}
	else if (!str.compare(0, 6, "float("))
	{
		int	i = 0;
		int	point = 0;

		str.erase(0, 6);
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (std::isdigit(str[i]) || str[i] == '.')
		{
			if (str[i] == '.')
				point++;
			i++;
		}
		if (str[i] != ')' || i == 0 || point > 1 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
			return (0);
		instructions.push_front(factoryMethod.createOperand(Float, str.substr(0, i)));
		return (1);
	}
	else if (!str.compare(0, 7, "double("))
	{
		int	i = 0;
		int	point = 0;

		str.erase(0, 7);
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (std::isdigit(str[i]) || str[i] == '.')
		{
			if (str[i] == '.')
				point++;
			i++;
		}
		if (str[i] != ')' || i == 0 || point > 1 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
			return (0);
		instructions.push_front(factoryMethod.createOperand(Double, str.substr(0, i)));
		return (1);
	}
	else
		return (0);
}

int	AbstractVM::push(std::string str, std::list<IOperand const *> & instructions)
{
	FactoryMethod	factoryMethod;

	if (!str.compare(0, 5, "push "))
	{
		str.erase(0, 5);
		if (push_assert(str, instructions))
			return (1);
		return (0);
	}
	return (0);
}

int	AbstractVM::pop(std::string str, std::list<IOperand const *> & instructions)
{
	if (!str.compare("pop"))
	{
		if (instructions.size() < 2)
			throw ErrorException("Error: Empty");
		instructions.pop_front();
		return (1);
	}
	return (0);
}

int	AbstractVM::dump(std::string str, std::list<IOperand const *> & instructions)
{
	std::list<IOperand const *>::iterator	it;
	std::list<IOperand const *>::iterator	ite = instructions.end();
	IOperand const	*operand;

	if (!str.compare("dump"))
	{
		for (it = instructions.begin(); it != ite; it++)
		{
			operand = *it;
			std::cout << operand->toString() << std::endl;
		}
		return (1);
	}
	return (0);
}

int	AbstractVM::assert(std::string str, std::list<IOperand const *> & instructions)
{
	std::list<IOperand const *>	tmp;
	IOperand const	*v1;
	IOperand const	*v2;

	if (instructions.size() < 1)
		throw ErrorException("Error: Empty");
	v1 = instructions.front();
	if (!str.compare(0, 7, "assert "))
	{
		str.erase(0, 7);
		if (push_assert(str, tmp))
		{
			v2 = tmp.front();
			if (v1->getPrecision() != v2->getPrecision() || v1->getType() != v2->getType() ||
				v1->toString().compare(v2->toString()))
				throw ErrorException("Error: Assert failed");
			delete v2;
			return (1);
		}
	}
	return (0);
}

void	AbstractVM::flush(std::list<IOperand const *> & instructions)
{
	std::list<IOperand const *>::iterator	it;
	std::list<IOperand const *>::iterator	ite = instructions.end();
	IOperand const	*operand;

	for (it = instructions.begin(); it != ite; it++)
	{
		operand = *it;
		delete operand;
	}
}
