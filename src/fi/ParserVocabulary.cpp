#include <fi/ParserVocabulary.h>
#include <fi/EncodingAlgorithms.h>
#include <fi/QualifiedNameTable.h>

#include <iostream>
#include <cassert>
#include <stdexcept>

#define THROW(s) { \
  std::stringstream ss; \
  ss << s; \
  throw std::runtime_error(ss.str());\
}

//#define OCTETS2STRING(octets, str) { (str).clear(); if ((octets).size())  (str).insert((str).begin(), (octets).begin(), (octets).end()); }
#define INDEX_NOT_SET 0

namespace FI {

  void ParserVocabulary::addElementName(const QualifiedNameOrIndex &name)
  {
    if (!name._nameSurrogateIndex)
    {
      getElementTable()->addUnique(name._literalQualifiedName);
      if(!name._literalQualifiedName._prefix._stringIndex && 
        name._literalQualifiedName._prefix._literalCharacterString.length())
      {
        addPrefix(name._literalQualifiedName._prefix._literalCharacterString);
      }
      if(!name._literalQualifiedName._namespaceName._stringIndex && 
        name._literalQualifiedName._namespaceName._literalCharacterString.length())
      {
        addNamespaceName(name._literalQualifiedName._namespaceName._literalCharacterString);
      }
      if(!name._literalQualifiedName._localName._stringIndex)
      {
        addLocalName(name._literalQualifiedName._localName._literalCharacterString);
      }
    }
  }

  void ParserVocabulary::addAttributeName(const QualifiedNameOrIndex &name)
  {
    if (!name._nameSurrogateIndex)
    {
      getAttributeTable()->addUnique(name._literalQualifiedName);
      if(!name._literalQualifiedName._prefix._stringIndex && 
        name._literalQualifiedName._prefix._literalCharacterString.length())
      {
        addPrefix(name._literalQualifiedName._prefix._literalCharacterString);
      }
      if(!name._literalQualifiedName._namespaceName._stringIndex && 
        name._literalQualifiedName._namespaceName._literalCharacterString.length())
      {
        addNamespaceName(name._literalQualifiedName._namespaceName._literalCharacterString);
      }
      if(!name._literalQualifiedName._localName._stringIndex)
      {
        addLocalName(name._literalQualifiedName._localName._literalCharacterString);
      }
    }
  }

  void ParserVocabulary::addAttributeValue(const NonIdentifyingStringOrIndex &value)
  {
    if (value._stringIndex == INDEX_NOT_SET && value._addToTable)
    {
      this->addAttributeValue(this->resolveAttributeValue(value));
    }
  }

  void ParserVocabulary::addCharacterChunk(const NonIdentifyingStringOrIndex& chunk)
  {
    if (chunk._stringIndex == INDEX_NOT_SET && chunk._addToTable)
    {
      this->addCharacterChunk(this->resolveCharacterChunk(chunk));
    }
  }

  void ParserVocabulary::addOtherString(const NonIdentifyingStringOrIndex& str)
  {
    if (str._stringIndex == INDEX_NOT_SET && str._addToTable)
    {
      this->addOtherString(this->resolveOtherString(str));
    }
  }

  void ParserVocabulary::resolveElementName(const QualifiedNameOrIndex &nameOrIndex, ResolvedQualifiedName& out) const
  {
    resolveQualifiedName(
      nameOrIndex._nameSurrogateIndex == INDEX_NOT_SET ?
      nameOrIndex._literalQualifiedName : getElementTable()->get(nameOrIndex._nameSurrogateIndex),
      out);
  }

  void ParserVocabulary::resolveAttributeName(const QualifiedNameOrIndex &nameOrIndex, ResolvedQualifiedName& out) const
  {
    resolveQualifiedName(
      nameOrIndex._nameSurrogateIndex == INDEX_NOT_SET ?
      nameOrIndex._literalQualifiedName : getAttributeTable()->get(nameOrIndex._nameSurrogateIndex),
      out);

    /*unsigned int surrogateIndex = nameOrIndex._nameSurrogateIndex;
    if (surrogateIndex == INDEX_NOT_SET)
    resolveQualifiedName(nameOrIndex, out);
    else
    {
    QualifiedName name = getAttributeTable().get(surrogateIndex);
    resolveQualifiedName(name, out);
    }*/
  }

  void ParserVocabulary::resolveQualifiedName(const QualifiedNameOrIndex &nameOrIndex, ResolvedQualifiedName& out) const
  {
    assert(nameOrIndex._nameSurrogateIndex == INDEX_NOT_SET);
    resolveQualifiedName(nameOrIndex._literalQualifiedName, out);
  }

  void ParserVocabulary::resolveQualifiedName(const QualifiedName &qname, ResolvedQualifiedName& out) const
  {
    out._prefix = resolvePrefix(qname._prefix);
    out._namespaceName = resolveNamespaceName(qname._namespaceName);

    if (qname._localName._stringIndex == INDEX_NOT_SET) {
      out._localName = qname._localName._literalCharacterString;
    } else {
      out._localName = getLocalName(qname._localName._stringIndex);
    }
  }

  NonEmptyOctetString ParserVocabulary::resolveAttributeValue(const NonIdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return decodeCharacterString(input._characterString);
    }
    return getAttributeValue(stringIndex);
  }

  NonEmptyOctetString	ParserVocabulary::resolveCharacterChunk(const NonIdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return decodeCharacterString(input._characterString);
    }
    return getCharacterChunk(stringIndex);
  }

  NonEmptyOctetString	ParserVocabulary::resolveOtherString(const NonIdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return decodeCharacterString(input._characterString);
    }
    return getOtherString(stringIndex);
  }

  NonEmptyOctetString	ParserVocabulary::resolvePrefix(const IdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return input._literalCharacterString;
    }
    return getPrefix(stringIndex);
  }

  
  NonEmptyOctetString	ParserVocabulary::resolveNamespaceName(const IdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return input._literalCharacterString;
    }
    return getNamespaceName(stringIndex);
  }

  NonEmptyOctetString	ParserVocabulary::decodeCharacterString(const EncodedCharacterString &input) const
  {
    switch (input._encodingFormat)
    {
    case ENCODINGFORMAT_UTF8:
      return input._octets;
    case ENCODINGFORMAT_UTF16:
      throw std::runtime_error("UTF-16 encoding is not supported (yet)");
    case ENCODINGFORMAT_ENCODING_ALGORITHM:
      return getEncodingAlgorithm(input._index)->decodeToString(input._octets);
    case ENCODINGFORMAT_RESTRICTED_ALPHABET:
        throw std::runtime_error("Restricted alphabets are not supported (yet)");
    default:
      throw std::runtime_error("Unknown encoding format.");
    }
  }


} // namespace FI
