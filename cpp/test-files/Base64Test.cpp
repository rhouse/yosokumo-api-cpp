// Base64Test.cpp  -  Test the Base64 class with UnitTest++

#include "UnitTest++.h"
#include "Base64.h"

#include "encode.h"    // libb64 headers to check our code against
#include "decode.h"

#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace Yosokumo;

// The libb64 C++ wrapper provides encode and decode methods which operate 
// on streams.  We use these methods to create an interface using C++ vectors 
// and strings.  This gives us an independent check of our base64 methods.

void other_encodeBytes(const std::vector<uint8_t> &source, std::string &dest)
{
    std::stringstream instream(
        std::stringstream::in  | std::stringstream::out | 
        std::stringstream::app | std::stringstream::binary);

    std::stringstream outstream(
        std::stringstream::in  | std::stringstream::out | 
        std::stringstream::app);

    for (unsigned i = 0;  i < source.size();  ++i)
        instream.put(source[i]);

    base64::encoder E;
    E.encode(instream, outstream);

    dest.clear();

    // E.encode inserts '\n' characters in the output to create lines of no 
    // more than 72 characters each; we get rid of these

    while (outstream.good())
    {
        char c;
        outstream.get(c);
        if (outstream.good() && c != '\n')
            dest.append(1, c);
    }

}   //  end other_encodeBytes


void other_decodeString(const std::string &source, std::vector<uint8_t> &dest)
{
    std::stringstream instream(source, std::stringstream::in);

    std::stringstream outstream(
        std::stringstream::in  | std::stringstream::out | 
        std::stringstream::app | std::stringstream::binary);

    base64::decoder E;
    E.decode(instream, outstream);

    dest.clear();

    while (outstream.good())
    {
        char c;
        outstream.get(c);
        if (outstream.good())
            dest.push_back((unsigned)c);
    }

}   //  other_decodeString

// Verify that all the characters in the input string are valid base64 chars.
// If an invalid character is encountered, a std::invalid_argument exception
// is thrown. -- Note that this function does NOT check if s is a valid 
// base64 string.  Call Base64::decodeString(s) to determine if s is valid.

void verifyBase64Chars(const std::string &s)
{
    std::string t = s;

    int n = t.size();

    for (int i = 1;  i <= 2;  ++i)
    {
        if (n > 0 && t[n-1] == '=')
        {
            t.erase(n-1, 1);
            --n;
        }
    }

    for (int i = 0;  i < n;  ++i)
        Base64::decode64(t[i]);     // throws an exception if t[i] invalid
}

// Convert the input bytes vector to a base64 string, convert the string back
// to bytes, and make sure the later byte vector equals the input byte vector.
// Then convert the input bytes vector to a base64 string using other_encode,
// and verify that the resulting string is the same as produced by our own
// methods.  Finally, convert the base64 string back to bytes using other_
// decode, and make sure the result is equal to the input bytes vector.

std::string bytesToBase64(const std::vector<uint8_t> &bytes)
{
    int n = bytes.size();

    std::string str;
    Base64::encodeBytes(bytes, str);    // bytes -> base64 string

    verifyBase64Chars(str);             // verify the base64 chars

    std::vector<uint8_t> b;
    Base64::decodeString(str, b);       // base64 string -> back to bytes b
    CHECK_EQUAL(n, (int)b.size());
    CHECK_ARRAY_EQUAL(bytes, b, n);     // check that bytes == b

    // Check our encoding and decoding against an independent implementation

    std::string strXXX;
    other_encodeBytes(bytes, strXXX);   // bytes -> base64 via other method
    CHECK_EQUAL(str.size(), strXXX.size());
    CHECK_EQUAL(str, strXXX);           // does other method agree with us?

    std::vector<uint8_t> bXXX;
    other_decodeString(strXXX, bXXX);   // base64 -> back to bytes via other
    CHECK_EQUAL(n, (int)bXXX.size());
    CHECK_ARRAY_EQUAL(bytes, bXXX, n);  // does other method agree with us?

    return str;
}

