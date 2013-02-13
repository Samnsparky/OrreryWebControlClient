#include "clockmac.c"
#include "minunit.h"

#include "HTTPClient.h"
#include "OrreryWebControl.h"

#define EXPECTED_POST_REQUSET_DATA "motorSpeed=%f&motorDraw=%f&rotations=%f";
#define TEST_POST_RET_VAL "{\"relay_enabled\": true, \"motor_speed\": 400.0}"


MU_TEST(test_init)
{
    OrreryWebControl control;
    byte exepectedIPBytes[] = SERVER_IP;
    mu_assert_int_eq(0, strcmp(control.getHost(), HOST_STR));
    mu_assert_int_eq(0, memcmp(control.getServerIP(), exepectedIPBytes, 4));
}

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

MU_TEST_SUITE(test_client)
{
    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_http_checkin);
}

int main(int argc, char * argv[])
{
    MU_RUN_SUITE(test_client);
    MU_REPORT();

    return 0;
}
