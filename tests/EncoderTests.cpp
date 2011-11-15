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

int oneNode() {
	FI::Encoder e;
	FI::StreamBitWriter writer;
	writer.setStream(&std::cout);
	e.setWriter(&writer);
	e.startDocument();
	e.startNode("root");
	e.endNode();
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

	switch (testNr) {
	case 0:
		return documentOnly();
		break;
	case 1:
		return oneNode();
		break;
	default:
		std::cerr << "Unknown test number: " << testNr << std::endl;
		return 1;
	}
	std::cerr << "Unknown failure: " << testNr << std::endl;
	return 1;
}

#endif /* ENCODERTESTS_H_ */
