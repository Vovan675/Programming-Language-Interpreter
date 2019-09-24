#pragma once

#include "Statement.h"
#include "..\Constants.h"

class AssignStatement : public Statement {

public:
	std::string m_name;
	Expression* m_value;

	AssignStatement(std::string name, Expression* value) : m_name(name), m_value(value) {}


	void execute() {
		variables[m_name] = m_value->eval();
	}


};