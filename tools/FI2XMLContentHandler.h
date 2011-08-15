#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <fi/SAXParser.h>
#include <fi/ContentHandler.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>



class FI2XMLContentHandler: public FI::DefaultContentHandler {

public:
	FI2XMLContentHandler() : _stream(0) {};

	void setStream(std::ostream* stream) {
		_stream = stream;

	}

		void startDocument() {
			if(!_stream)
				throw std::runtime_error("FI2XMLContentHandler: Stream is not set.");

		}

		void startElement(const FI::ParserVocabulary* vocab, const FI::Element &element, const std::vector<FI::Attribute> &attributes) {
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

			// Write attributes
			std::vector<FI::Attribute>::const_iterator I = attributes.begin();
			FI::ResolvedQualifiedName attributeName;
			while (I != attributes.end()) {
				vocab->resolveAttributeName((*I)._qualifiedName, attributeName);
				*_stream << " " << attributeName;
				*_stream << "=\"" << vocab->resolveAttributeValue((*I)._normalizedValue) << "\"";
				I++;
			}
			*_stream << ">";
		}

		void characters(const FI::ParserVocabulary* vocab, const FI::CharacterChunk &chunk) {
			*_stream << vocab->resolveCharacterChunk(chunk._characterCodes);
		}

    void processingInstruction(const FI::ParserVocabulary* vocab, const FI::ProcessingInstruction &pi) {
      *_stream << "<?" << vocab->resolveOtherNCName(pi._target) << " " << vocab->resolveOtherString(pi._content) << "?>";
    }

		void comment(const FI::ParserVocabulary* vocab, const FI::Comment &comment) {
			*_stream << "<!--" << vocab->resolveOtherString(comment._content) << "-->";
		}

		void endElement(const FI::ParserVocabulary* vocab, const FI::Element &element) {
			FI::ResolvedQualifiedName elementName;
			vocab->resolveElementName(element._qualifiedName, elementName);
			*_stream << "</" << elementName << ">";
		}

		void endDocument() {
			//*_stream << endl << "End Document" << endl;
		}
	
	std::ostream* _stream;
};


