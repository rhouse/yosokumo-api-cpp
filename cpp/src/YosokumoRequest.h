// YosokumoRequest.h

#ifndef YOSOKUMOREQUEST_H
#define YOSOKUMOREQUEST_H

#include "YosokumoDIF.h"
#include "Credentials.h"

#include <vector>

namespace Yosokumo
{
/**
 * Implements all HTTP requests to the Yosokumo web service.  These are the 
 * basic methods:
 * <ul>
 * <li>getFromServer()
 * <li>postToServer()
 * <li>deleteFromServer()
 * <li>putToServer()
 * </ul>
 * These above methods all return false in case of a problem.  The caller can 
 * then use these methods to determine the cause of the failure:
 * <ul>
 * <li>getStatusCode()
 * <li>getEntity()
 * <li>isException()
 * <li>getException()
 * </ul>
 * @author  Roger House
 * @version 0.9
 */

class YosokumoRequest
{
private:
    bool trace;                     // Set true to get debug trace 

    Credentials credentials;
    std::string hostName;
    int         port;
    std::string contentType;

    std::string auxHeaderName;      // Auxiliary header name
    std::string auxHeaderValue;     //   and value

    int                  statusCode;
    std::vector<uint8_t> entity;
    ServiceException     exception;

    static std::vector<uint8_t> emptyEntity;    // Only used as default value

public:
    /**
     * Initializes a newly created <code>YosokumoRequest</code> object with 
     * attributes specified by the input parameters.
     *
     * @param   credentials specifies user id and key for authentication.
     * @param   hostName is the name of the Yosokumo server.
     * @param   port is the port to use to access the Yosokumo service.
     * @param   contentType is the content type to use in HTTP communications
     *          with the Yosokumo server (e.g., application/yosokumo+protobuf).
     */
    YosokumoRequest(
        const Credentials &credentials,
        const std::string &hostName,
        int               port,
        const std::string &contentType);

    /**
     * Initialize for an HTTP operation.  Init various data fields to prepare 
     * for execution of a service request.
     */
    void initForOperation();

    /**
     * Set the credentials.
     *
     * @param  credentials to use in HTTP communications to authorize the 
     *             user on the Yokosumo server.
     */
    void setCredentials(Credentials credentials);

    /**
     * Set the auxiliary header.  Some HTTP requests use an auxiliary header
     * such as "x-yosokumo-full-entries: on" for Get Catalog.
     *
     * @param  name is the name of the auxiliary header, e.g., 
     *             "x-yosokumo-full-entries".
     * @param  value is the value of the auxiliary header, e.g., "on".
     */
    void setAuxHeader(const std::string &name, const std::string &value);

    /**
     * Set the trace flag.  When trace is on, text is written to cout
     * showing the progress of HTTP requests and reponses.
     *
     * @param  traceOn is the value to assign to the trace flag.
     */
    void setTrace(bool traceOn);

    /**
     * Return the trace flag.
     *
     * @return  the current setting of the trace flag.
     */
    bool getTrace();

    /**
     * Return the status code from an HTTP response.
     *
     * @return the status code from an HTTP response.
     */
    int getStatusCode();

    /**
     * Get the entity from an HTTP response.
     *
     * @param  putEntityHere specifies where to store the entity from 
     *         an HTTP response.
     */
    void getEntity(std::vector<uint8_t> &putEntityHere);

    /**
     * Test if an exception has occurred.
     *
     * @return <code>true</code> means there is an exception.
     *         <code>false</code> means there is no exception.
     */
    bool isException();

    /**
     * Return the exception from an HTTP process.
     *
     * @return an exception from an HTTP response.
     */
    ServiceException getException();

    /**
     * Issue an HTTP GET request.
     *
     * @param  resourceUri is the URI of the resource to get.
     *
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             to obtain the data returned from the server.
     */
    bool getFromServer(const std::string &resourceUri);

    /**
     * Issue an HTTP POST request.
     *
     * @param  resourceUri is the URI of the resource to post to.
     * @param  entityToPost is the entity to post to the server.
     *
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             to obtain the data returned from the server.
     */
    bool postToServer(
        const std::string          &resourceUri, 
        const std::vector<uint8_t> &entityToPost);

