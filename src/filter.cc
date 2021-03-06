/***

Copyright 2013-2016 Dave Cridland
Copyright 2014-2016 Surevine Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

***/

#include "filter.h"
#include "xmlstream.h"
#include "stanza.h"

using namespace Metre;

std::map<std::string, Filter::BaseDescription *> &Filter::all_filters() {
    static std::map<std::string, Filter::BaseDescription *> s_filters;
    return s_filters;
}

rapidxml::xml_node<> *Filter::BaseDescription::config(rapidxml::xml_document<> &doc) {
    auto config = doc.allocate_node(rapidxml::node_element, name.c_str());
    do_config(doc, config);
    return config;
}

void Filter::BaseDescription::config(rapidxml::xml_node<> *) {
}

rapidxml::xml_node<> *Filter::dump_config(rapidxml::xml_document<> &doc) {
    auto config = doc.allocate_node(rapidxml::node_element, m_description.name.c_str());
    do_dump_config(doc, config);
    return config;
}