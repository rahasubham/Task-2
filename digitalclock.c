#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // For sleep()

#define MAX_ALARMS 5

// Struct to store alarm information
typedef struct {
    int hour;
    int minute;
    int second;
    int isSet;
} Alarm;

// Function to display the current time (digital clock)
void displayClock() {
    time_t currentTime;
    struct tm *localTime;
    
    // Get current time
    time(&currentTime);
    localTime = localtime(&currentTime);
    
    // Format and display the time as HH:MM:SS
    printf("\nCurrent Time: %02d:%02d:%02d\n", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
}

// Function to set an alarm
void setAlarm(Alarm alarms[], int *alarmCount) {
    if (*alarmCount >= MAX_ALARMS) {
        printf("You have reached the maximum number of alarms!\n");
        return;
    }

    Alarm newAlarm;
    printf("Enter alarm time (HH MM SS): ");
    scanf("%d %d %d", &newAlarm.hour, &newAlarm.minute, &newAlarm.second);

    newAlarm.isSet = 1;
    alarms[*alarmCount] = newAlarm;
    (*alarmCount)++;

    printf("Alarm set for %02d:%02d:%02d\n", newAlarm.hour, newAlarm.minute, newAlarm.second);
}

// Function to check if any alarm matches the current time
void checkAlarms(Alarm alarms[], int alarmCount) {
    time_t currentTime;
    struct tm *localTime;

    // Get current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    for (int i = 0; i < alarmCount; i++) {
        if (alarms[i].isSet &&
            alarms[i].hour == localTime->tm_hour &&
            alarms[i].minute == localTime->tm_min &&
            alarms[i].second == localTime->tm_sec) {
            printf("\n** ALARM: %02d:%02d:%02d **\n", alarms[i].hour, alarms[i].minute, alarms[i].second);
            alarms[i].isSet = 0;  // Alarm is triggered and cleared
        }
    }
}

// Function to display the alarm list
void displayAlarms(Alarm alarms[], int alarmCount) {
    if (alarmCount == 0) {
        printf("No alarms set.\n");
        return;
    }

    printf("\nAlarms List:\n");
    for (int i = 0; i < alarmCount; i++) {
        if (alarms[i].isSet) {
            printf("%d. Alarm at %02d:%02d:%02d\n", i + 1, alarms[i].hour, alarms[i].minute, alarms[i].second);
        }
    }
}

// Function to remove an alarm
void removeAlarm(Alarm alarms[], int *alarmCount) {
    int alarmIndex;
    printf("Enter the alarm number to remove: ");
    scanf("%d", &alarmIndex);

    if (alarmIndex < 1 || alarmIndex > *alarmCount) {
        printf("Invalid alarm number!\n");
        return;
    }

    // Mark the alarm as unset
    alarms[alarmIndex - 1].isSet = 0;

    // Shift the alarms in the array to remove the gap
    for (int i = alarmIndex - 1; i < *alarmCount - 1; i++) {
        alarms[i] = alarms[i + 1];
    }

    (*alarmCount)--; // Decrease the count of alarms
    printf("Alarm %d removed successfully!\n", alarmIndex);
}

int main() {
    int choice;
    int alarmCount = 0;
    Alarm alarms[MAX_ALARMS];

    while (1) {
        // Display the menu
        printf("\nDigital Clock with Alarm Management\n");
        printf("1. View Current Time (Digital Clock)\n");
        printf("2. Set Alarm\n");
        printf("3. View Alarms\n");
        printf("4. Remove Alarm\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayClock();
                checkAlarms(alarms, alarmCount);
                break;
            case 2:
                setAlarm(alarms, &alarmCount);
                break;
            case 3:
                displayAlarms(alarms, alarmCount);
                break;
            case 4:
                removeAlarm(alarms, &alarmCount);
                break;
            case 5:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        sleep(1);  // Sleep for 1 second to update the clock
    }

    return 0;
}
