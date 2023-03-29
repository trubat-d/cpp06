#include <iostream>
#include <string>


class Base {
public:
	virtual ~Base() {};
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

Base * generate(void)
{
	std::srand(std::time(NULL));
	int var = std::rand() % 3;
	switch(var)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		case 2:
			return (new C());
	}
	return (NULL);
}

void identify(Base *p)
{
	std::string type;
	if(dynamic_cast<A *>(p))
		type = "A";
	else if (dynamic_cast<B *>(p))
		type = "B";
	else if (dynamic_cast<C *>(p))
		type = "C";
	else
		type = "none";
	std::cout << "Identified pointer : " << type << std::endl;
}

void identify(Base &p)
{
	std::string type;
	try
	{
		Base &test1 = dynamic_cast<A &>(p);
		(void)test1;
		type = "A";
	}
	catch (std::bad_cast& e)
	{
		try
		{
			Base &test2 = dynamic_cast<B &>(p);
			(void)test2;
			type = "B";
		}
		catch (std::bad_cast& e)
		{
			try
			{
				Base &test3 = dynamic_cast<C &>(p);
				(void)test3;
				type = "C";
			}
			catch (std::bad_cast& e)
			{
				type = "none";
			}
		}
	}
	std::cout << "Identified reference : " << type << std::endl;
}

int main()
{
	Base *_base = generate();
	if(_base)
	{
		identify(_base);
		identify(*_base);
	}
	else
	{
		std::cout << "pointer is null" << std::endl;
		return (1);
	}
	return (0);
}