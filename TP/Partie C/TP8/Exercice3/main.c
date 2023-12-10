#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>

#define FILENAME "output.txt"
#define CHAR_COUNT 50
#define ITERATIONS 10
#define WAIT_TIME 1

void write_lines(char character) {
    int fd = open(FILENAME, O_WRONLY | O_CREAT, 00660);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    flock(fd, LOCK_EX);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < CHAR_COUNT; ++j) {
            write(fd, &character, 1);
        }
        write(fd, "\n", 1);
    }

    flock(fd, LOCK_UN);

    close(fd);
}

void print_file_content() {
    int fd = open(FILENAME, O_RDONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[CHAR_COUNT + 1];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, CHAR_COUNT)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

    close(fd);
}

int main() {
    char character1 = 'a';
    char character2 = 'b';

    for (int i = 0; i < ITERATIONS; ++i) {
        if (fork() == 0) {
            flock(fd, LOCK_EX);
            if (i % 2 == 0) {
                write_lines(character1);
            } else {
                write_lines(character2);
            }
            flock(fd, LOCK_UN);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < ITERATIONS; ++i) {
        wait(NULL);
    }

    printf("Contenu du fichier à la fin :\n");
    print_file_content();

    return 0;
}
