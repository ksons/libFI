/*
 * EncoderTests.h
 *
 *  Created on: Nov 14, 2011
 *      Author: ksons
 */

#ifndef ENCODERTESTS_H_
#define ENCODERTESTS_H_

#include <iostream>
#include <sstream>
#include <fi/Encoder.h>
#include <fi/StreamBitWriter.h>

int documentOnly() {
	FI::Encoder e;
	FI::StreamBitWriter writer;
	writer.setStream(&std::cout);
	e.setWriter(&writer);
	e.startDocument();
	e.endDocument();
	return 0;
}

int oneElement() {
	FI::Encoder e;
	FI::StreamBitWriter writer;
	writer.setStream(&std::cout);
	e.setWriter(&writer);
	e.startDocument();
	e.startElement("root");
	e.endElement();
	e.endDocument();
	return 0;
}

int twoElements() {
	FI::Encoder e;
	FI::StreamBitWriter writer;
	writer.setStream(&std::cout);
	e.setWriter(&writer);
	e.startDocument();
	e.startElement("root");
	e.endElement();
	e.startElement("root");
	e.endElement();
	e.endDocument();
	return 0;
}
int nestedElements() {
	FI::Encoder e;
	FI::StreamBitWriter writer;
	writer.setStream(&std::cout);
	e.setWriter(&writer);
	e.startDocument();
	e.startElement("node1");
	e.startElement("node2");
	e.startElement("node3");
	e.endElement();
	e.endElement();
	e.endElement();
	e.endDocument();
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Running test with too few arguments." << std::endl;
		return 1;
	}
	std::stringstream ss(argv[1]);
	int testNr;
	ss >> testNr;

	try {
		switch (testNr) {
		case 0:
			return documentOnly();
			break;
		case 1:
			return oneElement();
			break;
		case 2:
			return twoElements();
			break;
		case 3:
			return nestedElements();
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

#endif /* ENCODERTESTS_H_ */
