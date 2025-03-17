#pragma once

#include <exception>
class NotImplementedException: public std::exception {
	virtual const char* what() const throw() {
		return "This function was not implemented!";
	}
};