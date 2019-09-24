#pragma once

#include "Statement.h"
#include "..\Constants.h"

#include "..\Functions\UserFunction.h"

class FunctionDefineStatement : public Statement {

public:
	std::string m_funcName;
	std::vector<std::string> m_argNames;
	Statement* m_bodyBlock;

	FunctionDefineStatement(std::string funcName, std::vector<std::string> argNames, Statement* bodyBlock) :
					m_funcName(funcName), m_argNames(argNames), m_bodyBlock(bodyBlock) {}


	void execute() {
		functions[m_funcName] = new UserFunction(m_argNames, m_bodyBlock);
	}


};