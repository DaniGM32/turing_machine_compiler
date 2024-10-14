/* Cîrstian Daniel 321CB */

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 10000
#define MAX_STATES 1000
#define MAX_LENGTH 50
#define MAX_ACC_STATES 50

typedef struct transition_state {
    char *name;
    char written_character;
    char direction;
} TransitionState;

typedef struct state {
    char *name;
    char character;
    TransitionState transition;
} State;

typedef struct accept_state {
    char *name;
} AcceptState;

State* AllocStatesArray(FILE* output_file) {
    State *states = (State *)calloc(MAX_STATES, sizeof(State));
    if (!states) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    for (int i = 0; i < MAX_STATES; i++) {
        states[i].name = (char *)calloc(MAX_LENGTH, sizeof(char));
        states[i].transition.name = (char *)calloc(MAX_LENGTH, sizeof(char));
        if (!(states[i].name) || !(states[i].transition.name)) {
            fprintf(output_file, "Allocation failed!");
            for (int j = 0; j < i; j++) {
                free(states[j].name);
                free(states[j].transition.name);
            }
            free(states);
            return NULL;
        }
    }
    return states;
}

TransitionState* AllocTransitionStatesArray(FILE* output_file) {
    TransitionState *transition_states = (TransitionState *)calloc(MAX_STATES, sizeof(TransitionState));
    if (!transition_states) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    for (int i = 0; i < MAX_STATES; i++) {
        transition_states[i].name = (char *)calloc(MAX_LENGTH, sizeof(char));
        if (!(transition_states[i].name)) {
            fprintf(output_file, "Allocation failed!");
            for (int j = 0; j < i; j++) {
                free(transition_states[j].name);
            }
            free(transition_states);
            return NULL;
        }
    }
    return transition_states;
}

AcceptState* AllocAcceptState(FILE* output_file) {
    AcceptState* accept_states = (AcceptState *)calloc(MAX_ACC_STATES, sizeof(AcceptState));
    if (!accept_states) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    for (int i = 0; i < MAX_ACC_STATES; i++) {
        accept_states[i].name = (char *)calloc(MAX_LENGTH, sizeof(char));
        if (!(accept_states[i].name)) {
            fprintf(output_file, "Allocation failed!");
            for (int j = 0; j < i; j++) {
                free(accept_states[j].name);
            }
            free(accept_states);
            return NULL;
        }
    }
    return accept_states;
}

char* AllocBuffer(FILE* output_file) {
    char *array = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (!array) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    return array;
}

void FreeMemory(State **states,
                AcceptState **accept_states,
                char **buffer) {
    if (!(*states) || !(*buffer)) {
        return;
    }
    for (int i = 0; i < MAX_STATES; i++) {
        free((*states)[i].name);
        free((*states)[i].transition.name);
    }
    free((*states));
    *states = NULL;

    for (int i = 0; i < MAX_ACC_STATES; i++) {
        free((*accept_states)[i].name);
    }
    free((*accept_states));
    *accept_states = NULL;

    free((*buffer));
    *buffer = NULL;
}

int VerifyAcceptState(AcceptState *accept_states, int size, char *state_name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(accept_states[i].name, state_name) == 0) {
            return 1;
        }
    }
    return 0;
}

State* FindNextState(State *states, int size, char *state_name, char character) {
    for (int i = 0; i < size; i++) {
        if (strcmp(states[i].name, state_name) == 0 && states[i].character == character) {
            return &states[i];
        }
    }
    return NULL;
}

void PrintStates(State *state, int size, FILE *output_file) {
    for (int i = 0; i < size; i++) {
        fprintf(output_file, "State %d: %s, %c -> %s, %c, %c\n", i,
                state[i].name,
                state[i].character,
                state[i].transition.name,
                state[i].transition.written_character,
                state[i].transition.direction);
    }
}

char* ReadMachineDescription(FILE *input_file, int type) {
    char *data = (char *)calloc(MAX_LENGTH, sizeof(char));
    char temp_buffer[MAX_LENGTH];
    fgets(temp_buffer, sizeof(temp_buffer), input_file);
    if (type == 0) {
        sscanf(temp_buffer, "name: %[^\n]", data);
    } else if (type == 1) {
        sscanf(temp_buffer, "init: %[^\n]", data);
    } else if (type == 2) {
        sscanf(temp_buffer, "accept: %[^\n]", data);
    }
    return data;
}
