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
	std::string sentence = StrInput("Enter your word: ");
	int middle = (int)std::round(float(sentence.length()) / 2);

	for (size_t i = 0; i < sentence.length(); i++)
	{
		// Covers ! to @ including numerical data
		if (sentence[i] > 31 && sentence[i] < 64)
			sentence[i] = '\0'; // 20 is space

		if (std::isupper(sentence[i]))
			sentence[i] = (char)sentence[i] + 32;
	}

	if (middle % 2 != 0) sentence[middle-1] = '\0';

	std::string palindrome = "";
	
	for (int i = sentence.length() - 1; i != -1; i--)
		palindrome += sentence[i];

	std::cout << palindrome;
	std::cout << std::endl << sentence;

	sentence == palindrome ? std::cout << "\nWord is a Palindrome" : std::cout << "\nWord is a not Palindrome";
}