#include "ConnectMessage.h"

namespace tttmessages
{

	ConnectMessage::ConnectMessage()
	{
		type = connect;
	}


	ConnectMessage::~ConnectMessage()
	{
	}

	void ConnectMessage::SetUsername(string username)
	{
		this->username = username;
	}

	string ConnectMessage::GetUsername()
	{
		return username;
	}

	void ConnectMessage::Serialise(ostream& os)
	{
		Message::Serialise(os);
		os << username;
	}

	void ConnectMessage::UnserialiseType(istream& is)
	{
		is >> username;
	}
}