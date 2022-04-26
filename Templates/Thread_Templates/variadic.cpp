#include <iostream>
#include <thread>
template <class T>
double sum(T t)
{ return t; }

template <class T, class... Ts>
double sum(T t, Ts... ts)
{ return t + sum(ts...); }

int main()
{
    std::cout << sum(1.0) << std::endl;
    std::cout << sum(1.0, 2.0) << std::endl;
    std::cout << sum(1.0, 2.0, 3.0) << std::endl;
    std::cout << sum(1.0, 2.0, 3.0, 4.0) << std::endl;
    std::cout << sum(1.0, 2.0, 3.0, 4.0, 5.0) << std::endl;
}