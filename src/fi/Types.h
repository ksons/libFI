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
#ifndef FI_FITYPES_H
#define FI_FITYPES_H

#include <vector>
#include <string>
#include <fi/Config.h>

namespace FI {

	/**
     * The NonEmptyOctetString type is:
	 * <code>NonEmptyOctetString ::= OCTET STRING (SIZE(1-four-gig))</code>
	 * @ingroup ASN1Types
     */
  struct NonEmptyOctetString : public std::basic_string<unsigned char> {
    NonEmptyOctetString() {};
    NonEmptyOctetString(std::string str) {
      clear();
      insert(begin(), str.begin(), str.end());
    }
    
    inline std::string toString() const
    {
      return std::string(begin(), end());
    }
  };
	
	/// Possible encoding formats of the EncodedCharacterString
	enum EncodingFormat {
		ENCODINGFORMAT_UTF8,
		ENCODINGFORMAT_UTF16,
		ENCODINGFORMAT_RESTRICTED_ALPHABET,
		ENCODINGFORMAT_ENCODING_ALGORITHM
	} ;
	
    /** 
     * TODO: Insert documentation
     **/
    struct AdditionalDatum  {
      NonEmptyOctetString _id;
      NonEmptyOctetString _data;
    }; // AdditionalDatum
    
    /** 
     * TODO: Insert documentation
     **/
    struct EncodedCharacterString  {
      EncodingFormat _encodingFormat;
      unsigned char _index;
      NonEmptyOctetString _octets;
    }; // EncodedCharacterString
    
    /** 
     * TODO: Insert documentation
     **/
    struct NameSurrogate  {
      unsigned int _prefixStringIndex;
      unsigned int _namespaceNameStringIndex;
      unsigned int _localNameStringIndex;
    }; // NameSurrogate
    
    /** 
     * TODO: Insert documentation
     **/
    struct Vocabulary  {
      NonEmptyOctetString _externalVocabulary;
      NonEmptyOctetString _restrictedAlphabets;
      NonEmptyOctetString _encodingAlgorithms;
      NonEmptyOctetString _prefixes;
      NonEmptyOctetString _namespaceNames;
      NonEmptyOctetString _otherNcnames;
      NonEmptyOctetString _otherUris;
      std::vector<EncodedCharacterString> _attributeValues;
      std::vector<EncodedCharacterString> _contentCharacterChunks;
      std::vector<EncodedCharacterString> _otherStrings;
      std::vector<NameSurrogate> _elementNameSurrogates;
      std::vector<NameSurrogate> _attributeNameSurrogates;
    }; // Vocabulary
    
    /** 
     * TODO: Insert documentation
     **/
    struct IdentifyingStringOrIndex  {
      IdentifyingStringOrIndex() : _stringIndex(0) {};
      unsigned int _stringIndex;
      NonEmptyOctetString _literalCharacterString;
      inline bool operator==(const IdentifyingStringOrIndex& rhs) const
      {
        return _stringIndex == 0  ? (rhs._stringIndex == 0 && _literalCharacterString == rhs._literalCharacterString)
          : _stringIndex == rhs._stringIndex;
      }
    }; // IdentifyingStringOrIndex
    
    /** 
     * TODO: Insert documentation
     **/
    struct Notation  {
      IdentifyingStringOrIndex _name;
      IdentifyingStringOrIndex _systemIdentifier;
      IdentifyingStringOrIndex _publicIdentifier;
    }; // Notation
    
    /** 
     * TODO: Insert documentation
     **/
    struct UnparsedEntity  {
      IdentifyingStringOrIndex _name;
      IdentifyingStringOrIndex _systemIdentifier;
      IdentifyingStringOrIndex _publicIdentifier;
      IdentifyingStringOrIndex _notationName;
    }; // UnparsedEntity
    
    /** 
     * TODO: Insert documentation
     **/
    struct DocumentChild  {
    }; // DocumentChild
    
    /** 
     * 7.2 The Document type
     * The Document type represents the document information item of an XML infoset. Since all other information
     * items in an XML infoset are either properties of this information item or properties of an item that is a child or
     * descendant of this item (at any depth), each Document represents a complete XML infoset.
     **/
    struct Document  {
      std::vector<AdditionalDatum> _additionalData;
      Vocabulary _initialVocabulary;
      std::vector<Notation> _notations;
      std::vector<UnparsedEntity> _unparsedEntities;
      std::vector<DocumentChild> _children;
    }; // Document
    
