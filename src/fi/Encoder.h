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
#ifndef FI_ENCODER_H
#define FI_ENCODER_H

#include <fi/Types.h>

namespace FI {

class ParserVocabulary;
class NodeInfoStack;

/**
 *  Encoder for FI files.
 *
 */
class LIBFI_EXPORT Encoder {
public:
	/// Constructor.
	Encoder();
	/// Destructor.
	virtual ~Encoder();

	void setWriter(IBitWriter* writer);

	void startDocument();
	void endDocument();

	void startNode(const std::string name);
	void endNode();


protected:
	void checkNode(bool fromAttribute);

	// C.13 Encoding of the IdentifyingStringOrIndex type
	void encodeIdentifyingStringOrIndex(const std::string &name);

	// C.18 Encoding of the QualifiedNameOrIndex type starting on the third bit of an octet
	void encodeQualifiedNameOrIndex3(const std::string &name);


	IBitWriter* _w;
	NodeInfoStack* _infoStack;
};

}

#endif
