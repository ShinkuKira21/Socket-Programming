//
// Created by edwardpatch1 on 4/30/22.
//

#include "smt.h"
#include "Messages/messages.h"

smt::StateHandler::StateHandler() {}
smt::StateHandler::~StateHandler() {}

void smt::StateHandler::Serialise(std::ostream& os)
{ os << state << std::endl; }

std::string smt::StateHandler::Serialise()
{
    std::stringstream stream;
    Serialise(stream);

    return stream.str();
}

smt::StateHandler* smt::StateHandler::Unserialise(std::istream& is)
{
    StateHandler* msgState = nullptr;

    unsigned int uState = 0;
    EState eState;

    if(is >> uState)
        eState = static_cast<EState>(uState);

    switch(eState)
    {
        case connect :
            msgState = new ConnectMessage();
            break;

        case disconnect :
            msgState = new DisconnectMessage();
            break;

        case accept :
            msgState = new AcceptMessage();
            break;

        case refuse :
            msgState = new RefuseMessage();
            break;

        case action:
            msgState = new ActionMessage();
            break;

        default:
            break;
    }

    msgState->UnserialiseState(is);
    return msgState;
}

smt::StateHandler* smt::StateHandler::Unserialise(const char* msg)
{
    std::stringstream stream;
    stream.str(msg);
    return Unserialise(stream);
}

void smt::StateHandler::SetState(EState state)
{ this->state = state; }

smt::EState smt::StateHandler::GetState()
{ return state; }

std::string smt::StateHandler::GetStringFromStream(std::istream& is)
{
    std::string msg;
    is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    while(is.peek() != '\n' && is.peek() != EOF)
    {
        std::string tmp;
        is >> tmp;
        msg += tmp + " ";
    }

    return msg;
}