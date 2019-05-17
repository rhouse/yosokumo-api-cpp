// IntegerValue.h

#ifndef INTEGERVALUE_H
#define INTEGERVALUE_H

#include <stdint.h>

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents a signed integer value.
 */
class IntegerValue : public Value
{
public:
    /**
     * Instantiate an IntegerValue and assign it a value.
     *
     * @param value  the value to assign to the new IntegerValue object.
     */
    IntegerValue(int64_t value);

    /**
     * Return the integer value stored in this object.
     *
     * @return the integer value.
     */
    int64_t getValue() const;

    /**
     * Return the integer value as a string.
     *
     * @return the integer value as a string.
     */
    virtual std::string toString() const;

};  // end class IntegerValue

}   // end namespace Yosokumo

#endif  // INTEGERVALUE_H

// end IntegerValue.h
