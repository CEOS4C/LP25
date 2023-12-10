#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int opt = 0;
    char *b_arg = NULL;  // Variable pour stocker l'argument de l'option 'b' facultative.

    // Utilisation de getopt pour traiter les options de la ligne de commande.
    while ((opt = getopt(argc, argv, "oa:b::")) != -1) {
        switch (opt) {
            case 'o':
                // Option 'o' détectée.
                printf("Option 'o' est activée.\n");
                break;

            case 'a':
                // Option 'a' détectée avec un argument.
                printf("Option 'a' est activée avec l'argument : %s\n", optarg);
                break;

            case 'b':
                // Option 'b' détectée avec un argument facultatif.
                if (optarg != NULL) {
                    // L'argument de l'option 'b' est présent.
                    printf("Option 'b' est activée avec l'argument : %s\n", optarg);
                    b_arg = optarg;
                } else {
                    // L'argument de l'option 'b' est absent.
                    printf("Option 'b' est activée sans argument.\n");
                    b_arg = NULL;
                }
                break;

            case '?':
                // Gestion des options non reconnues ou des arguments manquants.
                if (optopt == 'a') {
                    fprintf(stderr, "L'option 'a' nécessite un argument.\n");
                } else if (optopt == 'b') {
                    fprintf(stderr, "L'option 'b' nécessite un argument facultatif.\n");
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Option inconnue '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Caractère d'option inconnu '\\x%x'.\n", optopt);
                }
                return 1;

            default:
                // Cas inattendu dans l'instruction switch.
                fprintf(stderr, "Cas inattendu dans l'instruction switch.\n");
                return 1;
        }
    }

    // Afficher les arguments de ligne de commande qui ne sont pas des options.
    for (int i = optind; i < argc; i++) {
        printf("Argument non optionnel : %s\n", argv[i]);
    }

    // Afficher la valeur de l'argument de l'option 'b'.
    if (b_arg != NULL) {
        printf("La valeur de l'argument de 'b' est : %s\n", b_arg);
    }

    return 0;
}
