#include "argument_helper.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <fi/SAXParser.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>

#include "FI2XMLContentHandler.h"

using namespace std;


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
	handler.setStream(&std::cout);
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

  return 0;
}
