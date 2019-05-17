// DigestRequest.cpp


#include <openssl/hmac.h>
#include <openssl/evp.h>

#include <sstream>

#include "DigestRequest.h"
#include "Credentials.h"
#include "Base64.h"

using namespace Yosokumo;

std::string DigestRequest::makeDigest(
    const std::string &message, 
    const std::vector<uint8_t> &key) 
        throw(ServiceException)
{
    if (key.size() != Credentials::KEY_LEN)
    {
        std::stringstream s;
        s << "Invalid key length (" << key.size() << ") for making digest";
        throw ServiceException(s.str());
    }

     // digest of input message

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned digest_size;

    HMAC
    (
        EVP_sha512(),                     // hash function to use
        (void*) &key[0],                  // ptr to key
        Credentials::KEY_LEN,             // size of key
        (unsigned char*) message.c_str(), // ptr to the message to hash
        message.size(),                   // size of message to hash
        digest,                           // ptr to where to store output
        &digest_size                      // ptr to where to store output size
    );

    std::vector<uint8_t> digest_vec;
    for (unsigned i = 0;  i < digest_size;  ++i)
        digest_vec.push_back(digest[i]);

    std::string request;
    Base64::encodeBytes(digest_vec, request);

    if (request.size() != ENCODED_LEN)
    {
        std::stringstream s;
        s << "Invalid encoded digest length (" << request.size() << ")";
        throw ServiceException(s.str());
    }

    return request;

}   //  end makeDigest

// end DigestRequest.cpp

