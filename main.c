#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char device_id[7];
    double temperature;
    int humidity;
    char status;
    char location[15];
    char alert_level[7];
    int battery;
    char firmware_ver[7];
    int event_code;
} smartlog;

int main(){
    FILE *csv = fopen("C:\\DOM_HW\\smartlogs.csv", "r");
    FILE *bin =fopen("data.bin","wb");

    if(!csv||!bin){
        perror("file not open");
        return 1;
    }
    char delimiter=','; //seperator
    smartlog s;
    char line[100];

    while(fgets(line,sizeof(line),csv)){
        char *token;
        char *end;
        token=strtok(line,&delimiter);
        if(token==NULL) continue;
        strncpy(s.device_id, token, sizeof(s.device_id) - 1);
        s.device_id[sizeof(s.device_id) - 1] = '\0';

        fwrite(&s, sizeof(smartlog), 1, bin);
    }
    fclose(csv);
    fclose(bin);

aaaaaaaaaaaaaaaaaaaaaaa
    FILE *binFile = fopen("data.bin", "rb");
    smartlog sm;

    while (fread(&sm, sizeof(smartlog), 1, binFile)) {
        printf("ID: %d \n", sm.device_id);
    }

    fclose(binFile);


}
/*
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

int main() {
    FILE *csv = fopen("C:\\DOM_HW\\smartlogs.csv", "r");
    FILE *bin = fopen("data.bin", "wb");

    if (!csv || !bin) {
        perror("File not open");
        return 1;
    }

    char delimiter = ','; // separator
    smartlog s;
    char line[200]; // Increased size to accommodate longer lines

    // Skip the header if present
    fgets(line, sizeof(line), csv);

    // Process each line
    while (fgets(line, sizeof(line), csv)) {
        char *token;
        char *end;

        // Parse device_id
        token = strtok(line, &delimiter);
        if (token == NULL) continue;
        strncpy(s.device_id, token, sizeof(s.device_id) - 1);
        s.device_id[sizeof(s.device_id) - 1] = '\0';
       

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
        s.location[sizeof(s.location) - 1] = '\0';  // Ensure null-terminated

        // Parse alert_level
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.alert_level, token, sizeof(s.alert_level) - 1);
        s.alert_level[sizeof(s.alert_level) - 1] = '\0';  // Ensure null-terminated

        // Parse battery
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.battery = (int)strtol(token, &end, 10);

        // Parse firmware_ver
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        strncpy(s.firmware_ver, token, sizeof(s.firmware_ver) - 1);
        s.firmware_ver[sizeof(s.firmware_ver) - 1] = '\0';  // Ensure null-terminated

        // Parse event_code
        token = strtok(NULL, &delimiter);
        if (token == NULL) continue;
        s.event_code = (int)strtol(token, &end, 10);

        // Write the structure to the binary file
        fwrite(&s, sizeof(smartlog), 1, bin);
    }

    fclose(csv);
    fclose(bin);

    printf("CSV file has been successfully converted to binary.\n");

    FILE *binFile = fopen("data.bin", "rb");
    if (!binFile) {
        perror("Unable to open binary file");
        return 1;
    }

    smartlog sm;
    int record_number = 1;

    // Read the binary file and print the contents
    while (fread(&sm, sizeof(smartlog), 1, binFile)) {
        printf("Record %d:\n", record_number++);
        printf("Device ID: %s\n", sm.device_id);
        printf("Temperature: %.2f\n", sm.temperature);
        printf("Humidity: %d\n", sm.humidity);
        printf("Status: %c\n", sm.status);
        printf("Location: %s\n", sm.location);
        printf("Alert Level: %s\n", sm.alert_level);
        printf("Battery: %d\n", sm.battery);
        printf("Firmware Version: %s\n", sm.firmware_ver);
        printf("Event Code: %d\n\n", sm.event_code);
    }

    fclose(binFile);

    return 0;
}
*/
//aaaaaaaaaaaaaaaaaaaaaaaa