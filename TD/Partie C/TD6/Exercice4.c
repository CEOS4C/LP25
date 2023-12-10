#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparerTaille(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;

    int diffTaille = strlen(s1) - strlen(s2);
    if (diffTaille != 0) {
        return diffTaille;
    }

    return strcmp(s1, s2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <mot1> <mot2> ... <motN>\n", argv[0]);
        return 1;
    }

    char **mots = (char **)malloc((argc - 1) * sizeof(char *));

    for (int i = 1; i < argc; i++) {
        mots[i - 1] = strdup(argv[i]);
    }

    qsort(mots, argc - 1, sizeof(char *), comparerTaille);

    printf("Mots triés par taille et pseudo-alphabétique ASCII :\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s ", mots[i]);

        free(mots[i]);
    }
    printf("\n");

    free(mots);

    return 0;
}