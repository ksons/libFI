#include "Encoder.h"
#include "EncoderFunctions.h"

#include <cassert>
#include <iostream>

namespace FI {

struct NodeInfo {
	NodeInfo(const std::string &_name) :
		name(_name), attributesTerminated(true), isChecked(false) {
	}
	std::string name;
	bool attributesTerminated;
	bool isChecked;
};

class NodeInfoStack: public std::vector<NodeInfo> {
};

Encoder::Encoder() :
	_w(0) {
	_infoStack = new NodeInfoStack();
}

Encoder::~Encoder() {
	delete _infoStack;
}

void Encoder::setWriter(IBitWriter* writer) {
	_w = writer;
}

void Encoder::startDocument() {
	assert(_w);
	EncoderFunctions::encodeHeader(_w, false);
	EncoderFunctions::encodeInitialVocabulary(_w, "hallo");
}

void Encoder::endDocument() {
	EncoderFunctions::encodeTermination(_w);
	// This encoding ends either on the eighth or
	// on the fourth bit of an octet, depending on
	// the content of the fast infoset document.
	// In the latter case, the four bits '0000'
	// (padding) are appended to the bit stream.
	if (_w->getBitPos() == 5)
		_w->putBits("0000");

	assert(_w->getBitPos() == 1);
}

void Encoder::startNode(const std::string name) {
	if (!_infoStack->empty()) {
		checkNode(false);
		//?_encoder.fillByte();
	}

	_infoStack->push_back(NodeInfo(name));

	// ITU C.3.7.2: element is present
	_w->putBit(0);
}

void Encoder::endNode() {
	assert(!_infoStack->empty());
	checkNode(false);
	if (!_infoStack->back().attributesTerminated) {
		// ITU C.3.6.2: End of attribute
		EncoderFunctions::encodeTermination(_w);
	}
	// ITU C.3.8: The four bits '1111' (termination) are appended.
	EncoderFunctions::encodeTermination(_w);
	_infoStack->pop_back();
}

void Encoder::checkNode(bool fromAttribute) {
	if (!this->_infoStack->back().isChecked) {
		// Element has no attributes
		// ITU C.3.3: otherwise, the bit '0' (absence) is appended
		_w->putBit(0);

		// Write Node name (starting at third bit)
		// C.3.5 The value of the component qualified-name is encoded as described in C.18.
		encodeQualifiedNameOrIndex3(_infoStack->back().name);

		this->_infoStack->back().isChecked = true;
	}
	// Element has attributes and childs
	else if (!this->_infoStack->back().attributesTerminated) {
		// ITU C.3.6.2: End of attribute
		EncoderFunctions::encodeTermination(_w);
		this->_infoStack->back().attributesTerminated = true;
	}
}

// C.18 Encoding of the QualifiedNameOrIndex type starting on the third bit of an octet
void Encoder::encodeQualifiedNameOrIndex3(const std::string &name) {
	assert(_w->getBitPos() == 3);
	// C.18.3 If the alternative literal-qualified-name is present, then the four bits '1111' (identification) are
	// appended
	_w->putBits("1111");
	// C.18.3.1 For each of the optional components prefix and namespace-name (in this order), if the component is
	// present, then the bit '1' (presence) is appended to the bit stream; otherwise, the bit '0' (absence) is appended.
	_w->putBit(0);
	_w->putBit(0);
	// C.18.3.4 The component local-name is encoded as described in C.13.
	encodeIdentifyingStringOrIndex(name);

}

void Encoder::encodeIdentifyingStringOrIndex(const std::string &name) {
	assert(_w->getBitPos() == 1);
	// C.13.3 If the alternative literal-character-string is present, then the bit '0' (discriminant) is appended
	_w->putBit(0);
	// and the literal-character-string is encoded as described in C.22.
	EncoderFunctions::encodeNonEmptyOctetString2(_w, FI::NonEmptyOctetString(name));
}


} // end namespace FI

