#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char mot[1000];
    char *mots;
    int a;

    printf("Ce programme teste si une phrase passée en paramètre du programme est un anagramme\n");
    printf("Veuillez choisir une phrase : ");

    fgets(mot, sizeof(mot), stdin);

    if (strlen(mot) > 0 && mot[strlen(mot) - 1] == '\n') {
        mot[strlen(mot) - 1] = '\0';
    }

    a = strlen(mot);
    mots = malloc(a * sizeof(char) + 1);

    int l = 0;
    for(int k = 0; k < a; k++){
        if(mot[k] != ' ') {
            mots[l++] = mot[k];
        }
    }
    mots[l] = '\0';

    char motEnvers[1000];
    int j = 0;

    for (int i = strlen(mots) - 1; i >= 0; i--) {
        motEnvers[j++] = mots[i];
    }
    motEnvers[j] = '\0';

    if (strcmp(mots, motEnvers) == 0) {
        printf("La phrase saisie est un anagramme");
    } else {
        printf("La phrase saisie n'est pas un anagramme");
    }

    free(mots);

    return 0;
}