#ifndef CPP_ERRORMANAGER_H
#define CPP_ERRORMANAGER_H

#include <exception>
#include <iostream>
#include <string>

class ErrorManager
{
public:
	ErrorManager();
	ErrorManager(const ErrorManager &src);
	~ErrorManager();
	ErrorManager &operator=(const ErrorManager &src);
	class FormatException : public std::exception
			{
	public:
		virtual const char* what() const throw();
	};

	class LimitException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InputExcpetion : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};


#endif //CPP_ERRORMANAGER_H
