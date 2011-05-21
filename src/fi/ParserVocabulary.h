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
#ifndef FI_PARSERVOCABULARY_H
#define FI_PARSERVOCABULARY_H

#include <fi/Types.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace FI {

class EncodingAlgorithm;
class QualifiedNameTable;
typedef std::vector<EncodingAlgorithm*> AlgorithmTable;

/**
 * Abstract class that defines a ParserVocabulary
 */
class ParserVocabulary
{
public:
	virtual ~ParserVocabulary() {};

	virtual void resolveElementName(const QualifiedNameOrIndex &input, ResolvedQualifiedName& out) const;
	virtual void resolveAttributeName(const QualifiedNameOrIndex &input, ResolvedQualifiedName& out) const;

	virtual void resolveQualifiedName(const QualifiedNameOrIndex &input, ResolvedQualifiedName &out) const;
	virtual void resolveQualifiedName(const QualifiedName &input, ResolvedQualifiedName &out) const;

	virtual NonEmptyOctetString	resolveAttributeValue(const NonIdentifyingStringOrIndex &input) const;
	virtual NonEmptyOctetString	resolveCharacterChunk(const NonIdentifyingStringOrIndex &input) const;
  virtual NonEmptyOctetString	resolveOtherString(const NonIdentifyingStringOrIndex &input) const;
  virtual NonEmptyOctetString	resolvePrefix(const IdentifyingStringOrIndex &input) const;
  virtual NonEmptyOctetString	resolveNamespaceName(const IdentifyingStringOrIndex &input) const;
  virtual NonEmptyOctetString	resolveOtherNCName(const IdentifyingStringOrIndex &input) const;
	
	virtual NonEmptyOctetString	decodeCharacterString(const EncodedCharacterString &input) const;

	virtual QualifiedNameTable* getElementTable() const = 0;
	virtual QualifiedNameTable* getAttributeTable() const = 0;
	
  virtual void addAttributeName(const QualifiedNameOrIndex& name);
  virtual void addElementName(const QualifiedNameOrIndex& name);
  virtual void addAttributeValue(const NonIdentifyingStringOrIndex& value);
	virtual void addCharacterChunk(const NonIdentifyingStringOrIndex& chunk);
  virtual void addOtherString(const NonIdentifyingStringOrIndex& chunk);

	virtual NonEmptyOctetString getPrefix(unsigned int index) const = 0;
	virtual NonEmptyOctetString getNamespaceName(unsigned int index) const = 0;
	virtual NonEmptyOctetString getLocalName(unsigned int index) const = 0;
	virtual NonEmptyOctetString getAttributeValue(unsigned int index) const = 0;
	virtual NonEmptyOctetString getCharacterChunk(unsigned int index) const = 0;
  virtual NonEmptyOctetString getOtherString(unsigned int index) const = 0;
  virtual NonEmptyOctetString getOtherNCName(unsigned int index) const = 0;
	virtual EncodingAlgorithm* getEncodingAlgorithm(unsigned int index) const = 0;
	
	virtual void addAttributeValue(const NonEmptyOctetString &value) = 0;
  virtual void addCharacterChunk(const NonEmptyOctetString &value) = 0;
	virtual void addNamespaceName(const NonEmptyOctetString &value) = 0;
  virtual void addOtherNCName(const NonEmptyOctetString &value) = 0;
	virtual void addLocalName(const NonEmptyOctetString &value) = 0;
	virtual void addPrefix(const NonEmptyOctetString &value) = 0;
  virtual void addOtherString(const NonEmptyOctetString &value) = 0;
	virtual void addEncodingAlgorithm(EncodingAlgorithm* algorithm) = 0;

	virtual std::string getExternalVocabularyURI() const = 0;
};

} // namespace FI

#endif
