#include "AcceptMessage.h"

namespace tttmessages
{
	AcceptMessage::AcceptMessage()
	{
		type = accept;
	}

	AcceptMessage::AcceptMessage(string acceptMessage)
	{
		type = accept;
		this->acceptMessage = acceptMessage;
	}


	AcceptMessage::~AcceptMessage()
	{
	}

	string AcceptMessage::GetAcceptMessage()
	{
		return acceptMessage;
	}

	void AcceptMessage::Serialise(ostream& os)
	{
		Message::Serialise(os);
		os << acceptMessage << endl;
	}

	void AcceptMessage::UnserialiseType(istream& is)
	{
		acceptMessage = GetStringFromStream(is);
	}

	void AcceptMessage::SetMessage(string acceptMessage)
	{
		this->acceptMessage = acceptMessage;
	}
}