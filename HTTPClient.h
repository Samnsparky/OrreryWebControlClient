#ifndef HTTP_CLIENT_HEADER
#define HTTP_CLIENT_HEADER

#include <stdio.h>
#include <string.h>

#define TESTING 1

#if TESTING == 1
#include "emulated_env.h"
#endif

class HTTPClient
{
private:
    int nextReturnCode;
    char * lastURI;
    char * lastData;
    bool streamClosed;

public:
    HTTPClient(char * host, byte * server);
    FILE * postURI(char * uri, char * data);
    int getLastReturnCode();
    void closeStream(FILE * stream);

    void putNextRetVal(const char * val);
    void putNextReturnCodeCode(int code);
    const char * getLastURI();
    const char * getLastData();
    bool wasStreamClosed();
};

#endif