#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char buffer[100];

    // Create and open a file
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error opening/creating file");
        return 1;
    }
    printf("File 'example.txt' created and opened for writing.\n");

    // Write to the file
    bytes_written = write(fd, "Hello, UNIX System Calls!", 25);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Written %zd bytes to the file.\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing the file");
        return 1;
    }
    printf("File 'example.txt' closed after writing.\n");

    // Reopen the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("File 'example.txt' opened for reading.\n");

    // Read from the file
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    printf("Read %zd bytes from the file: %s\n", bytes_read, buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing the file");
        return 1;
    }
    printf("File 'example.txt' closed after reading.\n");

    // Delete the file
    if (unlink("example.txt") == -1) {
        perror("Error deleting the file");
        return 1;
    }
    printf("File 'example.txt' deleted.\n");

    return 0;
}
