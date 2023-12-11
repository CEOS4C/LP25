#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 150

volatile sig_atomic_t sigint_triggered = 0;

void sigint_handler(int signal) {
    sigint_triggered = 1;
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESETHAND;
    sa.sa_restorer = NULL;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen("dump.txt", "w");
    if (f == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char last_phrase[BUFFER_SIZE] = "";

    do {
        if (!sigint_triggered) {
            printf("Enter a phrase: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                perror("Error reading input");
                break; // Exit the loop on input error
            }

            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            if (strcmp(buffer, last_phrase) == 0) {
                printf("Vous venez d'entrer une phrase déjà utilisée, veuillez en entrer une autre.\n");
                continue;
            }

            if (!sigint_triggered) {
                if (fprintf(f, "%s\n", buffer) < 0) {
                    perror("Error writing to file");
                    break;
                }

                fflush(f);

                strcpy(last_phrase, buffer);
            }
        }
    } while (!sigint_triggered);

    if (fclose(f) != 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
