#pragma once

#include <WS2tcpip.h>
#include <io.h>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "ClientConnection.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace networkshapes;
using namespace std;

Shape* BuildShape()
{
	cout << "Enter:" << endl << "0 - Circle" << endl << "1 - Rectangle" << endl;

	ShapeType type;
	int tType;
	Shape *s;

	if (cin >> tType)
	{
		type = static_cast<ShapeType>(tType);
	}

	string colour;
	cout << "Enter colour" << endl;

	cin >> colour;

	switch (type)
	{
		case circle:
		{
			s = new networkshapes::Circle();

			double radius;
			cout << "Enter radius" << endl;
			cin >> radius;

			((networkshapes::Circle*)s)->SetRadius(radius);

			break;
		}
		case rectangle:
		{
			s = new networkshapes::Rectangle();

			double s1, s2;
			cout << "Enter sides 1 and 2" << endl;
			cin >> s1 >> s2;

			((networkshapes::Rectangle*)s)->SetSide1(s1);
			((networkshapes::Rectangle*)s)->SetSide2(s2);

			break;
		}
		default:
		{
			return nullptr;
		}
	}

	s->SetColour(colour);

	return s;

}

int main(int argc, char** argv)
{
	Shape* s = BuildShape();

	if (s == nullptr)
	{
		exit(-1);
	}

	stringstream ss;
	s->Serialise(ss);

	char ip[] = "127.0.0.1";
	INet4Address *serverAddress = new INet4Address(ip, 50018);

	ClientConnection* conn = new ClientConnection(serverAddress);
	ConnectionInstance* ci = conn->ConnectToServer();

	ci->SendString(ss.str());

	getchar();
}