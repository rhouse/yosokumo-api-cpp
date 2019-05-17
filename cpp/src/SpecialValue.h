// SpecialValue.h

#ifndef SPECIALVALUE_H
#define SPECIALVALUE_H

#include <stdint.h>

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents an unsigned integer value.
 */
class SpecialValue : public Value
{
public:
    /**
     * Instantiate a SpecialValue and assign it a value.
     *
     * @param value  the value to assign to the new SpecialValue object.
     */
    SpecialValue(uint64_t value);

    /**
     * Return the special value stored in this object.
     *
     * @return the special value.
     */
    uint64_t getValue() const;

    /**
     * Return the special value as a string.
     *
     * @return the special value as a string.
     */
    virtual std::string toString() const;

};  // end class SpecialValue

}   // end namespace Yosokumo

#endif  // SPECIALVALUE_H

// end SpecialValue.h
