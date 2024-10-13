/* Cîrstian Daniel 321CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "functions.c"
#define MAX_STATES 1000
#define MAX_LENGTH 50
#define BUFFER_SIZE 10000

State* AllocStateArray(FILE* output_file);
TransitionState* AllocTransitionStateArray(FILE* output_file);
AcceptState* AllocAcceptState(FILE* output_file);
char *AllocBuffer(FILE* output_file);
int VerifyAcceptState(AcceptState *accept_states, int size, char *state_name);
State* FindNextState(State *states, int size, char *state_name, char character);
void FreeMemory(State **states, AcceptState **accept_states, char **buffer);