TEST(variousLengths)
{
    std::cout << "Base64Test variousLengths" << '\n';

    uint8_t i1 [] = {22};
    uint8_t i2 [] = {22, 33};
    uint8_t i3 [] = {22, 33, 44};
    uint8_t i4 [] = {22, 33, 44, 55};
    uint8_t i5 [] = {22, 33, 44, 55, 66};
    uint8_t i6 [] = {22, 33, 44, 55, 66, 77};
    uint8_t i7 [] = {22, 33, 44, 55, 66, 88};
    uint8_t i8 [] = { 0, 16, -125, 16, 81, -128};
    uint8_t i9 [] = {16, 81};
    uint8_t i10[] = {16, 81,    0};
    uint8_t i11[] = {16, 81,   64};
    uint8_t i12[] = {16, 81, -128};
    uint8_t i13[] = {16, 81,  -64};
    uint8_t i14[] = {0, 16};
    uint8_t i15[] = {0};

    std::vector<uint8_t> b0;
    std::vector<uint8_t> b1 (i1,  i1+ 1);
    std::vector<uint8_t> b2 (i2,  i2+ 2);
    std::vector<uint8_t> b3 (i3,  i3+ 3);
    std::vector<uint8_t> b4 (i4,  i4+ 4);
    std::vector<uint8_t> b5 (i5,  i5+ 5);
    std::vector<uint8_t> b6 (i6,  i6+ 6);
    std::vector<uint8_t> b7 (i7,  i7+ 6);
    std::vector<uint8_t> b8 (i8,  i8+ 6);
    std::vector<uint8_t> b9 (i9,  i9+ 2);
    std::vector<uint8_t> b10(i10, i10+3);
    std::vector<uint8_t> b11(i11, i11+3);
    std::vector<uint8_t> b12(i12, i12+3);
    std::vector<uint8_t> b13(i13, i13+3);
    std::vector<uint8_t> b14 (i14, i14+ 2);
    std::vector<uint8_t> b15 (i15, i15+ 1);

    bytesToBase64(b0);
    bytesToBase64(b1);
    bytesToBase64(b2);
    bytesToBase64(b3);
    bytesToBase64(b4);
    bytesToBase64(b5);
    bytesToBase64(b6);
    bytesToBase64(b7);
    bytesToBase64(b8);
    bytesToBase64(b9);
    bytesToBase64(b10);
    bytesToBase64(b11);
    bytesToBase64(b12);
    bytesToBase64(b13);
    bytesToBase64(b14);
    bytesToBase64(b15);
}

TEST(allBitPatterns)
{
    std::cout << "Base64Test allBitPatterns" << '\n';

    int n = 3*256;

    std::vector<uint8_t> bytes(n);

    CHECK_EQUAL((int)bytes.size(), n);

    int k = 0;

    for (int i = 0;  i < 256;  ++i)
    {
        bytes[k++] = (uint8_t)i;
        bytes[k++] = (uint8_t)(i+1);
        bytes[k++] = (uint8_t)(i+2);
    }

    CHECK_EQUAL(k, n);

    std::string s = bytesToBase64(bytes);

    CHECK_EQUAL((int)s.size(), 4*256);

    // Now check that every possible base64 char appears in s

    std::vector<bool> sawChar(64);

    for (int i = 0;  i < 64;  ++i)
        sawChar[i] = false;

    for (int i = 0;  i < 4*256;  ++i)
        sawChar[ Base64::decode64( s[i] ) ] = true;

    for (int i = 0;  i < 64;  ++i)
        CHECK(sawChar[i]);
}

int random_int(int min, int max)
{
    return min + (rand() % (int)(max - min + 1));
}

TEST(randomBytes)
{
    std::cout << "Base64Test randomBytes" << '\n';

    int numTests = 100;
    int maxLen = 2048;

    for (int i = 0;  i < numTests;  ++i)
    {
        int len = random_int(1, maxLen);

        std::vector<uint8_t> bytes;

        for (int j = 0;  j < len;  ++j)
        {
            uint8_t b = (uint8_t)random_int(0, 255);
            bytes.push_back(b);
        }

        bytesToBase64(bytes);
    }
}

TEST(base64Exceptions)
{
    std::cout << "Base64Test base64Exceptions" << '\n';

    // Invalid Base64 character
    CHECK_THROW(Base64::decode64('*'), std::invalid_argument);

    // Base64 string length is not a multiple of 4
    std::vector<uint8_t> bytes;
    CHECK_THROW(Base64::decodeString("A",   bytes), std::invalid_argument);
    CHECK_THROW(Base64::decodeString("AB",  bytes), std::invalid_argument);
    CHECK_THROW(Base64::decodeString("ABC", bytes), std::invalid_argument);

    // Invalid Base64 character
    CHECK_THROW(Base64::decodeString("ABC*", bytes), std::invalid_argument);
}

// end Base64Test.cpp
