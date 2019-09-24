#pragma once

#include "Statement.h"
#include "..\Constants.h"

class DoWhileStatement : public Statement {

public:
	Expression* condition;
	Statement* statementBlock;

	DoWhileStatement(Statement* statementBlock, Expression* condition) : statementBlock(statementBlock), condition(condition) {}


	void execute() {
		do {
			statementBlock->execute();
		} while (condition->eval()->asDouble());
	}


};