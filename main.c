/* Cîrstian Daniel 321CB */

#include "main.h"

int main() {
    FILE *input_file = fopen("input_file", "r");
    FILE *output_file = fopen("output_file", "w");

    if (!input_file || !output_file) {
        printf("Files could not be open!");
        exit(1);
    }

    State *states = AllocStatesArray(output_file);
    AcceptState *accept_states = AllocAcceptState(output_file);
    char *buffer = AllocBuffer(output_file);

    int states_size, accept_states_size;
    states_size = accept_states_size = 0;
    char temp_buffer[MAX_LENGTH];

    char *machine_name = (char *)calloc(MAX_LENGTH, sizeof(char));
    fgets(temp_buffer, sizeof(temp_buffer), input_file);
    sscanf(temp_buffer, "name: %[^\n]", machine_name);
    //printf("%s\n", machine_name);

    char *start_state = (char *)calloc(MAX_LENGTH, sizeof(char));
    fgets(temp_buffer, sizeof(temp_buffer), input_file);
    sscanf(temp_buffer, "init: %s", start_state);
    // printf("%s\n", start_state);

    char *accept_line = (char *)calloc(MAX_LENGTH, sizeof(char));
    fgets(temp_buffer, sizeof(temp_buffer), input_file);
    sscanf(temp_buffer, "accept: %[^\n]", accept_line);
    // printf("%s\n", accept_line);

    char *token = strtok(accept_line, ", ");
    while(token) {
        strcpy(accept_states[accept_states_size].name, token);
        accept_states_size++;
        token = strtok(NULL, ", ");
    }
    free(accept_line);
    free(token);

    while (fgets(temp_buffer, sizeof(temp_buffer), input_file)) {
        if (temp_buffer[0] == 'e') {
            break;
        }
        if (sscanf(temp_buffer, "%49[^,],%c", states[states_size].name, &states[states_size].character) != 2) {
            fprintf(output_file, "Error reading state and character\n");
            continue; // continue if the line is not in the correct format
        }
        if (fgets(temp_buffer, sizeof(temp_buffer), input_file) == NULL || 
            sscanf(temp_buffer, "%49[^,],%c,%c", 
               states[states_size].transition.name,
               &states[states_size].transition.written_character,
               &states[states_size].transition.direction) != 3) {
            fprintf(output_file, "Error reading transition\n");
            continue; // continue if the line is not in the correct format
        }
        states_size++;

         // skip the empty line between transitions
        fgets(temp_buffer, sizeof(temp_buffer), input_file);
    }
    printf("%d\n", states_size);
    for (int i = 0; i < states_size; i++) {
        printf("State %d: %s, %c -> %s, %c, %c\n", i,
               states[i].name,
               states[i].character,
               states[i].transition.name,
               states[i].transition.written_character,
               states[i].transition.direction);
    }

    //where the magic happens, to be implemented
    // int buffer_index = 0;
    // char next_character;
    // State *current_state = FindNextState(states, states_size, start_state, next_character); 
    // while(VerifyAcceptState(accept_states, accept_states_size, current_state->name) == 0) {
    //     char direction = current_state->transition.direction;

    // }

    free(start_state);
    free(machine_name);
    FreeMemory(&states, &accept_states, &buffer);
    fclose(input_file);
    fclose(output_file);

    return 0;
}