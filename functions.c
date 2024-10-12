/* Cîrstian Daniel 321CB */

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 10000
#define MAX_STATES 1000
#define MAX_LENGTH 50

typedef struct state {
    char *name;
    char character;
} State;

typedef struct transition_state {
    char *name;
    char written_character;
    char direction;
} TransitionState;

State* AllocStateArray(FILE* output_file) {
    State *states = (State *)calloc(MAX_STATES, sizeof(State));
    if (!states) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    for (int i = 0; i < MAX_STATES; i++) {
        states[i].name = (char *)calloc(MAX_LENGTH, sizeof(char));
        if (!(states[i].name)) {
            fprintf(output_file, "Allocation failed!");
            for (int j = 0; j < i; j++) {
                free(states[j].name);
            }
            free(states);
            return NULL;
        }
    }
    return states;
}

TransitionState* AllocTransitionStateArray(FILE* output_file) {
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

char *AllocBuffer(FILE* output_file) {
    char *array = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (!array) {
        fprintf(output_file, "Allocation failed!");
        return NULL;
    }
    return array;
}

void FreeMemory(State **states, TransitionState **transition_states, char **buffer) {
    if (!(*states) || !(*transition_states) || !(*buffer)) {
        return;
    }
    for (int i = 0; i < MAX_STATES; i++) {
        free((*states)[i].name);
    }
    free((*states));
    *states = NULL;

    for (int i = 0; i < MAX_STATES; i++) {
        free((*transition_states)[i].name);
    }
    free((*transition_states));
    *transition_states = NULL;
    
    free((*buffer));
    *buffer = NULL;
}