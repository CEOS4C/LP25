#include "polynome.h"
#include <complex.h>
#include <stdio.h>
#include <math.h>

void polynome(double *a, double *b, double *c) {
    double delta = pow(*b, 2) - 4 * *a * *c; // Correction : pow(*b, 2) au lieu de pow(*b, *b)
    double complex racine1, racine2;

    if (cabs(delta) < 1e-10) {
        racine1 = -*b / (2 * *a);
        printf("La solution de l'équation est : %.2f\n", creal(racine1));
    } else if (cabs(delta) > 0) {
        racine1 = (-*b - csqrt(delta)) / (2 * *a);
        racine2 = (-*b + csqrt(delta)) / (2 * *a);
        printf("Les solutions de l'équation sont : (%.2f + %.2fi) et (%.2f - %.2fi)\n", creal(racine1), cimag(racine1),
               creal(racine2), cimag(racine2));
    } else {
        racine1 = -*b / (2 * *a);
        double imagPart = cimag(csqrt(-delta)) / (2 * *a);
        printf("Les solutions de l'équation sont : (%.2f + %.2fi) et (%.2f - %.2fi)\n", creal(racine1), imagPart,
               creal(racine1), -imagPart);
    }
}
