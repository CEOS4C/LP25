# LP25 - TD6 - Session 1 de C

L'objectif de ce TD est de faire quelques rappels sur le langage C. Ces rappels seront utiles pour réaliser l'ensemble des TD et TP portant sur le C pendant la seconde moitié du semestre.

## Compilation

Le langage C est un langage compilé, c'est-à-dire qu'il est analysé pour être converti en langage machine (des instructions binaires dépendantes de l'architecture de la machine) avant de pouvoir être exécuté. Sur les machines de TP, le compilateur utilisé est le compilateur C de la GCC (GNU Compiler Collection). Il s'utilise de la manière suivante :
```
gcc fichier_source.c -o programme
```
où :

 - _fichier_source.c_ est le code du programme
 - _programme_ est le nom de l'exécutable.

D'autres options existent et seront abordées au cours des TD et TP.

## Programme simple

Le premier programme que nous pouvons écrire est un simple _Hello, World!_ dont voici le code :

```c
#include <stdio.h>

int main() {
	printf("Hello, World!\n");
	return 0;
}
```

Ce programme inclut le fichier d'entête _stdio.h_ nécessaire à l'utilisation de la fonction _printf_, puis il déclare la fonction principale nommée `main` du programme (il n'en existe qu'une et une seule par programme). Dans cette fonction, délimitée par des accolades, l'instruction _printf_ permet d'afficher sur la sortie standard (le terminal où sera exécuté le programme) la chaîne de caractères qui lui est passée en paramètre. Puis la fonction retourne la valeur 0, qui signifie que l'exécution s'est bien déroulée.

Pour compiler ce programme, que vous sauvegarderez dans le fichier _hello.c_, vous utiliserez la commande suivante : `gcc hello.c -Wall -o hello`, puis vous pouvez l'exécuter en vous plaçant dans le répertoire où se trouve le fichier exécutable _hello_ et en saisissant la commande : `./hello`. Vous devriez voir sur le terminal la phrase `Hello, World!` s'afficher, puis votre prompt sur la ligne suivante.

## Gérer le code source

Au cours du semestre, vous serez amenés à utiliser du code fourni dans un dépôt git. Ce code sera à travailler en groupe pour le projet. Il vous sera donc utile d'utiliser les quelques commandes ci-dessous, si vous ne les connaissez pas déjà :

 - **clone [URL]** : permet de cloner le dépôt de code pour commencer à y travailler. Cette commande n'est utilisée que pour créer une copie locale du projet dans un emplacement qui ne contient pas encore de code ni de documents gérés par git. Le projet copié est celui dont l'URL est passée en paramètre
 - **branch [nom de branche]** : crée une branche à partir de laquelle les modifications du code seront indépendantes des autres branches, jusqu'à une éventuelle fusion. Le nom de la branche ne doit pas encore exister. Il vous sera demander de créer une branche nommée d'après votre login pour remettre vos TD et TP.
 - **checkout [nom de branche]** : se place dans une branche pour y travailler. Cette branche doit déjà exister.
 - **commit** : une fois que vos modifications du code ont été faites, vous devez les entériner avec la commande commit. Auparavant, tous les fichiers ajoutés ou modifiés doivent être ajoutés au commit avec la commande **add [nom de fichier]**.
 - **push** : une fois vos modifications _commitées_, vous pouvez les pousser sur le serveur distance grâce à la commande **push**
 - **pull** : à l'inverse, vous pouvez télécharger toutes les dernières modifications du code sur le serveur distant en les _tirant_ dans votre copie locale.

Vous pourrez également consulter la playlist suivante avec des exemples des commandes git : [liste à propos de git](https://www.youtube.com/playlist?list=PLNgzB9uJ0Ss58ZdoPk1vueOMYYdfBkKoS)

## Rappels succincts du C

Dans cette partie, des rappels utiles de bases du C vous sont donnés pour vous permettre de rafraichir vos connaissances en C.

### Variables, types et opérateurs

En programmation C, les valeurs manipulées, appelées variables, sont nommées par un identifiant et leur type est déclaré avant tout usage. Les types de base les plus utilisés sont :

 - **int** : un entier sur 32 bits (4 octets)
 - **short** : un entier sur 16 bits (2 octets)
 - **float** : un nombre à virgule flottante
 - **double** : un grand nombre à virgule flottante
 - **char** : un caractère ASCII sur 1 octet (8 bits)
 - Propriété **unsigned** : la propriété non signée permet à une valeur d'être définie sur l'intervalle 0..MAX au lieu de -MAX/2..MAX/2-1

Exemple avec les entiers et les caractères :

| Type | Min signé | Max signé | Min non signé | Max non signé |
|------|-----------|-----------|----------------|----------------|
| int  |-2147483648| 2147483647| 0 | 4294967295 |
| short| -32768  | 32767 | 0 | 65535 |
| char | -128 | 127 | 0 | 255 |

La déclaration d'une variable se fait avec la syntaxe suivante : TYPE nom; (le point-virgule est obligatoire comme à la fin de toute instruction), où type est un des types existant en C, et nom est un identifiant défini suivant les règles suivantes :

 - le premier caractère est une lettre (minuscule ou majuscule), ou un _underscore_ `_`
 - le reste des caractères est composé de chiffres, de lettres minuscules et majuscules, et du caractère `_`
 - chaque identifiant est unique dans sa portée (un seul nom de variable donné ne peut exister à un moment donné)

Ces variables peuvent ensuite être manipulées avec des opérateurs pour modifier leurs valeurs. Par exemple, les opérateurs arithmétiques permettent d'appliquer `+ - / *` à des variables.

### Structures de contrôle du flux

Les structures de contrôle du flux d'instruction permettent d'exécuter des instructions sous réserve de conditions, ou de répéter des instructions.

#### Conditionnelle if/else

Cette structure permet d'exécuter une alternative en fonction du résultat d'un test. Un test est une expression dont le résultat est booléen, c'est à dire **vrai** ou **faux**. Par exemple :

```c
int b = 10;
if (a != 0) {
	b = b / a;
} else {
	b = b - 1;
}
```
Dans ce code, `b` est divisé par `a` seulement si `a` est différent de `0` (dans le cas contraire, le programme rencontrera une erreur). Sinon, `b` se voit soustraire `1`.

#### Boucle for

La boucle `for` est une boucle dont le nombre d'itérations est généralement connu à l'avance, et qui est gérée avec un compteur (allant d'une valeur de départ à une condition d'arrêt, avec une valeur d'incrément). Par exemple :

```c
for (int i=0; i<10; ++i) {
	printf("%d\n", i);
}
```
Cette boucle va itérer pour les valeurs de `i` à partir de `0`, tant que `i` est inférieur strict à `10`, en incrémentant `i` de `1` à chaque itération (i.e. passage dans la boucle). Elle va afficher la valeur courante du compteur. Autrement dit, ce code va afficher les nombres de `0` à `9` (inclus).

#### Boucle while

La boucle `while` est une boucle qui se répète tant qu'une condition est vraie. La condition est testée dès l'entrée dans la boucle. Par exemple :
```c
char buffer[100];
size_t bytes = read(stdin, buffer, 100);
while (bytes > 0) {
	printf("Message reçu : %s\n");
	bytes = read(stdin, buffer, 100);
}
```
Cette boucle va lire sur l'entrée standard (clavier ou *pipe* entrant) et afficher ce qui a été lu, tant qu'il y a des données à lire.

#### Boucle do/while

La boucle `do/while` fonctionne comme la boucle `while` sauf qu'elle teste la condition à la fin de la boucle (donc les instructions de la boucle seront exécutées au moins une fois). Par exemple :
```c
int a = 25;
do {
	int b = a / 2;
	int c = a % 2;
	printf("%d", c);
	fflush(stdout);
} while (a != 0);
```
Cette boucle calcule le résultat de la division entière et du modulo par `2` de `a` et affiche `c` (résultat du modulo). Elle se répète tant que `a` est différent de `0` (le code affiche la valeur de `a` en binaire dans l'ordre inverse).

**Exercice 1**

Écrire un programme nommé _polynome.c_ qui prend en paramètre 3 valeurs décimales **a**, **b**, et **c** et résout le polynôme _ax^2 + bx + c = 0_, dans l'espace des complexes. Le programme doit prendre en compte tous les cas particuliers.

### Fonctions

Il est souvent nécessaire de décomposer un programme en plusieurs sections de code, que ce soit parce que ce code va être utilisé depuis plusieurs segments du code, ou pour faciliter la maintenance et le découpage logique du code. Pour réaliser cet objectif, le C permet de définir des fonctions. Celles-ci, définies d'une manière analogue à la fonction _main_, peuvent avoir des signatures très différentes. Une fonction doit être déclarée avant sont usage, et il est possible de séparer sa signature (son "modèle", composé du type de retour, du nom et des paramètres de la fonction) de sa définition (le code qu'elle contient).

Voici quelques signatures de fonctions :

```c
void do_something(void); // Fonction sans paramètre ni retour
void do_something_else(int v); // Fonction sans retour mais avec un paramètre entier v
char do_something_2(double v); // Fonction avec retour et paramètre décimal v
```

Des définitions de ces fonctions pourraient être :

```c
void do_something(void) {
	printf("Toujours ça\n");
}

void do_something_else(int v) {
	if (v == 0)
		printf("C'est zéro\n");
	else
		printf("Valeur non nulle\n");
}

char do_something_2(double v) {
	if (v != 0.0) {
		return 'Y';
	} else {
		return 'N';
	}
}
```

On les appellerait alors depuis une autre fonction (le _main_ par exemple) de la manière suivante :

```c
int main() {
	do_something();
	do_something_else(4);
	do_something_2(0.0);
	return 0;
}
```

**Exercice 2**

Écrire un programme nommé _polynom_fct.c_ qui reprend l'exercice précédent et traite la résolution du polynôme dans une fonction.

### Tableaux et chaînes de caractères

Les tableaux sont des séquences contigües d'élément du même type, accessibles par leur position dans le tableau, commençant à l'indice 0. Il existe deux types de tableaux : les tableaux statiques, et les tableaux dynamiques. Les tableaux statiques ont une taille définie à l'écriture du programme alors que les tableaux dynamiques reposent sur une allocation mémoire dynamique.

```c
int tableau1[10]; // Tableau de 10 entiers
int tableau2[] = {1, 2, 3, 4}; // Tableau de 4 entiers initialisés
int *tableau_dynamique = malloc(sizeof(int) * 15); // Tableau dynamique avec 15 entiers
// ...
// Utilisation de tableau_dynamique
// ...
free(tableau_dynamique); // Il faut toujours penser à désallouer un tableau dynamique
```

Les chaînes de caractères (qui définissent des séquences de caractères de type `char`) sont également des tableaux, dont les éléments sont des caractères. Les chaînes de caractères doivent terminer par le caractère nul dont le code est `'\0'`. Il est donc toujours nécessaire qu'une chaîne de caractère prévoit un caractère de plus que le mot de taille maximale qu'elle devra contenir.

```c
char chaine1[] = "Bob"; // initialisée avec le mot "Bob"
char chaine2[50]; // Peut contenir 49 caractères + fin de chaîne (caractère '\0')
char *chaine3 = "Bob2"; // Initialisée à Bob2
```

Contrairement à d'autres langages plus abstraits (C++, Java, Python), les chaînes de caractères ne s'utilisent pas avec des opérateurs arithmétiques mais par des fonctions (en effet, il s'agit de tableaux, et pas de types standard). Les plus utiles des fonctions sont :

 - **strcmp** permet la comparaison de deux chaînes de caractères. Renvoie 0 en cas d'égalité, une valeur inférieure à zéro si la première chaîne est avant la seconde (ordre des codes ASCII), une valeur supérieure à zéro dans le cas contraire.
 - **strncmp** fait comme **strcmp** mais sur **n** caractères au maximum
 - **strlen** retourne la taille de la chaîne de caractères passée en paramètre
 - **strcpy** copie la chaîne source (second paramètre) dans la chaîne destinatation (premier paramètre)
 - **strncpy** fait comme **strcpy** mais copie au maximum **n** caractères
 - **strcat** ajoute le contenu du second paramètre à la chaîne du premier paramètre et renvoie un pointeur sur la chaîne résultante
 - **strncat** fait comme **strcat** mais ajoute au maximum **n** caractères.

Leur utilisation est définie en détail dans les manuels accessibles avec la commande `man strcmp` pour **strcmp**, etc.

**Exercice 3**

Écrire un programme nommé _anagramme.c_ qui teste si une phrase passée en paramètre du programme est un anagramme (elle se lit pareillement du début à la fin de la fin au début, en ignorant les espaces). Par exemple, la phrase "_Esope reste ici et se repose_" est un anagramme.

## Passer un paramètre au programme

Nous allons maintenant changer la signature (le nom, le type de retour, et les paramètres de la fonction) pour lui permettre d'accepter des paramètres et de les traiter. Pour ce faire, `int main()` devient `int main(int argc, char *argv[])`. Ces deux paramètres ont des valeurs précises :

 - _argc_ est un entier dont la valeur est égale au nombre d'arguments du programme
 - _argv_ est un tableau de chaînes de caractères contenant les arguments, et dont la taille est égale à la valeur de _argc_

Attention ! le tableau _argv_ contient au minimum une valeur qui est à la première position (accessible avec l'indice zéro, donc _argv[0]_) et qui est le nom du programme lui même. Tous les autres arguments doivent être vérifiés avant utilisation pour éviter un accès à des valeurs inexistantes et une **erreur de segmentation** qui arrête le programme.

**Exercice 4**

Écrire un programme nommé _tri_taille.c_ qui trie les arguments qui lui sont passés par ordre croissant de taille (longueur de la chaîne de caractères) et, en cas d'égalité, par ordre pseudo alphabétique ASCII. Par exemple, si on lui passe les paramètres `un deux trois quatre cinq six sept`, il doit trier pour obtenir le résultat `un six cinq deux sept trois quatre`. Utilisez de la mémoire dynamique pour construire votre tableau de résultats avant de l'afficher.
