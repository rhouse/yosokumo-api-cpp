// RealValue.h

#ifndef REALVALUE_H
#define REALVALUE_H

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents a floating-point value.
 */
class RealValue : public Value
{
public:
    /**
     * Instantiate a RealValue and assign it a value.
     *
     * @param value  the value to assign to the new RealValue object.
     */
    RealValue(double value);

    /**
     * Return the real value stored in this object.
     *
     * @return the real value.
     */
    double getValue() const;

    /**
     * Return the real value as a string.
     *
     * @return the real value as a string.
     */
    virtual std::string toString() const;

};  // end class RealValue

}   // end namespace Yosokumo

#endif  // REALVALUE_H

// end RealValue.h
