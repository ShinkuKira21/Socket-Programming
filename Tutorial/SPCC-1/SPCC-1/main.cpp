#include <iostream>
#include <string>
#include <sstream>

std::string StrInput(const char* msg)
{
	std::string input;
	std::cout << msg;
	std::getline(std::cin, input);
	return input;
}

int NumberInput(const char* msg)
{
	std::string input;
	std::stringstream sstream;

	int x = 0;

	std::cout << msg;
	std::getline(std::cin, input);

	sstream.str(input);
	sstream >> x;
	sstream.clear();

	return x;
}

int main()
{
	int count = NumberInput("Enter count value: ");

	for(int i = 1; i <= count; i++)
	{
		float x = float(i) / float(3);
		float y = float(i) / float(5);

		if (floor(x) == x && floor(y) == y)
			std::cout << "fizzbuzz";

		else if (floor(x) == x)
			std::cout << "fizz";

		else if (floor(y) == y)
			std::cout << "buzz";

		else std::cout << i;

		if (i != count) std::cout << ", ";
	}

	return 0;
}