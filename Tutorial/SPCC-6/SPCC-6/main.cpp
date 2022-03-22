#include "INet4Address.h"

// Exercise 1
namespace E1
{
	void RUN_E1()
	{
		sockaddr_in address;

		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(13); //31

		inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

		if (htons(12) == 12)
			std::cout << "Big Endian" << std::endl;
		std::cout << "Little Endian" << std::endl;
	}
}

namespace E2
{
	void RUN_E2()
	{
		char add1[] = "127.0.0.1";

		INet4Address inet(add1, 13);
		inet.Print();

		std::cout << std::endl;

		INet4Address inet1(13);
		inet1.Print();
	}
}

namespace E3
{
	void RUN_E3()
	{
		
	}
}

int main(int argc, char** argv)
{
	//E1::RUN_E1();

	E2::RUN_E2();
}