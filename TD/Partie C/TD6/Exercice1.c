#include <stdio.h>
#include <complex.h>

int main() {
    double a, b, c;
    double complex racine1, racine2;
    printf("Ce programme permet de calculer les racines d'un polynome appartenant aux complexes\n");
    printf("Veuillez choisir une valeur de a : ");
    scanf("%lf", &a);
    printf("Veuillez choisir une valeur de b : ");
    scanf("%lf", &b);
    printf("Veuillez choisir une valeur de c : ");
    scanf("%lf", &c);

    double delta = b * b - 4 * a * c;

    if (cabs(delta) < 1e-10) {
        racine1 = -b / (2 * a);
        printf("La solution de l'équation est : %.2f\n", creal(racine1));
    } else if (cabs(delta) > 0) {
        racine1 = (-b - csqrt(delta)) / (2 * a);
        racine2 = (-b + csqrt(delta)) / (2 * a);
        printf("Les solutions de l'équation sont : (%.2f + %.2fi) et (%.2f - %.2fi)\n", creal(racine1), cimag(racine1), creal(racine2), cimag(racine2));
    } else {
        racine1 = -b / (2 * a);
        double imagPart = cimag(csqrt(-delta)) / (2 * a);
        printf("Les solutions de l'équation sont : (%.2f + %.2fi) et (%.2f - %.2fi)\n", creal(racine1), imagPart, creal(racine1), -imagPart);
    }

    return 0;
}
