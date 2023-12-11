#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        if (mkdir(path, 0777) == -1) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        } else {
            printf("Directory '%s' created successfully.\n", path);
        }
    } else {
        fprintf(stderr, "Directory '%s' already exists.\n", path);
        exit(EXIT_FAILURE);
    }
}

void create_intermediate_directories(const char *path) {
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, "/");
    char current_path[256] = "";

    while (token != NULL) {
        strcat(current_path, token);

        if (current_path[strlen(current_path) - 1] != '/') {
            if (mkdir(current_path, 0777) == -1) {
                perror("Error creating directory");
                exit(EXIT_FAILURE);
            }
        }

        strcat(current_path, "/");
        token = strtok(NULL, "/");
    }

    free(path_copy);
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s [-p] directory_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int use_intermediate = 0;

    if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        use_intermediate = 1;
    }

    const char *directory_name = argv[argc - 1];

    if (use_intermediate) {
        char current_directory[256];
        if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
            perror("Error getting current directory");
            exit(EXIT_FAILURE);
        }

        create_intermediate_directories(directory_name);

        if (chdir(current_directory) == -1) {
            perror("Error changing back to original directory");
            exit(EXIT_FAILURE);
        }
    } else {
        create_directory(directory_name);
    }

    return EXIT_SUCCESS;
}
