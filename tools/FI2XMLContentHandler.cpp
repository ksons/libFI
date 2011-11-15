#include "FI2XMLContentHandler.h"

FI2XMLContentHandler::FI2XMLContentHandler() :
    _stream(0)
{
}

void FI2XMLContentHandler::setStream(std::ostream* stream)
{
    _stream = stream;
}

void FI2XMLContentHandler::startDocument()
{
    if (!_stream)
        throw std::runtime_error("FI2XMLContentHandler: Stream is not set.");

}

void FI2XMLContentHandler::startElement(const FI::ParserVocabulary* vocab, const FI::Element &element, const std::vector<FI::Attribute> &attributes)
{
    FI::ResolvedQualifiedName elementName;
    vocab->resolveElementName(element._qualifiedName, elementName);

    *_stream << "<" << elementName;
    // Write namespaces
    std::vector<FI::NamespaceAttribute>::const_iterator N = element._namespaceAttributes.begin();
    while (N != element._namespaceAttributes.end()) {
        std::string prefix = vocab->resolvePrefix((*N)._prefix).toString();
        *_stream << " xmlns";
        if (!prefix.empty()) {
            *_stream << ":" << prefix;
        }
        *_stream << "=\"";
        *_stream << vocab->resolveNamespaceName((*N)._namespaceName);
        *_stream << "\"";
        N++;
    }
    *_stream << ">";
}

void FI2XMLContentHandler::characters(const FI::ParserVocabulary* vocab, const FI::CharacterChunk &chunk)
{
    *_stream << vocab->resolveCharacterChunk(chunk._characterCodes);
}

void FI2XMLContentHandler::processingInstruction(const FI::ParserVocabulary* vocab, const FI::ProcessingInstruction &pi)
{
    *_stream << "<?" << vocab->resolveOtherNCName(pi._target) << " " << vocab->resolveOtherString(pi._content) << "?>";
}

void FI2XMLContentHandler::comment(const FI::ParserVocabulary* vocab, const FI::Comment &comment)
{
    *_stream << "<!--" << vocab->resolveOtherString(comment._content) << "-->";
}

void FI2XMLContentHandler::endElement(const FI::ParserVocabulary* vocab, const FI::Element &element)
{
    FI::ResolvedQualifiedName elementName;
    vocab->resolveElementName(element._qualifiedName, elementName);
    *_stream << "</" << elementName << ">";
}

void FI2XMLContentHandler::endDocument()
{
    //*_stream << endl << "End Document" << endl;
}

