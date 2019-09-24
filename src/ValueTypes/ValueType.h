#pragma once
#include <string>


/*
	Expression it's the abstract class for all values classes in language
	It will override with other class that represents double or string value
*/

class ValueType {
public:
	

	virtual double asDouble() { return 999; }
	virtual std::string asString() { return ""; }
	

};


