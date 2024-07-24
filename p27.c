#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void print_file_info(const char *filepath, const char *filename) {
    struct stat file_stat;
    if (stat(filepath, &file_stat) == -1) {
        perror("Failed to get file status");
        return;
    }

    // Print file type
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %ld", file_stat.st_nlink);

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");

    printf(" %ld", file_stat.st_size);

    char timebuf[80];
    struct tm *tm_info;
    tm_info = localtime(&file_stat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
    printf(" %s", timebuf);

    printf(" %s\n", filename);
}

void list_directory(const char *dirname, int show_hidden, int detailed) {
    DIR *dir = opendir(dirname);
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if not showing hidden
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        if (detailed) {
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);
            print_file_info(filepath, entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int show_hidden = 0;
    int detailed = 0;
    const char *dirname = ".";

    // Parse command-line options
    int opt;
    while ((opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                detailed = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Check if a directory is specified
    if (optind < argc) {
        dirname = argv[optind];
    }

    list_directory(dirname, show_hidden, detailed);
    return 0;
}
