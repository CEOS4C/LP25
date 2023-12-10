#include <stdio.h>
#include <stdlib.h>

typedef struct _list_element {
    int value;
    struct _list_element *next;
    struct _list_element *prev;
} list_element_t;

typedef struct {
    list_element_t *head;
    list_element_t *tail;
} list_t;

void add_int_to_list(int value, list_t *list) {
    list_element_t *new_element = (list_element_t *)malloc(sizeof(list_element_t));
    new_element->value = value;
    new_element->next = NULL;
    new_element->prev = NULL;

    if (list->head == NULL) {
        list->head = new_element;
        list->tail = new_element;
    } else {
        list_element_t *current = list->head;
        while (current != NULL && current->value < value) {
            current = current->next;
        }

        if (current == NULL) {
            list->tail->next = new_element;
            new_element->prev = list->tail;
            list->tail = new_element;
        } else {
            new_element->next = current;
            new_element->prev = current->prev;
            if (current->prev != NULL) {
                current->prev->next = new_element;
            } else {
                list->head = new_element;
            }
            current->prev = new_element;
        }
    }
}

void clear_list(list_t *list) {
    list_element_t *current = list->head;
    while (current != NULL) {
        list_element_t *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

void display_list(list_t *list) {
    list_element_t *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void save_to_file(char *filename, list_t *list) {
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    list_element_t *current = list->head;

    while (current != NULL) {
        fwrite(&(current->value), sizeof(int), 1, file);
        current = current->next;
    }

    fclose(file);
}

void insertion_sort(list_t *list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }

    list_t sorted_list = {.head = NULL, .tail = NULL};
    list_element_t *current = list->head;

    while (current != NULL) {
        list_element_t *next = current->next;
        current->next = NULL;
        current->prev = NULL;
        add_int_to_list(current->value, &sorted_list);
        current = next;
    }

    list->head = sorted_list.head;
    list->tail = sorted_list.tail;
}

int main() {
    FILE *file = fopen("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP7/Exercice4/texte.txt", "wb");
    if (file == NULL) {
        perror("Error lors de l'ouverture du fichier");
        return 1;
    }

    list_t numbers = {.head = NULL, .tail = NULL};

    int value;
    size_t elements_read;

    while ((elements_read = fread(&value, sizeof(int), 1, file)) > 0) {
        add_int_to_list(value, &numbers);
    }

    fclose(file);

    insertion_sort(&numbers);

    save_to_file("/home/ceos4c/Documents/UTBM/TC03/LP25/TP/Partie C/TP7/Exercice4/save.txt", &numbers);

    display_list(&numbers);

    clear_list(&numbers);

    return 0;
}
