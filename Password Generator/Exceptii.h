#pragma once
#include <iostream>
#include <exception>

using namespace std;

class exception1 : public exception {
	virtual const char* what() const throw() {
		return "Answer must be y or n, meaning yes for y and no for n!";
	}
};

class exception2 : public exception {
	virtual const char* what() const throw() {
		return "Length must be a number!";
	}
};

class exception3 : public exception {
	virtual const char* what() const throw() {
		return "Length must be greater than 4!";
	}
};