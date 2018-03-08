#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "ErrorException.hpp"
# include "FactoryMethod.hpp"
# include <sstream>
# include <cfloat>

template<typename T>
class	Operand : public IOperand
{
private	:
	T		_value;
	int		_precision;
	eOperandType	_type;
	std::string	_str;

	Operand(void) : _value(static_cast<T>(0)), _precision(0), _type(Int8) {}

public	:
	Operand(eOperandType type, T & number)
	{
		std::stringstream	ss;

		_value = number;
		ss << number;
		_str = ss.str();
		if (type == Int8)
		{
			_precision = static_cast<int>(sizeof(int8_t));
			_type = Int8;
		}
		else if (type == Int16)
		{
			_precision = static_cast<int>(sizeof(int16_t));
			_type = Int16;
		}
		else if (type == Int32)
		{
			_precision = static_cast<int>(sizeof(int32_t));
			_type = Int32;
		}
		else if (type == Float)
		{
			_precision = static_cast<int>(sizeof(float));
			_type = Float;
		}
		else
		{
			_precision = static_cast<int>(sizeof(double));
			_type = Double;
		}
	}

	Operand(Operand const & operand)
	{
		_value = operand._value;
		_precision = operand._precision;
		_type = operand._type;
	}

	virtual ~Operand(void) {}

	Operand &	operator=(Operand const & operand)
	{
		_value = operand._value;
		_precision = operand._precision;
		_type = operand._type;
		return (*this);
	}

	virtual int getPrecision( void ) const
	{
		return (_precision);
	}

