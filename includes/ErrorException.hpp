#ifndef ERROREXCEPTION_HPP
# define ERROREXCEPTION_HPP

# include <exception>
# include <string>

class	ErrorException : public std::exception
{
public	:
	ErrorException(std::string const & str);
	virtual ~ErrorException(void) throw();

	const char *	what(void) const throw();

private	:
	ErrorException(void);
//	ErrorException(ErrorException const & errorException);
	ErrorException &	operator=(ErrorException const & errorException);

	std::string	_str;
};
#endif
