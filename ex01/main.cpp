#include <iostream>
#include <string>
#include <cstdint>

typedef struct s_data
{
	int content;
} Data;

uintptr_t serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main(void)
{
	Data *test = new Data();
	test->content = 1;
	std::cout << "Value of the default pointer		: " << test  << " with content : " << test->content << std::endl;
	uintptr_t val = serialize(test);
	std::cout << "Value of the serialized pointer		: " << val << std::endl;
	Data *desData = deserialize(val);
	std::cout << "Value of the deserialized pointer	: " << desData << " with content : " << desData->content << std::endl;
	delete test;
}