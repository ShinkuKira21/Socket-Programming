#include "messages.h"

smt::ConnectMessage::ConnectMessage()
{ state = connect; }

smt::ConnectMessage::~ConnectMessage() {}

void smt::ConnectMessage::Serialise(std::ostream& os)
{
    StateHandler::Serialise(os);
    os << username << std::endl;
}

void smt::ConnectMessage::UnserialiseState(std::istream& is)
{ is >> username; }

void smt::ConnectMessage::SetUsername(const char* username)
{ this->username = username; }

std::string smt::ConnectMessage::GetUsername()
{ return username; }