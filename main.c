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
    TransitionState *transition_states = AllocTransitionStatesArray(output_file);
    AcceptState *accept_states = AllocAcceptState(output_file);
    char *buffer = AllocBuffer(output_file);

    int states_size, transition_states_size, accept_states_size;
    states_size = transition_states_size = accept_states_size = 0;
    char temp_buffer[MAX_LENGTH];

    char *machine_name = (char *)calloc(MAX_LENGTH, sizeof(char));
    fgets(temp_buffer, sizeof(temp_buffer), input_file);
    sscanf(temp_buffer, "name: %[^\n]", machine_name);
    // printf("%s\n", machine_name);

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

    while (true) {    
        fscanf(input_file, "%s,%c\n", states[states_size].name, &states[states_size].character);
        fscanf(input_file, " -> %s,%c,%c\n", 
                    transition_states[transition_states_size].name,
                    &transition_states[transition_states_size].written_character,
                    &transition_states[transition_states_size].direction);
        states_size++;
        transition_states_size++;
        if (fgetc(input_file) == 'e') {
            break;
        }
    }
    for (int i = 0; i < states_size; i++) {
        printf("%s %c\n", states[i].name, states[i].character);
    }


    FreeMemory(&states, &transition_states, &accept_states, &buffer);
    fclose(input_file);
    fclose(output_file);

    return 0;
}