#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int opt = 0;

    // Utilisation de getopt pour traiter les options de la ligne de commande.
    while ((opt = getopt(argc, argv, "oa:")) != -1) {
        switch (opt) {
            case 'o':
                // Option 'o' détectée.
                printf("Option 'o' is set.\n");
                break;

            case 'a':
                // Option 'a' détectée avec un argument.
                printf("Option 'a' is set with argument: %s\n", optarg);
                break;

            case '?':
                // Gestion des options non reconnues ou des arguments manquants.
                if (optopt == 'a') {
                    fprintf(stderr, "Option 'a' requires an argument.\n");
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
                }
                return 1;

            default:
                // Cas inattendu dans l'instruction switch.
                fprintf(stderr, "Unexpected case in switch statement.\n");
                return 1;
        }
    }

    // Afficher les arguments de ligne de commande qui ne sont pas des options.
    for (int i = optind; i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
    }

    return 0;
}
