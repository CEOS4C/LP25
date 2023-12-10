#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 150

void afficherFichier(FILE *f) {
    fseek(f, 0, SEEK_SET);
    char ligne[BUFFER_SIZE];

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        printf("%s", ligne);
    }
}

int main() {
    FILE *f = fopen("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP7/Exercice1/texte.txt", "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier texte.txt");
        return EXIT_FAILURE;
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, f)) {
    }
    afficherFichier(f);
    fclose(f);
    return 0;
}
