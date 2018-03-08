#ifndef FACTORYMETHOD_HPP
# define FACTORYMETHOD_HPP

# include "IOperand.hpp"

class	FactoryMethod
{
public	:
	FactoryMethod(void);
	~FactoryMethod(void);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private	:
	IOperand const * (FactoryMethod::*_f[5])(std::string const &) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};
#endif
