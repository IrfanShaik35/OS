#include <stdio.h>

#define PAGE_TABLE_SIZE 4
#define REFERENCE_STRING_SIZE 10

// Function to simulate FIFO paging
void fifo_paging(int reference_string[REFERENCE_STRING_SIZE]) {
    int page_table[PAGE_TABLE_SIZE];
    int page_faults = 0;
    int page_replacements = 0;

    // Initialize page table with -1 (empty)
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }

    // Process reference string
    for (int i = 0; i < REFERENCE_STRING_SIZE; i++) {
        int page = reference_string[i];
        int found = 0;

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

            // Replace oldest page in page table (FIFO)
            page_table[page_replacements % PAGE_TABLE_SIZE] = page;
            page_replacements++;
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

    fifo_paging(reference_string);

    return 0;
}


