/**
 * HTTP-based Arduino library for controlling an Orrery through a web service.
 *
 * @auth Sam Pottinger
 * @lice GNU GPL v3
**/

#ifndef ORRERY_WEB_CONTROL_IMP
#define ORRERY_WEB_CONTROL_IMP

#include "OrreryWebControl.h"

OrreryWebControl::OrreryWebControl()
{
    byte tempServerIP[] = SERVER_IP;
    serverIP = new byte[SERVER_IP_LEN];
    memcpy(serverIP, tempServerIP, SERVER_IP_LEN);

    host = new char[HOST_LEN];
    strcpy(host, HOST_STR);
}

OrreryWebControl::~OrreryWebControl()
{
    delete host;
    delete serverIP;
}

void OrreryWebControl::checkIn(OrreryWebConfig * configStruct, float motorSpeed,
    float motorDraw, float rotations)
{
    HTTPClient client(host, serverIP);
    return checkIn(&client, configStruct, motorSpeed, motorDraw, rotations);
}

void OrreryWebControl::checkIn(HTTPClient * client,
    OrreryWebConfig * configStruct, float motorSpeed, float motorDraw,
    float rotations)
{
    char requestData[MAX_REQUEST_DATA_PAYLOAD_SIZE];
    char responseData[MAX_RESPONSE_DATA_PAYLOAD_SIZE];
    char statusPostURL[STATUS_POST_URL_LEN];
    strcpy(statusPostURL, STATUS_POST_URL);

    snprintf(
        requestData,
        MAX_REQUEST_DATA_PAYLOAD_SIZE,
        DATA_FORMAT_STR,
        motorSpeed,
        motorDraw,
        rotations
    );

    FILE * result = client->postURI(statusPostURL, requestData);
    int statusCode = client->getLastReturnCode();

    fgets(responseData, MAX_RESPONSE_DATA_PAYLOAD_SIZE, result);

    if (result == NULL)
    {
        configStruct->connectedSuccesfully = false;
        return;
    }

    configStruct->connectedSuccesfully = true;
    configStruct->statusCode = statusCode;

    if(statusCode == STATUS_OK)
    {
        configStruct->resultOK = true;
        extractConfig(configStruct, responseData);
    }
    else
    {
        configStruct->resultOK = false;
    }

    client->closeStream(result);
}

void OrreryWebControl::extractConfig(OrreryWebConfig * configStruct,
    const char * source)
{
    // TODO: Real JSON parse
    float motorSpeed;
    char relayEnabledStr[6];
    bool relayEnabled;

    if(sscanf(source, JSON_PARSE_STR, relayEnabledStr, &motorSpeed) != 2)
    {
        configStruct->successParse = false;
    }
    else
    {
        configStruct->successParse = true;
        relayEnabled = strcmp(JSON_true_STR, relayEnabledStr) == 0;
        configStruct->motorSpeed = motorSpeed;
        configStruct->relayEnabled = relayEnabled;
    }
}

const char * OrreryWebControl::getHost()
{
    return host;
}

const byte * OrreryWebControl::getServerIP()
{
    return serverIP;
}

#endif