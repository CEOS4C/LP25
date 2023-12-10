#include <stdio.h>

#define MASK 0x7f // Index mask from 0 to 127, i.e., 128 elements
#define BUFFER_SIZE 128

unsigned char read_index = 0;
unsigned char write_index = 0;
char circular_buffer[BUFFER_SIZE];

int write_char(char c);
int read_char(char *ch);  // Renommé pour éviter le conflit de noms

int main(int argc, char *argv[]) {
    char input_buffer[256];

    while (1) {
        printf("Enter a sentence (Ctrl+C to exit): ");
        fgets(input_buffer, sizeof(input_buffer), stdin);

        // Write characters to the circular buffer
        for (int i = 0; input_buffer[i] != '\0'; i++) {
            if (!write_char(input_buffer[i])) {
                printf("Circular buffer is full. Cannot write more characters.\n");
                break;
            }
        }

        // Read and process characters from the circular buffer
        char read_character;
        while (read_char(&read_character)) {
            // Process the character (e.g., convert to uppercase)
            if (read_character >= 'a' && read_character <= 'z') {
                read_character = read_character - 'a' + 'A';
            }

            // Print the processed character
            printf("%c", read_character);
        }
        printf("\n");
    }

    return 0;
}

/*!
 * \brief function write_char writes c to circular buffer unless it is full
 * \param c the character to be appended to the circular buffer
 * \return 1 if insertion is successful, 0 if buffer is full
 */
int write_char(char c) {
    unsigned char next_write_index = (write_index + 1) & MASK;

    // Check if the buffer is full
    if (next_write_index == read_index) {
        return 0; // Buffer is full
    }

    // Write the character to the circular buffer
    circular_buffer[write_index] = c;
    write_index = next_write_index;

    return 1; // Successful write
}

/*!
 * \brief function read_char reads a character from circular
 * \param ch a pointer to the character to be read
 * \return 1 if successful, 0 if buffer is empty
 */
int read_char(char *ch) {
    // Check if the buffer is empty
    if (read_index == write_index) {
        return 0; // Buffer is empty
    }

    // Read the character from the circular buffer
    *ch = circular_buffer[read_index];
    read_index = (read_index + 1) & MASK;

    return 1; // Successful read
}
