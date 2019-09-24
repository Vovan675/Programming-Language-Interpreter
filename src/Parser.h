#pragma once
#include <vector>
#include <string>

#include "Constants.h"
#include "Token.h"

#include "Modules\Module.h"


#include "Expressions\Expression.h"
#include "Expressions\ValueExpression.h"
#include "Expressions\UnaryExpression.h"
#include "Expressions\BinaryExpression.h"
#include "Expressions\ConditionalExpression.h"
#include "Expressions\VariableExpression.h"

#include "Functions\Function.h"
#include "Expressions\FunctionExpression.h"
#include "Statements\FunctionStatement.h"
#include "Statements\FunctionDefineStatement.h"



#include "Statements\Statement.h"
#include "Statements\BlockStatement.h"
#include "Statements\AssignStatement.h"
#include "Statements\IncrementStatement.h"
#include "Statements\IfStatement.h"
#include "Statements\WhileStatement.h"
#include "Statements\DoWhileStatement.h"
#include "Statements\ForStatement.h"
#include "Statements\IncludeStatement.h"

#include "Statements\ReturnStatement.h"





class Parser {
public:
	int currentPosition;
	std::vector<Token> m_tokens;

	Parser() {};

	Statement* parse(std::vector<Token> tokens) {
		currentPosition = 0;
		m_tokens = tokens;

		//std::vector<Statement*> statements;
		BlockStatement* blockStatement = new BlockStatement();

		while (!match(peek(0), EOF)) { //While current token isn't END (EOF) token...
			blockStatement->addStatement(statement());
		}

		return blockStatement;
	}

	Statement* blockStatement() {
		BlockStatement* blockSt = new BlockStatement();
		while (!match(peek(0), RCURLY)) {
			blockSt->addStatement(statement());
		}
		return blockSt;
	}


	Statement* statement() {
		Token token = peek(0);
		if (token.m_type == LCURLY) {
			currentPosition++;
			return blockStatement();
		}
		else if (token.m_type == USE_WORD) { // Include library
			currentPosition++; //Skip USE_WORD
			return new IncludeStatement(expression());
		}
		else if (token.m_type == WORD && peek(1).m_type == EQUAL) { // if current token is WORD, and next token is EQUAL
			currentPosition += 2; //Increase current token position to 2 tokens (WORD and EQUAL parsed already)
			return new AssignStatement(token.m_value, expression());
		}
		else if (token.m_type == WORD && peek(1).m_type == PLUS_EQUALS) { // if current token is WORD, and next token is EQUAL
			currentPosition += 2; //Increase current token position to 2 tokens (WORD and PLUS_EQUALS parsed already)
			Expression* incrementBy = expression();
			return new IncrementStatement(token.m_value, incrementBy);
		}
		else if (token.m_type == WORD && peek(1).m_type == MINUS_EQUALS) { // if current token is WORD, and next token is EQUAL
			currentPosition += 2; //Increase current token position to 2 tokens (WORD and PLUS_EQUALS parsed already)
			Expression* decrementBy = expression();
			return new IncrementStatement(token.m_value, new UnaryExpression('-', decrementBy));
		}
		else if (token.m_type == WORD && peek(1).m_type == LPAREN) { //Function
			return new FunctionStatement((FunctionExpression*)functionExpression());
		}
		else if (token.m_type == IF_WORD) { //If
			currentPosition++;
			Expression* condition = expression();
			Statement* ifBlock = statement();
			Statement* elseBlock = NULL;
			if (match(peek(0), ELSE_WORD)) {
				elseBlock = statement();
			}
			IfStatement* ifStatement = new IfStatement(condition, ifBlock, elseBlock);
			return ifStatement;
		}
		else if (token.m_type == WHILE_WORD) { //While
			currentPosition++;
			Expression* condition = expression();
			Statement* statementBlock = statement();
			WhileStatement* whileStatement = new WhileStatement(condition, statementBlock);
			return whileStatement;
		}
		else if (token.m_type == DO_WORD) { //Do-While
			currentPosition++;
			Statement* statementBlock = statement();
			match(peek(0), WHILE_WORD); //Skip WHILE_WORD
			Expression* condition = expression();
			DoWhileStatement* doWhileStatement = new DoWhileStatement(statementBlock, condition);
			return doWhileStatement;
		}
		else if (token.m_type == FOR_WORD) { //For
			currentPosition++;
			match(peek(0), LPAREN); //Skip probably ( (used to possible using or not parens)

			Statement* initializationBlock = statement();
			match(peek(0), SEMICOLON); //Skip ;
			Expression* condition = expression();
			match(peek(0), SEMICOLON); //Skip ;
			Statement* incrementBlockStatement = statement();


			match(peek(0), RPAREN); //Skip probably ) (used to possible using or not parens)

			Statement* statementBlock = statement();



			ForStatement* forStatement = new ForStatement(initializationBlock, condition, incrementBlockStatement, statementBlock);
			return forStatement;
		}
		else if (token.m_type == DEF_WORD) { //User function define
			currentPosition++; //skip DEF

			std::string funcName = peek(0).m_value;
			match(peek(0), WORD); //skip functionName
			match(peek(0), LPAREN); //skip (

			std::vector<std::string> argNames;
			while (!match(peek(0), RPAREN)) {
				argNames.push_back(peek(0).m_value);
				match(peek(0), WORD); //Skip value name
				match(peek(0), COMMA);
			}
			Statement* bodyBlock = statement();
			return new FunctionDefineStatement(funcName, argNames, bodyBlock);
		}
		else if (token.m_type == RETURN_WORD) { //User function returning
			currentPosition++; //skip RETURN

			return new ReturnStatement(expression());
		}
	}

	




