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
#ifndef FI_DECODER_H
#define FI_DECODER_H

#include <string>
#include <fstream>
#include <map>

#include <fi/Types.h>

namespace FI {

class ParserVocabulary;

/**  
 *  Decoder for FI files. 
 *
 *  The class implements the binary parsing of FI document
 *  It currently just implemets a subset of the Fast Infoset standard
 *  and will throw exception in all cases a not implemented part
 *  of the standard is found.
 *
 *  Normally a client will not use the Decoder directly but one of
 *  it`s derived classes, i.e. the until now only derived class FI::SAXParser.
 *  
 *  @see SAXParser
 */
class LIBFI_EXPORT Decoder {
public:
	/// Constructor.
	Decoder();
	/// Destructor.
	virtual ~Decoder();

	void setStream(std::istream* stream);

	/**
	 *  C.1 Fast infoset document.
	 *  This method validates the header of a Fast Infoset document
	 */
	bool detectFIDocument();

	/**
	 * C.2 Encoding of the Document type
	 */
	void getDocument(FI::Document &document);

	/**
	 * C.3 Encoding of the Element type
	 */
	void getElement(FI::Element &element);

	/**
	 * C.4 Encoding of the Attribute type
	 */
	void getAttribute(FI::Attribute &value);

	/**
	 * C.7 Encoding of the CharacterChunk type
	 */
	void getCharacterChunk(FI::CharacterChunk &chunk);

  /**
	 * C.8 Encoding of the Comment type
	 */
  void getComment(FI::Comment &comment);

  /**
	 * C.12 Encoding of the NamespaceAttribute type
	 */
	void getNamespaceAttribute(FI::NamespaceAttribute &value);

	/**
	 * C.13 Encoding of the IdentifyingStringOrIndex type
	 */
	unsigned int getIdentifyingStringOrIndex(FI::IdentifyingStringOrIndex &value);

	/**
	 * C.14 Encoding of the NonIdentifyingStringOrIndex type starting on the first bit of an octet
	 */
	void
	getNonIdentifyingStringOrIndex1(FI::NonIdentifyingStringOrIndex &value);

	/**
	 * C.15 Encoding of the NonIdentifyingStringOrIndex type starting on the third bit of an octet
	 */
	void
	getNonIdentifyingStringOrIndex3(FI::NonIdentifyingStringOrIndex &value);

	/**
	 * C.17 Encoding of the QualifiedNameOrIndex type starting on the second bit of an octet
	 */
	unsigned int getQualifiedNameOrIndex2(FI::QualifiedNameOrIndex& value);

	/**
	 * C.18 Encoding of the QualifiedNameOrIndex type starting on the third bit of an octet
	 */
	unsigned int getQualifiedNameOrIndex3(FI::QualifiedNameOrIndex& value);

	/**
	 * C.19 Encoding of the EncodedCharacterString type starting on the third bit of an octet
	 */
	void getEncodedCharacterString3(FI::EncodedCharacterString &value);

	/**
	 * C.20 Encoding of the EncodedCharacterString type starting on the fifth bit of an octet
	 */
	void getEncodedCharacterString5(FI::EncodedCharacterString &value);

	/**
	 * C.22 Encoding of the NonEmptyOctetString type starting on the second bit of an octet
	 */
	void getNonEmptyOctetString2(FI::NonEmptyOctetString &value);

	/**
	 * C.23 Encoding of the NonEmptyOctetString starting on the fifth bit of an octet
	 */
	void getNonEmptyOctetString5(FI::NonEmptyOctetString& value);

	/**
	 * C.24 Encoding of the NonEmptyOctetString type starting on the seventh bit of an octet
	 */
	void getNonEmptyOctetString7(FI::NonEmptyOctetString& value);

	/**
	 * C.25 Encoding of integers in the range 1 to 2^20 starting on the second bit of an octet
	 * C.26 Encoding of integers in the range 0 to 2^20 starting on the second bit of an octet
	 */
	unsigned int decodeInteger2();

	/**
	 * C.27 Encoding of integers in the range 1 to 2^20 starting on the third bit of an octet
	 */
	unsigned int decodeInteger3();

	/**
	 * C.28 Encoding of integers in the range 1 to 2^20 starting on the fourth bit of an octet
	 */
	unsigned int decodeInteger4();

	/**
	 * C.29 Encoding of integers in the range 1 to 256
	 * Starting at the 5th bit of the current byte
	 */
	unsigned int decodeSmallInteger5(unsigned char first, unsigned char second) const;

	/**
	 * C.29 Encoding of integers in the range 1 to 256
	 * Starting at the 7th bit of the current byte
	 */
	unsigned int decodeSmallInteger7(unsigned char first, unsigned char second) const;

	/**
	 * This method adds an external vocabulary to the intenal map of
	 * external vocabularies. If a external vocabulary is refernced inside
	 * the parsed document, the parser will look up for it using the
	 * give URI.
	 *
	 * @uri The URI to identifiy the given ParserVocabulary
	 * @parserVocabulary An external ParserVocabulary
	 */
	virtual void addExternalVocabularies(const std::string &uri,
			FI::ParserVocabulary* parserVocabulary);

 	/**
	 * The vocabulary used for decoding.
	 */
	ParserVocabulary* _vocab;

protected:
	void processDocumentProperties();

	void decodeAdditionalData();
	void decodeInitialVocabulary();
	void decodeNotations();
	void decodeUnparsedEntities();
	void decodeCharacterEncodingScheme();
	void decodeStandalone();
	void decodeVersion();

	void decodeExternalVocabularyURI();

	bool readChildren(); // C.2
	bool readAttributes(FI::Element& element); // C.4

	int checkBit(unsigned char c, unsigned char iPos);

protected:
	/**
	 * The current octet that is being read
	 */
	unsigned char _b;


	std::map<std::string, FI::ParserVocabulary*> _externalVocabularies;
	std::istream* _stream;
};

}

#endif
