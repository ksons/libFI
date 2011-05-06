#include "argument_helper.h"

#include <iostream>
#include <fstream>

#include <fi/SAXParser.h>
#include <fi/ContentHandler.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>

using namespace std;

class FI2XMLContentHandler: public FI::DefaultContentHandler {

		void startDocument() {
			cout << "Start Document" << endl;
		}

		void startElement(const FI::ParserVocabulary* vocab, const FI::Element &element, const std::vector<FI::Attribute> &attributes) {
			FI::ResolvedQualifiedName elementName;
			vocab->resolveElementName(element._qualifiedName, elementName);

			cout << "<" << elementName;
			// Write namespaces
			std::vector<FI::NamespaceAttribute>::const_iterator N = element._namespaceAttributes.begin();
			while (N != element._namespaceAttributes.end()) {
				std::string prefix = vocab->resolvePrefix((*N)._prefix).toString();
				cout << " xmlns";
				if (!prefix.empty()) {
					cout << ":" << prefix;
				}
				cout << "=\"";
				cout << vocab->resolveNamespaceName((*N)._namespaceName);
				cout << "\"";
				N++;
			}

			// Write attributes
			std::vector<FI::Attribute>::const_iterator I = attributes.begin();
			FI::ResolvedQualifiedName attributeName;
			while (I != attributes.end()) {
				vocab->resolveAttributeName((*I)._qualifiedName, attributeName);
				cout << " " << attributeName;
				cout << "=\"" << vocab->resolveAttributeValue((*I)._normalizedValue) << "\"";
				I++;
			}
			cout << ">";
		}

		void characters(const FI::ParserVocabulary* vocab, const FI::CharacterChunk &chunk) {
			cout << vocab->resolveCharacterChunk(chunk._characterCodes);
		}

		void comment(const FI::ParserVocabulary* vocab, const FI::Comment &comment) {
			cout << "<!--" << vocab->resolveOtherString(comment._content) << "-->";
		}

		void endElement(const FI::ParserVocabulary* vocab, const FI::Element &element) {
			FI::ResolvedQualifiedName elementName;
			vocab->resolveElementName(element._qualifiedName, elementName);
			cout << "</" << elementName << ">";
		}

		void endDocument() {
			cout << endl << "End Document" << endl;
		}

};

int main(int ac, char* av[]) {

	dsr::Argument_helper ah;
	std::string input_filename;

	ah.new_string("input_filename", "The name of the FI encoded input file (or '-' for stdin)", input_filename);

	ah.set_description("A simple test application for the FI parser");
	ah.set_author("Kristian Sons, kristian.sons@supporting.com");
	ah.set_version(0.1f);
	ah.set_build_date(__DATE__);

	ah.process(ac, av);

	FI::SAXParser parser;
	FI2XMLContentHandler handler;
	parser.setContentHandler(&handler);
	ifstream file;

	if (input_filename == "-") {
		//_setmode(_fileno( stdin ), _O_BINARY);
		parser.setStream(&std::cin);
	} else {
		file.open(input_filename.c_str(), ios::in | ios::binary);
		if (!file.is_open()) {
			std::cerr << "Can't open file: " << input_filename << std::endl;
			exit(1);
		}
		std::cout << "Opening " << input_filename << std::endl;
		parser.setStream(&file);
	}
	try {
		parser.parse();
	}
	catch (std::exception& e) {
		cerr << endl << "Parsing failed: " << e.what() << endl;
	}
	if (file.is_open())
		file.close();

	if (parser._vocab) {
		std::cout << "Attribute Name Table" << std::endl;
		for (int i = 1;;) {
			try {
				FI::ResolvedQualifiedName name;
				parser._vocab->resolveQualifiedName(parser._vocab->getAttributeTable()->get(i), name);
				std::cout << i << ": {" << name._namespaceName << "}" << name._prefix << ":" << name._localName << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Attribute Value Table" << std::endl;
		for (int i = 1;;) {
			try {
				std::string name = parser._vocab->getAttributeValue(i).toString();
				std::cout << i << ": " << name << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Character Content Chunk Table" << std::endl;
		for (int i = 1;;) {
			try {
				std::string name = parser._vocab->getCharacterChunk(i).toString();
				std::cout << i << ": " << name << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Element Name Table" << std::endl;
		for (int i = 1;;) {
			try {
				FI::ResolvedQualifiedName name;
				parser._vocab->resolveQualifiedName(parser._vocab->getElementTable()->get(i), name);
				std::cout << i << ": {" << name._namespaceName << "}" << name._prefix << ":" << name._localName << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Local Name Table" << std::endl;
		for (int i = 1;;) {
			try {
				std::string name = parser._vocab->getLocalName(i).toString();
				std::cout << i << ": " << name << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Namespace Name Table" << std::endl;
		for (int i = 1;;) {
			try {
				std::string name = parser._vocab->getNamespaceName(i).toString();
				std::cout << i << ": " << name << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}
		std::cout << "Prefix Table" << std::endl;
		for (int i = 1;;) {
			try {
				std::string name = parser._vocab->getPrefix(i).toString();
				std::cout << i << ": " << name << std::endl;
				i++;
			}
			catch (std::exception& ) {
				break;
			}
		}

	}

	return 0;
}
