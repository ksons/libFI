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

enum TableNames {
	ATTRIBUTE_VALUE = 0,
	CHARACTER_CHUNK,
	NAMESPACE_NAME,
	OTHER_NCNAME,
	LOCAL_NAME,
	PREFIX,
	OTHER_STRING,
	TABLENAMES_MAX
};

/**
 * Abstract class that defines a ParserVocabulary
 */
class ParserVocabulary
{
public:
	virtual ~ParserVocabulary() {};

	/* resolve */
	virtual void resolveElementName(const QualifiedNameOrIndex &input, ResolvedQualifiedName& out) const;
	virtual void resolveAttributeName(const QualifiedNameOrIndex &input, ResolvedQualifiedName& out) const;
	virtual void resolveQualifiedName(const QualifiedNameOrIndex &input, ResolvedQualifiedName &out) const;
	virtual void resolveQualifiedName(const QualifiedName &input, ResolvedQualifiedName &out) const;

	virtual NonEmptyOctetString	resolveStringOrIndex(TableNames table, const NonIdentifyingStringOrIndex &input) const;
	virtual NonEmptyOctetString resolveStringOrIndex(TableNames table, const IdentifyingStringOrIndex &input) const;
	virtual NonEmptyOctetString	decodeCharacterString(const EncodedCharacterString &input) const;
	
	/* add to tables */
	virtual void addStringToTable(TableNames table, const NonEmptyOctetString &value) = 0;

	virtual void addQualifiedName(QualifiedNameTable* table, const QualifiedName& name);
	inline void addAttributeName(const QualifiedNameOrIndex& name) {
		if(!name._nameSurrogateIndex)
			addQualifiedName(getAttributeTable(), name._literalQualifiedName);
	};
	virtual void addElementName(const QualifiedNameOrIndex& name) {
		if(!name._nameSurrogateIndex)
			addQualifiedName(getElementTable(), name._literalQualifiedName);
	};
	virtual void addStringOrIndex(TableNames table, const NonIdentifyingStringOrIndex& value);

	/* get from tables*/
	virtual QualifiedNameTable* getElementTable() const = 0;
	virtual QualifiedNameTable* getAttributeTable() const = 0;
	virtual NonEmptyOctetString getTableEntry(TableNames table, unsigned int index) const = 0;
	virtual EncodingAlgorithm* getEncodingAlgorithm(unsigned int index) const = 0;
	virtual std::string getExternalVocabularyURI() const = 0;
	
	/* encode values */  
	//virtual void encodeElementName(QualifiedNameOrIndex &name);

};

} // namespace FI

#endif
