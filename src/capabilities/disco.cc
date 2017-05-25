//
// Created by dwd on 24/05/17.
//

#include <capability.h>

using namespace Metre;

namespace {
    class Disco : public Capability {
    public:
        class Description : public Capability::Description<Disco> {
        public:
            Description(std::string const &name) : Capability::Description<Disco>(name) {
                m_disco.emplace_back("http://jabber.org/protocol/disco#info");
                m_disco.emplace_back("http://jabber.org/protocol/disco#items");
            }
        };

        Disco(BaseDescription const &descr, Endpoint &endpoint) : Capability(descr, endpoint) {
            endpoint.add_handler("http://jabber.org/protocol/disco#items", "query", [this](Iq const &iq) {

            });
            endpoint.add_handler("http://jabber.org/protocol/disco#info", "query", [this](Iq const &iq) {
                return info(iq);
            });
        }

        bool info(Iq const &iq) {
            auto query = iq.node()->first_node();
            auto node = query->first_attribute("node");
            if (node) {
                // We don't know what to do here yet!
                // TODO : dispatch to node endpoint.
                auto bounce = iq.create_bounce(Stanza::Error::service_unavailable);
                m_endpoint.send(std::move(bounce));
            } else {
                rapidxml::xml_document<> doc;
                auto response = doc.allocate_node(rapidxml::node_element, "query");
                response->append_attribute(doc.allocate_attribute("xmlns", "http://jabber.org/protocol/disco#info"));
                for (auto const &cap : m_endpoint.capabilities()) {
                    for (auto const &feature : cap->description().disco()) {
                        auto feat = doc.allocate_node(rapidxml::node_element, "feature");
                        feat->append_attribute(doc.allocate_attribute("var", feature.c_str()));
                        response->append_node(feat);
                    }
                }
                std::unique_ptr<Iq> result{new Iq(iq.to(), iq.from(), Metre::Iq::RESULT, iq.id())};
                result->payload(response);
                m_endpoint.send(std::move(result));
            }
            return true;
        }
    };

    DECLARE_CAPABILITY(Disco, "disco");
}