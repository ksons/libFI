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

  void ParserVocabulary::addQualifiedName(QualifiedNameTable* table, const QualifiedName& name)
  {
      table->addUnique(name); // Should be last action?
      if(!name._prefix._stringIndex && 
        name._prefix._literalCharacterString.length())
      {
		  addStringToTable(PREFIX, name._prefix._literalCharacterString);
      }
      if(!name._namespaceName._stringIndex && 
        name._namespaceName._literalCharacterString.length())
      {
		  addStringToTable(NAMESPACE_NAME, name._namespaceName._literalCharacterString);
      }
      if(!name._localName._stringIndex)
      {
		  addStringToTable(LOCAL_NAME, name._localName._literalCharacterString);
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
	out._prefix = resolveStringOrIndex(PREFIX, qname._prefix);
	out._namespaceName = resolveStringOrIndex(NAMESPACE_NAME, qname._namespaceName);
	out._localName = resolveStringOrIndex(LOCAL_NAME, qname._localName);
  }

  NonEmptyOctetString	ParserVocabulary::resolveStringOrIndex(TableNames table, const NonIdentifyingStringOrIndex &input) const
  {
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return decodeCharacterString(input._characterString);
    }
    return getTableEntry(table, stringIndex);
  }

  NonEmptyOctetString	ParserVocabulary::resolveStringOrIndex(TableNames table, const IdentifyingStringOrIndex &input) const
  {
    assert(table > 0 && table < TABLENAMES_MAX);
    unsigned int stringIndex = input._stringIndex;
    if (stringIndex == INDEX_NOT_SET)
    {
      return input._literalCharacterString;
    }
    return getTableEntry(table, stringIndex);
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

void ParserVocabulary::addStringOrIndex(TableNames table, const NonIdentifyingStringOrIndex &value)
{
	if (value._stringIndex == INDEX_NOT_SET && value._addToTable)
	{
		this->addStringToTable(table, decodeCharacterString(value._characterString));
	}
}

/*  void ParserVocabulary::encodeElementName(QualifiedNameOrIndex &name) {
	  assert(!name._nameSurrogateIndex);
	  if (name._literalQualifiedName._prefix._literalCharacterString.length())

  }*/



} // namespace FI
