// Define InputBuffer
typedef struct {
    char* buffer;
    size_t buffer_lenght;
    ssize_t input_buffer;
} InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer*)molloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_lenght = 0;
    input_buffer->input_buffer = 0;

    return input_buffer;
}

// This fuction will be called before reading each line of the input
void print_prompt(){
    printf("db > ");
}

// Read a line of input using getline()
ssize_t getline(char** lineptr, size_t* n, FILE* stream);

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_lenght), stdin);

    if (bytes_read <= 0){
        printf("Error read input \n");
        exit(EXIT_SUCCESS);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read-1;
    input_buffer->buffer[buffer_read-1] = 0 
}

// Free the allocated memory
void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argc[]){

    // Get a line of input, then process that line of input
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        print_prompt();
        read_input(input_buffer);

        // valid input? 
        if (strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        // invalid input?
        else {
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
    }
}