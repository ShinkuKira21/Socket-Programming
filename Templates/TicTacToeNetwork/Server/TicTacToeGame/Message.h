#pragma once

#include <iostream>
#include <sstream>

namespace tttmessages
{
	using namespace std;

	enum MessageType { connect, disconnect, accept, reject, requestupdate, gamegrid, makemove, gamestate  };

	class Message
	{
	public:
		Message();
		~Message();

		virtual void Serialise(ostream& os);
		string Serialise();
		static Message* Unserialise(istream& is);
		static Message* Unserialise(string s);

		virtual void UnserialiseType(istream& is) = 0;

		void SetType(MessageType type);
		MessageType GetType();

		string GetStringFromStream(istream& is);


	protected:
		MessageType type;
	};
}