#ifndef NAMESPACEABSTRACTVM_HPP
# define NAMESPACEABSTRACTVM_HPP

# include "Operand.hpp"
# include "FactoryMethod.hpp"
# include "ErrorException.hpp"
# include <list>
# include <fstream>
# include <iostream>
# include <cctype>

namespace	AbstractVM
{
	void	AbstractVM(int argc, char **argv);
	void	withoutFile(void);
	void	withFile(char *argv);
	void	parser(std::list<std::string> & lst);
	int	push_assert(std::string str, std::list<IOperand const *> & instructions);
	int	push(std::string str, std::list<IOperand const *> & instructions);
	int	pop(std::string str, std::list<IOperand const *> & instructions);
	int	dump(std::string str, std::list<IOperand const *> & instructions);
	int	assert(std::string str, std::list<IOperand const *> & instructions);
	void	flush(std::list<IOperand const *> & instructions);
};
#endif
