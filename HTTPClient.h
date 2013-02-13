/**
 * Header file for a dependency injection version of HTTPClient for testing.
 *
 * The header file for a mock HTTPClient for the Arduino platform that allows
 * fake response values to be injected for unit testing purposes.
 *
 * @auth Sam Pottinger
 * @lice GNU GPL v3
**/

#ifndef HTTP_CLIENT_HEADER
#define HTTP_CLIENT_HEADER

#include <stdio.h>
#include <string.h>

#define TESTING 1

#if TESTING == 1
#include "emulated_env.h"
#endif

/**
 * A version of the Arduino HTTPClient to allow for local unit testing.
**/
class HTTPClient
{
private:
    int nextReturnCode;
    char * lastURI;
    char * lastData;
    bool streamClosed;

public:
    /**
     * Create a new HTTP client.
     *
     * @param host: The name of the host to pretend to connect to.
     * @param server: The IP address in bytes of the server to pretend to
     *      connect to.
    **/
    HTTPClient(char * host, byte * server);

    /**
     * Emulate sending a POST request.
     *
     * @param uri: The URI of the resource to do a POST to.
     * @param data: Character array string containing form-encoded POST
     *      parameters.
     * @return: The response from the server as a FILE-like object or null if
     *      no response returned.
    **/
    FILE * postURI(char * uri, char * data);

    /**
     * Emulate returning the HTTP status code for the last request.
     *
     * @return: The HTTP status code for the last request through this client.
    **/
    int getLastReturnCode();

    /**
     * Close the read stream with the response from a remote site.
     *
     * @param stream: The stream to close.
    **/
    void closeStream(FILE * stream);

    /**
     * Set which return value (response payload) to return from this client.
     *
     * @param val: String that should be returned as the response to the next
     *      request sent through this client.
    **/
    void putNextRetVal(const char * val);

    /**
     * Set which HTTP response code to return next from this client.
     *
     * @param code: The integer HTTP status code to return next through this
     *      mocked client.
    **/
    void putNextReturnCodeCode(int code);

    /**
     * Get the last URI a request was made on through this mocked client.
     *
     * @return: Character array string with the last URI requested through this
     *      client.
    **/
    const char * getLastURI();

    /**
     * Get the data payload (form parameters) from the last request.
     *
     * Get the data payload (form encoded parameters) from the last request
     * made through this client.
     *
     * @return: Character array string with the last request's paramters.
    **/
    const char * getLastData();

    /**
     * Determine if the last stream opened through this client was closed.
     *
     * @return: true if the stream was closed and false otherwise.
     * @note: This does not guarantee that the right stream was closed but,
     *      instead, only guarantees that a stream was closed through the
     *      client after one was opened.
    **/
    bool wasStreamClosed();
};

#endif