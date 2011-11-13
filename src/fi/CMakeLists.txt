set (FI_SOURCES
	Decoder.cpp
	ParserVocabulary.cpp
	DefaultParserVocabulary.cpp
	EncodingAlgorithms.cpp
	SAXParser.cpp
	ContentHandler.cpp
	QualifiedNameTable.cpp
	EncoderFunctions.cpp
	)

set (FI_HEADER
	Types.h
	Decoder.h
	Constants.h
	ParserVocabulary.h
	DefaultParserVocabulary.h
	EncodingAlgorithms.h
	SAXParser.h
	ContentHandler.h
	QualifiedNameTable.h
	EncoderFunctions.h
	)
	
add_library(fi SHARED ${FI_SOURCES} ${FI_HEADER})