#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void readFromFile(FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fflush(stdout);
}

void readFromPipe() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argv[1][0] == '-') {
        readFromPipe();
    } else {
        FILE *file = fopen(argv[1], "rb");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        readFromFile(file);

        if (fclose(file) != 0) {
            perror("Error closing file");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
