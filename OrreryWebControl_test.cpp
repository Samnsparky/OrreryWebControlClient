/**
 * Unit tests for the Arduino OrreryWebControl library.
 *
 * @auth Sam Pottinger
 * @lice GNU GPL v3
**/

#include "clockmac.c"
#include "minunit.h"

#include "HTTPClient.h"
#include "OrreryWebControl.h"

#define EXPECTED_POST_REQUSET_DATA "motor_speed=%f&motor_draw=%f&rotations=%f";
#define TEST_POST_RET_VAL "{\"relay_enabled\": true, \"motor_speed\": 400.0}"


/**
 * Test the initialization of a OrreryWebControl with default values.
**/
MU_TEST(test_init)
{
    OrreryWebControl control;
    byte exepectedIPBytes[] = SERVER_IP;
    mu_assert_int_eq(0, strcmp(control.getHost(), HOST_STR));
    mu_assert_int_eq(0, memcmp(control.getServerIP(), exepectedIPBytes, 4));
}

/**
 * Test doing a check in using the OrreryWebControl library.
**/
MU_TEST(test_http_checkin)
{
    const char * requestPostStr;
    float motorSpeed;
    float motorDraw;
    float rotations;
    OrreryWebConfig configStruct;
    OrreryWebControl control;

    // TODO: This casting is dangerous... Although HTTPClient probably could
    //       take const versions, this introduces dangerous assumptions.
    const char * constHost = control.getHost();
    const byte * constServerIP = control.getServerIP();
    HTTPClient client((char *)constHost, (byte *)constServerIP);

    client.putNextReturnCodeCode(200);
    client.putNextRetVal(TEST_POST_RET_VAL);

    control.checkIn(&client, &configStruct, 100, 200, 300);

    requestPostStr = client.getLastData();
    sscanf(
        requestPostStr,
        DATA_FORMAT_STR,
        &motorSpeed,
        &motorDraw,
        &rotations
    );
    
    mu_assert_int_eq(0, strcmp(client.getLastURI(), STATUS_POST_URL));
    mu_assert_double_eq(motorSpeed, 100);
    mu_assert_double_eq(motorDraw, 200);
    mu_assert_double_eq(rotations, 300);
    mu_assert_int_eq(client.wasStreamClosed(), true);

    mu_assert_int_eq(configStruct.relayEnabled, true);
    mu_assert_double_eq(configStruct.motorSpeed, 400);
}

/**
 * Test suite containing all OrreryWebControl client unit tests.
**/
MU_TEST_SUITE(test_client)
{
    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_http_checkin);
}

/**
 * The C++ standard main routine that runns client unit tests.
 *
 * @param argc: The number of command line arguments passed.
 * @param argv: The array of c-style strings containing command line arguments.
 * @return: System-standard application success / failure code.
**/
int main(int argc, char * argv[])
{
    MU_RUN_SUITE(test_client);
    MU_REPORT();

    return 0;
}
