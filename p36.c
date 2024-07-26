#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10

// Structure to represent a disk block
typedef struct Block {
    int data;
    struct Block* next;
} Block;

// Structure to represent a file
typedef struct {
    Block* first_block;
    Block* last_block;
} File;

// Structure to represent the directory
typedef struct {
    File files[MAX_BLOCKS];
    int file_count;
} Directory;

// Function to create a new disk block
Block* create_block(int data) {
    Block* block = (Block*) malloc(sizeof(Block));
    block->data = data;
    block->next = NULL;
    return block;
}

// Function to create a new file
File* create_file() {
    File* file = (File*) malloc(sizeof(File));
    file->first_block = NULL;
    file->last_block = NULL;
    return file;
}

// Function to add a block to a file
void add_block(File* file, Block* block) {
    if (file->first_block == NULL) {
        file->first_block = block;
        file->last_block = block;
    } else {
        file->last_block->next = block;
        file->last_block = block;
    }
}

// Function to print a file
void print_file(File* file) {
    Block* block = file->first_block;
    while (block != NULL) {
        printf("%d ", block->data);
        block = block->next;
    }
    printf("\n");
}

// Function to create a new directory
Directory* create_directory() {
    Directory* directory = (Directory*) malloc(sizeof(Directory));
    directory->file_count = 0;
    return directory;
}

// Function to add a file to the directory
void add_file(Directory* directory, File* file) {
    directory->files[directory->file_count] = *file;
    directory->file_count++;
}

int main() {
    Directory* directory = create_directory();

    // Create files and add blocks
    File* file1 = create_file();
    add_block(file1, create_block(1));
    add_block(file1, create_block(2));
    add_file(directory, file1);

    File* file2 = create_file();
    add_block(file2, create_block(3));
    add_block(file2, create_block(4));
    add_file(directory, file2);

    // Print files
    print_file(&directory->files[0]);
    print_file(&directory->files[1]);

    return 0;
}

OUTPUT

1 2
3 4
