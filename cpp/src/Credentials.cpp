// Credentials.cpp


#include "Credentials.h"

#include <sstream>
#include <string.h>

using namespace Yosokumo;

Credentials::Credentials()
{
    userId = "";
    key.clear();
}

Credentials::Credentials(
    const std::string &userId, 
    const std::vector<uint8_t> &key) throw(ServiceException) :
        userId(userId), 
        key(key)
{
    if (key.size() != KEY_LEN)
        throw ServiceException("Key is not the correct length");
}

Credentials::Credentials(const Credentials &rhs)
{
    operator=(rhs);
}

Credentials::~Credentials()
{}

Credentials &Credentials::operator=(const Credentials& rhs)
{
    if (this == &rhs)
        return *this;

    userId   = rhs.userId  ;
    key      = rhs.key;

    return *this;
}


// Equality operators

bool Credentials::operator==(const Credentials &rhs) const 
{
    return
    (
        userId     == rhs.userId     &&
        key.size() == rhs.key.size() &&
        memcmp((void*)&key[0], (void*)&rhs.key[0], key.size()) == 0 
    );
}

bool Credentials::operator!=(const Credentials &rhs) const
{
    return !(*this == rhs);
}


std::string Credentials::getUserId()
{
    return userId;
} 

void Credentials::getKey(std::vector<uint8_t> &theKey)
{
    theKey = key;
} 

std::string Credentials::toString()
{
    std::stringstream s;

    s <<
    "Credentials:"                << "\n" <<
    "  userId = "  << getUserId() << "\n" <<
    keyToString(key)
    ;

    return s.str();
}

std::string Credentials::keyToString(const std::vector<uint8_t> &key)
{
    std::stringstream s;

    s << "  key    = ";

    if (key.empty())
    {
        s << "empty" << "\n";
        return s.str();
    }

    s << key.size() << " bytes";

    int numPerLine = 15;
    int i = 0;

    while (i < Credentials::KEY_LEN)
    {
        uint8_t n = key.at(i);
        if (i++ % numPerLine == 0)
            s << "\n";
        s << " " << unsigned(n);
    }
    s << "\n";

    return s.str();
}
/*
  key    = 64 bytes
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx -xxx
  -xxx -xxx -xxx -xxx
*/

// end Credentials.cpp
