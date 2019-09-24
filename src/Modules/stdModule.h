#pragma once

#include <iostream>
#include "Module.h"

class stdModule : public Module {
public:

	void init() {
		functions["print"] = _createFunction(
			if (args.size() == 0) {} //Exception
		for (int i = 0; i < args.size(); i++) {
			std::cout << args.at(i)->asString();
		}

		return new StringValue("Function:print");
		);

		functions["input"] = _createFunction(
			if (args.size() != 0) {} //Exception
		std::string a = "";
		std::cin >> a;
		return new StringValue(a);
		);
		
		functions["inputChar"] = _createFunction(
			if (args.size() != 0) {} //Exception
		std::string a = " ";
		a[0] = _getch();
		return new StringValue(a);
		);

		functions["clear"], _createFunction(
			if (args.size() != 0) {} //Exception
		system("cls");
		return new StringValue("Function:clear");
		);
			
			
	}

};