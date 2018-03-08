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

	try
	{
		status = 0;
		status |= push(lst, instructions);
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

int	AbstractVM::push(std::list<std::string> & lst, std::list<IOperand const *> & instructions)
{
	FactoryMethod	factoryMethod;
	std::string	str = lst.front();

	if (!str.compare(0, 5, "push "))
	{
		str.erase(0, 5);
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
			lst.pop_front();
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
			lst.pop_front();
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
			lst.pop_front();
			return (1);
		}
		else if (!str.compare(0, 6, "float("))
		{
			int	i = 0;
			int	point = 0;

			str.erase(0, 6);
			if (str[i] == '-' || str[i] == '+')
				i++;
			while (std::isdigit(str[i]) && str[i] == '.')
			{
				if (str[i] == '.')
					point++;
				i++;
			}
			if (str[i] != ')' || i == 0 || point > 1 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
				return (0);
			instructions.push_front(factoryMethod.createOperand(Float, str.substr(0, i)));
			lst.pop_front();
			return (1);
		}
		else if (!str.compare(0, 7, "double("))
		{
			int	i = 0;
			int	point = 0;

			str.erase(0, 6);
			if (str[i] == '-' || str[i] == '+')
				i++;
			while (std::isdigit(str[i]) && str[i] == '.')
			{
				if (str[i] == '.')
					point++;
				i++;
			}
			if (str[i] != ')' || i == 0 || point > 1 || (str[i + 1] != '\n' && str[i + 1] != '\0'))
				return (0);
			instructions.push_front(factoryMethod.createOperand(Double, str.substr(0, i)));
			lst.pop_front();
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}
