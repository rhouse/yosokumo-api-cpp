// YosokumoRequest.cpp

#include "YosokumoRequest.h"
#include "StringUtil.h"

using namespace Yosokumo;

// Only used as default value
std::vector<uint8_t> YosokumoRequest::emptyEntity;

YosokumoRequest::YosokumoRequest(
    const Credentials &credentials,
    const std::string &hostName,
    int               port,
    const std::string &contentType)
{
    this->trace       = false;

    this->credentials = credentials;
    this->hostName    = hostName;
    this->port        = port;
    this->contentType = contentType;

    initForOperation();

    emptyEntity.clear();
}

void YosokumoRequest::initForOperation()
{
    auxHeaderName  = "";
    auxHeaderValue = "";
    statusCode     = 0;
    entity.clear();
    exception      = ServiceException();
}

void YosokumoRequest::setCredentials(Credentials credentials)
{
    this->credentials = credentials;
}

void YosokumoRequest::setAuxHeader(
    const std::string &name, 
    const std::string &value)
{
    auxHeaderName  = name;
    auxHeaderValue = value;
}

void YosokumoRequest::setTrace(bool traceOn)
{
    this->trace = traceOn;
}

bool YosokumoRequest::getTrace()
{
    return trace;
}

int YosokumoRequest::getStatusCode()
{
    return statusCode;
}

void YosokumoRequest::getEntity(std::vector<uint8_t> &putEntityHere)
{
    putEntityHere = entity;
}

bool YosokumoRequest::isException()
{
    return YosokumoDIF::isException(exception);
}

ServiceException YosokumoRequest::getException()
{
    return exception;
}

//??? From this point on the code for the function bodies needs work

bool YosokumoRequest::getFromServer(const std::string &resourceUri)
{
    std::string uri = normalizeResourceUri(resourceUri, hostName, port);
    
    return makeRequest(1, "getFromServer");
//??    return makeRequest(new HttpGet(uri), "getFromServer");
}

bool YosokumoRequest::postToServer(
    const std::string          &resourceUri, 
    const std::vector<uint8_t> &entityToPost)
{
    std::string uri = normalizeResourceUri(resourceUri, hostName, port);
    return makeRequest(2, "postToServer", entityToPost);
//??    return makeRequest(new HttpPost(uri), "postToServer", entityToPost);
}

bool YosokumoRequest::deleteFromServer(const std::string &resourceUri)
{
    std::string uri = normalizeResourceUri(resourceUri, hostName, port);
    
    return makeRequest(3, "deleteFromServer");
//??    return makeRequest(new HttpDelete(uri), "deleteFromServer");
}

bool YosokumoRequest::putToServer(
    const std::string          &resourceUri,
    const std::vector<uint8_t> &entityToPost)
{
    std::string uri = normalizeResourceUri(resourceUri, hostName, port);
    
    return makeRequest(4, "putToServer", entityToPost);
//??    return makeRequest(new HttpPut(uri), "putToServer", entityToPost);
}



bool YosokumoRequest::makeRequest(
    HttpRequestBase httpRequest, 
    const std::string &traceName,
    const std::vector<uint8_t> &entityToSend)
{
#if 0   //??? patch out
    if (trace)
    {
        System.out.println(traceName+":");
        System.out.println(credentials.toString());
    }

    statusCode = 0;
    entity     = null;
    exception  = null;

    // Add headers to the request

    httpRequest.addHeader("Host",   hostName);
    httpRequest.addHeader("Date",   DateUtils.formatDate(new Date()));
    httpRequest.addHeader("Accept", contentType);

    if (auxHeaderName != null && !auxHeaderName.isEmpty())
    {
        httpRequest.addHeader(auxHeaderName, auxHeaderValue);
        auxHeaderName  = null;
        auxHeaderValue = null;
    }

    if (entityToSend != null)
    {
        httpRequest.addHeader("Content-Type", contentType);
        httpRequest.addHeader("Content-Length", 
                                Integer.toString(entityToSend.length));
    }

    std::string requestDigest = makeDigest(httpRequest);
    if (requestDigest == null)
        return false;

    httpRequest.addHeader("Authorization", "yosokumo " + 
                        credentials.getUserId() + ":" + requestDigest);

    if (entityToSend != null)
    {
        // We need the Content-Length header to compute the digest, but 
        // we can't keep it as a header because the call of setEntity 
        // below causes a Content-Length header to be automatically 
        // generated, and if there are two of them, an exception is 
        // thrown.

        httpRequest.removeHeaders("Content-Length");
        ByteArrayEntity baEntity = new ByteArrayEntity(entityToSend);
        ((HttpEntityEnclosingRequestBase)httpRequest).setEntity(baEntity);
    }

    if (trace)
    {
        System.out.println("  Request:");
        System.out.println("    Request line: " + 
                                            httpRequest.getRequestLine());
        HeaderIterator it = httpRequest.headerIterator(null);
        while (it.hasNext())
            System.out.println("    " + it.next());
    }

    // Execute the request and get the response

    return getResponse(httpRequest, traceName);
#endif
return false;    

}   //  end makeRequest

