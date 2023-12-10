#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compterSeparateurs(const char *chaine) {
    int compte = 0;
    while (*chaine) {
        if (*chaine == ';') {
            compte++;
        }
        chaine++;
    }
    return compte;
}

void extraireElements(const char *chaine, char **elements, int nbSeparateurs) {
    int indiceElement = 0;
    while (*chaine) {
        if (*chaine == ';') {
            chaine++;
        } else {

            elements[indiceElement] = malloc(strlen(chaine) + 1);

            int indiceCaractere = 0;
            while (*chaine && *chaine != ';') {
                elements[indiceElement][indiceCaractere++] = *chaine++;
            }
            elements[indiceElement][indiceCaractere] = '\0';

            indiceElement++;
        }
    }
}

int main() {
    char buffer[256];

    printf("Entrez une chaîne CSV : ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Erreur de saisie.\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    char *chaine = buffer;
    if (strchr(chaine, ' ') != NULL) {
        char *chaineEncadree = malloc(strlen(chaine) + 3);
        sprintf(chaineEncadree, "\"%s\"", chaine);
        chaine = chaineEncadree;
    }

    int nbSeparateurs = compterSeparateurs(chaine);

    char **elements = malloc(sizeof(char *) * (nbSeparateurs + 1));

    extraireElements(chaine, elements, nbSeparateurs);

    for (int i = 0; i <= nbSeparateurs; ++i) {
        printf("Element %d : %s\n", i + 1, elements[i]);
        free(elements[i]);
    }

    free(elements);
    if (chaine != buffer) {
        free(chaine);
    }

    return 0;
}