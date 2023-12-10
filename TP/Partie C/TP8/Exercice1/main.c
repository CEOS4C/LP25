#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define NB_VAL 255

void fusion(FILE *f, off_t debut, off_t milieu, off_t fin) {
    int fd = fileno(f);

    off_t n1 = milieu - debut + 1;
    off_t n2 = fin - milieu;

    unsigned long long *gauche = malloc(n1 * sizeof(unsigned long long));
    unsigned long long *droite = malloc(n2 * sizeof(unsigned long long));

    lseek(fd, debut * sizeof(unsigned long long), SEEK_SET);
    read(fd, gauche, n1 * sizeof(unsigned long long));

    lseek(fd, (milieu + 1) * sizeof(unsigned long long), SEEK_SET);
    read(fd, droite, n2 * sizeof(unsigned long long));

    off_t i = 0, j = 0, k = debut;
    while (i < n1 && j < n2) {
        if (gauche[i] <= droite[j]) {
            lseek(fd, k * sizeof(unsigned long long), SEEK_SET);
            write(fd, &gauche[i], sizeof(unsigned long long));
            i++;
        } else {
            lseek(fd, k * sizeof(unsigned long long), SEEK_SET);
            write(fd, &droite[j], sizeof(unsigned long long));
            j++;
        }
        k++;
    }

    while (i < n1) {
        lseek(fd, k * sizeof(unsigned long long), SEEK_SET);
        write(fd, &gauche[i], sizeof(unsigned long long));
        i++;
        k++;
    }

    while (j < n2) {
        lseek(fd, k * sizeof(unsigned long long), SEEK_SET);
        write(fd, &droite[j], sizeof(unsigned long long));
        j++;
        k++;
    }

    free(gauche);
    free(droite);
}

void triFusion(FILE *f, off_t debut, off_t fin) {
    if (debut < fin) {
        off_t milieu = debut + (fin - debut) / 2;

        triFusion(f, debut, milieu);
        triFusion(f, milieu + 1, fin);

        fusion(f, debut, milieu, fin);
    }
}

int main() {
    srand(time(NULL));

    unsigned long long nombre;
    FILE *f = fopen("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP8/Exercice1/texte.txt", "r+b");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier texte.txt en lecture/écriture binaire");
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
