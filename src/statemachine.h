/**
 * @file statemachine.h
 * @author dabbinavo
 *
 * @brief API for a easy-to-use statemachine. See /examples/basic/basic_example.c for an example of how to use this API.
 *
 * @date 2021-12-08
 * 
 * Copyright (c) 2021 dabbinavo
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H


//==============================================================================================================================================================
// Headers

#include <stddef.h>


//==============================================================================================================================================================
// Define directives


//==============================================================================================================================================================
// Macros


//==============================================================================================================================================================
// Type definitions

typedef int state_t;

typedef struct statemachine statemachine_t;
typedef struct state_functions state_functions_t;

typedef void (*statemachine_runnable_t)(statemachine_t *statemachine);

typedef enum {
  STATE_FINAL = -1,
  STATE_START = -2,
} statemachine_states_t;


struct statemachine {
  state_functions_t *sm;
  state_t current_state;
  state_t next_state;
};

struct state_functions {
  statemachine_runnable_t enter;
  statemachine_runnable_t runnable;
  statemachine_runnable_t exit;  
};


//==============================================================================================================================================================
// Function declarations

void statemachine_init(statemachine_t *handle, state_functions_t *state_matrix, state_t initial_state);

state_t statemachine_process(statemachine_t *handle);


//==============================================================================================================================================================
#ifdef __cplusplus
}       // extern "C"
#endif

#endif  // #ifndef STATEMACHINE_H