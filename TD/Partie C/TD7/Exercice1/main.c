#include <stdio.h>
#include "polynome.h"

int main() {
    double a, b, c;

    printf("Ce programme permet de calculer les racines d'un polynome appartenant aux complexes\n");
    printf("Veuillez choisir une valeur de a : ");
    scanf("%lf", &a);
    printf("Veuillez choisir une valeur de b : ");
    scanf("%lf", &b);
    printf("Veuillez choisir une valeur de c : ");
    scanf("%lf", &c);

    polynome(&a, &b, &c);

    return 0;
}
