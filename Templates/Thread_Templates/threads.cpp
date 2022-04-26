#include <iostream>
#include <thread>
#include <sstream>
#include <string>

void ThreadedMethod(int n)
{
    std::stringstream ss;
    ss << "Thread " << n << " starting." << std::endl;

    std::cout << ss.str();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    ss.str(std::string());

    ss << "Thread " << n << " ending." << std::endl;

    std::cout << ss.str();
}

int main()
{
    for(int i = 0; i < 5; i++)
    {
        std::thread* t = new std::thread([=] { ThreadedMethod(i); });
        free(t);
    }

    return 0;
}