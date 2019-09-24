#pragma once

#pragma once
#include <vector>
#include <string>

#include "Expression.h"


/*
	Binary Expression
	Takes two other expressions and operation in constructor, and then does corresponding operation to them
*/

class BinaryExpression : public Expression {
public:

	char m_operation; // '+', '-', '*', '/'
	Expression* m_first;
	Expression* m_second;


	BinaryExpression(char operation, Expression* first, Expression* second) : m_operation(operation), m_first(first), m_second(second) {}

	//Calculate expression
	ValueType* eval() {
		ValueType* value1 = m_first->eval();
		ValueType* value2 = m_second->eval();
		if (typeid(*value1) == typeid(StringValue)) {
			switch (m_operation)
			{
			case '+':
				return new StringValue(value1->asString() + value2->asString());
			case '*':
			{
				std::string str = "";
				std::string refStr = value1->asString();
				int times = value2->asDouble();
				for (int i = 0; i < times; i++) {
					str += refStr;
				}

				return new StringValue(str);
			}

			default:
				return new StringValue(""); //EXCEPTION
			}
		}
		else {

			switch (m_operation)
			{
			case '+': {
				if (typeid(*value2) == typeid(StringValue)) {

					return new StringValue(value1->asString() + value2->asString());
				}
				return new NumberValue(value1->asDouble() + value2->asDouble());
			}
			case '-':
				return new NumberValue(value1->asDouble() - value2->asDouble());
			case '*':
				return new NumberValue(value1->asDouble() * value2->asDouble());
			case '/':
				return new NumberValue(value1->asDouble() / value2->asDouble());

			default:
				return new NumberValue(value1->asDouble() + value2->asDouble());
			}
		}
	}

};