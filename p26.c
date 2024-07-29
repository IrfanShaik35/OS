#include <stdio.h>
#include <stdlib.h>

// Function to create a file
void createFile(const char *fileName) {
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Could not create file %s\n", fileName);
        return;
    }
    printf("File %s created successfully\n", fileName);
    fclose(fp);
}

// Function to write to a file
void writeFile(const char *fileName, const char *content) {
    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        printf("Could not open file %s for writing\n", fileName);
        return;
    }
    fprintf(fp, "%s", content);
    printf("Written to file %s successfully\n", fileName);
    fclose(fp);
}

// Function to read from a file
void readFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Could not open file %s for reading\n", fileName);
        return;
    }
    char ch;
    printf("Contents of file %s:\n", fileName);
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    fclose(fp);
}

// Function to delete a file
void deleteFile(const char *fileName) {
    if (remove(fileName) == 0) {
        printf("File %s deleted successfully\n", fileName);
    } else {
        printf("Could not delete file %s\n", fileName);
    }
}

int main() {
    int choice;
    char fileName[50], content[100];

    while (1) {
        printf("File Management Operations\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read from File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                createFile(fileName);
                break;
            case 2:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter content: ");
                scanf("%s", content);
                writeFile(fileName, content);
                break;
            case 3:
                printf("Enter file name: ");
                scanf("%s", fileName);
                readFile(fileName);
                break;
            case 4:
                printf("Enter file name: ");
                scanf("%s", fileName);
                deleteFile(fileName);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please choose a valid option.\n");
        }
    }

    return 0;
}


OUTPUT

File Management Operations
1. Create File
2. Write to File
3. Read from File
4. Delete File
5. Exit
Enter your choice: 1
Enter file name: os
File os created successfully
File Management Operations
1. Create File
2. Write to File
3. Read from File
4. Delete File
5. Exit
Enter your choice: 2
Enter file name: os
Enter content: hello
Written to file os successfully
File Management Operations
1. Create File
2. Write to File
3. Read from File
4. Delete File
5. Exit
Enter your choice: 3
Enter file name: os
Contents of file os:
helloFile Management Operations
1. Create File
2. Write to File
3. Read from File
4. Delete File
5. Exit
Enter your choice: 5
