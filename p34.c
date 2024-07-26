#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 10

// Structure to represent a file
typedef struct {
    int records[MAX_RECORDS];
    int size;
} File;

// Function to create a new file
File* create_file() {
    File* file = (File*) malloc(sizeof(File));
    file->size = 0;
    return file;
}

// Function to add a record to the file
void add_record(File* file, int record) {
    if (file->size < MAX_RECORDS) {
        file->records[file->size] = record;
        file->size++;
    } else {
        printf("File is full\n");
    }
}

// Function to read a record from the file
void read_record(File* file, int index) {
    if (index < file->size) {
        printf("Record %d: %d\n", index, file->records[index]);
    } else {
        printf("Record not found\n");
    }
}

// Function to read all records from the file
void read_all_records(File* file) {
    for (int i = 0; i < file->size; i++) {
        printf("Record %d: %d\n", i, file->records[i]);
    }
}

int main() {
    File* file = create_file();

    // Add records to the file
    add_record(file, 10);
    add_record(file, 20);
    add_record(file, 30);

    // Read all records from the file
    read_all_records(file);

    // Read a specific record from the file
    read_record(file, 1);

    return 0;
}

