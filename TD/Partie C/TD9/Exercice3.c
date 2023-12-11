#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void remove_directory(const char *path) {
    if (rmdir(path) == 0) {
        printf("Directory '%s' deleted successfully.\n", path);
    } else {
        perror("Error deleting directory");
    }
}

int is_directory_empty(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return 0;
        }
    }

    closedir(dir);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s [-r] directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int recursive = 0;
    char *directory;

    if (argc == 2) {
        directory = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "-r") != 0) {
            fprintf(stderr, "Usage: %s [-r] directory\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        recursive = 1;
        directory = argv[2];
    }

    if (recursive) {
        printf("Are you sure you want to delete the directory '%s' and its contents? (y/n): ", directory);
        char response;
        scanf(" %c", &response);

        if (response != 'y' && response != 'Y') {
            printf("Operation canceled.\n");
            exit(EXIT_SUCCESS);
        }
    } else {
        if (!is_directory_empty(directory)) {
            printf("Directory '%s' is not empty. Use -r option to delete non-empty directories.\n", directory);
            exit(EXIT_FAILURE);
        }
    }

    remove_directory(directory);

    return EXIT_SUCCESS;
}
