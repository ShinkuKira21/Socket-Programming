#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

namespace networkshapes {

	Shape::Shape()
	{
	}

	Shape::Shape(string colour)
	{
		SetColour(colour);
	}

	Shape::~Shape()
	{
	}

	void Shape::SetColour(string colour)
	{
		this->colour = colour;
	}

	string Shape::GetColour()
	{
		return colour;
	}

	void Shape::Print()
	{
		cout << "Area: " << GetArea() << endl;
		cout << "Colour: " << colour << endl;
	}

	void Shape::Serialise(ostream& os)
	{
		os << type << endl;
		os << colour << endl;
	}

	Shape* Shape::Unserialise(istream& is)
	{
		//TODO: complete this.
	}

	void Shape::SetType(ShapeType type)
	{
		this->type = type;
	}

	ShapeType Shape::GetType()
	{
		return type;
	}
}