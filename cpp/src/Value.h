// Value.h

#ifndef VALUE_H
#define VALUE_H

#include <stdint.h>
#include <string>

namespace Yosokumo
{

/**
 * A base class for value classes which store specific primitive data types,
 * e.g., <code>IntegerValue</code> and <code>RealValue</code>.  Note that 
 * all storage is in the base class itself.
 */
class Value
{
public:
    /**
     * Indicates the data type stored in the <code>Value</code>, e.g., 
     * integer or real.
     */
    enum Type
    {
        /**
         *  empty value.
         */
        EMPTY,
        /**
         * an unsigned integer.
         */
        NATURAL,
        /**
         * a signed integer.
         */
        INTEGER,
        /**
         * real, i.e., floating-point.
         */
        REAL,
        /**
         *  special value (represented as an unsigned integer).
         */
        SPECIAL
    };

protected:

    Type valueType;

    union
    {
        int64_t  int_value;
        uint64_t uint_value;
        double   double_value;
    };

    Value(Type type, int64_t ival);

    Value(Type type, uint64_t uval);

    Value(Type type, double dval);

public:

    /**
     * Default constructor for Value.
     */
    Value();

    /**
     * Return the type of the value.
     *
     * @return the type of the value.
     */
    Type getType() const;

    /**
     * Return an empty value.  The type of the Value must be EMPTY.
     *
     * @return an empty value.
     */
    void *getEmptyValue() const;

    /**
     * Return a natural value.  The type of the Value must be NATURAL.
     *
     * @return a natural value.
     */
    uint64_t getNaturalValue() const;

    /**
     * Return a special value.  The type of the Value must be SPECIAL.
     *
     * @return a special value.
     */
    uint64_t getSpecialValue() const;

    /**
     * Return an integer value.  The type of the Value must be INTEGER.
     *
     * @return an integer value.
     */
    int64_t getIntegerValue() const;

    /**
     * Return a real value.  The type of the Value must be REAL.
     *
     * @return a real value.
     */
    double getRealValue() const;

    // Equality operators

    /**
     * Equality operator - compare two <code>Values</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Values</code> and the righthand side 
     *              <code>Values</code> are identically equal.
     */
    bool operator==(const Value &rhs) const;

    /**
     * Inequality operator - compare two <code>Values</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Values</code> and the righthand side 
     *              <code>Values</code> are not identically equal.
     */
    bool operator!=(const Value &rhs) const;

    /**
     * Return the value as a string.
     *
     * @return the value as a string.
     */
    virtual std::string toString() const;

};  // end class Value

}   // end namespace Yosokumo

#endif  // VALUE_H

// end Value.h
