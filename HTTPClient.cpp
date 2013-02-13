/**
 * Implementation of the HTTPClient dependency injection construct.
 *
 * @auth Sam Pottinger
 * @license GNU GPL v3
**/

#ifndef HTTP_CLIENT_IMP
#define HTTP_CLIENT_IMP

#include "HTTPClient.h"


HTTPClient::HTTPClient(char * newHost, byte * newServer)
{
    nextReturnCode = -1;

    lastURI = new char[1];
    lastURI[0] = '\0';

    lastData = new char[1];
    lastData[0] = '\0';

    streamClosed = true;
}

FILE * HTTPClient::postURI(char * uri, char * data)
{
    delete lastURI;
    delete lastData;

    lastURI = new char[strlen(uri)];
    strcpy(lastURI, uri);

    lastData = new char[strlen(data)];
    strcpy(lastData, data);

    streamClosed = false;

    return fopen(TEST_RET_VAL_FILE,"r");
}

int HTTPClient::getLastReturnCode()
{
    return nextReturnCode;
}

void HTTPClient::closeStream(FILE * stream)
{
    streamClosed = true;
    fclose(stream);
}

void HTTPClient::putNextRetVal(const char * val)
{
    FILE * file;
    file = fopen(TEST_RET_VAL_FILE,"w");
    fputs(val, file);
    fclose(file);
}

void HTTPClient::putNextReturnCodeCode(int code)
{
    nextReturnCode = code;
}

bool HTTPClient::wasStreamClosed()
{
    return streamClosed;
}

const char * HTTPClient::getLastData()
{
    return lastData;
}

const char * HTTPClient::getLastURI()
{
    return lastURI;
}

#endif
