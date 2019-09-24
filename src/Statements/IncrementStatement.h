#pragma once

#include "Statement.h"
#include "..\Constants.h"

class IncrementStatement : public Statement {

public:
	std::string m_name;
	Expression* m_value;

	IncrementStatement(std::string name, Expression* value) : m_name(name), m_value(value) {}


	void execute() {
		ValueType* value = m_value->eval();
		if (typeid(*value) == typeid(NumberValue)) {
			variables[m_name] = new NumberValue(variables[m_name]->asDouble() + m_value->eval()->asDouble());
		}
		else if (typeid(*value) == typeid(StringValue)) {
			variables[m_name] = new StringValue(variables[m_name]->asString() + m_value->eval()->asString());
		}
	}


};