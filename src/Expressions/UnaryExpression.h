#pragma once
#include <vector>
#include <string>

#include "Expression.h"


/*
	Unary Expression
	Takes expression and operation in constructor, and then does corresponding operation to expression
*/

class UnaryExpression : public Expression {
public:
	char m_operation; // '+', '-', '!' (Logical not)
	Expression* m_expr;


	UnaryExpression(char operation, Expression* expr) : m_operation(operation), m_expr(expr) {}

	ValueType* eval() {
		switch (m_operation)
		{
		case '+': //Its equals number itself
			return new NumberValue(m_expr->eval()->asDouble());
		case '-':
			return new NumberValue(-m_expr->eval()->asDouble());
		case '!':
			return new NumberValue(!m_expr->eval()->asDouble());
		default:
			return new NumberValue(m_expr->eval()->asDouble());
		}
		
	}

};