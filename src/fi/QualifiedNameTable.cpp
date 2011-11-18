/*
 * QualifiedNameTable.cpp
 *
 *  Created on: 12.01.2010
 *      Author: Kristian
 */

#include "fi/QualifiedNameTable.h"

#include <algorithm>

namespace FI {

QualifiedNameTable::QualifiedNameTable() {
	// TODO Auto-generated constructor stub

}

QualifiedNameTable::~QualifiedNameTable() {
	// TODO Auto-generated destructor stub
}

QualifiedName QualifiedNameTable::get(unsigned int i) const {
	return _names.at(i-1);
}


unsigned int QualifiedNameTable::addUnique(const QualifiedName& name) {
	std::vector<QualifiedName>::const_iterator I = find(_names.begin(), _names.end(), name);
	if (I == _names.end())
	{
		_names.push_back(name);
		return _names.size() - 1;
	}
	return I - _names.begin();
}
}
