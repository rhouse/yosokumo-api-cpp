// ServiceException.h


#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include <exception>
#include <string>

namespace Yosokumo
{
/**
 * Encapsulates all exceptions which can be thrown by the Yosokumo Service.
 */

class ServiceException : public std::exception
{
    std::string detailMessage;
    std::string failedMethodName;
    int statusCode;

public:

    /**
     * Constructs a new default exception.
     */
    ServiceException();

    /**
     * Constructs a new exception with the specified detail message.  
     *
     * @param  message the detail message. The detail message is saved for 
     *                 later retrieval by the <code>what()</code> method.
     */
    ServiceException(const std::string &message);

    /**
     * Constructs a new exception with the specified detail message and 
     * failed method name.  
     *
     * @param  message the detail message (which is saved for later retrieval 
     *                 by the <code>what()</code> method.
     * @param  failedMethodName the name of the method which failed 
     *                 with the exception.
     */
    ServiceException(
        const std::string &message,
        const std::string &failedMethodName);

    /**
     * Constructs a new exception with the specified detail message, 
     * status code, and failed method name.  
     *
     * @param  message the detail message (which is saved for later retrieval 
     *                 by the <code>what()</code> method.
     * @param  statusCode the status code from most recent HTTP response.  
     *                 A zero means the most recent HTTP request did not
     *                 result in a response, e.g., there is no network 
     *                 connection.
     * @param  failedMethodName the name of the Service method which failed
     *                 with the exception.
     */
    ServiceException(
        const std::string &message,
        int               statusCode,
        const std::string &failedMethodName);

    /**
     * Copy constructor - initializes a newly created 
     * <code>ServiceException</code> object with a copy of another 
     * <code>ServiceException</code> object. 
     *
     * @param  rhs  the <code>ServiceException</code> to make a copy of.
     */
    ServiceException(const ServiceException &rhs) throw();

    /**
     * Destructor - destroy a <code>ServiceException</code> object.
     */
    virtual ~ServiceException() throw();

    /**
     * Assignment operator - assign one <code>ServiceException</code> to 
     * another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> ServiceException.
     */
    ServiceException& operator=(const ServiceException& rhs) throw();

    // getters

    /**
     * Return message telling what exception occurred.
     *
     * @return  message telling what exception occurred.
     */
    const char* what() const throw();

    /**
     * Return HTTP status code.
     *
     * @return  status code from most recent HTTP response.  A zero means 
     *              the most recent HTTP request did not result in a response,
     *              e.g., there is no network connection.
     */
    int getStatusCode() const;

    /**
     * Return the name of the Service method which failed with this exception.
     *
     * @return  name of the Service method which failed.
     */
    std::string getFailedMethodName() const;

};  //  end class ServiceException

}   //  end namespace Yosokumo

#endif  // SERVICEEXCEPTION_H

// end ServiceException.h
