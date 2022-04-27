#include "messages.h"

smt::RefuseMessage::RefuseMessage()
{ state = refuse; }

smt::RefuseMessage::RefuseMessage(const char* msg)
{
    state = refuse;
    this->msg = msg;
}

smt::RefuseMessage::~RefuseMessage() {}

void smt::RefuseMessage::Serialise(std::ostream& os)
{
    os << state << std::endl;
    os << msg << std::endl;
}

void smt::RefuseMessage::UnserialiseState(std::istream& is)
{ is >> msg; }

void smt::RefuseMessage::SetMessage(const char* msg)
{ this->msg = msg; }

std::string smt::RefuseMessage::GetMessage()
{ return msg; }