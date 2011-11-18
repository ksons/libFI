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
#ifndef STREAMBITWRITER_H_
#define STREAMBITWRITER_H_

#include <iostream>
#include <fi/Types.h>

namespace FI {

class LIBFI_EXPORT StreamBitWriter: public IBitWriter {
public:
	StreamBitWriter();
	virtual ~StreamBitWriter();

	void setStream(std::ostream* stream);

	virtual void putBit(bool on);
	virtual void putBits(const std::string &bitString);
	virtual void putBits(unsigned int value, unsigned char count);
	virtual void putBytes(const unsigned char* bytes, size_t length);
	virtual int getBitPos();

	virtual inline void fillByte(bool on) {
		while (_currentBitPos)
			putBit(on);
	}

protected:
	unsigned char append(unsigned int value, unsigned char count);
	void tryFlush();

	// This is the current byte to fill
	unsigned char _currentByte;
	// This is the number of the current bit in the byte. Range: 0-7
	int _currentBitPos;
	std::ostream* _stream;

};

} // end namespace FI

#endif /* STREAMBITWRITER_H_ */
