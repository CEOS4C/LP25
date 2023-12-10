#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NB_VAL 255

void fusion(FILE *f, long debut, long milieu, long fin) {
    off_t n1 = milieu - debut + 1;
    off_t n2 = fin - milieu;

    unsigned long long *gauche = malloc(n1 * sizeof(unsigned long long));
    unsigned long long *droite = malloc(n2 * sizeof(unsigned long long));

    fseek(f, debut * sizeof(unsigned long long), SEEK_SET);
    fread(gauche, sizeof(unsigned long long), n1, f);

    fseek(f, (milieu + 1) * sizeof(unsigned long long), SEEK_SET);
    fread(droite, sizeof(unsigned long long), n2, f);

    long i = 0, j = 0, k = debut;
    while (i < n1 && j < n2) {
        if (gauche[i] <= droite[j]) {
            fseek(f, k * sizeof(unsigned long long), SEEK_SET);
            fwrite(&gauche[i], sizeof(unsigned long long), 1, f);
            i++;
        } else {
            fseek(f, k * sizeof(unsigned long long), SEEK_SET);
            fwrite(&droite[j], sizeof(unsigned long long), 1, f);
            j++;
        }
        k++;
    }

    while (i < n1) {
        fseek(f, k * sizeof(unsigned long long), SEEK_SET);
        fwrite(&gauche[i], sizeof(unsigned long long), 1, f);
        i++;
        k++;
    }

    while (j < n2) {
        fseek(f, k * sizeof(unsigned long long), SEEK_SET);
        fwrite(&droite[j], sizeof(unsigned long long), 1, f);
        j++;
        k++;
    }

    free(gauche);
    free(droite);
}

void triFusion(FILE *f, long debut, long fin) {
    if (debut < fin) {
        long milieu = debut + (fin - debut) / 2;

        triFusion(f, debut, milieu);
        triFusion(f, milieu + 1, fin);

        fusion(f, debut, milieu, fin);
    }
}

int main() {
    srand(time(NULL));

    unsigned long long nombre;
    FILE *f = fopen("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP8/Exercice1/texte.txt", "w+b");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture/écriture binaire");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NB_VAL; ++i) {
        nombre = rand();
        fwrite(&nombre, sizeof(unsigned long long), 1, f);
    }

    triFusion(f, 0, NB_VAL - 1);

    printf("Contenu du fichier trié :\n");
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < NB_VAL; ++i) {
        fread(&nombre, sizeof(unsigned long long), 1, f);
        printf("%llu\n", nombre);
    }

    fclose(f);

    return EXIT_SUCCESS;
}
