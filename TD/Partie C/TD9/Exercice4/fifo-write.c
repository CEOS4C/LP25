#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "myfifo"

int main() {
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char input[100];
    printf("Entrez du texte à envoyer à fifo-read.c (Ctrl+D pour terminer) :\n");

    while (fgets(input, sizeof(input), stdin) != NULL) {
        size_t input_length = strlen(input);
        write(fd, input, input_length);
    }

    close(fd);

    return EXIT_SUCCESS;
}
