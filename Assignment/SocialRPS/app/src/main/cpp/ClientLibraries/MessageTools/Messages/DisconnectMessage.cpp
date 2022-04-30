#include "messages.h"

smt::DisconnectMessage::DisconnectMessage()
{ state = disconnect; }

smt::DisconnectMessage::DisconnectMessage(const char* msg)
{
    state = disconnect;
    this->msg = std::string(msg);
}

smt::DisconnectMessage::~DisconnectMessage() {}

void smt::DisconnectMessage::Serialise(std::ostream& os)
{
    StateHandler::Serialise(os);
    os << msg << std::endl;
}

void smt::DisconnectMessage::UnserialiseState(std::istream& is)
{ is >> msg; }

void smt::DisconnectMessage::SetMessage(const char* msg)
{ this->msg = msg; }

std::string smt::DisconnectMessage::GetMessage()
{ return msg; }