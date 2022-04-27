#include "messages.h"

smt::AcceptMessage::AcceptMessage()
{ state = accept; }

smt::AcceptMessage::AcceptMessage(const char* msg)
{
    state = accept;
    this->msg = std::string(msg);
}

smt::AcceptMessage::~AcceptMessage() {}

void smt::AcceptMessage::Serialise(std::ostream& os)
{
    StateHandler::Serialise(os);
    os << msg << std::endl;
}

void smt::AcceptMessage::UnserialiseState(std::istream& is)
{ is >> msg; }

void smt::AcceptMessage::SetMessage(const char* msg)
{ this->msg = msg; }

std::string smt::AcceptMessage::GetMessage()
{ return msg; }