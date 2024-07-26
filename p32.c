#include <stdio.h>

#define PAGE_TABLE_SIZE 4
#define REFERENCE_STRING_SIZE 10

// Function to simulate LRU paging
void lru_paging(int reference_string[REFERENCE_STRING_SIZE]) {
    int page_table[PAGE_TABLE_SIZE];
    int lru_bits[PAGE_TABLE_SIZE];
    int page_faults = 0;

    // Initialize page table with -1 (empty) and lru_bits with 0
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
        lru_bits[i] = 0;
    }

    // Process reference string
    for (int i = 0; i < REFERENCE_STRING_SIZE; i++) {
        int page = reference_string[i];
        int found = 0;
        int max_lru = 0;
        int max_lru_index = 0;

        // Check if page is in page table
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            if (page_table[j] == page) {
                found = 1;
                lru_bits[j] = 1;
                break;
            }
        }

        // If page is not in page table, page fault occurs
        if (!found) {
            page_faults++;

            // Find LRU page (page with max lru_bits)
            for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
                if (lru_bits[j] > max_lru) {
                    max_lru = lru_bits[j];
                    max_lru_index = j;
                }
            }

            // Replace LRU page with new page
            page_table[max_lru_index] = page;
            lru_bits[max_lru_index] = 1;
        }

        // Update lru_bits
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            if (page_table[j] != -1) {
                lru_bits[j] = (lru_bits[j] + 1) / 2;
            }
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

    lru_paging(reference_string);

    return 0;
}

OUTPUT

Reference string: 1
Page table: 1 -1 -1 -1
Reference string: 2
Page table: 2 -1 -1 -1
Reference string: 3
Page table: 3 -1 -1 -1
Reference string: 4
Page table: 4 -1 -1 -1
Reference string: 2
Page table: 2 -1 -1 -1
Reference string: 1
Page table: 1 -1 -1 -1
Reference string: 5
Page table: 5 -1 -1 -1
Reference string: 6
Page table: 6 -1 -1 -1
Reference string: 2
Page table: 2 -1 -1 -1
Reference string: 1
Page table: 1 -1 -1 -1
Page faults: 10
