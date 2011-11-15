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
class LIBFI_EXPORT EncoderFunctions {
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

protected:

	static inline void encodeEncodingAlgorithmStart(IBitWriter* w, int algorithmID) {
		// ITU C.19.3.4: If the alternative encoding-algorithm is present,
		// then the two bits '11' (discriminant) are appended
		w->putBits("11");
		//C.29.2 The value, minus the lower bound of the range, is encoded as an unsigned integer in a field of eight bits and
		//appended to the bit stream.
		w->putBits(algorithmID - 1, 8);
	}

private:

};

} // namespace FI

#endif // FI_FIENCODER_H
