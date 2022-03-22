#pragma once
#include "Shape.h"

namespace networkshapes {

	using namespace std;

	class Circle :
		public Shape
	{
	public:
		Circle();
		Circle(string colour, double radius);
		~Circle();

		void SetRadius(double radius);
		double GetRadius();

		void Print() override;
		double GetArea();

		void Serialise(ostream& os) override;
		void UnserialiseType(istream& is);

	private:
		double radius;
		string colour;

	};

}