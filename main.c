#define MAX_INPUT_SIZE 1024

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char*  buffer;
    size_t buffer_length;   // capacity
    size_t input_length;    // number of chars (excl. '\0')
} InputBuffer;

InputBuffer* new_input_buffer(void) {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    if (!input_buffer) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->buffer = (char*)malloc(MAX_INPUT_SIZE);
    if (!input_buffer->buffer) {
        fprintf(stderr, "malloc failed\n");
        free(input_buffer);
        exit(EXIT_FAILURE);
    }
    input_buffer->buffer_length = MAX_INPUT_SIZE;
    input_buffer->input_length  = 0;
    return input_buffer;
}

void print_prompt(void) {
    printf("db > ");
    fflush(stdout); // make sure prompt shows up
}

void read_input(InputBuffer* input_buffer) {
    if (!fgets(input_buffer->buffer, (int)input_buffer->buffer_length, stdin)) {
        if (feof(stdin)) {
            // Treat Ctrl+Z/EOF as clean exit
            printf("\n");
            free(input_buffer->buffer);
            free(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            perror("fgets");
            free(input_buffer->buffer);
            free(input_buffer);
            exit(EXIT_FAILURE);
        }
    }

    // strip trailing newline if present
    size_t len = strlen(input_buffer->buffer);
    if (len > 0 && input_buffer->buffer[len - 1] == '\n') {
        input_buffer->buffer[len - 1] = '\0';
        len--;
    }
    input_buffer->input_length = len;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(void) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
