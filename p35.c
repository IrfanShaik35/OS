#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_FILES 5

// Structure to represent a file
typedef struct {
    int index_block[MAX_BLOCKS];
    int size;
} File;

// Structure to represent the file system
typedef struct {
    File files[MAX_FILES];
    int file_count;
} FileSystem;

// Function to create a new file system
FileSystem* create_file_system() {
    FileSystem* fs = (FileSystem*) malloc(sizeof(FileSystem));
    fs->file_count = 0;
    return fs;
}

// Function to create a new file
File* create_file() {
    File* file = (File*) malloc(sizeof(File));
    file->size = 0;
    return file;
}

// Function to add a block to a file
void add_block(File* file, int block_number) {
    if (file->size < MAX_BLOCKS) {
        file->index_block[file->size] = block_number;
        file->size++;
    } else {
        printf("File is full\n");
    }
}

// Function to read a block from a file
void read_block(File* file, int block_number) {
    for (int i = 0; i < file->size; i++) {
        if (file->index_block[i] == block_number) {
            printf("Block %d found\n", block_number);
            return;
        }
    }
    printf("Block not found\n");
}

// Function to add a file to the file system
void add_file(FileSystem* fs, File* file) {
    if (fs->file_count < MAX_FILES) {
        fs->files[fs->file_count] = *file;
        fs->file_count++;
    } else {
        printf("File system is full\n");
    }
}

int main() {
    FileSystem* fs = create_file_system();

    // Create files and add blocks
    File* file1 = create_file();
    add_block(file1, 1);
    add_block(file1, 2);
    add_file(fs, file1);

    File* file2 = create_file();
    add_block(file2, 3);
    add_block(file2, 4);
    add_file(fs, file2);

    // Read blocks from files
    read_block(&fs->files[0], 1);
    read_block(&fs->files[1], 3);

    return 0;
}

OUTPUT

Block 1 found
Block 3 found
