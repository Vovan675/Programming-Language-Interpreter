#pragma once
#include <vector>
#include <string>
#include <map>

#include "Constants.h"
#include "Token.h"






/*
	Tokenizer (Lexer)
	Gets a string and then split it into a corresponding tokens 
	i.e str="50+30"; output=[Token(NUMBER, "50"), Token(PLUS), TOKEN(NUMBER, "30")]
*/

class Tokenizer {

public:
	int currentPosition; //Position of the current character
	std::string currentString; //String to tokenize


	std::vector<Token> m_tokens; //There will be tokens for a given string


	Tokenizer() : currentPosition(0), currentString("") {}


	//Main method. Tokenizes and returns tokens for a given string
	std::vector<Token> tokenize(std::string str) {
		m_tokens.clear(); //Clear tokens array

		currentPosition = 0; //Set current position to zero
		currentString = str; //Set current string to given

		//While not the end of a string
		while (currentPosition < currentString.length()) {
			
			//if digit, then add digit token, otherwise add another tokens...
			if (isDigit(peek(0))) {
				m_tokens.push_back(tokenizeDigit());
			}
			else if (isWord(peek(0))) {
				m_tokens.push_back(tokenizeWord());
			}
			else if (peek(0) == '"') { 
				m_tokens.push_back(tokenizeString());
			}
			else if (tokenChars.find(std::string(1, peek(0))) != tokenChars.end()){
				m_tokens.push_back(tokenizeOperator());
			}
			nextChar(); //Increase current position
		
		}

		
		return m_tokens; //Return tokens (it also stored in class instance's variable)
	}


private:
	
	//Parse next characters and returns corresponding token from map
	Token tokenizeOperator() {
		std::string str = "";
		//if (tokenChars.find(peek(0)) != tokenChars.end()) { //If found
		while (true) {
			char currentChar = peek(0);
			if (tokenChars.find(str + currentChar) == tokenChars.end() && tokenChars.find(str) != tokenChars.end()) {
				break;
			}
			str += peek(0);
			nextChar();
		}
		currentPosition--;
		return Token(tokenChars[str]);
	}


	//Parse next characters and returns corresponding number token
	Token tokenizeDigit() {
		std::string digitStr = "";

		//While current character is digit...
		while(true) {
			if (isDigit(peek(0))) {
				digitStr += peek(0); //Add current char(part of number) to string
				nextChar(); //Increase position
			}
			//If current char isn't digit
			else {
				break;
			}
		}
		currentPosition--;
		return Token(NUMBER, digitStr);
	}


	//Parse next characters and returns corresponding WORD token
	Token tokenizeWord() {
		std::string wordStr = "";

		//While current character is word or digit...
		while (true) {
			if (isWord(peek(0)) || isDigit(peek(0))) {
				wordStr += peek(0); //Add current char(part of number) to string
				nextChar(); //Increase position
			}
			//If current char isn't word or digit
			else {
				break;
			}
		}
		currentPosition--;

		if (wordStr == "if") {
			return Token(IF_WORD);
		}
		else if (wordStr == "else") {
			return Token(ELSE_WORD);
		}
		else if (wordStr == "while") {
			return Token(WHILE_WORD);
		}
		else if (wordStr == "do") {
			return Token(DO_WORD);
		}
		else if (wordStr == "for") {
			return Token(FOR_WORD);
		}
		else if (wordStr == "use") {
			return Token(USE_WORD);
		}
		else if (wordStr == "def") {
			return Token(DEF_WORD);
		}
		else if (wordStr == "return") {
			return Token(RETURN_WORD);
		}
		else {
			return Token(WORD, wordStr);
		}
	}

	//Parse next characters and returns corresponding STRING token
	Token tokenizeString() {
		std::string str = "";
		nextChar(); // skip "
		//While current character is word or digit...
		while (peek(0) != '"') {
			if (peek(0) == '\\') {
				switch (peek(1))
				{
				case 'n': {
					str += '\n';
					nextChar();
					nextChar();
					continue;
				}
				case '\\':
				{
					str += '\\';
					nextChar();
					nextChar();
					continue;
				}
				case '"':
				{
					str += '"';
					nextChar();
					nextChar();
					continue;
				}
				}
			}

			str += peek(0);
			nextChar();
		}
		
		return Token(STRING, str);
	}


	//Returns characher with position (currentPosition+1)
	char nextChar() {
		return currentString[currentPosition++];
	}


	//Returns characher with position (currentPosition+rel)
	char peek(int rel) {
		return currentString[currentPosition + rel];
	}


	//Returns true if ch is a digit
	bool isDigit(char ch) {
		if ((ch >= '0' && ch <= '9') || ch == '.') {
			return true;
		}
		return false;
	}

	//Returns true if ch is a word (Not used function!!!)
	bool isWord(char ch) {
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_') {
			return true;
		}
		return false;
	}

};