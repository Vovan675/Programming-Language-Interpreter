#pragma once

#include <iostream>
#include "Module.h"

class mathModule : public Module {
public:

	void init() {
		functions["sin"] = _createFunction(
			if (args.size() != 1) {} //Exception
		return new NumberValue(sin(args.at(0)->asDouble()));
		);
		
		functions["cos"] = _createFunction(
			if (args.size() != 1) {} //Exception
		return new NumberValue(cos(args.at(0)->asDouble()));
		);


		functions["pow"] = _createFunction(
			if (args.size() != 2) {} //Exception
		return new NumberValue(pow(args.at(0)->asDouble(), args.at(1)->asDouble()));
		);

		functions["sqrt"] = _createFunction(
			if (args.size() != 1) {} //Exception
		return new NumberValue(sqrt(args.at(0)->asDouble()));
		);
						


	}

};