bool YosokumoRequest::getResponse(HttpRequestBase httpRequest, const std::string &traceName) 
{
#if 0 //???
    HttpClient httpclient = new DefaultHttpClient();

    try
    {
        HttpResponse response = httpclient.execute(httpRequest);

        statusCode = response.getStatusLine().getStatusCode();

        HttpEntity theEntity = response.getEntity();

        if (theEntity != null)
        { 
            int contentLen = (int)theEntity.getContentLength();

            if (contentLen < 0)
            {
                //  Content length unknown so reading content is awkward
                final int BUFF_SIZE = 16384;
                byte [] buffer = new byte[BUFF_SIZE];
                int totalBytesRead = 0;
                InputStream is = theEntity.getContent();
                while (true)
                {
                    if (totalBytesRead == buffer.length)
                    {
                        byte [] tempArray = new byte[4*buffer.length];
                        System.arraycopy(buffer, 0, tempArray, 0,  
                                                        totalBytesRead);
                        buffer = tempArray;
                    }

                    int numRead = is.read(buffer, totalBytesRead, 
                                            buffer.length-totalBytesRead);
                    if (numRead == -1)
                        break;
                    totalBytesRead += numRead;
                }
                if (totalBytesRead > 0)
                {
                    entity = new byte[totalBytesRead];
                    System.arraycopy(buffer, 0, entity, 0, totalBytesRead);
                }
            }

            if (contentLen >= 0)
            {
                // Content length is known so reading content is easy
                entity = new byte[contentLen];
                InputStream is = theEntity.getContent();
                int offset = 0;
                while (contentLen > 0)
                {
                    int numRead = is.read(entity, offset, contentLen);
                    if (numRead == -1)
                        break;
                    offset += numRead;
                    contentLen -= numRead;
                }
                if (contentLen > 0)
                {
                    exception = new ServiceException("Attempt to read " + 
                        "last " + contentLen + " bytes of entity failed"); 
                    return false;
                }
            }
        }
        if (trace)
        {
            System.out.println("  Response:");
            System.out.println("    Status line: " + 
                                            response.getStatusLine());
            HeaderIterator it = response.headerIterator(null);
            while (it.hasNext())
                System.out.println("    " + it.next());
        }

    }
    catch (IOException e)
    {
        exception = new ServiceException("Fatal transport error in " + 
                                                        traceName, e);
        return false;
    }
    finally
    {
        // When the HttpClient instance is no longer needed, shut down the 
        // connection manager to ensure immediate deallocation of all 
        // system resources

        httpclient.getConnectionManager().shutdown();
    }

    return true;
#endif
return false;    

}   //  end getResponse

std::string YosokumoRequest::normalizeResourceUri(
    const std::string &resourceUri, 
    const std::string &hostName,
    int port)
{
    std::stringstream s;
    s << port;
    std::string portAsString = s.str();

    std::string scheme = "http://";

    if (startsWith(resourceUri, scheme))
    {
        std::string schemeHostName = scheme + hostName;
        if (!startsWith(resourceUri, schemeHostName))
            return resourceUri;
        int len = schemeHostName.length();
        return (resourceUri.substr(0, len) + ":" + portAsString + 
            resourceUri.substr(len));
    }

    std::string newUri = "http://";

    if (!startsWith(resourceUri, hostName))
        newUri.append(hostName + ":" + portAsString);

    newUri.append(resourceUri);

    return newUri;
}

std::string YosokumoRequest::makeDigest(HttpRequestBase request)
{
#if 0 //???
    std::string requestString = makeRequestString(request);

    if (trace)
        System.out.println("    requestString: " + requestString);

    std::string requestDigest;

    try
    {
        requestDigest = DigestRequest.makeDigest(requestString, 
                                                 credentials.getKey());
    }
    catch (ServiceException e)
    {
        exception = e;
        requestDigest = null;
    }

    return requestDigest; 
#endif
return "";

}   //  end makeDigest

std::string YosokumoRequest::makeRequestString(HttpRequestBase r)
{
#if 0
    StringBuilder s = new StringBuilder();
    Header h;

    s.append(r.getRequestLine().getMethod());       // method
    appendHeaderValue(r, "Host", s);                // host
    s.append("+" + r.getURI().getPath());           // uri 
    appendHeaderValue(r, "Date",             s);    // date
    appendHeaderValue(r, "Content-Type",     s);    // content type
    appendHeaderValue(r, "Content-Length",   s);    // content length
    appendHeaderValue(r, "Content-Encoding", s);    // content encoding
    appendHeaderValue(r, "Content-MD5",      s);    // content MD5
    return s.toString();
#endif
return "";

}   //  end makeRequestString

void YosokumoRequest::appendHeaderValue(
    HttpRequest   r,
    const std::string        &headerName,
    std::string &s)
{
#if 0 //??
    Header h;

    s.append("+");
    h = r.getFirstHeader(headerName);
    if (h != null)
        s.append(h.getValue());
#endif
}

// end YosokumoRequest.cpp

