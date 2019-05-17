// DigestRequest.h


#ifndef DIGESTREQUEST_H
#define DIGESTREQUEST_H

#include "ServiceException.h"

#include <stdint.h>
#include <vector>

namespace Yosokumo
{

/**
 * Provides a method to digest (using HMAC) and encode (using Base64) an 
 * input message.
 */

class DigestRequest
{
public:

    /**
     * Length of the encoded digest.
     */
    enum { ENCODED_LEN = 88 };

    /**
     * Make an encoded digest of a message.
     *
     * @param  message  the input message to encode.
     * @param  key      the key to use to digest the input message.  It must
     *                      be exactly 64 bytes in length.
     * @return the digested, encoded key.  It is exactly 88 characters long.
     * @throws ServiceException if the input key length is not correct.
     * @throws ServiceException if there is any problem encoding the message.
     */

    static std::string makeDigest(
        const std::string &message, 
        const std::vector<uint8_t> &key)
            throw(ServiceException);

};  //  end class DigestRequest

}   //  end namespace Yosokumo

#endif  // DIGESTREQUEST_H

// end DigestRequest.h