	virtual eOperandType getType( void ) const
	{
		return (_type);
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		int		type = (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision();
		FactoryMethod	factoryMethod;
		std::stringstream	ss;

		if (type == static_cast<int>(sizeof(int8_t)))
		{
			int	valueInt8 = std::atoi(rhs.toString().c_str());

			if (_value + valueInt8 > 127)
				throw ErrorException("Error: Overflow");
			else if (_value + valueInt8 < -128)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt8 += _value;
				ss << valueInt8;
				return (factoryMethod.createOperand(Int8, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int16_t)))
		{
			int	valueInt16 = std::atoi(rhs.toString().c_str());

			if (_value + valueInt16 > 32767)
				throw ErrorException("Error: Overflow");
			else if (_value + valueInt16 < -32768)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt16 += _value;
				ss << valueInt16;
				return (factoryMethod.createOperand(Int16, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int32_t)))
		{
			long	valueInt32 = std::atol(rhs.toString().c_str());

			if (_value + valueInt32 > 2147483647)
				throw ErrorException("Error: Overflow");
			else if (_value + valueInt32 < -2147483648)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt32 += _value;
				ss << valueInt32;
				return (factoryMethod.createOperand(Int32, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(float)))
		{
			double	valueFloat = std::atof(rhs.toString().c_str());

			if (_value + valueFloat > FLT_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value + valueFloat < FLT_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueFloat += _value;
				ss << valueFloat;
				return (factoryMethod.createOperand(Float, ss.str()));
			}
		}
		else
		{
			long double	valueDouble = std::strtold(rhs.toString().c_str(), NULL);

			if (_value + valueDouble > DBL_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value + valueDouble < DBL_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueDouble += _value;
				ss << valueDouble;
				return (factoryMethod.createOperand(Double, ss.str()));
			}
		}
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		int		type = (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision();
		FactoryMethod	factoryMethod;
		std::stringstream	ss;

		if (type == static_cast<int>(sizeof(int8_t)))
		{
			int	valueInt8 = std::atoi(rhs.toString().c_str());

			if (_value - valueInt8 > 127)
				throw ErrorException("Error: Overflow");
			else if (_value - valueInt8 < -128)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt8 += _value;
				ss << valueInt8;
				return (factoryMethod.createOperand(Int8, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int16_t)))
		{
			int	valueInt16 = std::atoi(rhs.toString().c_str());

			if (_value - valueInt16 > 32767)
				throw ErrorException("Error: Overflow");
			else if (_value - valueInt16 < -32768)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt16 += _value;
				ss << valueInt16;
				return (factoryMethod.createOperand(Int16, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int32_t)))
		{
			long	valueInt32 = std::atol(rhs.toString().c_str());

			if (_value - valueInt32 > 2147483647)
				throw ErrorException("Error: Overflow");
			else if (_value - valueInt32 < -2147483648)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt32 += _value;
				ss << valueInt32;
				return (factoryMethod.createOperand(Int32, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(float)))
		{
			double	valueFloat = std::atof(rhs.toString().c_str());

			if (_value - valueFloat > FLT_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value - valueFloat < FLT_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueFloat += _value;
				ss << valueFloat;
				return (factoryMethod.createOperand(Float, ss.str()));
			}
		}
		else
		{
			long double	valueDouble = std::strtold(rhs.toString().c_str(), NULL);

			if (_value - valueDouble > DBL_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value - valueDouble < DBL_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueDouble += _value;
				ss << valueDouble;
				return (factoryMethod.createOperand(Double, ss.str()));
			}
		}
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		int		type = (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision();
		FactoryMethod	factoryMethod;
		std::stringstream	ss;

		if (type == static_cast<int>(sizeof(int8_t)))
		{
			int	valueInt8 = std::atoi(rhs.toString().c_str());

			if (_value * valueInt8 > 127)
				throw ErrorException("Error: Overflow");
			else if (_value * valueInt8 < -128)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt8 += _value;
				ss << valueInt8;
				return (factoryMethod.createOperand(Int8, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int16_t)))
		{
			int	valueInt16 = std::atoi(rhs.toString().c_str());

			if (_value * valueInt16 > 32767)
				throw ErrorException("Error: Overflow");
			else if (_value * valueInt16 < -32768)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt16 += _value;
				ss << valueInt16;
				return (factoryMethod.createOperand(Int16, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(int32_t)))
		{
			long	valueInt32 = std::atol(rhs.toString().c_str());

			if (_value * valueInt32 > 2147483647)
				throw ErrorException("Error: Overflow");
			else if (_value * valueInt32 < -2147483648)
				throw ErrorException("Error: Underflow");
			else
			{
				valueInt32 += _value;
				ss << valueInt32;
				return (factoryMethod.createOperand(Int32, ss.str()));
			}
		}
		else if (type == static_cast<int>(sizeof(float)))
		{
			double	valueFloat = std::atof(rhs.toString().c_str());

			if (_value * valueFloat > FLT_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value * valueFloat < FLT_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueFloat += _value;
				ss << valueFloat;
				return (factoryMethod.createOperand(Float, ss.str()));
			}
		}
		else
		{
			long double	valueDouble = std::strtold(rhs.toString().c_str(), NULL);

			if (_value * valueDouble > DBL_MAX)
				throw ErrorException("Error: Overflow");
			else if (_value * valueDouble < DBL_MIN)
				throw ErrorException("Error: Underflow");
			else
			{
				valueDouble += _value;
				ss << valueDouble;
				return (factoryMethod.createOperand(Double, ss.str()));
			}
		}
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		int		type = (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision();
		FactoryMethod	factoryMethod;
		std::stringstream	ss;

		if (type == static_cast<int>(sizeof(int8_t)))
		{
			int	valueInt8 = std::atoi(rhs.toString().c_str());

			if (!valueInt8)
				throw ErrorException("Error: Division by zero");
			else
			{
				if (_value / valueInt8 > 127)
					throw ErrorException("Error: Overflow");
				else if (_value / valueInt8 < -128)
					throw ErrorException("Error: Underflow");
				else
				{
					valueInt8 += _value;
					ss << valueInt8;
					return (factoryMethod.createOperand(Int8, ss.str()));
				}
			}
		}
		if (type == static_cast<int>(sizeof(int16_t)))
		{
			int	valueInt16 = std::atoi(rhs.toString().c_str());

			if (!valueInt16)
				throw ErrorException("Error: Division by zero");
			else
			{
				if (_value / valueInt16 > 32767)
					throw ErrorException("Error: Overflow");
				else if (_value / valueInt16 < -32768)
					throw ErrorException("Error: Underflow");
				else
				{
					valueInt16 += _value;
					ss << valueInt16;
					return (factoryMethod.createOperand(Int8, ss.str()));
				}
			}
		}
		if (type == static_cast<int>(sizeof(int32_t)))
		{
			long	valueInt32 = std::atol(rhs.toString().c_str());

			if (!valueInt32)
				throw ErrorException("Error: Division by zero");
			else
			{
				if (_value / valueInt32 > 2147483647)
					throw ErrorException("Error: Overflow");
				else if (_value / valueInt32 < -2147483648)
					throw ErrorException("Error: Underflow");
				else
				{
					valueInt32 += _value;
					ss << valueInt32;
					return (factoryMethod.createOperand(Int8, ss.str()));
				}
			}
		}
		else if (type == static_cast<int>(sizeof(float)))
		{
			double	valueFloat = std::atof(rhs.toString().c_str());

			if (!valueFloat)
				throw ErrorException("Error: Division by zero");
			else
			{
				if (_value / valueFloat > FLT_MAX)
					throw ErrorException("Error: Overflow");
				else if (_value / valueFloat < FLT_MIN)
					throw ErrorException("Error: Underflow");
				else
				{
					valueFloat += _value;
					ss << valueFloat;
					return (factoryMethod.createOperand(Float, ss.str()));
				}
			}
		}
		else
		{
			long double	valueDouble = std::strtold(rhs.toString().c_str(), NULL);

			if (!valueDouble)
				throw ErrorException("Error: Division by zero");
			else
			{
				if (_value / valueDouble > DBL_MAX)
					throw ErrorException("Error: Overflow");
				else if (_value / valueDouble < DBL_MIN)
					throw ErrorException("Error: Underflow");
				else
				{
					valueDouble += _value;
					ss << valueDouble;
					return (factoryMethod.createOperand(Double, ss.str()));
				}
			}
		}
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		int		type = (getPrecision() > rhs.getPrecision()) ? getPrecision() : rhs.getPrecision();
		FactoryMethod	factoryMethod;
		std::stringstream	ss;

		if (type == static_cast<int>(sizeof(float)) || type == static_cast<int>(sizeof(double)))
			throw ErrorException("Error: Invalid operands to binary %");
		else
		{
			if (type == static_cast<int>(sizeof(int8_t)))
			{
				int	valueInt8 = std::atoi(rhs.toString().c_str());

				if (!valueInt8)
					throw ErrorException("Error: Modulo by zero");
				else
				{
					valueInt8 = static_cast<int8_t>(_value) % static_cast<int8_t>(valueInt8);
					ss << valueInt8;
					return (factoryMethod.createOperand(Int8, ss.str()));
				}
			}
			else if (type == static_cast<int>(sizeof(int16_t)))
			{
				int	valueInt16 = std::atoi(rhs.toString().c_str());

				if (!valueInt16)
					throw ErrorException("Error: Modulo by zero");
				else
				{
					valueInt16 = static_cast<int16_t>(_value) % static_cast<int16_t>(valueInt16);
					ss << valueInt16;
					return (factoryMethod.createOperand(Int16, ss.str()));
				}
			}
			else
			{
				long	valueInt32 = std::atol(rhs.toString().c_str());

				if (!valueInt32)
					throw ErrorException("Error: Modulo by zero");
				else
				{
					valueInt32 = static_cast<int32_t>(_value) % static_cast<int32_t>(valueInt32);
					ss << valueInt32;
					return (factoryMethod.createOperand(Int32, ss.str()));
				}
			}
		}
	}

	virtual std::string const & toString( void ) const
	{
		return (_str);
	}
};
#endif
