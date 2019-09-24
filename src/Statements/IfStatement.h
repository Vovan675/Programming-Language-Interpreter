#pragma once

#include "Statement.h"
#include "..\Constants.h"

class IfStatement : public Statement {

public:
	Expression* condition;
	Statement* ifBlock;
	Statement* elseBlock;

	IfStatement(Expression* condition, Statement* ifBlock, Statement* elseBlock) : condition(condition), ifBlock(ifBlock), elseBlock(elseBlock) {}


	void execute() {
		if (condition->eval()->asDouble()) {
			ifBlock->execute();
		}
		else {
			if (elseBlock != NULL) {
				elseBlock->execute();
			}
		}
	}


};