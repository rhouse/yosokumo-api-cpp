// Cell.h

#ifndef CELL_H
#define CELL_H

#include "Value.h"

namespace Yosokumo
{

/**
 * Represents a <code>Value</code> with an associated key or name.
 * <ul>
 * <li>name when the cell appears in a row (only case seen in the API)
 * <li>key when the cell appears in a column
 * </ul> 
 */

class Cell
{
    /**
     * A name or a key, depending on the context in which the cell appears.
     */
    uint64_t  nameOrKey;
    /**
     * The value of the cell.
     */
    Value value;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Cell</code> object with default 
     * values:
     * <ul>
     * <li>key - 0
     * <li>value - EmptyValue
     * </ul>
     */
    Cell();


    /**
     * Initializes a newly created <code>Cell</code> object with key and value
     * specified by the input parameter.
     *
     * @param  nameOrKey  the name or key of the cell.
     * @param  value  the value of the cell.
     */

    Cell(uint64_t nameOrKey, const Value &value);

    // Equality operators

    /**
     * Equality operator - compare two <code>Cells</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Cells</code> and the righthand side 
     *              <code>Cells</code> are identically equal.
     */
    bool operator==(const Cell &rhs) const;

    /**
     * Inequality operator - compare two <code>Cells</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Cells</code> and the righthand side 
     *              <code>Cells</code> are not identically equal.
     */
    bool operator!=(const Cell &rhs) const;

    // Setters and getters

    /**
     * Set the name of the cell.
     *
     * @param name  the new name to assign to the cell.
     */
    void setName(uint64_t name);

    /**
     * Return the name of the cell.
     *
     * @return the name of the cell.
     */
    uint64_t getName() const;

    /**
     * Set the key of the cell.
     *
     * @param key  the new key to assign to the cell.
     */
    void setKey(uint64_t key);

    /**
     * Return the key of the cell.
     *
     * @return the key of the cell.
     */
    uint64_t getKey() const;

    /**
     * Set the value of the cell.
     *
     * @param value  the new value to assign to the cell.
     */
    void setValue(const Value &value);

    /**
     * Return the value of the cell.
     *
     * @return the value of the cell.
     */
    Value getValue() const;

    /**
     * Return a string representation of this <code>Cell</code>.
     *
     * @return  the string representation of this <code>Cell</code>.
     */
    std::string toString() const;

};   // end class Cell

}   // end namespace Yosokumo

#endif  // CELL_H

// end Cell.h
