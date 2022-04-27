#include "messages.h"

smt::UpdateMessage::UpdateMessage()
{ state = update; }

smt::UpdateMessage::~UpdateMessage() {}

void smt::UpdateMessage::Serialise(std::ostream& os)
{ StateHandler::Serialise(os); }

void smt::UpdateMessage::UnserialiseState(std::istream& is) {}

