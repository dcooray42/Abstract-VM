#include "ErrorException.hpp"

ErrorException::ErrorException(void) : _str("\0")
{
}

ErrorException::ErrorException(std::string const & str) : _str(str)
{
}
/*
ErrorException::ErrorException(ErrorException const & errorException)
{
	*this = errorException;
}*/

ErrorException::~ErrorException(void) throw()
{
}

ErrorException &	ErrorException::operator=(ErrorException const & errorException)
{
	_str = errorException._str;
	return (*this);
}

const char *	ErrorException::what(void) const throw()
{
	return (_str.c_str());
}
