#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    char chemin[200];
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
        printf("%s\n", dir->d_name);
    }

    closedir(directory);
    return 0;
}