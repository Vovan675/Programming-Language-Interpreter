#pragma once
#include <string>

#include "ValueType.h"


class StringValue : public ValueType {
public:

	std::string m_value;

	StringValue(std::string value) : m_value(value) {}



	virtual double asDouble() {
		return std::stod(m_value);
	}

	virtual std::string asString() {
		return m_value;
	}


};