#include "Circle.h"

namespace networkshapes 
{
	Circle::Circle()
	{
		type = circle;
	}

	Circle::Circle(string colour, double radius) : Shape(colour)
	{
		type = circle;
		SetRadius(radius);
	}

	Circle::~Circle()
	{
	}

	void Circle::SetRadius(double radius)
	{
		this->radius = radius;
	}

	double Circle::GetRadius()
	{
		return radius;
	}

	void Circle::Print()
	{
		cout << "Circle" << endl;
		Shape::Print();
		cout << "Radius: " << radius << endl;
	}

	double Circle::GetArea()
	{
		return 3.14159 * radius * radius;
	}

	void Circle::Serialise(ostream& os)
	{
		Shape::Serialise(os);
		os << radius;
	}

	void Circle::UnserialiseType(istream& is)
	{
		is >> radius;
	}
}