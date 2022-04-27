#include "messages.h"

smt::ActionMessage::ActionMessage()
{ state = action; }

smt::ActionMessage::ActionMessage(const char* msg)
{
    state = accept;
    this->msg = msg;
}

smt::ActionMessage::~ActionMessage() {}

void smt::ActionMessage::Serialise(std::ostream& os)
{
    smt::StateHandler::Serialise(os);
    os << msg << std::endl;
}

void smt::ActionMessage::UnserialiseState(std::istream& is)
{ is >> msg; }

void smt::ActionMessage::SetMessage(const char* msg)
{ this->msg = msg; }

std::string smt::ActionMessage::GetMessage()
{ return msg; }