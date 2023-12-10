#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct dirent *next_entry(DIR *directory) {
    struct dirent *entry = NULL;
    char current_path[PATH_MAX];

    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        perror("Erreur lors de la récupération du répertoire de travail actuel");
        return NULL;
    }

    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        struct stat entry_stat;
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entry->d_name);

        if (stat(full_path, &entry_stat) == -1) {
            perror("Erreur lors de la récupération des informations sur le fichier");
            return NULL;
        }

        if (S_ISDIR(entry_stat.st_mode) && (entry->d_type == DT_DIR)) {
            return entry;
        }
    }

    return NULL;
}

int main() {
    DIR *directory = opendir(".");

    if (directory == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    while ((entry = next_entry(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(directory);

    return 0;
}
