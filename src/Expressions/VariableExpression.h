#pragma once

#include "..\Constants.h"
#include "Expression.h"

#include "..\ValueTypes.h"

/*
	Variable Expression
	Just takes an name of the variable and then return number in variables array with corresponding name
*/

class VariableExpression : public Expression {

public:
	std::string m_name;

	VariableExpression(std::string name) : m_name(name) {
		
	}

	
	ValueType* eval() {
		return variables[m_name];
	}


};