/*
 * QualifiedNameTable.h
 *
 *  Created on: 12.01.2010
 *      Author: Kristian
 */

#ifndef FI_QUALIFIEDNAMETABLE_H_
#define FI_QUALIFIEDNAMETABLE_H_

#include <fi/Types.h>

namespace FI {

class LIBFI_EXPORT QualifiedNameTable {
public:
	QualifiedNameTable();
	virtual ~QualifiedNameTable();

	QualifiedName get(unsigned int) const;
	unsigned int addUnique(const QualifiedName& name);
	size_t size();

protected:
	std::vector<QualifiedName> _names;
};

}

#endif /* QUALIFIEDNAMETABLE_H_ */
