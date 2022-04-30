#pragma once
#include "../smt.h"

namespace smt {
    class ConnectMessage : public StateHandler {
        private:
            std::string username;

        public:
            ConnectMessage();
            virtual ~ConnectMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;

            void SetUsername(const char* username);
            std::string GetUsername();
    };

    class DisconnectMessage : public StateHandler {
        private:
            std::string msg;

        public:
            DisconnectMessage();
            DisconnectMessage(const char* msg);
            virtual ~DisconnectMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;

            void SetMessage(const char* msg);
            std::string GetMessage();
    };

    class AcceptMessage : public StateHandler {
        private:
            std::string msg;

        public:
            AcceptMessage();
            AcceptMessage(const char* msg);
            virtual ~AcceptMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;

            void SetMessage(const char* msg);
            std::string GetMessage();
    };

    class RefuseMessage : public StateHandler {
        private:
            std::string msg;

        public:
            RefuseMessage();
            RefuseMessage(const char* msg);
            virtual ~RefuseMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;

            void SetMessage(const char* msg);
            std::string GetMessage();
    };

    class UpdateMessage : public StateHandler {
        private:
            std::string msg;

        public:
            UpdateMessage();
            virtual ~UpdateMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;
    };

    class ActionMessage : public StateHandler {
        private:
            std::string msg;
    
        public:
            ActionMessage();
            ActionMessage(const char* msg);
            virtual ~ActionMessage();

            void Serialise(std::ostream& os) override;
            void UnserialiseState(std::istream& is) override;

            void SetMessage(const char* msg);
            std::string GetMessage();
    };
}