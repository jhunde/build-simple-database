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

int main(int argc, char* argc[]){

    // Get a line of input, then process that line of input
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        print_prompt();
        read_line(input_buffer);

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