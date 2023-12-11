#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/poll.h>
#include <sys/stat.h>

#define FIFO_NAME1 "fifo1"
#define FIFO_NAME2 "fifo2"

void sigint_handler(int signo) {
    if (signo == SIGINT) {
        printf("\nReceived SIGINT. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    if (mkfifo(FIFO_NAME1, 0666) == -1) {
        perror("Error creating FIFO 1");
        exit(EXIT_FAILURE);
    }

    int fd_fifo1 = open(FIFO_NAME1, O_RDONLY | O_NONBLOCK);
    if (fd_fifo1 == -1) {
        perror("Error opening FIFO 1 for reading");
        exit(EXIT_FAILURE);
    }

    printf("FIFO 1 opened for reading. Waiting for data...\n");

    if (mkfifo(FIFO_NAME2, 0666) == -1) {
        perror("Error creating FIFO 2");
        exit(EXIT_FAILURE);
    }

    int fd_fifo2 = open(FIFO_NAME2, O_RDONLY | O_NONBLOCK);
    if (fd_fifo2 == -1) {
        perror("Error opening FIFO 2 for reading");
        exit(EXIT_FAILURE);
    }

    printf("FIFO 2 opened for reading. Waiting for data...\n");

    struct pollfd read_fds[2] = {
            { .fd=fd_fifo1, .events=POLLIN },
            { .fd=fd_fifo2, .events=POLLIN },
    };

    char buffer[256];

    while (1) {
        int ready = poll(read_fds, 2, -1);

        if (ready == -1) {
            perror("Error in poll");
            exit(EXIT_FAILURE);
        } else if (ready > 0) {
            for (int i = 0; i < 2; ++i) {
                if (read_fds[i].revents & POLLIN) {
                    ssize_t bytes_read = read(read_fds[i].fd, buffer, sizeof(buffer));
                    if (bytes_read > 0) {
                        printf("Received from FIFO %d: %.*s", i + 1, (int)bytes_read, buffer);
                    }
                } else if (read_fds[i].revents & (POLLHUP | POLLERR | POLLNVAL)) {
                    close(read_fds[i].fd);
                }
            }
        }
    }

    close(fd_fifo1);
    close(fd_fifo2);
    return EXIT_SUCCESS;
}
