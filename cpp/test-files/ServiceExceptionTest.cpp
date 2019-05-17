// ServiceExceptionTest.cpp  -  Test the ServiceException class

#include "UnitTest++.h"

#include "ServiceException.h"

#include <iostream>

using namespace Yosokumo;


static void throwBasic(const std::string &message)
{
    throw ServiceException(message);
}

TEST(basicCtorForServiceException)
{
    std::cout << "ServiceException basicCtorForServiceException" << '\n';

    std::string mess = "our very first exception";

    try
    {
        throwBasic(mess);
    }
    catch(const ServiceException &e)
    {
        CHECK_EQUAL(e.what(), mess);
        CHECK_EQUAL(e.getStatusCode(), 0);
        CHECK_EQUAL(e.getFailedMethodName(), "");
    }
}

static void throwAdvanced(
    const std::string &message, 
    int               statusCode,
    const std::string &methodName)
{
    throw ServiceException(message, statusCode, methodName);
}

TEST(advancedCtorForServiceException)
{
    std::cout << "ServiceException advancedCtorForServiceException" << '\n';

    std::string mess   = "not the first exception";
    std::string method = "ThisMethodFailed";
    int status         = 123456789;

    try
    {
        throwAdvanced(mess, status, method);
    }
    catch(const ServiceException &e)
    {
        CHECK_EQUAL(e.what(), mess);
        CHECK_EQUAL(e.getStatusCode(), status);
        CHECK_EQUAL(e.getFailedMethodName(), method);
    }
}

TEST(copyCtorAndAssignmentOperatorForServiceException)
{
    std::cout << "ServiceException copyCtorAndAssignmentOperatorForServiceException" << '\n';

    std::string mess   = "the message";
    std::string method = "the method";
    int status         = 314159;

    // copy ctor
    ServiceException *pException = new ServiceException(mess, status, method);
    ServiceException e(*pException);
    delete pException;

    CHECK_EQUAL(e.what(), mess);
    CHECK_EQUAL(e.getStatusCode(), status);
    CHECK_EQUAL(e.getFailedMethodName(), method);

    // assignment operator
    ServiceException e2("junk");
    e2 = e;

    CHECK_EQUAL(e2.what(), mess);
    CHECK_EQUAL(e2.getStatusCode(), status);
    CHECK_EQUAL(e2.getFailedMethodName(), method);

}

TEST(noGarbageLeftBehindForServiceException)
{
    std::cout << "ServiceException noGarbageLeftBehindForServiceException" << '\n';

    std::string mess   = "message";
    std::string method = "method";
    int status         = 5000;

    while (status > 0)
    {
        try
        {
            throwAdvanced(mess, status, method);
        }
        catch(const ServiceException &e)
        {
            CHECK_EQUAL(e.what(), mess);
            CHECK_EQUAL(e.getStatusCode(), status);
            CHECK_EQUAL(e.getFailedMethodName(), method);
        }

        --status;
    }
}

// end ServiceExceptionTest.cpp
