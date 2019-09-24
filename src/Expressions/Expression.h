#pragma once
#include <vector>
#include <string>

#include "Token.h"

#include "..\ValueTypes\ValueType.h"



/*
	Expression it's the abstract class for all expressions
	Every child must create his own constructor and eval function
*/

class Expression {
public:
	
	virtual ValueType* eval() { return new ValueType(); };



};