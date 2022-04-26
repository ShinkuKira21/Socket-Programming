#include "RequestUpdate.h"

namespace tttmessages
{

	RequestUpdate::RequestUpdate()
	{
		type = requestupdate;
	}


	RequestUpdate::~RequestUpdate()
	{
	}

	void RequestUpdate::Serialise(ostream& os)
	{
		Message::Serialise(os);
	}

	void RequestUpdate::UnserialiseType(istream& is)
	{
	}
}