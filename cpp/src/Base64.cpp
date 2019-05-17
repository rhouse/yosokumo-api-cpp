// Base64.cpp

#include <sstream>
#include <cassert>
#include "Base64.h"

using namespace Yosokumo;

char Base64::encode64[] = 
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', 
    '4', '5', '6', '7', '8', '9', '+', '/'
};


void Base64::map3to4(uint8_t A, uint8_t B, uint8_t C, std::string &abcd)
{
    unsigned AA = ((unsigned)A) & 0xff;
    unsigned BB = ((unsigned)B) & 0xff;
    unsigned CC = ((unsigned)C) & 0xff;

    char buff[4];

    buff[0] = encode64[(AA >> 2) & 0x3f];
    buff[1] = encode64[((AA << 4) & 0x3f) | ((BB >> 4) & 0x3f)];
    buff[2] = encode64[((BB << 2) & 0x3f) | ((CC >> 6) & 0x3f)];
    buff[3] = encode64[CC & 0x3f];

    abcd.append(buff, 4);

#if 0
    unsigned AA = ((unsigned)A) & 0xff;
    unsigned BB = ((unsigned)B) & 0xff;
    unsigned CC = ((unsigned)C) & 0xff;

    char a, b, c, d;

    a = encode64[(AA >> 2) & 0x3f];
    b = encode64[((AA << 4) & 0x3f) | ((BB >> 4) & 0x3f)];
    c = encode64[((BB << 2) & 0x3f) | ((CC >> 6) & 0x3f)];
    d = encode64[CC & 0x3f];

    abcd.append(a).append(b).append(c).append(d);
#endif
#if 0

    buff[0] = encode64[A >> 2];
    buff[1] = encode64[(A << 4) | (B >> 4)];
    buff[2] = encode64[(B << 2) | (C >> 6)];
    buff[3] = encode64[C];

    abcd.append(buff, 4);
#endif
}


void Base64::encodeBytes(const std::vector<uint8_t> &source, std::string &dest)
{
    dest.clear();

    int n = source.size()/3;    // No. times to loop
    int i, j;

    for (i = 0, j = 1;  j <= n;  ++j, i += 3)
        map3to4(source[i], source[i+1], source[i+2], dest);

    uint8_t zero = 0;

    switch (source.size() % 3)
    {
    case 1:
        map3to4(source[i], zero, zero, dest);
        dest.replace(dest.size()-2, 2, "==");
        break;

    case 2:
        map3to4(source[i], source[i+1], zero, dest);
        dest.replace(dest.size()-1, 1, "=");
        break;
    }

}   //  end encodeBytes


uint8_t Base64::decode64(char c) throw(std::invalid_argument)
{
    uint8_t cc = (uint8_t)c;
    int b;

    if ('A' <= cc && cc <= 'Z')
        b = (int)cc - (int)'A';

    else if ('a' <= cc && cc <= 'z')
        b = (int)cc - (int)'a' + 26;

    else if ('0' <= cc && cc <= '9')
        b = (int)cc - (int)'0' + 52;

    else if (cc == '+')
        b = 62;

    else if (cc == '/')
        b = 63;

    else
    {
        std::stringstream s;
        s << "Base64 string contains invalid character with decimal value " 
          << (unsigned)cc;
        throw std::invalid_argument(s.str());
    }

    return (uint8_t)b;
}

void Base64::map4to3(
    char a, char b, char c, char d, 
    std::vector<uint8_t> &ABC, int j,
    int n) throw(std::invalid_argument)
{
    int aa = decode64(a);
    int bb = decode64(b);
    int cc = decode64(c);
    int dd = decode64(d);

    uint8_t A = (uint8_t)((aa << 2) | (bb >> 4));
    uint8_t B = (uint8_t)((bb << 4) | (cc >> 2));
    uint8_t C = (uint8_t)((cc << 6) | dd);

    ABC[j] = A;
    --n;
    if (n-- > 0)
        ABC[j+1] = B;
    if (n > 0)
        ABC[j+2] = C;
}

// Why, oh why, doesn't std::string have ends_with?

static bool ends_with(const std::string &s, const std::string &ending) 
{
    if (ending.size() > s.size())
        return false;

    return s.compare(s.size()-ending.size(), ending.size(), ending) == 0;
}

void Base64::decodeString(
    const std::string &source, 
    std::vector<uint8_t> &dest) throw(std::invalid_argument)
{
    int m = source.size();

    if (m % 4 != 0)
    {
        std::stringstream s;
        s << "Base64 string length " << m << "is not a multiple of 4";
        throw std::invalid_argument(s.str());
    }

    int resultLen = (m/4) * 3;

    if (ends_with(source, "=="))
    {
        resultLen -= 2;
        m -= 2;
    }
    else if (ends_with(source, "="))
    {
        --resultLen;
        --m;
    }

    // Now m is the no. of source chars to transform and resultLen is the 
    // number of output bytes to return

    dest.resize(resultLen, 0);

    int n = m / 4;      // No. times to loop
    int i, j, k = 0;

    for (i = 0, j = 1;  j <= n;  ++j, i += 4, k += 3)
        map4to3(source[i], source[i+1], source[i+2], source[i+3], dest, k, 3);

    switch (m % 4)
    {
    case 1:
        assert(false);      // "Impossible length during Base64 decoding"
        break;

    case 2:
        map4to3(source[i], source[i+1], 'A', 'A', dest, k, 1);
        break;

    case 3:
        map4to3(source[i], source[i+1], source[i+2], 'A', dest, k, 2);
        break;
    }

}   //  end encodeBytes

// end Base64.cpp
