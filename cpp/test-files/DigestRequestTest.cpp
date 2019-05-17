// DigestRequestTest.cpp  -  Test the DigestRequest class

#include "UnitTest++.h"

#include "DigestRequest.h"
#include "Credentials.h"

#include <iostream>

using namespace Yosokumo;


static void makeKey(std::vector<uint8_t> &key)
{
    key.clear();

    for (uint8_t i = 1;  i <= Credentials::KEY_LEN;  ++i)
        key.push_back(i);
}


static void modifyKey(std::vector<uint8_t> &key, int offset)
{
    uint8_t newcode;
    int inc;

    offset %= Credentials::KEY_LEN;

    if (offset % 2 == 0)
    {
        newcode = 1;
        inc = +1;
    }
    else
    {
        newcode = 255;
        inc = -1;
    }

    for (int i = offset;  0 <= i && i < Credentials::KEY_LEN;  i += inc)
    {
        key[i] = newcode;
        newcode += inc;
    }
}

TEST(makeDigestForDigestRequest)
{
    std::cout << "DigestRequest makeDigestForDigestRequest" << '\n';

    std::vector<uint8_t> key;
    makeKey(key);

    std::string actualDigest;

    try
    {
        actualDigest = DigestRequest::makeDigest(
            "This is the message which we want to digest", key);
    }
    catch (const ServiceException &e)
    {
        std::cout << "***** DigestRequest::makeDigest threw an exception:  "
            << e.what();
        CHECK(false); 
    }

    // See comment below about this expected text
    std::string expectedDigest = 
        "CuUvGGXmrPcbHHRqozOCKea+NqI9xZZ3J4LLkguM/Zl1" 
        "feq0P54JWusIxrH3yTe9IuLgv22llMvrG2piYLTFPw==";

    CHECK_EQUAL(actualDigest, expectedDigest);
}

TEST(exerciseMakeDigestForDigestRequest)
{
    std::cout << "DigestRequest exerciseMakeDigestForDigestRequest" << '\n';

    std::vector<uint8_t> key;
    makeKey(key);

    std::string message = "This is the message we want to digest, long "
        "enough to be of more interest than a little short message.";

    // The expected texts below were computed by the Java test program
    // DigestRequestTest.java.  Since both the C++ OpenSSL HMAC function
    // and the Java SecretKeySpec stuff compute the same digests, we're
    // reasonably certain that both our C++ and Java versions of DigestRequest
    // are working.
    std::vector<std::string> expectedDigest;
    expectedDigest.push_back(
            "tuxAMHZv4KKzYXtpctNZCvehM/TKyVLAPFZ2wJLpjToc"
            "7MSzO10XyK5G3Wbi7Ng4uiFgEHcW0F1PxZA+9aKWUA==");
    expectedDigest.push_back(
            "qIbt7I9xBQ8KEl8bsRPvvj+rHvDnSpULod/4ZUEjmJkN"
            "6+UfaEpM0LbLLaAdtHDPrxDKG8brl0IfV0pjEyvBkQ==");
    expectedDigest.push_back(
            "ALmFQDeeprAE5JS9Y2XGP89E2DmS+0RRsMLXmw/TgceI" 
            "Mab1OVCLMwEPzPQQMw4UeyEV+GGTWWAQa41XwEeHzQ==");
    expectedDigest.push_back(
            "z7mbEK2eQR+0U6bPmJ0AbPALZiMU8qHsRbm0UTQM/sLb"
            "262AiKj8pwCD6/GQ0cedssx/E3GhAO5CoDfmWiW8nA==");
    expectedDigest.push_back(
            "j3V+WWUNTcRDayo0TUmd+yWIZMfRnHbk/c6YrA3/PHcW"
            "8VxnbhNgRHgNPlD4P5LrHbjhSMudYMe3KqXSZbra0A==");
    expectedDigest.push_back(
            "uqrGrZczgDOr73AH9pwhK/GFk5tHv5TgpaatS83bFz4E"
            "OGBl89t7fe1D38nwY/C0hWy4igYNAX7FamZp3hlj5Q==");
    expectedDigest.push_back(
            "Nll7o9UGAhgGv4w1NmHwhbcu/V4AwE3NEPembkYaXxmu"
            "7LQg9jqFXZBygPk42mt7hDwoLlGLgjnO/sJdi0HM0w==");

    int i = 0;

    for (int offset = 2;  offset <= 20;  offset += 3)
    {
        modifyKey(key, offset);

        std::string actualDigest;
    
        try
        {
            actualDigest = DigestRequest::makeDigest(message, key);
        }
        catch (const ServiceException &e)
        {
            std::cout << "***** DigestRequest::makeDigest threw an exception:  "
                << e.what();
            CHECK(false); 
        }

        CHECK_EQUAL(actualDigest, expectedDigest.at(i));
        ++i;
    }
}

// end DigestRequestTest.cpp
