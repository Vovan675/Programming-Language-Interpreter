#pragma once


class Function {
public:

	virtual ValueType* execute(std::vector<ValueType*> args) { return new ValueType(); }
};