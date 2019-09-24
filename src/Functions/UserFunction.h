#pragma once

#include "Function.h"
#include "..\Statements\Statement.h"

#include "..\Statements\ReturnStatement.h"


class UserFunction : public Function {

public:
	std::vector<std::string> m_argNames;
	Statement* m_bodyBlock;

	UserFunction(std::vector<std::string> argNames, Statement* bodyBlock) : m_argNames(argNames), m_bodyBlock(bodyBlock) {}

	ValueType* execute(std::vector<ValueType*> args) { 
		try {
			m_bodyBlock->execute();
		}
		catch (ReturnStatement* ex) {
			return ex->getValue();
		}
		return new NumberValue(1337);
	}

};