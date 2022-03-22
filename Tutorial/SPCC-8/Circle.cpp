#include "Shapes.h"

void Circle::SetRadius(double radius)
{
    this->radius = radius;
}
double Circle::GetRadius()
{
    return radius;
}

void Circle::SetColour(const char* colour)
{
    this->colour = colour;
}

const char* Circle::GetColour()
{
    return colour.c_str();
}

void Circle::Print() 
{
    std::cout << "Colour: " << colour << std::endl;
    std::cout << "Radius: " << radius << std::endl;
    
    std::cout << float(3.1415926535897932384626433832795) * radius * radius << std::endl;
}

void Circle::Serialise(std::ostream& os)
{
    os << radius;
    os << colour;
}

void Circle::UnSerialise(std::istream& is)
{
    is >> radius;
    is >> colour;
}