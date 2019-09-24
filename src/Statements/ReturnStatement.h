#pragma once

#include "Statement.h"
#include "..\Constants.h"

#include <exception>

class ReturnStatement : public Statement, public std::exception {

public:
	Expression* m_valueToReturn;
	ValueType* m_calculatedValue;

	ReturnStatement(Expression* valueToReturn) : m_valueToReturn(valueToReturn) {}

	ValueType* getValue() {
		return m_calculatedValue;
	}

	void execute() {
		m_calculatedValue = m_valueToReturn->eval();
		throw this;
	}


};