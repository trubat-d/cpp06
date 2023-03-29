#include "ErrorManager.h"

ErrorManager::ErrorManager()
{

}

ErrorManager::~ErrorManager()
{

}

ErrorManager::ErrorManager(const ErrorManager &src)
{
	(void)src;
}

ErrorManager &ErrorManager::operator=(const ErrorManager &src)
{
	(void)src;
	return (*this);
}

const char* ErrorManager::FormatException::what() const throw()
{
	return ("The input sent as not a good format : float (-42.95f), int (54), char (c), double(98.56) ");
}

const char* ErrorManager::LimitException::what() const throw()
{
	return ("The input sent is over the limit of the type specified");
}

const char* ErrorManager::InputExcpetion::what() const throw()
{
	return ("Enter a : float, int, char or double");
}


