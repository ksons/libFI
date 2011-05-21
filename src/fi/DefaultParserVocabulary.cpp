#include <fi/DefaultParserVocabulary.h>
#include <fi/Constants.h>
#include <fi/QualifiedNameTable.h>
#include <stdexcept>
#include <sstream>
#include <algorithm>


#define THROW(s) { \
std::stringstream ss; \
ss << s; \
throw std::runtime_error(ss.str());\
}

#define XML_NAMESPACE_PREFIX "xml"
#define XML_NAMESPACE_NAME "http://www.w3.org/XML/1998/namespace"


namespace FI {

DefaultParserVocabulary::DefaultParserVocabulary()
{
	initTableEntries();
	initEncodingAlgorithms();
}

DefaultParserVocabulary::~DefaultParserVocabulary()
{
	delete _elementNames;
	delete _attributeNames;
}

DefaultParserVocabulary::DefaultParserVocabulary(const char* uri) : _externalVocabularyURI(uri)
{
	initTableEntries();
	initEncodingAlgorithms();
}

void DefaultParserVocabulary::initEncodingAlgorithms()
{
  _encodingAlgorithms.insert(_encodingAlgorithms.begin(), Constants::ENCODING_ALGORITHM_BUILTIN_END, NULL);
  _encodingAlgorithms[IntEncodingAlgorithm::ALGORITHM_ID] = &_intEncodingAlgorithm;
  _encodingAlgorithms[FloatEncodingAlgorithm::ALGORITHM_ID] = &_floatEncodingAlgorithm;
}


void DefaultParserVocabulary::initTableEntries()
{
  _elementNames = new QualifiedNameTable();
  _attributeNames = new QualifiedNameTable();

  // 7.2.21 The PREFIX table shall have a built-in prefix entry of "xml",
  NonEmptyOctetString xmlNamespacePrefix(XML_NAMESPACE_PREFIX);
  _prefixNames.push_back(xmlNamespacePrefix);

  // 7.2.22 The NAMESPACE NAME table shall have a built-in namespace name entry of:
  // http://www.w3.org/XML/1998/namespace
  NonEmptyOctetString xmlNamespace(XML_NAMESPACE_NAME);
  _nameSpaceNames.push_back(xmlNamespace);
}


EncodingAlgorithm* DefaultParserVocabulary::getEncodingAlgorithm(unsigned int index) const
{
	if (index < Constants::ENCODING_ALGORITHM_BUILTIN_END)
	{
		EncodingAlgorithm* result = _encodingAlgorithms[index];
		if (result)
			return result;

		if (!result)
		{
			THROW("Built-in encoding algorithm not implemented (yet) " << index);
		}
		return result;
	}
	if (index >= Constants::ENCODING_ALGORITHM_APPLICATION_START)
	{
		try {
			EncodingAlgorithm* result = _encodingAlgorithms.at(index);
			if (!result) throw std::out_of_range("");
			return result;
		} catch (std::out_of_range&)
		{
			THROW("URI not present for encoding algorithm identifier " << index);
		}
	}
	THROW("Encoding algorithm index 11-31 are reserved for future versions of FastInfoSet");
}

void DefaultParserVocabulary::addAttributeValue(const NonEmptyOctetString &value)
{
  StringTable::const_iterator I = find(_attributeValues.begin(), _attributeValues.end(), value);
  if (I == _attributeValues.end())
    _attributeValues.push_back(value);
}

void DefaultParserVocabulary::addCharacterChunk(const NonEmptyOctetString &value)
{
	StringTable::const_iterator I = find(_characterChunks.begin(), _characterChunks.end(), value);
  if (I == _characterChunks.end())
    _characterChunks.push_back(value);

}

void DefaultParserVocabulary::addNamespaceName(const NonEmptyOctetString &value)
{
  StringTable::const_iterator I = find(_nameSpaceNames.begin(), _nameSpaceNames.end(), value);
  if (I == _nameSpaceNames.end())
    _nameSpaceNames.push_back(value);
}

void DefaultParserVocabulary::addLocalName(const NonEmptyOctetString &value)
{
  StringTable::const_iterator I = find(_localNames.begin(), _localNames.end(), value);
  if (I == _localNames.end())
	  _localNames.push_back(value);
}

void DefaultParserVocabulary::addPrefix(const NonEmptyOctetString &value)
{
  StringTable::const_iterator I = find(_prefixNames.begin(), _prefixNames.end(), value);
  if (I == _prefixNames.end())
	  _prefixNames.push_back(value);
}

void DefaultParserVocabulary::addOtherString(const NonEmptyOctetString &value)
{
  StringTable::const_iterator I = find(_comments.begin(), _comments.end(), value);
  if (I == _comments.end())
	  _comments.push_back(value);
}

void DefaultParserVocabulary::addEncodingAlgorithm(EncodingAlgorithm* algorithm)
{
	if (_encodingAlgorithms.size() <= Constants::ENCODING_ALGORITHM_APPLICATION_START)
		_encodingAlgorithms.resize(Constants::ENCODING_ALGORITHM_APPLICATION_START+1, NULL);
	//std::cout << "Adding alogrithm to table pos: " << _encodingAlgorithms.size() << std::endl;
	_encodingAlgorithms.push_back(algorithm);
}

}
