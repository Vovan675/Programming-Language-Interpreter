#pragma once
#include <vector>
#include <string>

#include "Expression.h"


#include "..\ValueTypes.h"



/*
	Value Expression
*/

class ValueExpression : public Expression {
public:
	ValueType* m_value;

	ValueExpression(double value) : m_value(new NumberValue(value)) {}
	ValueExpression(std::string value) : m_value(new StringValue(value)) {}

	ValueType* eval() {
		return m_value;
	}

};