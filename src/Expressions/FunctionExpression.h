#pragma once

#include "..\Constants.h"
#include "Expression.h"

#include "..\ValueTypes.h"

#include "..\Functions\UserFunction.h"

/*
	Variable Expression
	Just takes an name of the variable and then return number in variables array with corresponding name
*/

class FunctionExpression : public Expression {

public:
	std::string m_name;
	std::vector<Expression*> m_arguments;

	FunctionExpression(std::string name, std::vector<Expression*> arguments) : m_name(name), m_arguments(arguments) {}

	FunctionExpression(std::string name) : m_name(name) {}

	void addArgument(Expression* argument) {
		m_arguments.push_back(argument);
	}


	ValueType* eval() {

		std::vector<ValueType*> args;
		for (int i = 0; i < m_arguments.size(); i++) {
			args.push_back(m_arguments.at(i)->eval());
		}

		Function* func = functions[m_name];
		if (typeid(*func) == typeid(UserFunction)) {
			UserFunction* userFunc = (UserFunction*)func;
			int argsCount = userFunc->m_argNames.size();

			std::map<std::string, ValueType*> savedVariables;
			savedVariables = variables;

			for (int i = 0; i < argsCount; i++) { //Save variables + set arguments
				savedVariables[userFunc->m_argNames.at(i)] = variables[userFunc->m_argNames.at(i)];
				variables[userFunc->m_argNames.at(i)] = args[i];
			}

			
			ValueType* val = functions[m_name]->execute(args);

			for (int i = 0; i < argsCount; i++) { //Restore variables
				 variables[userFunc->m_argNames.at(i)] = savedVariables[userFunc->m_argNames.at(i)];
			}
			variables = savedVariables;

			return val;
		}
		return functions[m_name]->execute(args);
	}


};