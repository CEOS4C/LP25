#include <stdio.h>
#include <stdlib.h>

void afficherTableau(int *tableau, int taille) {
    for (int i = 0; i < taille; ++i) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Entrez une valeur entière pour n : ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Erreur : veuillez entrer un entier positif.\n");
        return 1;
    }

    int *tableau = malloc(sizeof(int) * n);
    if (tableau == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        tableau[i] = i + 1;
    }

    printf("Tableau : ");
    afficherTableau(tableau, n);

    free(tableau);

    return 0;
}
