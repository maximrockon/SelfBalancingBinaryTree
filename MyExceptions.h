#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H
#include <exception>
#include <iostream>

class StatisticOutOfRange : public std::exception {
private:
	const char* reason_;
public:
	StatisticOutOfRange():
		reason_("Statistic Out Of Range") {}

	const char* what() {
		return reason_;
	}
};

class NullPointerDereference : public std::exception {
private:
	const char* reason_;
public:
	NullPointerDereference() :
		reason_("Null Pointer Dereference") {}

	const char* what() {
		return reason_;
	}
};

#endif