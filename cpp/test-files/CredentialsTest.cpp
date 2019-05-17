// CredentialsTest.cpp  -  Test the Credentials class

#include "UnitTest++.h"

#include "Credentials.h"

#include <iostream>

using namespace Yosokumo;


static void makeKey(std::vector<uint8_t> &key)
{
    key.clear();

    for (uint8_t i = 1;  i <= Credentials::KEY_LEN;  ++i)
        key.push_back(i);
}

TEST(allMethodsForCredentials)
{
    std::cout << "Credentials allMethodsForCredentials" << '\n';

    std::string userId = "my user id";
    std::vector<uint8_t> key;
    makeKey(key);

    Credentials creds(userId, key);
    
    CHECK_EQUAL(creds.getUserId(), userId);

    std::vector<uint8_t> key2;
    creds.getKey(key2);

    CHECK(key == key2);

    std::string actualToString = creds.toString();
    std::string expectedToString = 
        "Credentials:\n"
        "  userId = my user id\n"
        "  key    = 64 bytes\n"
        " 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n"
        " 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30\n"
        " 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45\n"
        " 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60\n"
        " 61 62 63 64\n";

    CHECK_EQUAL(actualToString, expectedToString);
}

// end CredentialsTest.cpp
