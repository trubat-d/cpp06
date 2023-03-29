#include <iostream>
#include <iomanip>
#include <sstream>
#include <float.h>
#include "ErrorManager.h"


int get_precision(const char *str)
{
	int count = 0;
	if(std::string(str).find('.') == std::string::npos)
		return (1);
	for(int i = std::string(str).find('.')+1; str[i]; i++)
	{
		count++;
	}
	if(count == 0)
		return 1;
	return (count);
}

int count_char(const char *str, char c)
{
	int count = 0;
	for(int i = 0; str[i]; i++)
	{
		if(str[i] == c)
			count++;
	}
	return (count);
}

void show_char(int i)
{
	if(isascii(i) && isprint(i))
		std::cout << "char	: '" << static_cast<char>(i) << "'" << std::endl;
	else if (isascii(i) && !isprint(i))
		std::cout << "char	: Non displayable" << std::endl;
	else
		std::cout << "char	: impossible" << std::endl;
}

void show_float(float i, int prec)
{
	std::cout << "float	: " << std::fixed << std::setprecision(prec) << i << "f" << std::endl;
}

void show_double(double i, int prec)
{
	std::cout << "double	: " << std::fixed << std::setprecision(prec) << i << std::endl;
}

void show_int(int i)
{
	std::cout << "int	: " << i << std::endl;
}

void show_all(int _char, int _int, float _float, double _double, int prec)
{
	show_char(_char);
	show_int(_int);
	show_float(_float, prec);
	show_double(_double, prec);
}

void show_special(std::string const a, std::string const b,std::string const c,std::string const d)
{
	std::cout << "char	: " << a << std::endl;
	std::cout << "int	: " << b << std::endl;
	std::cout << "float	: " << c << std::endl;
	std::cout << "double: " << d << std::endl;
}

bool is_valid_point_number(std::string str)
{
	const char *cstr = str.c_str();
	int len = strlen(cstr);
	for(int i = 0; i < len;i++)
	{
		if(!isdigit(cstr[i]) && cstr[i] !='+' && cstr[i] != '-' && cstr[i] != '.')
			return false;
	}
	int min_num = count_char(cstr, '-');
	int plus_num = count_char(cstr, '+');
	int point_num = count_char(cstr, '.');
	if(min_num > 1 || plus_num > 1 || point_num > 1)
		throw ErrorManager::FormatException();
	if(min_num || plus_num)
		if((cstr[0] != '-' && cstr[0] != '+') || min_num == plus_num)
			return false;
	if(point_num)
	{
		int point_pos = str.find('.');
		if((point_pos == 1 && (min_num||plus_num)) || point_pos == 0)
			return false;
	}
	return true;
}

void float_transpose(std::string str)
{
	str.pop_back();
	if(!is_valid_point_number(str))
		throw ErrorManager::FormatException();
	double d_printer = 0;
	std::istringstream(str) >> d_printer;
	if(d_printer > MAXFLOAT || d_printer < -MAXFLOAT)
		throw ErrorManager::LimitException();
	float f_printer = static_cast<float>(d_printer);
	std::cout << "Found type : float" << std::endl;
	show_all(static_cast<int>(f_printer), static_cast<int>(f_printer), f_printer,\
	static_cast<double>(f_printer), get_precision(str.c_str()));
}

void int_transpose(std::string str)
{
	const char *cstr = str.c_str();
	for(size_t i = 0; i < strlen(cstr); i++)
	{
		if(!isdigit(cstr[i]) && cstr[i] != '+' && cstr[i] != '-')
			throw ErrorManager::FormatException();
	}
	int min_num = count_char(cstr, '-');
	int plus_num = count_char(cstr, '+');
	if(min_num > 1 || plus_num > 1)
		throw ErrorManager::FormatException();
	if(min_num || plus_num)
		if((cstr[0] != '-' && cstr[0] != '+') || min_num == plus_num)
			throw ErrorManager::FormatException();
	long int l_printer = 0;
	std::istringstream(str) >> l_printer;
	if(l_printer > INT_MAX || l_printer < INT_MIN)
		throw ErrorManager::LimitException();
	int i_printer = static_cast<int>(l_printer);
	std::cout << "Found type : int" << std::endl;
	show_all(i_printer, i_printer, static_cast<float>(i_printer), \
	static_cast<double>(i_printer), get_precision(str.c_str()));
}

void	double_transpose(std::string str)
{

	if(!is_valid_point_number(str))
		throw ErrorManager::FormatException();
	long double ld_printer = 0;
	std::istringstream(str) >> ld_printer;
	if(ld_printer > DBL_MAX || ld_printer < -DBL_MAX)
		throw ErrorManager::LimitException();
	double d_printer = static_cast<double>(ld_printer);
	std::cout << "Found type : double" << std::endl;
	show_all(static_cast<int>(d_printer), static_cast<int>(d_printer), static_cast<float>(d_printer), \
	d_printer, get_precision(str.c_str()));
}

void	char_transpose(std::string str)
{
	std::cout << "Found type : char" << std::endl;
	char c = str.c_str()[0];
	show_all(c, static_cast<float>(c), static_cast<float>(c), \
	static_cast<double>(c), get_precision(str.c_str()));
}

void show_special(std::string str)
{
	if(str == "nan" || str == "nanf")
		show_special("impossible", "impossible", "nanf", "nan");
	else if (str == "+inf" || str == "+inff")
		show_special("impossible", "impossible", "+inff", "+inf");
	else if (str == "-inf" || str == "-inff")
		show_special("impossible", "impossible", "-inff", "-inf");
	else
		throw ErrorManager::InputExcpetion();
}

int main(int ac, char **av)
{
	try {
		if(ac !=2)
			throw ErrorManager::InputExcpetion();
		std::string str(av[1]);
		if(str.back() == 'f')
			float_transpose(str);
		else if (str.find('.') != std::string::npos)
			double_transpose(str);
		else if (str.length() > 0)
		{
			if(isdigit(str.c_str()[0]) || ((str.c_str()[0] == '-' || str.c_str()[0] == '+') && isdigit(str.c_str()[1])))
				int_transpose(str);
			else if (str.length() > 1)
				show_special(str);
			else
				char_transpose(str);
		}
		else
			throw ErrorManager::InputExcpetion();
	}
	catch (std::exception& e)
	{
		std::cout << "Error found : " << e.what() << std::endl;
		return (1);
	}
	return (0);
}