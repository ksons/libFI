/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FI_ENCODERFUNCTIONS_H
#define FI_ENCODERFUNCTIONS_H

#include <fi/Types.h>

namespace FI {

class IBitWriter;

/**  
 *  Encoder Functions.
 */
class LIBFI_EXPORT EncoderFunctions
{
public:
	
	// ITU 12.6 - 12.8
	static void encodeHeader(IBitWriter* w, bool encodeXmlDecl);


	static void encodeInitialVocabulary(IBitWriter* w, const std::string &external_voc);

	static void encodeTermination(IBitWriter* w);

	// ITU C.14 Encoding of the NonIdentifyingStringOrIndex 
	// type starting on the first bit of an octet
	//void encodeNonIdentifyingStringOnFirstBit();

	// ITU C.19 Encoding of the EncodedCharacterString type starting 
	// on the third bit of an octet
	void encodeCharacterString3(IBitWriter* w, const std::string &value);

	// ITU C.22 Encoding of the NonEmptyOctetString type starting 
	// on the second bit of an octet
	static void encodeNonEmptyOctetString2(IBitWriter* w, const NonEmptyOctetString &value);

	// ITU C.23: Encoding of the NonEmptyByteString starting
	// on the fifth bit of an byte
	static void encodeNonEmptyByteString5(IBitWriter* w, const NonEmptyOctetString &value);

	// ITU C.25: Encoding of integers in the range 1 to 2^20
	// starting on the second bit of an byte
	static void encodeInteger2(IBitWriter* w, int value);

	// ITU C.27: Encoding of integers in the range 1 to 2^20
    // starting on the third bit of an byte
	static void encodeInteger3(IBitWriter* w, int value);

	static void encodeAttributeIntegerArray(IBitWriter* w, const int* values, size_t size);
	static void encodeAttributeFloatArray(IBitWriter* w, const float* values, size_t size);

  // Puts a bitstring to the current byte bit by bit
/*  void putBits(const std::string &bitstring) {
	for(std::string::const_iterator I = bitstring.begin(); I != bitstring.end(); I++)
      putBit((*I) == '1');
  }

  // Puts the integer value to the stream using count bits
  // for encoding
  void putBits(unsigned int value, unsigned char count)
  {
	// Can be optimized
    while (count > 0)
    {
      count = this->append(value, count);
    }
  }


  // Puts on bit to the current byte true = 1, false = 0
  inline void putBit(bool on) {
	  assert(_currentBytePos < 8);
	  if (on)
		{
		unsigned char pos = _currentBytePos;
		unsigned char mask = (unsigned char)(0x80 >> pos);
		_currentByte |= mask;
		}
		_currentBytePos++;
		tryFlush();
  }

  // Puts whole bytes to the file stream. CurrentBytePos must
  // be 0 for this
  void putBytes(const unsigned char* bytes, size_t length) {
	if(_currentBytePos == 0)
		_stream->write(reinterpret_cast<const char*>(bytes), length);
	else {
	    assert(false);
		throw std::runtime_error("Wrong position in FiEncode::PutBytes");
    }
  }
  
  // Fills up the current byte with 0 values
  inline void fillByte() {
	while (_currentBytePos)
	    putBit(0);
  };*/
protected:


  static inline void encodeEncodingAlgorithmStart(IBitWriter* w, int algorithmID)
  {
    // ITU C.19.3.4: If the alternative encoding-algorithm is present, 
    // then the two bits '11' (discriminant) are appended
    w->putBits("11");
    //C.29.2 The value, minus the lower bound of the range, is encoded as an unsigned integer in a field of eight bits and
    //appended to the bit stream.
    w->putBits(algorithmID-1, 8);
  }


  /*
  inline unsigned char append(unsigned int value, unsigned char count)
  {
    assert(_currentBytePos < 8);
	while ((_currentBytePos < 8) && count > 0)
    {
		// Value and der Stelle i
		unsigned int mask = 1;
		bool isSet = !(((mask << (count - 1)) & value) == 0);
		if (isSet)
		{
			_currentByte |= static_cast<unsigned char>(0x80 >> _currentBytePos);
      }
    _currentBytePos++;
    count--;
    }
  tryFlush();
  return count;
}*/


private:



};

} // namespace FI

#endif // FI_FIENCODER_H

