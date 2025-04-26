#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char device_id[7];    
    double temperature;
    int humidity;
    char status;
    char location[30];    
    char alert_level[7];   
    int battery;
    char firmware_ver[7];  
    int event_code;
} smartlog;

int main() {
    FILE *csv = fopen("smartlogs.csv", "r");
    FILE *bin = fopen("data.bin", "wb");

    if (!csv || !bin) {
        perror("dosya yok");
        return 1;
    }

    char delimiter = ','; 
    smartlog sl;
    char line[200]; 

    // Skip the first sentence
    fgets(line, sizeof(line), csv);

    // csvyi parçalara ayırır
    while (fgets(line, sizeof(line), csv)) {
        char *token;
        char *end;

        // parse device_id
        token = strtok(line, &delimiter);
        if (token == NULL) continue;
        strncpy(sl.device_id, token, sizeof(sl.device_id) - 1);
        sl.device_id[sizeof(sl.device_id) - 1] = '\0';  

        // parse temperature
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        sl.temperature = strtod(token, &end);

        // parse humidity
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        sl.humidity = (int)strtol(token, &end, 10);

        // parse status
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        sl.status = token[0];  

        // parse location
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(sl.location, token, sizeof(sl.location) - 1);
        sl.location[sizeof(sl.location) - 1] = '\0';  

        // parse alert_level
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(sl.alert_level, token, sizeof(sl.alert_level) - 1);
        sl.alert_level[sizeof(sl.alert_level) - 1] = '\0';  

        // parse battery
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        sl.battery = (int)strtol(token, &end, 10);

        // parse firmware_ver
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(sl.firmware_ver, token, sizeof(sl.firmware_ver) - 1);
        sl.firmware_ver[sizeof(sl.firmware_ver) - 1] = '\0';  

        // parse event_code
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        sl.event_code = (int)strtol(token, &end, 10);
       

        // Write csv to the binary file
        fwrite(&sl, sizeof(smartlog), 1, bin);
    }
    fclose(csv);
    fclose(bin);

    printf("CSV file to binary.\n");


    return 0;
}
