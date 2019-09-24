#pragma once

#include "Statement.h"
#include "..\Constants.h"

class WhileStatement : public Statement {

public:
	Expression* condition;
	Statement* statementBlock;

	WhileStatement(Expression* condition, Statement* statementBlock) : condition(condition), statementBlock(statementBlock) {}


	void execute() {
		while (condition->eval()->asDouble()) {
			statementBlock->execute();
		}
	}


};