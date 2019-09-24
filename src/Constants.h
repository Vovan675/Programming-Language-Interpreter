#pragma once

#include <vector>
#include <map>
#include <stack>
#include <conio.h> //For _getch()



#include "ValueTypes.h"
#include "Functions/Function.h"

#if WINDOWS
#include <Windows.h>
#endif // WINDOWS


/*
	Types of all tokens
*/


#define NUMBER 0

#define PLUS 1
#define MINUS 2

#define MULTIPLICATION 3
#define DIVISION 4


#define LPAREN 5
#define RPAREN 6


#define WORD 7
#define EQUAL 8

#define STRING 9






#define DOUBLE_EQUAL 14
#define NOT_EQUAL 15

#define LOGICAL_NOT 16

#define GREATER_THAN 16
#define GREATER_EQUAL 17
#define LESS_THAN 18
#define LESS_EQUAL 19

#define OR 20
#define LOGICAL_OR 21
#define AND 22
#define LOGICAL_AND 23


//#define PRINT_WORD 24

#define IF_WORD 25
#define ELSE_WORD 26
#define WHILE_WORD 27
#define DO_WORD 28 // DO-WHILE
#define FOR_WORD 29 // DO-WHILE


#define LCURLY 30 // {
#define RCURLY 31 // }
#define SEMICOLON 32 // ;

#define PLUS_EQUALS 33
#define MINUS_EQUALS 34


#define COMMA 35
#define USE_WORD 36

#define DEF_WORD 37
#define RETURN_WORD 38









#define EOF 999


/*
	Strings of all tokens
*/

std::map<std::string, int> tokenChars = {
	{"+", PLUS},
	{"-", MINUS},
	{"*", MULTIPLICATION},
	{"/", DIVISION},
	{"(", LPAREN},
	{")", RPAREN},
	{"=", EQUAL},
	{"==", DOUBLE_EQUAL},
	{"!", LOGICAL_NOT},
	{"!=", NOT_EQUAL},
	{"<", LESS_THAN},
	{"<=", LESS_EQUAL},
	{">", GREATER_THAN},
	{">=", GREATER_EQUAL},
	{"|", OR},
	{"||", LOGICAL_OR},
	{"&", AND},
	{"&&", LOGICAL_AND},
	{"{", LCURLY},
	{"}", RCURLY},
	{";", SEMICOLON},
	{"+=", PLUS_EQUALS},
	{"-=", MINUS_EQUALS},
	{",", COMMA},
};




/*
	Variables
*/

std::map<std::string, ValueType*> variables = {
	{"PI", new NumberValue(3.1415926)},
	{"E", new NumberValue(2.7182818)},
	{"GOLDEN_RATIO", new NumberValue(1.6180339)},
};

std::stack<std::map<std::string, ValueType*>*> variablesStack;



/*
	Functions
*/

class Func : public Function {
public:
	
	ValueType* execute(std::vector<ValueType*> args) { 
		if (args.size() != 1) {} //Exception

		for (auto it = args.begin(); it != args.end(); it++) {
			std::cout << (*it)->asString();
		}

		//std::cout << "helloWorld" << std::endl;
		return new NumberValue(9991);
	}

};

#define _createFunction(funcBody) ([]() -> Function* { \
class Func : public Function { \
public: \
	ValueType* execute(std::vector<ValueType*> args) { \
	funcBody\
	} \
}; \
return new Func(); \
})()



std::map<std::string, Function*> functions = {
	
	{"num", _createFunction(
		if (args.size() != 1) {} //Exception
			return new NumberValue(args.at(0)->asDouble());
		)
	},
	{"str", _createFunction(
		if (args.size() != 1) {} //Exception
			return new StringValue(args.at(0)->asString());
		)
	},
	{"sleep", _createFunction(
		if (args.size() != 1) {} //Exception
		Sleep(args.at(0)->asDouble());
		return new StringValue("Function:sleep");
			)
	},

	

};


