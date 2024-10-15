## Turing Machine Interpreter in C

### Full commits history: https://github.com/DaniGM32/turing_machine_compiler
This project implements a Turing Machine interpreter in C. The interpreter reads a description of a Turing machine from an input file, processes a binary sequence based on the machine’s states and transitions, and then outputs whether the input sequence is accepted or rejected. This README explains how input is handled, the data structures used, and the core logic of the interpreter. The input format is inspired

## Input
The input file contains the following sections:

## Machine Name: 
A single line defining the name of the machine.
## Start State: 
A line indicating the initial state of the machine.
## Accept States: 
A comma-separated list of states considered as accepting states.
## States and Transitions: 
Multiple lines defining the states, the characters they read, and their transitions. Each state has a transition to another state based on the character it reads from the tape. Transitions specify the next state, the character to write, and the direction to move the tape head (left or right).
## Sequence: 
The sequence of characters to be processed by the machine.



## Data Structures
### State, each state contains:

1) name: A string representing the state name.
2) character: The character the state expects to read.
3) transition: A TransitionState struct holding the target state, the character to write, and the direction to move.

### TransitionState, a transition is represented by:

1) name: The next state.
2) written_character: The character to write on the tape.
3) direction: The direction to move the tape head ('<' for left, '>' for right).

### AcceptState, a simple structure to store accepting states by name.

##  Buffer for Tape
The tape is represented as a char array of size BUFFER_SIZE, padded to prevent overflow when the head moves. The sequence to be processed is read into this buffer, which is then manipulated as the machine runs.

## Main Logic
The core of the interpreter is the state transition loop, implemented as a while(true) loop:


1) Initialization: 
The program begins by reading the Turing machine’s states, transitions, and sequence from the input file. These are stored in the states array and the sequence is copied into the buffer.


2) Processing States:
The machine starts from the initial state and reads the character from the current position on the tape.
Using the current state and character, the program searches for the corresponding transition in the states array.
Once a valid transition is found, the machine writes the new character to the tape, moves the tape head in the specified direction (left or right), and updates the current state to the new state.
This process continues until the machine reaches an accepting state or an invalid transition.


3) Acceptance Check:
At each step, the program checks if the current state matches any of the accept states. If an accept state is found, the machine halts, and the input sequence is considered accepted.
If no accepting state is reached after processing all transitions, the sequence is rejected.


4) Loop Termination:
The loop terminates either when an accept state is found or when the machine encounters an invalid state or an out-of-bounds tape index.


5) Output:
After processing, the machine prints whether the sequence was accepted or rejected and outputs the final tape contents (excluding the padding).

## Memory Management
The program dynamically allocates memory for states, transitions, and the tape buffer. Memory is freed before exiting the program to prevent memory leaks, using the FreeMemory() function, which deallocates the arrays and buffers.

## Conclusion
This Turing machine interpreter efficiently reads and processes Turing machine descriptions and input sequences, following the formal rules of a Turing machine. The structure of the code allows for flexible modifications and additional functionalities.