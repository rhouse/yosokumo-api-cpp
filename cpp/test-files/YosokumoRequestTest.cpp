// YosokumoRequestTest.cpp  -  Test the YosokumoRequest class

#include "UnitTest++.h"

#include "YosokumoRequest.h"

#include <iostream>

using namespace Yosokumo;

static Credentials creds;
static std::string hostName;
static int         port;
static std::string portAsString;
static std::string contentType;

static void setupCredsEtc(
    Credentials &creds,
    std::string &hostName,
    int         &port,
    std::string &contentType)
{
    std::string userId = "THIS-IS-USER-ID1";

    std::vector<uint8_t> key;
    for (uint8_t i = 1;  i <= Credentials::KEY_LEN;  ++i)
        key.push_back(i);

    creds = Credentials(userId, key);

    hostName = "my-host-name";
    port = 98765;
    contentType = "this-is-content-type";

    std::stringstream s;
    s << port;
    portAsString = s.str();
}

TEST(basicMethodsForYosokumoRequest)
{
    std::cout << "YosokumoRequest basicMethodsForYosokumoRequest" << '\n';

    setupCredsEtc(creds, hostName, port, contentType);
    YosokumoRequest yr(creds, hostName, port, contentType);

    CHECK(!yr.getTrace());
    yr.setTrace(true);
    CHECK(yr.getTrace());
    yr.setTrace(false);
    CHECK(!yr.getTrace());

    CHECK_EQUAL(yr.getStatusCode(), 0);

    CHECK(!yr.isException());

    std::vector<uint8_t> entity;
    entity.push_back(254);              // So the vector is not empty

    yr.getEntity(entity);

    CHECK_EQUAL(entity.size(), 0U);      // Returned entity is empty

    ServiceException e = yr.getException();

    std::string auxHeaderName  = "aux header name";
    std::string auxHeaderValue = "aux header value";

    yr.setAuxHeader(auxHeaderName, auxHeaderValue);

    std::string anotherUserId = "zyxwvutsrqponmlk";

    std::vector<uint8_t> anotherKey;
    for (uint8_t i = Credentials::KEY_LEN;  i != 0;  --i)
        anotherKey.push_back(i);

    Credentials anotherCreds(anotherUserId, anotherKey);

    yr.setCredentials(anotherCreds);

}   //  end basicMethodsForYosokumoRequest

TEST(normalizeResourceUriForYosokumoRequest)
{
    std::cout << "YosokumoRequest normalizeResourceUriForYosokumoRequest" << '\n';

    setupCredsEtc(creds, hostName, port, contentType);
    YosokumoRequest yr(creds, hostName, port, contentType);

    std::string uri1 = "http://not-host-name";
    std::string norm_uri1 = uri1;
    CHECK_EQUAL(yr.normalizeResourceUri(uri1, hostName, port), norm_uri1);

    std::string uri2 = "http://" + hostName;
    std::string norm_uri2 = uri2 + ":" + portAsString;
    CHECK_EQUAL(yr.normalizeResourceUri(uri2, hostName, port), norm_uri2);

    std::string uri2_5 = "http://" + hostName + "some-more-stuff";
    std::string norm_uri2_5 = "http://" + hostName + ":" + portAsString + 
                                                        "some-more-stuff";;
    CHECK_EQUAL(yr.normalizeResourceUri(uri2_5, hostName, port), norm_uri2_5);

    std::string uri3 = hostName;
    std::string norm_uri3 = "http://" + uri3;
    CHECK_EQUAL(yr.normalizeResourceUri(uri3, hostName, port), norm_uri3);

    std::string uri4 = hostName + ":" + portAsString;
    std::string norm_uri4 = "http://" + uri4;
    CHECK_EQUAL(yr.normalizeResourceUri(uri4, hostName, port), norm_uri4);

    std::string uri5 = "";
    std::string norm_uri5 = "http://" + hostName + ":" + portAsString;
    CHECK_EQUAL(yr.normalizeResourceUri(uri5, hostName, port), norm_uri5);

    std::string uri6 = "?fred";
    std::string norm_uri6 = "http://" + hostName + ":" + portAsString + uri6;
    CHECK_EQUAL(yr.normalizeResourceUri(uri6, hostName, port), norm_uri6);

}   //  end normalizeResourceUriForYosokumoRequest

// end YosokumoRequestTest.cpp
