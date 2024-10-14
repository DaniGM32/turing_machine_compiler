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

    char *machine_name = ReadMachineDescription(input_file, 0);
    char *start_state = ReadMachineDescription(input_file, 1); 
    char *accept_line = ReadMachineDescription(input_file, 2);

    char *token = strtok(accept_line, ", ");
    while(token) {
        strcpy(accept_states[accept_states_size].name, token);
        accept_states_size++;
        token = strtok(NULL, ", ");
    }
    free(accept_line);
    free(token);
      
    while (fgets(temp_buffer, sizeof(temp_buffer), input_file)) {
        if (strstr(temp_buffer, "Sequence:") != NULL) {
            break;
        }
        if (sscanf(temp_buffer, "%49[^,],%c", states[states_size].name, &states[states_size].character) != 2) {
            printf("Error reading state and character\n");
            continue; // continue if the line is not in the correct format
        }
        if (fgets(temp_buffer, sizeof(temp_buffer), input_file) == NULL || 
            sscanf(temp_buffer, "%49[^,],%c,%c", 
               states[states_size].transition.name,
               &states[states_size].transition.written_character,
               &states[states_size].transition.direction) != 3) {
            printf("Error reading transition\n");
            continue; // continue if the line is not in the correct format
        }
        states_size++;
        // skip the empty line between transitions
        fgets(temp_buffer, sizeof(temp_buffer), input_file);
    }
    if (strstr(temp_buffer, "Sequence:") != NULL) {
        if (fgets(temp_buffer, sizeof(temp_buffer), input_file)) {
            if (temp_buffer[0] != 'e' && temp_buffer[0] != '\n') {
                strcpy(buffer, temp_buffer);
                buffer[strcspn(buffer, "\n")] = '\0';
                printf("Sequence read into buffer: %s\n", buffer);
            } else {
                printf("No valid sequence found after 'Sequence:'\n");
            }
        } else {
            printf("Error reading sequence\n");
        }
    }
    //PrintStates(states, states_size, output_file);

    //where the magic happens, to be implemented
    int buffer_index = 0;
    char next_character;
    State *current_state = FindNextState(states, states_size, start_state, next_character); 
    printf("Current state: %s\n", current_state->name);
    while(VerifyAcceptState(accept_states, accept_states_size, current_state->name) == 0) {
        char direction = current_state->transition.direction;

        if (direction == '>') {
            buffer_index++;
        } else if (direction == '<') {
            buffer_index--;
        }

    }

    free(start_state);
    free(machine_name);
    FreeMemory(&states, &accept_states, &buffer);
    fclose(input_file);
    fclose(output_file);

    return 0;
}