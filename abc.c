#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char device_id[10];
    double temperature;
    int humidity;
    char status;
    char location[15];
    char alert_level[7];
    int battery;
    char firmware_ver[7];
    int event_code;
} smartlog;
