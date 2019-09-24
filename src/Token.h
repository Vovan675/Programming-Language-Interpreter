#pragma once



/*
	Token
	Has type and value, i.e m_type=NUMBER (Is defined in TokenTypes.h), m_value="50"
*/

class Token {
public:
	unsigned int m_type;
	std::string m_value;

	Token(int type, std::string value) : m_type(type), m_value(value) {};

	Token(int type) : m_type(type), m_value("") {};

};