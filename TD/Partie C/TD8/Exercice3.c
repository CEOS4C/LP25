#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void printFileSize(off_t size) {
    if (size < 1024) {
        printf("%lld %lld octets ", (long long)size, (long long)size);
    } else if (size < 1024 * 1024) {
        printf("%lld %.2f kio ", (long long)size, (double)size / 1024);
    } else if (size < 1024 * 1024 * 1024) {
        printf("%lld %.2f mio ", (long long)size, (double)size / (1024 * 1024));
    } else {
        printf("%lld %.2f gio ", (long long)size, (double)size / (1024 * 1024 * 1024));
    }
}

int main() {
    char chemin[200];
    struct stat stats;

    printf("Veuillez choisir un repertoire à scanner : ");

    if (scanf(" %[^\n]", chemin) != 1) {
        printf("Erreur de lecture de la chaine.\n");
        return EXIT_FAILURE;
    }

    printf("Chemin saisi : %s\n", chemin);

    DIR *directory = opendir(chemin);

    if (directory == NULL) {
        printf("Erreur lors de l'ouverture du dossier");
        return EXIT_FAILURE;
    }

    struct dirent *dir;
    while ((dir = readdir(directory)) != NULL) {
        char fullPath[300];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", chemin, dir->d_name);

        if (stat(fullPath, &stats) == -1) {
            perror("Erreur lors de la récupération des informations du fichier");
            continue;
        }

        printf("%s ", dir->d_name);
        printFileSize(stats.st_size);
        printf("\n");
    }

    closedir(directory);
    return 0;
}