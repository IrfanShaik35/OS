
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate grep command
void grep(const char *pattern, const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    char line[256];

    if (fp == NULL) {
        perror("fopen");
        return;
    }

    printf("Lines containing pattern '%s' in file %s:\n", pattern, fileName);
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <pattern> <file1> [<file2> ...]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    for (int i = 2; i < argc; i++) {
        grep(pattern, argv[i]);
    }

    return 0;
}

