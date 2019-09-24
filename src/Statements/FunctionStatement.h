#pragma once

#include "Statement.h"
#include "..\Constants.h"

class FunctionStatement : public Statement {

public:
	FunctionExpression* m_funcExpression;

	FunctionStatement(FunctionExpression* funcExpression) : m_funcExpression(funcExpression) {}


	void execute() {
		m_funcExpression->eval();

	}


};