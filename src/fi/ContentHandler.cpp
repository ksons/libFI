#include <fi/ContentHandler.h>
#include <iostream>
#include <sstream>

using namespace std;

namespace FI {

void DefaultContentHandler::startDocument()
{
}

void DefaultContentHandler::endDocument()
{
}

void DefaultContentHandler::startElement(const ParserVocabulary* , const Element &, const std::vector<Attribute> &)
{
}

void DefaultContentHandler::endElement(const ParserVocabulary* , const Element &)
{
}

void DefaultContentHandler::characters(const ParserVocabulary* , const CharacterChunk &)
{
}

void DefaultContentHandler::comment(const ParserVocabulary* , const Comment &)
{
}

}
