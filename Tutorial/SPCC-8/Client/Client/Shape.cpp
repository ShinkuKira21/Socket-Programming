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
		Shape* s = nullptr;

		unsigned int tType = 0;
		string colour;
		ShapeType type;

		if (is >> tType)
		{
			type = static_cast<ShapeType>(tType);
		}

		is >> colour;

		switch (type)
		{
			case circle:
			{
				s = new Circle();
			}
			break;

			case rectangle:
			{
				s = new Rectangle();
			}
			break;

			default:
			{
				return nullptr;
			}
		}

		s->SetColour(colour);
		s->UnserialiseType(is);


		return s;
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