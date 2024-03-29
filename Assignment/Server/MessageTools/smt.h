#pragma once
#include <limits>
#include <sstream>

// server message tools
namespace smt 
{
    // Configure on creation
    enum EState 
    {
        connect,
        disconnect,
        accept,
        refuse,
        update,
        action
    };

    enum EGamePhase {
        waiting,
        playing,
        p1win,
        p2win,
        draw
    };

    class StateHandler 
    {
        protected:
            EState state;

        public:
            StateHandler();
            virtual ~StateHandler();
            
            std::string Serialise();
            virtual void Serialise(std::ostream& os);

            static StateHandler* Unserialise(std::istream& is);
            static StateHandler* Unserialise(const char* msg);

            virtual void UnserialiseState(std::istream& is) = 0;

            void SetState(EState state);
            EState GetState();

            std::string GetStringFromStream(std::istream& is);
    };
}