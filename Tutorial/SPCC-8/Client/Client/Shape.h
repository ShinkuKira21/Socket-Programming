#pragma once

class Circle;
class Rectangle;

#include <string>
#include <iostream>

namespace networkshapes {

	using namespace std;

	enum ShapeType { circle, rectangle };

	class Shape
	{
	public:
		Shape();
		Shape(string colour);
		virtual ~Shape();

		virtual void Print();
		virtual double GetArea() = 0;

		virtual void Serialise(ostream& os);
		virtual void UnserialiseType(istream& is) = 0;

		static Shape* Unserialise(istream& is);


		void SetColour(string colour);
		string GetColour();

		void SetType(ShapeType type);
		ShapeType GetType();

	private:
		string colour;

	protected:
		ShapeType type;

	};

}