	Expression* functionExpression() {
		FunctionExpression* funcExpression = new FunctionExpression(peek(0).m_value);
		currentPosition += 2; // Skip WORD(func name) and LPAREN

		while (!match(peek(0), RPAREN)) {
			funcExpression->addArgument(expression());
			match(peek(0), COMMA);
		}
		return funcExpression;
	}


	
	Expression* expression() {
		return logicalOperators();
	}

	Expression* logicalOperators() {
		Expression* expr = logicalCompare();
		if (match(peek(0), AND)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::_AND, expr, logicalCompare());
		}
		else if (match(peek(0), LOGICAL_AND)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::_LOGICAL_AND, expr, logicalCompare());
		}
		else if (match(peek(0), OR)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::_OR, expr, logicalCompare());
		}
		else if (match(peek(0), LOGICAL_OR)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::_LOGICAL_OR, expr, logicalCompare());
		}
		return expr;
	}

	Expression* logicalCompare() {
		Expression* expr = addition();
		if (match(peek(0), DOUBLE_EQUAL)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::EQUAL_EQUAL, expr, addition());
		}
		else if (match(peek(0), NOT_EQUAL)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::NOT_EQUAL_EQUAL, expr, addition());
		}
		else if (match(peek(0), LESS_THAN)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::LESS, expr, addition());
		}
		else if (match(peek(0), LESS_EQUAL)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::LESS_EQUAL_EQUAL, expr, addition());
		}
		else if (match(peek(0), GREATER_THAN)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::GREATER, expr, addition());
		}
		else if (match(peek(0), GREATER_EQUAL)) {
			expr = new ConditionalExpression(ConditionalExpression::OPERATION::GREATER_EQUAL_EQUAL, expr, addition());
		}
		return expr;
	}

	


	Expression* addition() {
		Expression* expr = multiplication();
		while (true) {
			if (match(peek(0), PLUS)) {
				expr = new BinaryExpression('+', expr, multiplication());
			}
			else if (match(peek(0), MINUS)) {
				expr = new BinaryExpression('-', expr, multiplication());
			}
			else {
				break;
			}
		}

		return expr;
	}


	Expression* multiplication() {
		Expression* expr = negating();
		while (true) {
			if (match(peek(0), MULTIPLICATION)) {
				expr = new BinaryExpression('*', expr, negating());
			}
			else if (match(peek(0), DIVISION)) {
				expr = new BinaryExpression('/', expr, negating());
			}
			else {
				break;
			}


		}
		return expr;
	}

	
	Expression* negating() {
		Expression* expr;
		//Number sign
		if (match(peek(0), PLUS)) {
			expr = new UnaryExpression('+', number());
		}
		else if (match(peek(0), MINUS)) {
			expr = new UnaryExpression('-', number());
		}
		//Boolean inversion
		else if (match(peek(0), LOGICAL_NOT)) {
			expr = new UnaryExpression('!', number());
		}
		else {
			expr = number();
		}

		return expr;
	}
	

	Expression* number() {
		Token token = peek(0);
		if (match(token, NUMBER)) {
			return new ValueExpression(std::stod(token.m_value));
		}
		else if (match(token, STRING)) {
			return new ValueExpression(token.m_value);
		}
		else if (token.m_type == WORD && peek(1).m_type == LPAREN) { //Function expression
			return functionExpression();
		}
		else if (match(token, WORD)) {
			return new VariableExpression(token.m_value);
		}
		else if (match(token, LPAREN)) {
			Expression* exprInParen = expression();
			currentPosition++; // skip )
			return exprInParen;
		}

	}





	bool match(Token token, int type) {
		if (token.m_type == type) {
			currentPosition++;
			return true;
		}
		return false;
	}

	Token peek(int rel) {
		if (currentPosition + rel >= m_tokens.size()) {
			return Token(EOF);
		}
		return m_tokens.at(currentPosition + rel);
	}

	



private:


};