/*
 * DecoderTests.h
 *
 *  Created on: Nov 14, 2011
 *      Author: ksons
 */

#ifndef DECODERTESTS_H_
#define DECODERTESTS_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

#include <fi/SAXParser.h>
#include <fi/ContentHandler.h>
#include <fi/ParserVocabulary.h>
#include <fi/QualifiedNameTable.h>


int getSize(FI::TableNames table, FI::ParserVocabulary* v) {
	int i = 0;
	while (true) {
		try {
			v->getTableEntry(table, i+1);
			i++;
		}
		catch (std::exception& ) {
			break;
		}
	}
	return i;
}

int elementsOnly(const std::string &fileName) {
	FI::SAXParser p;
	FI::DefaultContentHandler handler;
	p.setContentHandler(&handler);

	std::ifstream file;
	file.open(fileName.c_str(), std::ios::in | std::ios::binary);
	p.setStream(&file);

	p.parse();

	FI::ParserVocabulary* v = p._vocab;
	assert(v);

	int count;
	count = v->getAttributeTable()->size();
	assert(count == 0);

	count = v->getElementTable()->size();
	assert(count == 5);

	FI::ResolvedQualifiedName name;
	v->resolveQualifiedName(v->getElementTable()->get(1), name);

	assert(name._localName.toString() == "note");
	assert(name._namespaceName.length() == 0);
	assert(name._prefix.length() == 0);

	assert(getSize(FI::CHARACTER_CHUNK, v) == 4);
	assert(getSize(FI::NAMESPACE_NAME, v) == 1);
	assert(getSize(FI::LOCAL_NAME, v) == 5);

	assert(v->getTableEntry(FI::LOCAL_NAME, 5).toString() == "body");

	return 0;
}

int elementsAttributes(const std::string &fileName) {
	FI::SAXParser p;
	FI::DefaultContentHandler handler;
	p.setContentHandler(&handler);

	std::ifstream file;
	file.open(fileName.c_str(), std::ios::in | std::ios::binary);
	p.setStream(&file);

	p.parse();

	FI::ParserVocabulary* v = p._vocab;
	assert(v);

	int count;
	count = v->getAttributeTable()->size();
	assert(count == 3);

	count = v->getElementTable()->size();
	assert(count == 5);

	FI::ResolvedQualifiedName name;
	v->resolveQualifiedName(v->getElementTable()->get(1), name);

	assert(name._localName.toString() == "note");
	assert(name._namespaceName.length() == 0);
	assert(name._prefix.length() == 0);

	assert(getSize(FI::CHARACTER_CHUNK, v) == 4);
	assert(getSize(FI::NAMESPACE_NAME, v) == 1);
	assert(getSize(FI::LOCAL_NAME, v) == 8);

	assert(v->getTableEntry(FI::LOCAL_NAME, 5).toString() == "heading");

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cerr << "Running test with too few arguments." << std::endl;
		return 1;
	}
	std::stringstream ss(argv[1]);
	int testNr;
	ss >> testNr;

	try {
		switch (testNr) {
		case 0:
			return elementsOnly(argv[2]);
			break;
		case 1:
			return elementsAttributes(argv[2]);
			break;
		default:
			std::cerr << "Unknown test number: " << testNr << std::endl;
			return 1;
		}
	} catch (...) {
		std::cerr << "Unknown exeption occured: " << testNr << std::endl;
		return 1;
	}
	std::cerr << "Unknown failure: " << testNr << std::endl;
	return 1;
}

#endif /* DECODERTESTS_H_ */
