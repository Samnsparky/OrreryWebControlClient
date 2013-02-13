/**
 * HTTP-based Arduino library for controlling an Orrery through a web service.
 *
 * @auth Sam Pottinger
 * @lice GNU GPL v3
**/

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
#define DATA_FORMAT_STR "motor_speed=%f&motor_draw=%f&rotations=%f"
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
#include <stdlib.h>

#if TESTING == 1
#include "emulated_env.h"
#include "HTTPClient.h"
#else
#include <HTTPClient.h>
#include "Arduino.h"
#endif


/**
 * Struct containing the orrery configuration settings read from the server.
**/
typedef struct
{
    bool connectedSuccesfully;
    bool resultOK;
    int statusCode;
    float motorSpeed;
    bool relayEnabled;
    bool successParse;
}OrreryWebConfig;


/**
 * Class that allows communication with a orrery control web service.
**/
class OrreryWebControl
{
private:
    char * host;
    byte * serverIP;

    /**
     * Extract configuration settings from server status JSON document.
     *
     * @param configStruct: The struct to load the configuration settings into.
     * @param source: The c-string JSON document to load configuration settings
     *      from.
    **/
    void extractConfig(OrreryWebConfig * configStruct, const char * source);

public:

    /**
     * Create a new OrreryWebControl client.
    **/
    OrreryWebControl();

    /**
     * Clean up after a OrreryWebControl client.
    **/
    ~OrreryWebControl();

    // TODO: These values should have units in the docs
    /**
     * Perform a server check in.
     *
     * Update the orrery system status on the web server and read any updated
     * orrery configuration settings.
     *
     * @param configStruct: The configuration structure to load configuration
     *      settings into.
     * @param motorSpeed: The current actual speed of the motor.
     * @param motorDraw: The draw in mA of the motor.
     * @param rotations: The number of rotations the orrery shaft has made.
    **/
    void checkIn(OrreryWebConfig * configStruct, float motorSpeed,
        float motorDraw, float rotations);

    /**
     * Perform a server check in using a given HTTP client.
     *
     * Update the orrery system status on the web server and read any updated
     * orrery configuration settings using a provided HTTP client.
     *
     * @param client: The HTTPClient to use to perform this check in.
     * @param configStruct: The configuration structure to load configuration
     *      settings into.
     * @param motorSpeed: The current actual speed of the motor.
     * @param motorDraw: The draw in mA of the motor.
     * @param rotations: The number of rotations the orrery shaft has made.
    **/
    void checkIn(HTTPClient * client, OrreryWebConfig * configStruct,
        float motorSpeed, float motorDraw, float rotations);

    /**
     * Get the host this web control targets.
     *
     * @return: The host name of this web control's server.
    **/
    const char * getHost();

    /**
     * Get the byte array version of the IP address this web control targets.
     *
     * @return: The byte array version of the IP address of this control's
     *      server.
    **/
    const byte * getServerIP();
};

#endif