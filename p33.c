#include <stdio.h>

#define PAGE_TABLE_SIZE 4
#define REFERENCE_STRING_SIZE 10

// Function to simulate optimal paging
void optimal_paging(int reference_string[REFERENCE_STRING_SIZE]) {
    int page_table[PAGE_TABLE_SIZE];
    int page_faults = 0;

    // Initialize page table with -1 (empty)
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }

    // Process reference string
    for (int i = 0; i < REFERENCE_STRING_SIZE; i++) {
        int page = reference_string[i];
        int found = 0;
        int max_distance = 0;
        int max_distance_index = 0;

        // Check if page is in page table
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            if (page_table[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not in page table, page fault occurs
        if (!found) {
            page_faults++;

            // Find page with max distance (page that will not be referenced for longest time)
            for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
                int distance = 0;
                int k;
                for (k = i + 1; k < REFERENCE_STRING_SIZE; k++) {
                    if (page_table[j] == reference_string[k]) {
                        distance = k - i;
                        break;
                    }
                }
                if (distance > max_distance) {
                    max_distance = distance;
                    max_distance_index = j;
                }
            }

            // Replace page with max distance with new page
            page_table[max_distance_index] = page;
        }

        printf("Reference string: %d\n", page);
        printf("Page table: ");
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            printf("%d ", page_table[j]);
        }
        printf("\n");
    }

    printf("Page faults: %d\n", page_faults);
}

int main() {
    int reference_string[REFERENCE_STRING_SIZE] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1};

    optimal_paging(reference_string);

    return 0;
}

