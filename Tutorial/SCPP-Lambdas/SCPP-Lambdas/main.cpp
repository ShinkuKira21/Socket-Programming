#include <iostream>
#include <vector>
#include <algorithm>

void Iterators()
{
	std::vector<int> v = { 1, 3, 5, 7, 9 };
	std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), [](int x) { return x == 5; });

	// for_each
	std::for_each(v.begin(), v.end(), [](int d) {std::cout << d << std::endl; });

	// for_each
	for(const auto d : v)
	{
		std::cout << d << std::endl;
	}

	v.erase(std::unique(v.begin(), v.end(), v.end()));
	v.erase(std::remove_if(v.begin(), v.end(), [](auto d) {return d == 5; }));

	if (it != v.end()) std::cout << "Found!\n";
	else std::cout << "Not Found!\n";
}

int main(int argc, char** argv)
{
	Iterators();
	auto Add = [](int x, int y) {return x + y; };
	std::cout << Add(2, 10);
}