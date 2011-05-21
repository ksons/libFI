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
#ifndef DEFAULTPARSERVOCABULARY_H_
#define DEFAULTPARSERVOCABULARY_H_

#include <fi/ParserVocabulary.h>
#include <fi/EncodingAlgorithms.h>

namespace FI {

  typedef std::vector<NonEmptyOctetString> StringTable;
  class QualifiedNameTable;

  /**
  * The DefaultParserVocabulary implements all the needed functionality of a ParserVocabulary
  * including all the table that are supported yet.
  */
  class DefaultParserVocabulary : public FI::ParserVocabulary
    {
    public:
      DefaultParserVocabulary();
      DefaultParserVocabulary(const char* uri);
      virtual ~DefaultParserVocabulary();

      //virtual inline ResolvedQualifiedName getElementName(unsigned int index) const { return _elementNames.at(index-1); };
      //virtual ResolvedQualifiedName getAttributeName(unsigned int index) const { return _attributeNames.at(index-1); };

      virtual inline NonEmptyOctetString getPrefix(unsigned int index) const { return _prefixNames.at(index-1); };
      virtual inline NonEmptyOctetString getNamespaceName(unsigned int index)  const { return _nameSpaceNames.at(index-1); };
      virtual inline NonEmptyOctetString getLocalName(unsigned int index) const { return _localNames.at(index-1); };
      virtual inline NonEmptyOctetString getAttributeValue(unsigned int index) const { return _attributeValues.at(index-1); };
      virtual inline NonEmptyOctetString getCharacterChunk(unsigned int index) const { return _characterChunks.at(index-1); };
      virtual inline NonEmptyOctetString getOtherString(unsigned int index) const { return _otherStrings.at(index-1); };
      virtual inline NonEmptyOctetString getOtherNCName(unsigned int index) const { return _otherNCNames.at(index-1); };
	    virtual EncodingAlgorithm* getEncodingAlgorithm(unsigned int index) const;

      virtual inline QualifiedNameTable* getElementTable() const { return _elementNames; };
      virtual inline QualifiedNameTable* getAttributeTable() const { return _attributeNames; };

      virtual void addAttributeValue(const NonEmptyOctetString &value);
      virtual void addCharacterChunk(const NonEmptyOctetString &value);
      virtual void addNamespaceName(const NonEmptyOctetString &value);
      virtual void addLocalName(const NonEmptyOctetString &value);
      virtual void addPrefix(const NonEmptyOctetString &value);
      virtual void addOtherString(const NonEmptyOctetString &value);
      virtual void addOtherNCName(const NonEmptyOctetString &value);
      virtual void addEncodingAlgorithm(EncodingAlgorithm* algorithm);

      virtual inline std::string getExternalVocabularyURI() const { return _externalVocabularyURI; };

    protected:

      virtual void initEncodingAlgorithms();
      virtual void initTableEntries();

      QualifiedNameTable* _elementNames;
      QualifiedNameTable* _attributeNames;
      
      /* 8.4  The dynamic string tables
      Each fast infoset document has eight dynamic string tables associated with it. Each dynamic string table
      contains character strings that can be referenced through a vocabulary table index */
      
      StringTable _prefixNames;     // a) PREFIX
      StringTable _nameSpaceNames;  // b) NAMESPACE NAME
      StringTable _localNames;      // c) LOCAL NAME
      StringTable _otherNCNames;    // d) OTHER NCNAME
      StringTable _otherURI;        // e) OTHER URI
      StringTable _attributeValues; // f) ATTRIBUTE VALUE
      StringTable _characterChunks; // g) CONTENT CHARACTER CHUNK
      StringTable _otherStrings;        // h) OTHER STRING

      AlgorithmTable _encodingAlgorithms;

      FI::IntEncodingAlgorithm _intEncodingAlgorithm;
      FI::FloatEncodingAlgorithm _floatEncodingAlgorithm;

      std::string _externalVocabularyURI;

    };
  } // namespace FI

#endif /* DEFAULTPARSERVOCABULARY_H_ */
