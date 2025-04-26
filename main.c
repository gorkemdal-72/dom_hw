#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char device_id[7];     // 6 characters for device_id + null terminator
    double temperature;
    int humidity;
    char status;
    char location[30];     // 30 characters for location
    char alert_level[7];   // 6 characters for alert level + null terminator
    int battery;
    char firmware_ver[7];  // Firmware version (vX.Y.Z format)
    int event_code;
} smartlog;

int main() {
    FILE *csv = fopen("smartlogs.csv", "r");
    FILE *bin = fopen("data.bin", "wb");

    if (!csv || !bin) {
        perror("File not open");
        return 1;
    }

    char delimiter = ','; // separator (can be modified based on input)
    smartlog s;
    char line[200]; // Increased size to accommodate longer lines

    // Skip the header if present
    fgets(line, sizeof(line), csv);

    // Process each line in the CSV file
    while (fgets(line, sizeof(line), csv)) {
        char *token;
        char *end;

        // Parse device_id
        token = strtok(line, &delimiter);
        if (token == NULL) continue;
        strncpy(s.device_id, token, sizeof(s.device_id) - 1);
        s.device_id[sizeof(s.device_id) - 1] = '\0';  // Null-terminate

        // Parse temperature
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.temperature = strtod(token, &end);

        // Parse humidity
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.humidity = (int)strtol(token, &end, 10);

        // Parse status
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.status = token[0];  // Assuming status is a single character

        // Parse location
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.location, token, sizeof(s.location) - 1);
        s.location[sizeof(s.location) - 1] = '\0';  // Null-terminate

        // Parse alert_level
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.alert_level, token, sizeof(s.alert_level) - 1);
        s.alert_level[sizeof(s.alert_level) - 1] = '\0';  // Null-terminate

        // Parse battery
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.battery = (int)strtol(token, &end, 10);

        // Parse firmware_ver
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.firmware_ver, token, sizeof(s.firmware_ver) - 1);
        s.firmware_ver[sizeof(s.firmware_ver) - 1] = '\0';  // Null-terminate

        // Parse event_code
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.event_code = (int)strtol(token, &end, 10);
       

        // Write the structure to the binary file
        fwrite(&s, sizeof(smartlog), 1, bin);
    }
    printf("%s,%d,%s,%d,%s",s.alert_level,s.battery,s.device_id,s.event_code,s.firmware_ver,"\n");
    fclose(csv);
    fclose(bin);

    printf("CSV file has been successfully converted to binary.\n");


    return 0;
}
