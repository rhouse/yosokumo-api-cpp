// Credentials.h


#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <stdint.h>
#include <vector>

#include "ServiceException.h"

namespace Yosokumo
{

/**
 * Specifies credentials (user id and key) for Yosokumo authentication.
 */

class Credentials
{
public:

    /**
     * The exact length of a key.
     */
    enum { KEY_LEN = 64 };

private:

    /**
     * The user to whom the key belongs.
     */
    std::string userId;

    /**
     * The key belonging to the user.  It contains KEY_LEN bytes.
     */
    std::vector<uint8_t> key;

public:

    /**
     * Default constructor - initializes a newly created 
     * <code>Credentials</code> object with default values.
     */
    Credentials();

    /**
     * Initializes a newly created <code>Credentials</code> object to 
     * the user id and key given as parameters.
     *
     * @param userId  the user to whom the key belongs.
     * @param key     the key.
     *
     * @throws ServiceException if the key length is not correct.
     */
    Credentials(const std::string &userId, const std::vector<uint8_t> &key) 
        throw(ServiceException);

    /**
     * Copy constructor - initializes a newly created <code>Credentials</code> 
     * object with a copy of another <code>Credentials</code> object. 
     *
     * @param  rhs  the <code>Credentials</code> to make a copy of.
     */
    Credentials(const Credentials &rhs);


    /**
     * Destructor - destroy a <code>Credentials</code> object.
     */
    virtual ~Credentials();

    /**
     * Assignment operator - assign one <code>Credentials</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Credentials.
     */
    Credentials& operator=(const Credentials& rhs);


    // Equality operators

    /**
     * Equality operator - compare two <code>Credentials</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Credentials</code> and the righthand side 
     *              <code>Credentials</code> are identically equal.
     */
    bool operator==(const Credentials &rhs) const;

    /**
     * Inequality operator - compare two <code>Credentials</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Credentials</code> and the righthand side 
     *              <code>Credentials</code> are not identically equal.
     */
    bool operator!=(const Credentials &rhs) const;

    /**
     * Return the user id.
     *
     * @return the user id.
     */
    std::string getUserId();

    /**
     * Return a copy of the user key.
     *
     * @param theKey  a copy of the user key is placed in this vector.
     */
    void getKey(std::vector<uint8_t> &theKey);

    /**
     * Return a string representation of the <code>Credentials</code>.
     *
     * @return  the string representation of the <code>Credentials</code>.
     */
    std::string toString();

    /**
     * Return a string representation of a key.
     *
     * @param key  the key to convert to a string.
     * @return  the string representation of key.
     */
    static std::string keyToString(const std::vector<uint8_t> &key);

/*
  key    = 64 bytes
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx
*/

};  //  end class Credentials

}   //  end namespace Yosokumo

#endif  // CREDENTIALS_H`

// end Credentials.h
