#include <stdio.h>
#include <ctype.h>

typedef void (*ptr_function)(char);

void make_caps(char c) {
    putc(toupper(c), stdout);
}

void make_small(char c) {
    putc(tolower(c), stdout);
}

void remove_lines(char c) {
    if (c != '\n') {
        putc(c, stdout);
    }
}

int main() {
    ptr_function mon_ptr_fonction;

    mon_ptr_fonction = make_caps;
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        mon_ptr_fonction((char) c);
    }

    mon_ptr_fonction = make_small;
    rewind(stdin);
    while ((c = fgetc(stdin)) != EOF) {
        mon_ptr_fonction((char) c);
    }

    mon_ptr_fonction = remove_lines;
    rewind(stdin);
    while ((c = fgetc(stdin)) != EOF) {
        mon_ptr_fonction((char) c);
    }

    return 0;
}
