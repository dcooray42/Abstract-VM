#include "FactoryMethod.hpp"
#include "Operand.hpp"

FactoryMethod::FactoryMethod(void)
{
	_f[0] = &FactoryMethod::createInt8;
	_f[1] = &FactoryMethod::createInt16;
	_f[2] = &FactoryMethod::createInt32;
	_f[3] = &FactoryMethod::createFloat;
	_f[4] = &FactoryMethod::createDouble;
}

FactoryMethod::~FactoryMethod(void)
{
}

IOperand const *	FactoryMethod::createOperand(eOperandType type, std::string const & value) const
{
	return ((this->*_f[type])(value));
}

IOperand const *	FactoryMethod::createInt8(std::string const & value) const
{
	long long	valueInt8 = std::atoll(value.c_str());

	if (valueInt8 > 127)
		throw ErrorException("Error: Overflow");
	else if (valueInt8 < -128)
		throw ErrorException("Error: Underflow");
	else
	{
		int8_t	tmp = static_cast<int8_t>(valueInt8);
		return (new Operand<int8_t>(Int8, tmp));
	}
}

IOperand const *	FactoryMethod::createInt16(std::string const & value) const
{
	long long	valueInt16 = std::atoll(value.c_str());

	if (valueInt16 > 32767)
		throw ErrorException("Error: Overflow");
	else if (valueInt16 < -32768)
		throw ErrorException("Error: Underflow");
	else
	{
		int16_t	tmp = static_cast<int16_t>(valueInt16);
		return (new Operand<int16_t>(Int16, tmp));
	}
}

IOperand const *	FactoryMethod::createInt32(std::string const & value) const
{
	long long	valueInt32 = std::atoll(value.c_str());

	if (valueInt32 > 2147483647)
		throw ErrorException("Error: Overflow");
	else if (valueInt32 < -2147483648)
		throw ErrorException("Error: Underflow");
	else
	{
		int32_t	tmp = static_cast<int32_t>(valueInt32);
		return (new Operand<int32_t>(Int32, tmp));
	}
}

IOperand const *	FactoryMethod::createFloat(std::string const & value) const
{
	long double	valueFloat = std::strtold(value.c_str(), NULL);

	if (valueFloat > FLT_MAX)
		throw ErrorException("Error: Overflow");
	else if (valueFloat < -FLT_MAX)
		throw ErrorException("Error: Underflow");
	else
	{
		float	tmp = static_cast<float>(valueFloat);
		return (new Operand<float>(Float, tmp));
	}
}

IOperand const *	FactoryMethod::createDouble(std::string const & value) const
{
	long double valueDouble = std::strtold(value.c_str(), NULL);

	if (valueDouble > DBL_MAX)
		throw ErrorException("Error: Overflow");
	else if (valueDouble < -DBL_MAX)
		throw ErrorException("Error: Underflow");
	else
	{
		double	tmp = static_cast<double>(valueDouble);
		return (new Operand<double>(Double, tmp));
	}
}
