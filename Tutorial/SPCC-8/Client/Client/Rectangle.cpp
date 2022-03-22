#include "Rectangle.h"

namespace networkshapes {

	Rectangle::Rectangle()
	{
		type = rectangle;
	}

	Rectangle::Rectangle(string colour, double side1, double side2) : Shape(colour)
	{
		type = rectangle;
		SetSide1(side1);
		SetSide2(side2);
	}

	Rectangle::~Rectangle()
	{
	}

	void Rectangle::SetSide1(double side1)
	{
		this->side1 = side1;
	}

	double Rectangle::GetSide1()
	{
		return side1;
	}

	void Rectangle::SetSide2(double side2)
	{
		this->side2 = side2;
	}

	double Rectangle::GetSide2()
	{
		return side2;
	}

	void Rectangle::Print()
	{
		cout << "Rectangle" << endl;
		Shape::Print();
		cout << "Side 1: " << side1 << endl;
		cout << "Side 2: " << side2 << endl;
	}

	double Rectangle::GetArea()
	{
		return side1 * side2;
	}

	void Rectangle::Serialise(ostream& os)
	{
		Shape::Serialise(os);
		os << side1 << endl;
		os << side2;
	}

	void Rectangle::UnserialiseType(istream& is)
	{
		is >> side1;
		is >> side2;
	}

}