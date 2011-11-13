#include <fi/EncoderFunctions.h>
#include <fi/Constants.h>
#include <fi/EncodingAlgorithms.h>
#include <cassert>

using namespace std;

namespace FI {

void EncoderFunctions::encodeHeader(IBitWriter* w, bool /* encodeXmlDecl */) {
	assert(w);
	assert(w->getBitPos() == 0);

	// ITU 12.6: 1110000000000000
	w->putBits("1110000000000000");
	// ITU 12.7 / 12.9: Version of standard: 1 as 16bit
	w->putBits("0000000000000001");
	// ITU 12.8: The bit '0' (padding) shall then be appended to the bit stream
	w->putBit(0);
}

void EncoderFunctions::encodeInitialVocabulary(IBitWriter* w, const std::string &external_voc) {
	assert(w);
	// TODO: assert(w->getBitPos() == 0);

	// ITU C.2.3
	w->putBit(0); // additional-data
	w->putBit(1); // initial-vocabulary
	w->putBit(0); // notations
	w->putBit(0); // unparsed-entities
	w->putBit(0); // character-encoding-scheme
	w->putBit(0); // standalone
	w->putBit(0); // and version
	// ITU C.2.5: padding '000' for optional component initial-vocabulary
	w->putBits("000");
	// ITU C.2.5.1: For each of the thirteen optional components:
	// presence ? 1 : 0
	w->putBits("1000000000000"); // 'external-vocabulary'
	// ITU C.2.5.2: external-vocabulary is present
	w->putBit(0);
	encodeNonEmptyOctetString2(w, NonEmptyOctetString(external_voc));
}

void EncoderFunctions::encodeTermination(IBitWriter* w) {
	assert(w);
	// ITU C.2.12: The four bits '1111' (termination) are appended
	w->putBits("1111");
}

/// C.19 Encoding of the EncodedCharacterString type starting 
/// on the third bit of an octet
void EncoderFunctions::encodeCharacterString3(IBitWriter* w, const std::string &value) {
	assert(w);
	// We want to start at position 3
	assert(w->getBitPos() == 3);

	// ITU C.19.3.1 If the alternative utf-8 is present, then the two bits '00'
	// are appended to the bit stream.
	w->putBits("00");
	// ITU C.19.4: The component bytes is encoded as described in C.23.
	encodeNonEmptyByteString5(w, NonEmptyOctetString(value));
}

// ITU C.22 Encoding of the NonEmptyOctetString type starting 
// on the second bit of an octet
void EncoderFunctions::encodeNonEmptyOctetString2(IBitWriter* w, const NonEmptyOctetString &value) {
	assert(w);
	// We want to start at position 2
	assert(w->getBitPos() == 2);
	// Non-empty bytes
	assert(!value.empty());

	size_t length = value.size();
	if (length <= 64) {
		w->putBit(0);
		w->putBits(static_cast<int> (length) - 1, 6);
	} else if (length <= 320) {
		w->putBits("10");
		w->putBits(static_cast<int> (length) - 65, 8);
	} else {
		w->putBits("1100");
		w->putBits(static_cast<int> (length) - 321, 32);
	}
	w->putBytes(value.c_str(), value.size());
}

// ITU C.23: Encoding of the NonEmptyByteString starting
// on the fifth bit of an byte
void EncoderFunctions::encodeNonEmptyByteString5(IBitWriter* w, const NonEmptyOctetString &value) {
	assert(w);
	// We want to start at position 5
	assert(w->getBitPos() == 5);
	// Non-empty bytes
	assert(!value.empty());

	size_t length = value.size();
	if (length <= 8) {
		w->putBit(0);
		w->putBits(static_cast<int> (length) - 1, 3);
	} else if (length <= 264) {
		w->putBits("1000");
		w->putBits(static_cast<int> (length) - 9, 8);
	} else {
		w->putBits("1100");
		w->putBits(static_cast<int> (length) - 265, 32);
	}
	w->putBytes(value.c_str(), value.size());
}

// ITU C.25: Encoding of integers in the range 1 to 2^20
// starting on the second bit of an byte
void EncoderFunctions::encodeInteger2(IBitWriter* w, int value) {
	assert(w);
	// We want to start at position 2
	assert(w->getBitPos() == 2);

	if (value <= 64) // ITU  C.25.2
	{
		w->putBits("0");
		w->putBits(value - 1, 6);
	} else if (value <= 8256) // ITU C.25.3
	{
		w->putBits("10");
		w->putBits(value - 65, 13);
	} else // ITU C.25.4
	{
		w->putBits("110");
		w->putBits(value - 8257, 20);
	}
}

// ITU C.27: Encoding of integers in the range 1 to 2^20
// starting on the third bit of an byte
void EncoderFunctions::encodeInteger3(IBitWriter* w, int value) {
	assert(w);
	// We want to start at position 3
	assert(w->getBitPos() == 3);

	if (value <= 32) // ITU  C.27.2
	{
		w->putBit(0);
		w->putBits(value - 1, 5);
	} else if (value <= 2080) // ITU C.27.3
	{
		w->putBits("100");
		w->putBits(value - 33, 11);
	} else if (value < 526368) // ITU C.27.4
	{
		w->putBits("101");
		w->putBits(value - 2081, 19);
	} else // ITU C.27.5
	{
		w->putBits("1100000000");
		w->putBits(value - 526369, 20);
	}
}

void EncoderFunctions::encodeAttributeFloatArray(IBitWriter* w, const float* values, size_t size) {
	assert(w);
	// We want to start at position 3
	assert(w->getBitPos() == 3);

	// ITU 10.8.1: This encoding algorithm has a vocabulary table index of 7
	encodeEncodingAlgorithmStart(w, FloatEncodingAlgorithm::ALGORITHM_ID);

	NonEmptyOctetString octets;
	FloatEncodingAlgorithm::encode(values, size, octets);
	encodeNonEmptyByteString5(w, octets);
}

void EncoderFunctions::encodeAttributeIntegerArray(IBitWriter* w, const int* values, size_t size) {
	assert(w);
	// We want to start at position 3
	assert(w->getBitPos() == 3);

	// ITU 10.8.1: This encoding algorithm has a vocabulary table index of 4
	encodeEncodingAlgorithmStart(w, IntEncodingAlgorithm::ALGORITHM_ID);

	NonEmptyOctetString octets;
	IntEncodingAlgorithm::encode(values, size, octets);
	encodeNonEmptyByteString5(w, octets);
}

} // namespace FI

