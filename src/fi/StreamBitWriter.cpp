/*
 * StreamBitWriter.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: ksons
 */

#include <fi/StreamBitWriter.h>
#include <cassert>
#include <stdexcept>

namespace FI {

StreamBitWriter::StreamBitWriter() :
	_currentBitPos(0),_currentByte(0), _stream(0) {
}

StreamBitWriter::~StreamBitWriter() {
}

void StreamBitWriter::setStream(std::ostream* stream) {
	_stream = stream;
}

void StreamBitWriter::putBit(bool on) {
	assert(_currentBitPos < 8);
	if (on) {
		unsigned char pos = _currentBitPos;
		unsigned char mask = (unsigned char) (0x80 >> pos);
		_currentByte |= mask;
	}
	_currentBitPos++;
	tryFlush();

}

void StreamBitWriter::putBits(const std::string &bitString) {
	for (std::string::const_iterator I = bitString.begin(); I != bitString.end(); I++)
		putBit((*I) == '1');
}

// Puts the integer value to the stream using count bits
// for encoding
void StreamBitWriter::putBits(unsigned int value, unsigned char count) {
	// Can be optimized
	while (count > 0) {
		count = this->append(value, count);
	}
}
// Puts whole bytes to the file stream. CurrentBytePos must
// be 0 for this
void StreamBitWriter::putBytes(const unsigned char* bytes, size_t length) {
	if (_currentBitPos == 0)
		_stream->write(reinterpret_cast<const char*> (bytes), length);
	else {
		assert(false);
		throw std::runtime_error("Wrong position in FiEncode::PutBytes");
	}
}

int StreamBitWriter::getBitPos() {
	return _currentBitPos + 1;
}

unsigned char StreamBitWriter::append(unsigned int value, unsigned char count) {
	assert(_currentBitPos < 8);
	while ((_currentBitPos < 8) && count > 0) {
		// Value and der Stelle i
		unsigned int mask = 1;
		bool isSet = !(((mask << (count - 1)) & value) == 0);
		if (isSet) {
			_currentByte |= static_cast<unsigned char> (0x80 >> _currentBitPos);
		}
		_currentBitPos++;
		count--;
	}
	tryFlush();
	return count;
}

void StreamBitWriter::tryFlush() {
	assert(_stream);
	if (_currentBitPos == 8) {
		_stream->put(_currentByte);
		_currentByte = 0;
		_currentBitPos = 0;
	}

}

// Fills up the current byte with 0 values
/*  inline void fillByte() {
 while (_currentBitPos)
 putBit(0);
 };*/

} // end namespace FI

