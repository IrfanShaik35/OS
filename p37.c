#include <stdio.h>

#define MAX_REQUESTS 10

// Structure to represent a disk request
typedef struct {
    int track;
    int arrival_time;
} Request;

// Function to simulate FCFS disk scheduling
void fcfs(Request requests[MAX_REQUESTS], int num_requests, int initial_track) {
    int total_head_movement = 0;
    int current_track = initial_track;

    printf("Track movement sequence: %d", current_track);
    for (int i = 0; i < num_requests; i++) {
        printf(" -> %d", requests[i].track);
        total_head_movement += abs(requests[i].track - current_track);
        current_track = requests[i].track;
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

    fcfs(requests, num_requests, initial_track);

    return 0;
}
