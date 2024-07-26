#include <stdio.h>

#define MAX_REQUESTS 10

// Structure to represent a disk request
typedef struct {
    int track;
    int arrival_time;
} Request;

// Function to simulate SCAN disk scheduling
void scan(Request requests[MAX_REQUESTS], int num_requests, int initial_track, int direction) {
    int total_head_movement = 0;
    int current_track = initial_track;
    int index = 0;

    // Sort requests by track number
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = i + 1; j < num_requests; j++) {
            if (requests[i].track > requests[j].track) {
                Request temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Move in the specified direction
    if (direction == 1) { // Move towards higher tracks
        for (int i = 0; i < num_requests; i++) {
            if (requests[i].track >= current_track) {
                printf("Track movement sequence: %d", current_track);
                total_head_movement += abs(requests[i].track - current_track);
                current_track = requests[i].track;
                index = i;
                break;
            }
        }
        for (int i = index + 1; i < num_requests; i++) {
            printf(" -> %d", requests[i].track);
            total_head_movement += abs(requests[i].track - current_track);
            current_track = requests[i].track;
        }
    } else { // Move towards lower tracks
        for (int i = 0; i < num_requests; i++) {
            if (requests[i].track <= current_track) {
                printf("Track movement sequence: %d", current_track);
                total_head_movement += abs(requests[i].track - current_track);
                current_track = requests[i].track;
                index = i;
                break;
            }
        }
        for (int i = index - 1; i >= 0; i--) {
            printf(" -> %d", requests[i].track);
            total_head_movement += abs(requests[i].track - current_track);
            current_track = requests[i].track;
        }
    }
    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main() {
    Request requests[MAX_REQUESTS] = {
        {100, 0},
        {50, 1},
        {200, 2},
        {30, 3},
        {150, 4},
        {80, 5},
        {120, 6},
        {20, 7},
        {10, 8},
        {60, 9}
    };
    int num_requests = 10;
    int initial_track = 50;
    int direction = 1; // 1 for higher tracks, -1 for lower tracks

    scan(requests, num_requests, initial_track, direction);

    return 0;
}
