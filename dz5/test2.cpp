#include "VBool.hpp"
#include <iostream>


int main()
{
	uint64_t mem1 = 0;
	VBool bool1(mem1, 0);
	VBool bool2(mem1, 5);
	try
	{
		VBool bool3(mem1, 64);
	}
	catch(std::runtime_error err)
	{
		std::cout << "exception caught: " << err.what() << std::endl;
	}

	printf("%lu\n", mem1);
	bool1 = true;
	printf("%lu\n", mem1);
	bool2 = bool1;
	printf("%lu\n", mem1);
	
	bool bool3 = static_cast<bool>(bool2);
	std::cout << bool3 << std::endl;

	std::cout << "Hello world!" << std::endl;
	return EXIT_SUCCESS;
}