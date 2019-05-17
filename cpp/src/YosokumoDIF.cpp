// YosokumoDIF.cpp

#include <string.h>

#include "YosokumoDIF.h"

using namespace Yosokumo;


YosokumoDIF::YosokumoDIF()
{
    clearException();
}

YosokumoDIF::~YosokumoDIF()
{}

bool YosokumoDIF::isException()
{
    return isException(exception);
}

bool YosokumoDIF::isException(const ServiceException &e)
{
    return
    (!(
           (e.what() == NULL || strlen(e.what()) == 0)
        && e.getStatusCode() == 0
        && e.getFailedMethodName().empty()
      )
    );
}

bool YosokumoDIF::getException(ServiceException &e)
{
    if (isException())
    {
        e = exception;
        return true;
    }

    return false;
}

void YosokumoDIF::clearException()
{
    exception = ServiceException("", 0, "");
}

// end YosokumoDIF.cpp
