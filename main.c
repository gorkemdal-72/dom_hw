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
    smartlog s;
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
        strncpy(s.device_id, token, sizeof(s.device_id) - 1);
        s.device_id[sizeof(s.device_id) - 1] = '\0';  

        // parse temperature
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.temperature = strtod(token, &end);

        // parse humidity
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.humidity = (int)strtol(token, &end, 10);

        // parse status
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.status = token[0];  

        // parse location
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.location, token, sizeof(s.location) - 1);
        s.location[sizeof(s.location) - 1] = '\0';  

        // parse alert_level
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.alert_level, token, sizeof(s.alert_level) - 1);
        s.alert_level[sizeof(s.alert_level) - 1] = '\0';  

        // parse battery
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.battery = (int)strtol(token, &end, 10);

        // parse firmware_ver
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.firmware_ver, token, sizeof(s.firmware_ver) - 1);
        s.firmware_ver[sizeof(s.firmware_ver) - 1] = '\0';  

        // parse event_code
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.event_code = (int)strtol(token, &end, 10);
       

        // Write csv to the binary file
        fwrite(&s, sizeof(smartlog), 1, bin);
    }
    fclose(csv);
    fclose(bin);

    printf("CSV file to binary.\n");


    return 0;
}
