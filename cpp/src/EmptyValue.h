// EmptyValue.h

#ifndef EMPTYVALUE_H
#define EMPTYVALUE_H

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents no value or an unknown value.
 */
class EmptyValue : public Value
{
public:
    /**
     * Instantiate an EmptyValue.
     */
    EmptyValue();

    /**
     * Return the value stored in this empty object.
     *
     * @return an empty value (NULL).
     */
    void *getValue() const;

    /**
     * Return the empty value as a string.
     *
     * @return the empty value as a string.
     */
    virtual std::string toString() const;

};  // end class EmptyValue

}   // end namespace Yosokumo

#endif  // EMPTYVALUE_H

// end EmptyValue.h
