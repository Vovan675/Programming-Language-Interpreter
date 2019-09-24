#pragma once

#include "Statement.h"
#include "..\Constants.h"

class BlockStatement : public Statement {

public:
	std::vector<Statement*> statements;

	BlockStatement(std::vector<Statement*> statements) : statements(statements) {}
	BlockStatement() { statements.clear(); }


	void execute() {
		for (auto it = statements.begin(); it != statements.end(); it++) {
			(*it)->execute();
		}
	}

	void addStatement(Statement* statement) {
		statements.push_back(statement);
	}


};