// NaturalValue.h

#ifndef NATURALVALUE_H
#define NATURALVALUE_H

#include <stdint.h>

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents an unsigned integer value.
 */
class NaturalValue : public Value
{
public:
    /**
     * Instantiate a NaturalValue and assign it a value.
     *
     * @param value  the value to assign to the new NaturalValue object.
     */
    NaturalValue(uint64_t value);

    /**
     * Return the natural value stored in this object.
     *
     * @return the natural value.
     */
    uint64_t getValue() const;

    /**
     * Return the natural value as a string.
     *
     * @return the natural value as a string.
     */
    virtual std::string toString() const;

};  // end class NaturalValue

}   // end namespace Yosokumo

#endif  // NATURALVALUE_H

// end NaturalValue.h
