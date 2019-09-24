#pragma once
#include <string>

#include "ValueType.h"


class NumberValue : public ValueType {
public:

	double m_value;

	NumberValue(double value) : m_value(value) {}



	virtual double asDouble() {
		return m_value;
	}

	virtual std::string asString() {
		return std::to_string(m_value);
	}


};