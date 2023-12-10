#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void printFileType(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Fichier standard");
    } else if (S_ISDIR(mode)) {
        printf("Répertoire");
    } else if (S_ISLNK(mode)) {
        printf("Lien symbolique");
    } else if (S_ISCHR(mode)) {
        printf("Fichier de caractère spécial");
    } else if (S_ISBLK(mode)) {
        printf("Fichier de bloc spécial");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (tube nommé)");
    } else if (S_ISSOCK(mode)) {
        printf("Socket");
    } else {
        printf("Type inconnu");
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

        printf("%s - ", dir->d_name);
        printFileType(stats.st_mode);
        printf("\n");
    }

    closedir(directory);
    return 0;
}
