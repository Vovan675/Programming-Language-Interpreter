#pragma once


#include "Statement.h"
#include "..\Constants.h"

#include "..\Modules\stdModule.h"
#include "..\Modules\mathModule.h"

std::map<std::string, Module*> moduleNames = {
		{"std", new stdModule()},
		{"math", new mathModule()}
};

class IncludeStatement : public Statement {
	

public:
	

	Expression* m_moduleName;

	IncludeStatement(Expression* moduleName) : m_moduleName(moduleName) {}


	void execute() {
		std::string name = m_moduleName->eval()->asString();
		moduleNames[name]->init();
	}


};