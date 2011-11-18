#include "argument_helper.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <fi/SAXParser.h>
#include <fi/ContentHandler.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>

using namespace std;

int main(int ac, char* av[]) {

	dsr::Argument_helper ah;
	std::string input_filename;

	ah.new_string("input_filename", "The name of the FI encoded input file (or '-' for stdin)", input_filename);

	ah.set_description("Prints the tables for a given FI file");
	ah.set_author("Kristian Sons, kristian.sons@supporting.com");
	ah.set_version(0.1f);
	ah.set_build_date(__DATE__);

	ah.process(ac, av);

	FI::SAXParser parser;
  FI::DefaultContentHandler handler;
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
				std::string name = parser._vocab->getTableEntry(FI::ATTRIBUTE_VALUE, i).toString();
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
				std::string name = parser._vocab->getTableEntry(FI::CHARACTER_CHUNK, i).toString();
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
				std::string name = parser._vocab->getTableEntry(FI::LOCAL_NAME, i).toString();
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
				std::string name = parser._vocab->getTableEntry(FI::NAMESPACE_NAME, i).toString();
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
				std::string name = parser._vocab->getTableEntry(FI::PREFIX, i).toString();
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
