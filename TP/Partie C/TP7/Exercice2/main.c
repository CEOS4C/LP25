#include <stdio.h>
#include <stdlib.h>

#define TAILLE_LOSAGE 5

void losange(FILE *f, int s) {
    int taille = 1 + 2 * (s - 1);
    int espaces, etoiles;

    for (int i = 0; i < taille; i += 2) {
        espaces = (taille - i) / 2;
        etoiles = i + 1;

        for (int j = 0; j < espaces; ++j) {
            fprintf(f, " ");
        }

        for (int j = 0; j < etoiles; ++j) {
            fprintf(f, "*");
        }

        fprintf(f, "\n");
    }

    for (int i = taille - 3; i >= 0; i -= 2) {
        espaces = (taille - i) / 2;
        etoiles = i + 1;

        for (int j = 0; j < espaces; ++j) {
            fprintf(f, " ");
        }

        for (int j = 0; j < etoiles; ++j) {
            fprintf(f, "*");
        }

        fprintf(f, "\n");
    }
}

void afficherContenu(FILE *f) {
    fseek(f, 0, SEEK_SET);

    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
}

int main() {
    FILE *f = fopen("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP7/Exercice2/losange.txt", "w+");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier losange.txt");
        return EXIT_FAILURE;
    }

    int s = TAILLE_LOSAGE;
    losange(f, s);

    printf("Contenu du fichier losange.txt :\n");
    afficherContenu(f);

    fclose(f);
    return 0;
}
