// ServiceException.cpp

#include "ServiceException.h"

using namespace Yosokumo;

ServiceException::ServiceException() :
    detailMessage(""),
    failedMethodName(""),
    statusCode(0)
{}

ServiceException::ServiceException(const std::string &message) :
    detailMessage(message),
    failedMethodName(""),
    statusCode(0)
{}

ServiceException::ServiceException(
    const std::string &message,
    const std::string &failedMethodName) :
        detailMessage(message),
        failedMethodName(failedMethodName),
        statusCode(0)
{}

ServiceException::ServiceException(
    const std::string &message,
    int               statusCode,
    const std::string &failedMethodName) :
        detailMessage(message),
        failedMethodName(failedMethodName),
        statusCode(statusCode)
{}

ServiceException::ServiceException(const ServiceException &rhs) throw()
{
    operator=(rhs);
}


ServiceException::~ServiceException() throw()
{}

ServiceException &ServiceException::operator=(const ServiceException& rhs) 
    throw()
{
    if (this == &rhs)
        return *this;

    detailMessage    = rhs.detailMessage;
    failedMethodName = rhs.failedMethodName;
    statusCode       = rhs.statusCode;

    return *this;
}


// getters

const char* ServiceException::what() const throw()
{
    return detailMessage.c_str();
}

int ServiceException::getStatusCode() const
{
    return statusCode;
}

std::string ServiceException::getFailedMethodName() const
{
    return failedMethodName;
}

// end ServiceException.cpp
