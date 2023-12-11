#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];

        if (remove(filename) == 0) {
            printf("File '%s' deleted successfully.\n", filename);
        } else {
            perror("Error deleting file");
        }
    }

    return EXIT_SUCCESS;
}
