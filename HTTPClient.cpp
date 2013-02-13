#include "HTTPClient.h"


HTTPClient::HTTPClient(char * newHost, byte * newServer)
{
    nextReturnCode = -1;

    lastURI = new char[1];
    lastURI[0] = '\0';

    lastData = new char[1];
    lastData[0] = '\0';

    streamClosed = TRUE;
}

FILE * HTTPClient::postURI(char * uri, char * data)
{
    delete lastURI;
    delete lastData;

    lastURI = new char[strlen(uri)];
    strcpy(lastURI, uri);

    lastData = new char[strlen(data)];
    strcpy(lastData, data);

    streamClosed = FALSE;

    return fopen(TEST_RET_VAL_FILE,"r");
}

int HTTPClient::getLastReturnCode()
{
    return nextReturnCode;
}

void HTTPClient::closeStream(FILE * stream)
{
    streamClosed = TRUE;
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