    /** 
     * TODO: Insert documentation
     **/
    struct ElementChild  {
    }; // ElementChild
    
    /** 
     * TODO: Insert documentation
     **/
    struct NamespaceAttribute  {
      IdentifyingStringOrIndex _prefix;
      IdentifyingStringOrIndex _namespaceName;
    }; // NamespaceAttribute
    
    /** 
     * TODO: Insert documentation
     **/
    struct QualifiedName  {
      IdentifyingStringOrIndex _prefix;
      IdentifyingStringOrIndex _namespaceName;
      IdentifyingStringOrIndex _localName;
      inline bool operator==(const QualifiedName& rhs) const
      {
        return _localName == rhs._localName &&
           _namespaceName == rhs._namespaceName &&
           _prefix == rhs._prefix;
      }
    }; // QualifiedName
    
    /** 
     * TODO: Insert documentation
     **/
    struct QualifiedNameOrIndex  {
      QualifiedNameOrIndex() : _nameSurrogateIndex(0) {};
      unsigned int _nameSurrogateIndex;
      QualifiedName _literalQualifiedName;
    }; // QualifiedNameOrIndex
    
    /** 
     * TODO: Insert documentation
     **/
    struct NonIdentifyingStringOrIndex  {
      NonIdentifyingStringOrIndex() : _stringIndex(0) {};
      bool _addToTable;
      unsigned int _stringIndex;
      EncodedCharacterString _characterString;
    }; // NonIdentifyingStringOrIndex
    
    /** 
     * TODO: Insert documentation
     **/
    struct Attribute  {
      QualifiedNameOrIndex _qualifiedName;
      NonIdentifyingStringOrIndex _normalizedValue;
    }; // Attribute
    
    /** 
     * TODO: Insert documentation
     **/
    struct Element : public ElementChild, public DocumentChild {
      std::vector<NamespaceAttribute> _namespaceAttributes;
      QualifiedNameOrIndex _qualifiedName;
      std::vector<Attribute> _attributes;
      std::vector<ElementChild> _children;
    }; // Element
    
    /** 
     * TODO: Insert documentation
     **/
    struct ProcessingInstruction : public ElementChild, public DocumentChild {
      IdentifyingStringOrIndex _target;
      NonIdentifyingStringOrIndex _content;
    }; // ProcessingInstruction
    
    /** 
     * TODO: Insert documentation
     **/
    struct UnexpandedEntityReference : public ElementChild {
      IdentifyingStringOrIndex _name;
      IdentifyingStringOrIndex _systemIdentifier;
      IdentifyingStringOrIndex _publicIdentifier;
    }; // UnexpandedEntityReference
    
    /** 
     * TODO: Insert documentation
     **/
    struct CharacterChunk : public ElementChild {
      NonIdentifyingStringOrIndex _characterCodes;
    }; // CharacterChunk
    
    /** 
     * TODO: Insert documentation
     **/
    struct Comment : public ElementChild, public DocumentChild {
      NonIdentifyingStringOrIndex _content;
    }; // Comment
    
    /** 
     * TODO: Insert documentation
     **/
    struct DocumentTypeDeclaration : public DocumentChild {
      IdentifyingStringOrIndex _systemIdentifier;
      IdentifyingStringOrIndex _publicIdentifier;
      std::vector<ProcessingInstruction> _children;
    }; // DocumentTypeDeclaration
    
    /** 
     * TODO: Insert documentation
     **/
    struct Encoder  {
    }; // Encoder
    

	struct ResolvedQualifiedName
	{
    ResolvedQualifiedName() : _prefix(""), _namespaceName(""), _localName("") {};
		ResolvedQualifiedName(NonEmptyOctetString localName) : _prefix(""), _namespaceName(""), _localName(localName) {};
		ResolvedQualifiedName(NonEmptyOctetString prefix, NonEmptyOctetString namespaceName, NonEmptyOctetString localName) : _prefix(prefix), _namespaceName(namespaceName), _localName(localName) {};
		NonEmptyOctetString _prefix;
		NonEmptyOctetString _namespaceName;
		NonEmptyOctetString _localName;

		static inline std::string getQName(const NonEmptyOctetString &p, const NonEmptyOctetString &l) {
			if (p.empty()) return l.toString();
      return p.toString().append(":").append(l.toString());
		}
	};

  inline std::ostream& operator<<(std::ostream& o, const ResolvedQualifiedName &qn)
	{
		return o << ResolvedQualifiedName::getQName(qn._prefix, qn._localName);
	}

}; // namespace FI

#endif // FI_FITYPES_H
