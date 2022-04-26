#pragma once
#include "Message.h"

namespace tttmessages
{

	class RequestUpdate :
		public Message
	{
	public:
		RequestUpdate();
		~RequestUpdate();

		void Serialise(ostream& os) override;
		void UnserialiseType(istream& is) override;
	};

}