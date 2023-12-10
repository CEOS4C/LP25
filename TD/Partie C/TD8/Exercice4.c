#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

void search_file(const char *directory_path, const char *target_file_name) {
    DIR *directory = opendir(directory_path);

    if (directory == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        return;
    }

    struct dirent *entry;
    bool file_found = false;

    while ((entry = readdir(directory)) != NULL && !file_found) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory_path, entry->d_name);

        struct stat entry_stat;
        if (stat(full_path, &entry_stat) == -1) {
            perror("Erreur lors de la récupération des informations sur le fichier");
            closedir(directory);
            return;
        }

        if (S_ISDIR(entry_stat.st_mode)) {
            search_file(full_path, target_file_name);
        } else if (strcmp(entry->d_name, target_file_name) == 0) {
            printf("Fichier trouvé : %s\n", full_path);
            file_found = true;
        }
    }

    if (!file_found) {
        printf("Le fichier n'existe pas dans ce répertoire.\n");
        exit(EXIT_FAILURE);
    }

    closedir(directory);
}

int main() {
    char chemin[200];
    char fichier[100];

    printf("Veuillez choisir un repertoire à scanner : ");
    if (scanf(" %[^\n]", chemin) != 1) {
        printf("Erreur de lecture de la chaine.\n");
        return EXIT_FAILURE;
    }

    printf("Veuillez choisir un fichier à chercher dans le repertorie spécifié : ");
    if (scanf(" %[^\n]", fichier) != 1) {
        printf("Erreur de lecture de la chaine.\n");
        return EXIT_FAILURE;
    }

    const char *directory_path = chemin;
    const char *target_file_name = fichier;

    search_file(directory_path, target_file_name);

    return 0;
}
