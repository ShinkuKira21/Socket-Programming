#pragma once
#include "Message.h"

namespace tttmessages
{

	class ConnectMessage :
		public Message
	{
	public:
		ConnectMessage();
		~ConnectMessage();

		void SetUsername(string username);
		string GetUsername();

		void Serialise(ostream& os) override;
		void UnserialiseType(istream& is) override;

	private:
		string username;
	};

}