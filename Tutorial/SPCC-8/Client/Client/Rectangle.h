#pragma once
#include "Shape.h"

namespace networkshapes {

	using namespace std;

	class Rectangle :
		public Shape
	{
	public:
		Rectangle();
		Rectangle(string colour, double side1, double side2);
		~Rectangle();

		void SetSide1(double side1);
		double GetSide1();

		void SetSide2(double side2);
		double GetSide2();

		void Print() override;
		double GetArea();

		void Serialise(ostream& os) override;
		void UnserialiseType(istream& is);

	private:
		double side1;
		double side2;
	};

}