#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[]) {
    int opt = 0;
    int verbose_flag = 0;
    char *data_source = NULL;
    char *temporary_directory = NULL;
    char *output_file = NULL;
    int cpu_multiplier = 1;

    struct option long_options[] = {
        {"verbose", no_argument, &verbose_flag, 1},
        {"data-source", required_argument, NULL, 'd'},
        {"temporary-directory", required_argument, NULL, 't'},
        {"output-file", required_argument, NULL, 'o'},
        {"cpu-multiplier", required_argument, NULL, 'c'},
        {0, 0, 0, 0} // last element must be zero
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
        switch (opt) {
            case 0:
                break;

            case 'd':
                data_source = optarg;
                break;

            case 't':
                temporary_directory = optarg;
                break;

            case 'o':
                output_file = optarg;
                break;

            case 'c':
                cpu_multiplier = atoi(optarg);
                break;

            case '?':
                // Gestion des options non reconnues ou des arguments manquants.
                fprintf(stderr, "Usage: %s --verbose --data-source=... --temporary-directory=... --output-file=... --cpu-multiplier=...\n", argv[0]);
                return 1;

            default:
                fprintf(stderr, "Unexpected case in switch statement.\n");
                return 1;
        }
    }

    printf("Verbose mode is %s\n", (verbose_flag ? "on" : "off"));
    if (data_source != NULL) {
        printf("Data source is located on %s\n", data_source);
    }
    if (temporary_directory != NULL) {
        printf("Temporary files will be located on %s\n", temporary_directory);
    }
    if (output_file != NULL) {
        printf("Output file will be produced on %s\n", output_file);
    }

    int num_cpus = get_nprocs();
    printf("%d tasks will run in parallel\n", cpu_multiplier * num_cpus);

    return 0;
}

