# include "NamespaceAbstractVM.hpp"

void	AbstractVM::AbstractVM(int argc, char **argv)
{
	try
	{
		if (argc == 1)
			AbstractVM::withoutFile();
		else if (argc == 2)
			AbstractVM::withFile(argv);
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
	std::list<std::string>	lst;
	std::list<std::string>::iterator	ite;
	std::string	str;
	int	exitValue = 0;

	while (std::getline(std::cin, str))
	{
		lst.push_back(str);
		if (!str.compare(0, 4, "exit"))
			exitValue++;
		if (!str.compare(";;"))
			break ;
	}
	try
	{
		ite = --lst.end();
		if (str.compare(";;") || exitValue != 1 || (*--ite).compare(0, 4, "exit") ||
			((*ite)[4] != '\n' && (*ite)[4] != '\0' && ((*ite).compare(4, 2, " ;") || str[6] == ';')))
			throw ErrorException("Error: Syntax");
	}
	catch (std::exception const & error)
	{
		std::cerr << error.what() << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	parser(lst);
}

void	AbstractVM::withFile(char **argv)
{
	std::ifstream	ifs;
	std::list<std::string>	lst;
	std::list<std::string>::iterator	ite;
	std::string	str;
	std::stringstream	ss;
	int	exitValue = 0;

	errno = 0;
	ifs.open(argv[1]);
	if (!errno)
	{
		while (std::getline(ifs, str))
		{
			lst.push_back(str);
			if (!str.compare(0, 4, "exit"))
				exitValue++;
		}
		try
		{
			ifs.close();
			if (errno == EISDIR)
			{
				ss << argv[0] << ": " << argv[1] << ": " << std::strerror(errno);
				throw ErrorException(ss.str().c_str());
			}
			ite = --lst.end();
			if (exitValue != 1 || (*ite).compare(0, 4, "exit") ||
				((*ite)[4] != '\n' && (*ite)[4] != '\0' && ((*ite).compare(4, 2, " ;") || str[6] == ';')))
				throw ErrorException("Error: Syntax");
		}
		catch (std::exception const & error)
		{
			std::cerr << error.what() << std::endl;
			std::exit(EXIT_SUCCESS);
		}
	}
	else
	{
		try
		{
			ss << argv[0] << ": " << argv[1] << ": " << std::strerror(errno);
			throw ErrorException(ss.str().c_str());
		}
		catch (std::exception const & error)
		{
			std::cerr << error.what() << std::endl;
			std::exit(EXIT_SUCCESS);
		}
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
			status |= add(str, instructions);
			status |= sub(str, instructions);
			status |= mul(str, instructions);
			status |= div(str, instructions);
			status |= mod(str, instructions);
			status |= print(str, instructions);
			status |= (!str.compare(0, 1, ";") && str[1] != ';' ? 1 : 0);
			if (!str.compare(0, 4, "exit"))
				 break;
			if (!status)
				throw ErrorException("Error: Syntax");
		}
		catch (std::exception const & error)
		{
			std::cerr << "Line " << i << ": " << error.what() << std::endl;
			flush(instructions);
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
		if (str[i] != ')' || i == 0)
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int8, str.substr(0, i)));
		str.erase(0, i + 1);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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
		if (str[i] != ')' || i == 0)
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int16, str.substr(0, i)));
		str.erase(0, i + 1);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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
		if (str[i] != ')' || i == 0)
			return (0);
		instructions.push_front(factoryMethod.createOperand(Int32, str.substr(0, i)));
		str.erase(0, i + 1);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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
		if (str[i] != ')' || i == 0 || point > 1)
			return (0);
		instructions.push_front(factoryMethod.createOperand(Float, str.substr(0, i)));
		str.erase(0, i + 1);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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
		if (str[i] != ')' || i == 0 || point > 1)
			return (0);
		instructions.push_front(factoryMethod.createOperand(Double, str.substr(0, i)));
		str.erase(0, i + 1);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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
	if (!str.compare(0, 3, "pop"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 1)
			throw ErrorException("Error: Pop: Empty stack");
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

	if (!str.compare(0, 4, "dump"))
	{
		str.erase(0, 4);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
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

	v1 = instructions.front();
	if (!str.compare(0, 7, "assert "))
	{
		if (instructions.size() < 1)
			throw ErrorException("Error: Assert: Empty stack");
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

int	AbstractVM::add(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*v1;
	IOperand const	*v2;
	IOperand const	*rslt;

	if (!str.compare(0, 3, "add"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 2)
			throw ErrorException("Error: Add: Stack less than 2 values");
		v2 = instructions.front();
		instructions.pop_front();
		v1 = instructions.front();
		instructions.pop_front();
		rslt = *v1 + *v2;
		delete v1;
		delete v2;
		instructions.push_front(rslt);
		return (1);
	}
	return (0);
}

int	AbstractVM::sub(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*v1;
	IOperand const	*v2;
	IOperand const	*rslt;

	if (!str.compare(0, 3, "sub"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 2)
			throw ErrorException("Error: Sub: Stack contains less than 2 values");
		v2 = instructions.front();
		instructions.pop_front();
		v1 = instructions.front();
		instructions.pop_front();
		rslt = *v1 - *v2;
		delete v1;
		delete v2;
		instructions.push_front(rslt);
		return (1);
	}
	return (0);
}

int	AbstractVM::mul(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*v1;
	IOperand const	*v2;
	IOperand const	*rslt;

	if (!str.compare(0, 3, "mul"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 2)
			throw ErrorException("Error: Mul: Stack constains less than 2 values");
		v2 = instructions.front();
		instructions.pop_front();
		v1 = instructions.front();
		instructions.pop_front();
		rslt = *v1 * *v2;
		delete v1;
		delete v2;
		instructions.push_front(rslt);
		return (1);
	}
	return (0);
}

int	AbstractVM::div(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*v1;
	IOperand const	*v2;
	IOperand const	*rslt;

	if (!str.compare(0, 3, "div"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 2)
			throw ErrorException("Error: Div: Stack constains less than 2 values");
		v2 = instructions.front();
		instructions.pop_front();
		v1 = instructions.front();
		instructions.pop_front();
		rslt = *v1 / *v2;
		delete v1;
		delete v2;
		instructions.push_front(rslt);
		return (1);
	}
	return (0);
}

int	AbstractVM::mod(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*v1;
	IOperand const	*v2;
	IOperand const	*rslt;

	if (!str.compare(0, 3, "mod"))
	{
		str.erase(0, 3);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 2)
			throw ErrorException("Error: Mod: Stack contains less than 2 values");
		v2 = instructions.front();
		instructions.pop_front();
		v1 = instructions.front();
		instructions.pop_front();
		rslt = *v1 % *v2;
		delete v1;
		delete v2;
		instructions.push_front(rslt);
		return (1);
	}
	return (0);
}

int	AbstractVM::print(std::string str, std::list<IOperand const *> & instructions)
{
	IOperand const	*operand;
	int8_t		value;

	if (!str.compare(0, 5, "print"))
	{
		str.erase(0, 5);
		if (str[0] != '\n' && str[0] != '\0' && (str.compare(0, 2, " ;") || str[2] == ';'))
			return (0);
		if (instructions.size() < 1)
			throw ErrorException("Error: Print: Empty stack");
		operand = instructions.front();
		if (operand->getType() != Int8)
			throw ErrorException("Error: Print: Value different from Int8");
		value = static_cast<int8_t>(std::atoi(operand->toString().c_str()));
		if (value < 32 || value > 126)
			throw ErrorException("Error: Print: Value non printable");
		std::cout << value << std::endl;
		return (1);
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
