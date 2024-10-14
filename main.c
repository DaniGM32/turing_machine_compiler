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
    char temp_buffer[MAX_LENGTH];       // used for reading lines from the input file

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
                // printf("Sequence read into buffer: %s\n", buffer);
            } else {
                printf("No valid sequence found after 'Sequence:'\n");
            }
        } else {
            printf("Error reading sequence\n");
        }
    }
    // PrintStates(states, states_size, output_file);
    ModifyBuffer(&buffer);
    int buffer_index = PADDING;
    char next_character = buffer[PADDING];
    State *current_state = FindNextState(states, states_size, start_state, next_character); 

    int accept_index = -1;
    while(true) {
        if (current_state == NULL) {
            break;
        }
        if (VerifyAcceptState(accept_states, accept_states_size, current_state->name) == 1) {
            accept_index = FindAcceptStateIndex(accept_states, accept_states_size, current_state->name);
            break;
        }
        char direction = current_state->transition.direction;
        buffer[buffer_index] = current_state->transition.written_character;

        if (direction == '>') {
            buffer_index++;
        } else if (direction == '<') {
            buffer_index--;
        }

        next_character = buffer[buffer_index];

        accept_index = FindAcceptStateIndex(accept_states, accept_states_size, current_state->transition.name);
        current_state = FindNextState(states, states_size, current_state->transition.name, next_character);
    }
    printf("%d\n", accept_index);
    if (accept_index != -1) {
        fprintf(output_file, "Accepted\n");
    } else {
        fprintf(output_file, "Rejected\n");
    }
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] != '_') {
            fprintf(output_file, "%c", buffer[i]);
        }
    }

    free(start_state);
    free(machine_name);
    FreeMemory(&states, &accept_states, &buffer);
    fclose(input_file);
    fclose(output_file);

    return 0;
}