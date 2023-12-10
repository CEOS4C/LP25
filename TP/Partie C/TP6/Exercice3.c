#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX 1024
#define PARAMETER_BUFFER_SIZE 16

typedef enum {
    PARAM_VERBOSE,
    PARAM_DATA_SOURCE,
    PARAM_TEMP_DIR,
    PARAM_OUTPUT_FILE,
    PARAM_CPU_MULT,
} parameter_id_t;

typedef union {
    long long int_param;
    bool flag_param;
    char str_param[STR_MAX];
} data_wrapper_t;

typedef struct {
    parameter_id_t parameter_type;
    data_wrapper_t parameter_value;
} parameter_t;

bool are_parameters_valid(parameter_t *params, int params_count) {
    for (int i = 0; i < params_count; ++i) {
        switch (params[i].parameter_type) {
            case PARAM_DATA_SOURCE:
            case PARAM_TEMP_DIR:
            case PARAM_OUTPUT_FILE:
                if (params[i].parameter_value.str_param[0] == '\0') {
                    return false; // Chemin vide n'est pas acceptable
                }
                break;

            case PARAM_CPU_MULT:
                if (params[i].parameter_value.int_param < 1 || params[i].parameter_value.int_param > 4) {
                    return false; // Valeur du multiplicateur de CPU hors limites
                }
                break;

            default:
                break; // Autres paramètres, pas de vérification spécifique
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    parameter_t my_parameters[PARAMETER_BUFFER_SIZE];
    int parameters_count = 0;

    parameter_t default_parameters[] = {
            {.parameter_type = PARAM_VERBOSE, .parameter_value.flag_param = false},
            {.parameter_type = PARAM_DATA_SOURCE, .parameter_value.str_param = ""},
            {.parameter_type = PARAM_TEMP_DIR, .parameter_value.str_param = "./temp"},
            {.parameter_type = PARAM_OUTPUT_FILE, .parameter_value.str_param = ""},
            {.parameter_type = PARAM_CPU_MULT, .parameter_value.int_param = 2},
    };

    int default_parameters_count = sizeof(default_parameters) / sizeof(parameter_t);

    // Fusion des paramètres par défaut avec les nouveaux paramètres de la ligne de commande
    for (int i = 0; i < default_parameters_count; ++i) {
        my_parameters[i] = default_parameters[i];
        parameters_count++;
    }

    // Analyse des arguments de la ligne de commande
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--verbose") == 0) {
            my_parameters[parameters_count].parameter_type = PARAM_VERBOSE;
            my_parameters[parameters_count].parameter_value.flag_param = true;
            parameters_count++;
        } else if (strcmp(argv[i], "--data-source") == 0) {
            i++;
            my_parameters[parameters_count].parameter_type = PARAM_DATA_SOURCE;
            strncpy(my_parameters[parameters_count].parameter_value.str_param, argv[i], STR_MAX - 1);
            parameters_count++;
        } else if (strcmp(argv[i], "--temporary-directory") == 0) {
            i++;
            my_parameters[parameters_count].parameter_type = PARAM_TEMP_DIR;
            strncpy(my_parameters[parameters_count].parameter_value.str_param, argv[i], STR_MAX - 1);
            parameters_count++;
        } else if (strcmp(argv[i], "--output-file") == 0) {
            i++;
            my_parameters[parameters_count].parameter_type = PARAM_OUTPUT_FILE;
            strncpy(my_parameters[parameters_count].parameter_value.str_param, argv[i], STR_MAX - 1);
            parameters_count++;
        } else if (strcmp(argv[i], "--cpu-multiplier") == 0) {
            i++;
            my_parameters[parameters_count].parameter_type = PARAM_CPU_MULT;
            my_parameters[parameters_count].parameter_value.int_param = atoi(argv[i]);
            parameters_count++;
        }
    }

    if (are_parameters_valid(my_parameters, parameters_count)) {
        printf("Parameters are acceptable.\n");
    } else {
        printf("Parameters are not acceptable.\n");
    }

    return 0;
}