#ifndef ORRERY_WEB_CONTROL_HEADER
#define ORRERY_WEB_CONTROL_HEADER

// TODO: Put in note about MAX_DATA_PAYLOAD_SIZE 

#define TESTING 1
#define HOST_LEN 16
#define HOST_STR "test.example.com"
#define SERVER_IP_LEN 4
#define MAX_REQUEST_DATA_PAYLOAD_SIZE 70
#define MAX_RESPONSE_DATA_PAYLOAD_SIZE 200
#define NUM_RESPONSE_JSON_TOKENS 6
#define DATA_FORMAT_STR "motorSpeed=%f&motorDraw=%f&rotations=%f"
#define STATUS_POST_URL "/api/status.json"
#define STATUS_POST_URL_LEN 16
#define STATUS_OK 200
#define MOTOR_SPEED_TOKEN_NAME "motor_speed"
#define RELAY_ENABLED_TOKEN_NAME "relay_enabled"
#define SERVER_IP { 0, 0, 0, 0 }
#define JSON_PARSE_STR "{\"relay_enabled\": %[^,], \"motor_speed\": %f}"
#define JSON_true_STR "true"

#include <string.h>
#include <stdio.h>

#if TESTING == 1
#include "emulated_env.h"
#include "HTTPClient.h"
#else
#include <HTTPClient.h>
#include "Arduino.h"
#endif


typedef struct
{
    bool connectedSuccesfully;
    bool resultOK;
    int statusCode;
    float motorSpeed;
    bool relayEnabled;
    bool successParse;
}OrreryWebConfig;


class OrreryWebControl
{
private:
    char * host;
    byte * serverIP;
    void extractConfig(OrreryWebConfig * configStruct, const char * source);
public:
    OrreryWebControl();
    ~OrreryWebControl();
    void checkIn(OrreryWebConfig * configStruct, float motorSpeed,
        float motorDraw, float rotations);
    void checkIn(HTTPClient * client, OrreryWebConfig * configStruct,
        float motorSpeed, float motorDraw, float rotations);
    const char * getHost();
    const byte * getServerIP();
};

#endif