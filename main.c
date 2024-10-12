/* Cîrstian Daniel 321CB */

#include "main.h"

int main() {

    FILE *input_file = fopen("input_file", "r");
    FILE *output_file = fopen("output_file", "w");

    if (!input_file || !output_file) {
        printf("Files could not be open!");
        exit(1);
    }

    State *states = AllocStateArray(output_file);
    TransitionState *transition_states = AllocTransitionStateArray(output_file);
    char *buffer = AllocBuffer(output_file);

    char start_state[MAX_LENGTH];
    fscanf(input_file, "init: %s", start_state);
    while (true) {
        char current_state[MAX_LENGTH];
        fscanf(input_file, "%s", current_state);

        if (strcmp(current_state, "end") == 0) {
            printf("111\n");
            break;
        }
    }

    FreeMemory(&states, &transition_states, &buffer);
    fclose(input_file);
    fclose(output_file);

    return 0;
}