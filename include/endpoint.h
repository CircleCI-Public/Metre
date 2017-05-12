//
// Created by dwd on 11/05/17.
//

#ifndef METRE_ENDPOINT_H
#define METRE_ENDPOINT_H

#include "jid.h"
#include "stanza.h"
#include "capability.h"

namespace Metre {
    class Capability;

    class Endpoint {
    public:
        static Endpoint &endpoint(Jid const &);

        Endpoint(Jid const &);

        virtual void process(Presence const &presence);

        virtual void process(Message const &message);

        virtual void process(Iq const &iq);

        void process(Stanza const &stanza);

        // Config API:
        void add_capability(std::string const &name);

        void add_handler(std::string const &xmlns, std::string const &local, std::function<void(Iq const &)> const &fn);

        virtual ~Endpoint();

    private:
        Jid m_jid;
        std::list<std::unique_ptr<Capability>> m_capabilities;
        std::map<std::pair<std::string, std::string>, std::function<void(Iq const &)>> m_handlers;
    };
}

#endif //METRE_ENDPOINT_H
