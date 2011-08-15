#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <fi/SAXParser.h>
#include <fi/ContentHandler.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>

class FI2XMLContentHandler: public FI::DefaultContentHandler
{

    public:
        FI2XMLContentHandler();

        void setStream(std::ostream* stream);

        virtual void startDocument();
        virtual void startElement(const FI::ParserVocabulary* vocab, const FI::Element &element, const std::vector<FI::Attribute> &attributes);
        virtual void characters(const FI::ParserVocabulary* vocab, const FI::CharacterChunk &chunk);
        virtual void processingInstruction(const FI::ParserVocabulary* vocab, const FI::ProcessingInstruction &pi);
        virtual void comment(const FI::ParserVocabulary* vocab, const FI::Comment &comment);
        virtual void endElement(const FI::ParserVocabulary* vocab, const FI::Element &element);
        virtual void endDocument();
        std::ostream* _stream;
};

