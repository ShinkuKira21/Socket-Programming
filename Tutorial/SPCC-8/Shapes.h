#pragma once
#include <iostream>
#include <ostream>

class Circle
{
    private:
        double radius;
        std::string colour;

    public:
        void SetRadius(double radius);
        double GetRadius();

        void SetColour(const char* colour);
        const char* GetColour();

        void Print();
        void Serialise(std::ostream& os);
        void UnSerialise(std::istream& is);
};