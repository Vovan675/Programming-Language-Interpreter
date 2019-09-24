#pragma once

#include "Statement.h"
#include "..\Constants.h"

class ForStatement : public Statement {

public:
	Statement* initializationBlock;
	Expression* condition;
	Statement* incrementBlockStatement;
	Statement* statementBlock;

	ForStatement(Statement* initializationBlock, Expression* condition, Statement* incrementBlockStatement, Statement* statementBlock) 
		: initializationBlock(initializationBlock), condition(condition), incrementBlockStatement(incrementBlockStatement), statementBlock(statementBlock) {}


	void execute() {
		for (initializationBlock->execute(); condition->eval()->asDouble(); incrementBlockStatement->execute()) {
			statementBlock->execute();
		}
	}


};