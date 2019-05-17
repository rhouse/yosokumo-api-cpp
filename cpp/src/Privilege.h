// Privilege.h

#ifndef PRIVILEGE_H
#define PRIVILEGE_H

#include <string>

namespace Yosokumo
{
/*
 * A <code>Privilege</code> specifies an operation which is or is not allowed 
 * on a study.
 *
 * @author  Roger House
 * @version 0.9
 */
class Privilege
{
public:

    enum { NUMBER_OF_PRIVILEGES  = 13 };  

    /**
     * Indicates an operation which a given user is or is not allowed to 
     * perform on a given study.
     */
    enum Type
    {
        GET_STUDY    =  1,
        DELETE_STUDY =  2,
        GET_ROSTER   =  3,
        POST_ROSTER  =  4,
        GET_ROLE     =  5,
        PUT_ROLE     =  6,
        DELETE_ROLE  =  7,
        GET_PANEL    =  8,
        GET_CONTROL  =  9,
        PUT_CONTROL  = 10,
        POST_TABLE   = 11,
        GET_MODEL    = 12,
        POST_MODEL   = 13,

        GET_CATALOG  = 14,   // Not a role; exists so indices exist for all ops
        POST_CATALOG = 15    // Not a role; exists so indices exist for all ops
    };

private:

    int value;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Privilege</code> object with a value
     * specified by the input parameter.
     *
     * @param  value  the value to assign to the privilege.
     */

    Privilege(int value);

    /**
     * Return the <code>Privilege</code> enum value as an integer.
     *
     * @return the enum value of this <code>Privilege</code> as an integer.
     */
    int getNumber() const;

    /**
     * Return the <code>Privilege</code> name.
     *
     * @return the name of this <code>Privilege</code>.
     */
    std::string getName() const;

    /**
     * Convert an integer to a <code>Privilege</code> enum value.
     *
     * @param  value  the integer to convert.
     *
     * @return the <code>Type</code> enum value corresponding to the 
     *         value parameter, or zero if the parameter does not correspond
     *         to any enum value.  
     */
    static Type valueOf(int value) ;

};  // end class Privilege

}   // end namespace Yosokumo

#endif  // PRIVILEGE_H

// end Privilege.h
