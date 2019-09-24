#pragma once

#pragma once
#include <vector>
#include <string>

#include "Expression.h"


/*
	Conditional Expression
	Takes two other expressions and operation in constructor, and then does corresponding operation to them
*/

class ConditionalExpression : public Expression {
public:
	static enum OPERATION {
		NOT_EQUAL_EQUAL = 0,
		EQUAL_EQUAL,
		GREATER,
		GREATER_EQUAL_EQUAL,
		LESS,
		LESS_EQUAL_EQUAL,
		_AND,
		_OR,
		_LOGICAL_AND, // &&
		_LOGICAL_OR // ||
	};


	int m_operation; // "==", "&", '|', "&&", '||'
	Expression* m_first;
	Expression* m_second;


	ConditionalExpression(int operation, Expression* first, Expression* second) : m_operation(operation), m_first(first), m_second(second) {}

	//Calculate expression
	ValueType* eval() {
		ValueType* value1 = m_first->eval();
		ValueType* value2 = m_second->eval();
		if (typeid(*value1) == typeid(StringValue)) {

			switch (m_operation)
			{
			case OPERATION::EQUAL_EQUAL: {
				return new NumberValue(value1->asString() == value2->asString());
			}
			case OPERATION::NOT_EQUAL_EQUAL: {
				return new NumberValue(value1->asString() != value2->asString());
			}

			default:
				return new StringValue(""); //EXCEPTION
			}
		}
		else {

			switch (m_operation)
			{
			case OPERATION::EQUAL_EQUAL: {
				return new NumberValue(value1->asDouble() == value2->asDouble());
			}
			case OPERATION::NOT_EQUAL_EQUAL: {
				return new NumberValue(value1->asDouble() != value2->asDouble());
			}
			case OPERATION::GREATER: {
				return new NumberValue(value1->asDouble() > value2->asDouble());
			}
			case OPERATION::GREATER_EQUAL_EQUAL: {
				return new NumberValue(value1->asDouble() >= value2->asDouble());
			}
			case OPERATION::LESS: {
				return new NumberValue(value1->asDouble() < value2->asDouble());
			}
			case OPERATION::LESS_EQUAL_EQUAL: {
				return new NumberValue(value1->asDouble() <= value2->asDouble());
			}

			case OPERATION::_AND:
				return new NumberValue(int(value1->asDouble()) & int(value2->asDouble()));
			case OPERATION::_LOGICAL_AND:
				return new NumberValue(value1->asDouble() && value2->asDouble());
			case OPERATION::_OR:
				return new NumberValue(int(value1->asDouble()) | int(value2->asDouble()));
			case OPERATION::_LOGICAL_OR:
				return new NumberValue(value1->asDouble() || value2->asDouble());


			default:
				return new NumberValue(value1->asDouble() == value2->asDouble());
			}
		}
	}

};