    /**
     * Issue an HTTP DELETE request.
     *
     * @param  resourceUri is the URI of the resource to delete.
     *
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             for more information.
     */
    bool deleteFromServer(const std::string &resourceUri);

    /**
     * Issue an HTTP PUT request.
     *
     * @param  resourceUri is the URI where to put the resource.
     * @param  entityToPut is the entity to put to the server.
     *
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             for more information.
     */
    bool putToServer(
        const std::string          &resourceUri, 
        const std::vector<uint8_t> &entityToPut);

//??? Very temporary defs
typedef int HttpRequestBase;
typedef int HttpRequest;

    /**
     * Make an HTTP request.  This is the workhorse method which does all the 
     * work of making an HTTP request and processing the response.
     *
     * @param  httpRequest is HttpGet, HttpPut, HttpPost, or HttpDelete.
     * @param  entityToSend is an entity to put to the server.
     * @param  traceName is the name of the request to be used in trace output.
     *
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             for more information.
     */
    bool makeRequest(
        HttpRequestBase httpRequest, 
        const std::string &traceName,
        const std::vector<uint8_t> &entityToSend = emptyEntity);

    /**
     * Execute an HTTP request and process the response.
     *
     * @param  httpRequest is an HTTP request, ready to be executed
     * @param  traceName is the name of the request to be used in trace output.
     * @return <code>false</code> means there was a problem (call 
     *             <code>getStatusCode()</code>, <code>getEntity()</code>, and
     *             <code>getException()</code> for more information).
     *         <code>true</code> means the request was successful.  Call 
     *             <code>getStatusCode()</code> and <code>getEntity()</code>
     *             for more information.
     */
    bool getResponse(HttpRequestBase httpRequest, const std::string &traceName);

    /**
     * Normalize a resource URI.  There are several cases:
     * <ul>
     * <li>The input URI begins with <code>"http://"</code> but the next part of 
     *         the URI is not the host name:  Return the URI as is.
     * <li>The input URI begins with <code>"http://"</code>+hostname:  Return the 
     *         URI with <code>":"+port</code> inserted after the host name.
     * <li>The input URI begins with the host name:  Return the URI with 
     *          <code>"http://"</code> prepended.
     * <li>None of the above:  Return the URI with 
     *          <code>"http://"+hostName+":"+port</code> prepended.
     * </ul>
     * One reason this method exists is that the HttpClient classes HttpGet, 
     * HttpPost, etc., require that the resource URIs passed to their 
     * constructors have the <code>"http://"+hostName</code> prefix, despite the 
     * fact that the HTTP request lines created by these classes strip the 
     * prefix and use only the resource URI.  This normalization method 
     * allows the programmer to use only the URI, or the fully-prefixed 
     * URI, whichever is more convenient.
     *
     * @param   resourceUri  the input URI to normalize.
     * @param   hostName     the host name to use.
     * @param   port         the port to use.
     *
     * @return  a normalized version of the input URI.
     */
    std::string normalizeResourceUri(
        const std::string &resourceUri, 
        const std::string &hostName,
        int port);

    /**
     * Make a digest of an HTTP request.
     *
     * @param   request is the HTTP request to digest.
     * @return  <code>null</code> means there was a problem; <code>exception</code> 
     *              is set.  Otherwise the return value is a digest of the 
     *              input request.
     */
    std::string makeDigest(HttpRequestBase request);

    /**
     * Make a string from an HTTP request.  This string is used for Yosokumo
     * authentication.
     *
     * @param   r is the input HTTP request.
     * @return  is a string containing a number of fields from r. 
     */
    std::string makeRequestString(HttpRequestBase r);

    /**
     * Append an HTTP header value.  This is a helper method for 
     * makeRequestString.
     *
     * @param   r is the input HTTP request.
     * @param   headerName is the name of the header whose value is wanted.
     * @param   s is the string to append the header value to.
     */
    void appendHeaderValue(
        HttpRequest       r,
        const std::string &headerName,
              std::string &s);

};  //  end YosokumoRequest

}   //  end namespace Yosokumo

#endif  // YOSOKUMOREQUEST_H

// end YosokumoRequest.h

